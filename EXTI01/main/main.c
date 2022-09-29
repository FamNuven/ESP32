#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "sdkconfig.h"
/******************************************************************************************************/
// дефайны ножек, типа чтобы не писать номера выводов
// кароч, проге нужен не номер вывода, а номер бита 0b100 (второй вывод)
#define GPIO_OUTPUT_PIN_SEL    (1ULL << CONFIG_BLINK_GPIO)
#define GPIO_INPUT_PIN_SEL     ((1ULL << CONFIG_BUTTON_GPIO_1)|(1ULL << CONFIG_BUTTON_GPIO_2))
#define ESP_INTR_FLAG_DEFAULT  0
/******************************************************************************************************/
static xQueueHandle gpio_evt_queue = NULL;
/******************************************************************************************************/
// ф-ция обработчика
static void IRAM_ATTR gpio_isr_handler (void *arg)
{
	uint32_t gpio_num = (uint32_t) arg;
	xQueueSendFromISR(gpio_evt_queue, &gpio_num, NULL);    // отправление в очередь
}
/******************************************************************************************************/
static void task1(void *arg)
{
	uint32_t io_num;
	for(;;)
	{
		if (xQueueReceive(gpio_evt_queue, &io_num, portMAX_DELAY))
			printf("GPIO[%d] intr, val: %d\n", io_num, gpio_get_level(io_num));
	}
}

/******************************************************************************************************/

void app_main(void)
{
	int cnt = 0;
	gpio_config_t io_conf = {};                 // создание структуры для инициализации вывода
	io_conf.intr_type = GPIO_INTR_DISABLE;      // заполнение структуры
	io_conf.mode = GPIO_MODE_OUTPUT;
	io_conf.pin_bit_mask = 0b100;               // GPIO2
	io_conf.pull_down_en = 0;
	io_conf.pull_up_en   = 0;
	gpio_config(&io_conf);
	// заполнение структуры
	io_conf.intr_type = GPIO_INTR_NEGEDGE;      // на какой фронт будет реагировать прерывание (от дребезга может не совпадать запись с терминал с причиной)
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;  // вот сюда писать номера ножек
	io_conf.pull_up_en   = 1;
	gpio_config(&io_conf);


	gpio_evt_queue = xQueueCreate(10, sizeof(uint32_t)); //??

	xTaskCreate(task1, "task1", 2048, NULL, 10, NULL);

	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);              // включение прерываний

	gpio_isr_handler_add(CONFIG_BUTTON_GPIO_1, gpio_isr_handler, (void*) CONFIG_BUTTON_GPIO_1);
	gpio_isr_handler_add(CONFIG_BUTTON_GPIO_2, gpio_isr_handler, (void*) CONFIG_BUTTON_GPIO_2);

	while (1)
	{
		printf("cnt: %d\n", cnt++);
		gpio_set_level(CONFIG_BLINK_GPIO, cnt % 2);
		vTaskDelay(1000 / portTICK_RATE_MS);
	}
}
