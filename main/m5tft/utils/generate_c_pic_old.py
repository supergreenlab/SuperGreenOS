#!/usr/bin/python3

import sys
import cairosvg
from PIL import Image
from io import BytesIO

def svg_to_raster(input_svg):
    # Convert SVG to raster in memory (using BytesIO)
    output_buffer = BytesIO()
    cairosvg.svg2png(url=input_svg, write_to=output_buffer)
    output_buffer.seek(0)

    # Use PIL to open the raster image
    return Image.open(output_buffer)

def handle_transparency(img):
    """
    Replace transparent pixels with {255, 0, 255}
    """
    img = img.convert("RGBA")

    datas = img.getdata()
    newData = []

    for item in datas:
        # Change all white (also shades of whites)
        # pixels to yellow
        if item[3] == 0:  # Alpha is 0, which means transparent
            newData.append((255, 0, 255, 255))
        else:
            newData.append(item)

    img.putdata(newData)
    return img.convert("RGB")

def generate_palette_and_bitmap(image):
    image = handle_transparency(image)
    
    # Getting all colors
    colors = list(image.getdata())
    unique_colors = list(set(colors))
    
    # Create a palette
    palette = {color: idx for idx, color in enumerate(unique_colors)}
    
    # Create a bitmap
    bitmap = [palette[color] for color in colors]
    
    return unique_colors, bitmap

def generate_c_code(palette, bitmap, width, height):
    palette_str = ",\n".join([f"{{ {color[0]}, {color[1]}, {color[2]} }}" for color in palette])

    bitmap_str = ", ".join(map(str, bitmap))
    bitmap_rows = [bitmap_str[i:i+width] for i in range(0, len(bitmap_str), width)]

    bitmap_final = ",\n".join(bitmap_rows)
    
    return f"""
color_t image_palette[] = {{
    {palette_str}
}};

uint8_t image_bitmap[{width}][{height}] = {{
    {bitmap_final}
}};
"""

input_svg = sys.argv[1]
image = svg_to_raster(input_svg)
palette, bitmap = generate_palette_and_bitmap(image)
c_code = generate_c_code(palette, bitmap, 160, 80)
print(c_code)
