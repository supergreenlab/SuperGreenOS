/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sgl.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../core/kv/kv.h"
#include "../core/log/log.h"
#include "../core/mqtt/mqtt.h"

#include "mbedtls/aes.h"
#include "mbedtls/md.h"

static unsigned char key[16] = { 0 };

static void sgl_task(void *param);

int generate_key_from_uuid(const char *uuid, unsigned char *key) {
	mbedtls_md_context_t ctx;
	mbedtls_md_type_t md_type = MBEDTLS_MD_SHA256;
	const size_t key_len = 16; // 128 bits

	mbedtls_md_init(&ctx);

	if (mbedtls_md_setup(&ctx, mbedtls_md_info_from_type(md_type), 0) != 0) {
		return -1; // Handle error
	}

	mbedtls_md_starts(&ctx);
	mbedtls_md_update(&ctx, (const unsigned char *) uuid, strlen(uuid));
	mbedtls_md_finish(&ctx, key);

	mbedtls_md_free(&ctx);

	// Truncate the SHA-256 hash to 128 bits
	memset(key + key_len, 0, 32 - key_len);

	return 0;
}

int aes_encrypt_msg(const unsigned char *input, size_t input_len, unsigned char *output, const unsigned char *key) {
	mbedtls_aes_context aes;
	mbedtls_aes_init(&aes);

	if (mbedtls_aes_setkey_enc(&aes, key, 128) != 0) {
		return -1; // Handle error
	}

	// Note: Since we are using ECB mode, input_len must be a multiple of the block size (16 bytes).
	// If it's not, you'll need to pad the input to be a multiple of the block size.

	for (size_t i = 0; i < input_len; i += 16) {
		if (mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_ENCRYPT, input + i, output + i) != 0) {
			mbedtls_aes_free(&aes);
			return -1; // Handle error
		}
	}

	mbedtls_aes_free(&aes);
	return 0;
}


int aes_decrypt_msg(const unsigned char *input, size_t input_len, unsigned char *output, const unsigned char *key) {
	mbedtls_aes_context aes;
	mbedtls_aes_init(&aes);

	if (mbedtls_aes_setkey_dec(&aes, key, 128) != 0) {
		return -1; // Handle error
	}

	// Note: Since we are using ECB mode, input_len must be a multiple of the block size (16 bytes).
	// Ensure the encrypted input complies with this.

	for (size_t i = 0; i < input_len; i += 16) {
		if (mbedtls_aes_crypt_ecb(&aes, MBEDTLS_AES_DECRYPT, input + i, output + i) != 0) {
			mbedtls_aes_free(&aes);
			return -1; // Handle error
		}
	}

	mbedtls_aes_free(&aes);
	return 0;
}

void init_sgl() {
  ESP_LOGI(SGO_LOG_EVENT, "@SGL Initializing sgl module");

  const char *password = "3fb3c822-21de-4764-a01d-5e162eac411b"; // Test only

	if (generate_key_from_uuid(password, key) == -1) {
		ESP_LOGE(SGO_LOG_NOSEND, "Unable to generate key");
	}

  xTaskCreatePinnedToCore(sgl_task, "SGL", 4096, NULL, 10, NULL, 1);
}

static void sgl_task(void *param) {
  int i = 0;
  char msg[MAX_QUEUE_ITEM_SIZE] = { 0 };
  unsigned char msgenc[MAX_QUEUE_ITEM_SIZE] = { 0 };

  while (true) {
		memset(msg, 0, sizeof(msg));
		memset(msgenc, 0, sizeof(msgenc));

    int len = snprintf(msg, sizeof(msg) - 1, "Pouet poeuwt pout wepout wpeout %d", i++);
    ESP_LOGI(SGO_LOG_NOSEND, "Sending %s %d", msg, (int)(ceilf((float)len/16.0f)*16));

		aes_encrypt_msg((const unsigned char *)msg, len, msgenc, key);
    send_screen_message((const char*)msgenc);

    vTaskDelay(10 * 1000 / portTICK_PERIOD_MS);
  }
}

void mqtt_message(const char *str, int len) {
	unsigned char strdec[MAX_QUEUE_ITEM_SIZE] = { 0 };
	if (aes_decrypt_msg((unsigned char*) str, len, strdec, key) == -1) {
		ESP_LOGE(SGO_LOG_NOSEND, "Unable to decrypt");
		return;
	}
  ESP_LOGI(SGO_LOG_EVENT, "@SGL MQTT received %.*s", len, strdec);
}
