#!/usr/bin/python3

import sys
import os
import yaml
import argparse
import cairosvg
from PIL import Image
from io import BytesIO
import numpy as np

def get_filename_without_extension(filepath):
	"""
	Given a filepath, return the filename without its extension.
	"""
	return os.path.splitext(os.path.basename(filepath))[0]

def scale_image_to_max_size(image, max_width, max_height):
	"""
	Scale the image to fit within max_width and max_height, while preserving the aspect ratio.
	"""
	img_width, img_height = image.size
	img_ratio = img_width / img_height
	max_ratio = max_width / max_height

	# Compare the aspect ratios
	if img_ratio > max_ratio:
		# Image is wider than the desired ratio, so set width to max_width and scale height
		new_width = max_width
		new_height = int(new_width / img_ratio)
	else:
		# Image is taller or equal to the desired ratio, so set height to max_height and scale width
		new_height = max_height
		new_width = int(new_height * img_ratio)

	return image.resize((new_width, new_height), Image.Resampling.LANCZOS)

def svg_to_raster(input_svg):
	# Convert SVG to raster in memory (using BytesIO)
	output_buffer = BytesIO()
	cairosvg.svg2png(url=input_svg, write_to=output_buffer, output_width=None, output_height=None, dpi=300, parent_width=None, parent_height=None, scale=1)
	output_buffer.seek(0)

	# Use PIL to open the raster image
	return Image.open(output_buffer)

def find_nearest_color(color, palette):
	# Compute the distance between the given color and all colors in the palette
	distances = np.sqrt(np.sum((palette - color)**2, axis=1))
	# Find the index of the nearest color
	nearest_color_index = np.argmin(distances)
	return palette[nearest_color_index]

def quantize_image_to_palette(img, palette):
	# Convert image to numpy array for easier processing
	img_np = np.array(img)

	# Iterate over each pixel and quantize
	for i in range(img_np.shape[0]):
		for j in range(img_np.shape[1]):
			img_np[i, j] = find_nearest_color(img_np[i, j], palette)

	# Convert the numpy array back to an image
	quantized_img = Image.fromarray(img_np, 'RGBA')

	return quantized_img

def load_svg(svg_file, config, quantize=True, palette=None):
	image = svg_to_raster(svg_file)
	image = scale_image_to_max_size(image, config['max_width'], config['max_height'])
	if quantize:
		if palette == None:
			image = image.quantize(colors=16)
			image = image.convert("RGBA")
		else:
			image = image.convert("RGBA")
			image = quantize_image_to_palette(image, palette)
	else:
		image = image.convert("RGBA")
	#alpha = image.split()[3]
	#image = image.convert("L")
	#image = Image.merge("LA", (image, alpha))
	return image

def generate_bitmap(image, unique_colors):
	colors = list(image.getdata())
	palette = {color: idx for idx, color in enumerate(unique_colors)}
	bitmap = [palette[color] for color in colors]
	return bitmap

def generate_palette(image):
	colors = list(image.getdata())
	unique_colors = list(set(colors))
	
	return unique_colors


def pack_bytes(byte_list):
	packed_list = []
	for i in range(0, len(byte_list), 2):
		if i + 1 < len(byte_list):
			second_byte = byte_list[i + 1]
		else:
			second_byte = 0

		packed_byte = (byte_list[i] << 4) + second_byte
		packed_list.append(packed_byte)

	return packed_list

def generate_c_code(mask, bitmap, width, height, filename, var_index, prefix):
	bitmap_str = ", ".join(map(str, pack_bytes(bitmap)))
	
	return f"""
bitmap_data {prefix}_{var_index} = {{
    .palette = bmp_db_palette,
	.mask = {mask},
	.bitmap = {{
		{bitmap_str}
	}},
	.width = {width},
	.height = {height},
	.name = "{filename}"
}};
"""

def process_svg_file(results, config, svg_file, palette):
	image = load_svg(svg_file, config, True, palette)
	bitmap = generate_bitmap(image, palette)
	filename_no_ext = get_filename_without_extension(svg_file)
	result = {
		'bitmap': bitmap,
		'name': filename_no_ext,
		'width': image.width,
		'height': image.height,
	}
	result.update(config)
	if results == None:
		results = []
	results.append(result)
	return results

def generate_large_image_palette(results, config, svg_file, args):
	new_image = load_svg(svg_file, config, False)

	if results == None:
		results = {}

	if 'large_image' not in results:
		results['large_image'] = new_image
	else:
		large_image = results['large_image']
		new_width = large_image.width + new_image.width
		new_height = max(large_image.height, new_image.height)

		updated_large_image = Image.new('RGBA', (new_width, new_height))
		updated_large_image.paste(large_image, (0, 0))
		updated_large_image.paste(new_image, (large_image.width, 0))

		results['large_image'] = updated_large_image

	tmp = results['large_image'].quantize(colors=16)
	tmp = tmp.convert('RGBA')
	# tmp.save(f"large_image.png")
	results['palette'] = generate_palette(tmp)
	return results

def parse_yaml_file(yaml_file):
	with open(yaml_file, 'r') as file:
		try:
			return yaml.safe_load(file)
		except yaml.YAMLError as exc:
			print(exc)
			return None

def traverse_folders(root_folder, traverse_func, traverse_args=None):
	results = None
	for subdir, dirs, files in os.walk(root_folder):
		config = parse_yaml_file(os.path.join(subdir, 'config.yml'))
		for file in files:
			if file == None:
				continue
			if file.endswith('.svg'):
				filepath = os.path.join(subdir, file)
				results = traverse_func(results, config, filepath, traverse_args)
	return results

def main():
	parser = argparse.ArgumentParser(description="Convert SVG images to C code with a color palette.")
	parser.add_argument("directory", type=str, help="Path to the directory containing SVG files to convert.")
	parser.add_argument("output", type=str, help="Output files without extension")

	args = parser.parse_args()

	large_image = traverse_folders(args.directory, generate_large_image_palette)
	global_palette = large_image['palette']

	files = traverse_folders(args.directory, process_svg_file, global_palette)

	palette_str = ",\n".join([f"{{ {color[0]}, {color[3]} }}" for color in global_palette])

	pointHContent = f"""
// Generated by utils/generate_c_pic.py

#ifndef BITMAPS_DEFINITIONS
#define BITMAPS_DEFINITIONS

#include "bitmaps.h"

bmp_grey_color_t bmp_db_palette[16];

"""
	pointCContent = f"""
// Generated by utils/generate_c_pic.py

#include "bitmaps_definitions.h"

bmp_grey_color_t bmp_db_palette[16] = {{ {palette_str} }};

"""

	variablesDeclaration = "bitmap_data *bitmap_db[] = { "
	for index, file in enumerate(files):
		pointHContent += f"extern bitmap_data bmp_db_{index};\n";
		pointCContent += generate_c_code(file['mask'], file['bitmap'], file['width'], file['height'], file['name'], index+1, 'bmp_db')
		variablesDeclaration += f"&bmp_db_{index+1}, "

	variablesDeclaration += "};"
	pointCContent += variablesDeclaration
	pointCContent += f"""

int n_bitmaps = {len(files)};
"""


	pointHContent += """

extern int n_bitmaps;
extern bitmap_data *bitmap_db[];

#endif
"""

	with open(f'{args.output}.c', 'w') as file:
		file.write(pointCContent)

	with open(f'{args.output}.h', 'w') as file:
		file.write(pointHContent)

	print(pointHContent)
	print(pointCContent)


if __name__ == "__main__":
	main()
