/**
 * button.c
 *
 * (C) 2019 - Hades2001 <hades2001@foxmail.com>
 * This code is licensed under the MIT License.
 */

#include "button.h"

esp_event_loop_handle_t event_loop;

static const char *TAG = "button";

esp_err_t button_ioinit(button_t *button);
void IRAM_ATTR button_isr_handler(void *arg);
void button_task(void *pvParameter);

ESP_EVENT_DEFINE_BASE(BUTTON_A_EVENT_BASE);
ESP_EVENT_DEFINE_BASE(BUTTON_B_EVENT_BASE);

button_t button_a = {
    .gpionumber = BUTTON_BUTTON_A_GPIO,
    .Countime = BUTTON_COUNT_TIME,
    .Pressedtime = BUTTON_PRESS_TIME
};

button_t button_b = {
    .gpionumber = BUTTON_BUTTON_B_GPIO,
    .Countime = BUTTON_COUNT_TIME,
    .Pressedtime = BUTTON_PRESS_TIME
    };

void IRAM_ATTR button_isr_handler(void *arg)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    button_t *button = (button_t *)arg;

    if (gpio_get_level(button->gpionumber) == 0)
    {
        xEventGroupSetBitsFromISR(button->event_group, BUTTON_PLUSED_BIT, &xHigherPriorityTaskWoken);
    }
    else
    {
        xEventGroupSetBitsFromISR(button->event_group, BUTTON_RELESED_BIT, &xHigherPriorityTaskWoken);
    }
}

bool button_is_pressed(button_t *button)
{
    return (gpio_get_level(button->gpionumber) == 0) ? true : false;
}

esp_err_t button_ioinit(button_t *button)
{
    esp_err_t e;

    if (button == NULL)
    {
        return ESP_ERR_INVALID_ARG;
    }

    // Set gpio as input
    gpio_pad_select_gpio(button->gpionumber);
    e = gpio_set_direction(button->gpionumber, GPIO_MODE_INPUT);
    if (e != ESP_OK)
    {
        return ESP_FAIL;
    }

// Init event_group
#if defined(CONFIG_SUPPORT_STATIC_ALLOCATION)
    button->event_group = xEventGroupCreateStatic(&(button->event_group_buffer));
#else
    button->event_group = xEventGroupCreate();
#endif
    if (button->event_group == NULL)
    {
        ESP_LOGE(TAG, "Error creating button event group");
        return ESP_FAIL;
    }

// Start task
#if defined(CONFIG_SUPPORT_STATIC_ALLOCATION)
    button->task = xTaskCreateStatic(button_task, "button_task", BUTTON_TASK_STACK_DEPTH, (void *)button, 20, button->task_stack, &(button->task_buffer));
    if (button->task == NULL)
    {
        ESP_LOGE(TAG, "Error creating button_task");
        vEventGroupDelete(button->event_group);
        return ESP_FAIL;
    }
#else
    BaseType_t r = xTaskCreate(button_task, "button_task", BUTTON_TASK_STACK_DEPTH, (void *)button, 3, &(button->task));
    if (r != pdPASS)
    {
        ESP_LOGE(TAG, "Error creating button_task");
        vEventGroupDelete(button->event_group);
        return ESP_FAIL;
    }
#endif

    // Set interrupt type
    e = gpio_set_intr_type(button->gpionumber, GPIO_INTR_ANYEDGE);
    if (e != ESP_OK)
    {
        return e;
    }

    // Enable interrupt
    e = gpio_isr_handler_add(button->gpionumber, button_isr_handler, button);
    if (e != ESP_OK)
    {
        vTaskDelete(button->task);
        return ESP_FAIL;
    }

    return ESP_OK;
}

esp_err_t ButtonInit()
{
    esp_err_t e;

		esp_event_loop_args_t loop_args = {
			.queue_size = 5,
			.task_name = "event_loop",
			.task_priority = 10,
			.task_stack_size = 2048,
			.task_core_id = 0};

		e = esp_event_loop_create(&loop_args, &event_loop);
		if (e != ESP_OK) {
			ESP_LOGE(TAG, "Error creating event loop: %s", esp_err_to_name(e));
			return ESP_FAIL;
		}

    button_a.esp_event_base = BUTTON_A_EVENT_BASE;
    button_b.esp_event_base = BUTTON_B_EVENT_BASE;

    #define ESP_INTR_FLAG_DEFAULT 0

    e = gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    if (e == ESP_ERR_INVALID_STATE)
    {
        ESP_LOGD(TAG, "ISR service already installed");
    }
    else if (e == ESP_ERR_NO_MEM || e == ESP_ERR_NOT_FOUND)
    {
        ESP_LOGE(TAG, "Error installing ISR service");
        return ESP_FAIL;
    }

    e = button_ioinit(&button_a);
    if (e == ESP_OK)
    {
        ESP_LOGD(TAG, "Button A enabled");
    }
    else
    {
        ESP_LOGE(TAG, "Error enabling button A");
    }

    e += button_ioinit(&button_b); // Notice += on error return to accumulate previous error
    if (e == ESP_OK)
    {
        ESP_LOGD(TAG, "Button B enabled");
    }
    else
    {
        ESP_LOGE(TAG, "Error enabling button B");
    }

    if (e != ESP_OK)
    {
        return ESP_FAIL;
    }
    return ESP_OK;
}

void button_task(void *pvParameter)
{
    EventBits_t event;
    button_t *button = (button_t *)pvParameter;

    ESP_LOGD(TAG, "Button task started");

    while (1)
    {
        event = xEventGroupWaitBits(button->event_group, BUTTON_PLUSED_BIT, pdTRUE, pdFALSE, portMAX_DELAY);

        if ((event & BUTTON_PLUSED_BIT) != 0)
        {
            vTaskDelay( button->Countime / portTICK_PERIOD_MS );
            xEventGroupClearBits(button->event_group, BUTTON_RELESED_BIT);
            event = xEventGroupWaitBits(button->event_group, BUTTON_RELESED_BIT, pdTRUE, pdFALSE, button->Pressedtime);
            if ((event & BUTTON_RELESED_BIT) != 0)
            {
                esp_event_post_to(event_loop, button->esp_event_base, BUTTON_PRESSED_EVENT, NULL, 0, portMAX_DELAY);
                ESP_LOGD(TAG, "BUTTON_PRESSED_EVENT event");
            }
            else
            {
                esp_event_post_to(event_loop, button->esp_event_base, BUTTON_HOLDPRESS_EVENT, NULL, 0, portMAX_DELAY);
                ESP_LOGD(TAG, "BUTTON_HOLDPRESS_EVENT event");
            }
        }
        vTaskDelay( 10 / portTICK_PERIOD_MS);
    }
}
