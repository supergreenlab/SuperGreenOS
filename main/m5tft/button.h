/**
 * button.h
 *
 * (C) 2019 - Hades2001 <hades2001@foxmail.com>
 * This code is licensed under the MIT License.
 */

#ifndef _BUTTON_H_
#define _BUTTON_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "esp_system.h"
#include "esp_log.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

extern esp_event_loop_handle_t event_loop;

#define BUTTON_BUTTON_A_GPIO GPIO_NUM_37
#define BUTTON_BUTTON_B_GPIO GPIO_NUM_39

ESP_EVENT_DECLARE_BASE(BUTTON_A_EVENT_BASE); /*!< BASE event of button A */
ESP_EVENT_DECLARE_BASE(BUTTON_B_EVENT_BASE); /*!< BASE event of button B */

#define BUTTON_TASK_STACK_DEPTH 2048

/*!< event_group flag bits */
#define BUTTON_PLUSED_BIT   0x01U
#define BUTTON_RELESED_BIT  0x02U

/*!< Time constants */
#define BUTTON_COUNT_TIME 10
#define BUTTON_PRESS_TIME 2000

typedef enum
{
    BUTTON_PRESSED_EVENT = 0, /*!< Normal button press */
    BUTTON_HOLDPRESS_EVENT,   /*!< Button hold */
    EVENT_MAX
} button_event_id_t;

typedef struct
{
    gpio_num_t gpionumber;

    uint32_t Countime;               /*!< Button debounce time */
    uint32_t Pressedtime;            /*!< Button hold time */

    esp_event_base_t esp_event_base; /*!< Button event base */
    EventGroupHandle_t event_group;  /*!< Event group handle */
    TaskHandle_t task;               /*!< Button task handle */

    #if defined(CONFIG_SUPPORT_STATIC_ALLOCATION)
        StaticEventGroup_t event_group_buffer;             /*!< Event group buffer for static allocation */
        StaticTask_t task_buffer;                          /*!< Task buffer for static allocation */
        StackType_t task_stack[BUTTON_TASK_STACK_DEPTH]; /*!< Task stack for static allocation */
    #endif                                                     // STATIC_ALLOCATION

} button_t;


extern button_t button_a; 
extern button_t button_b; 
extern esp_err_t ButtonInit();

#ifdef __cplusplus
}
#endif

#endif // _M5BUTTON_H_
