#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"                                            // либа ошибок :)
#include "esp_log.h"
#include "sdkconfig.h"
#include "at24c.h"
/******************************************************************************************************/
#define I2C_ADDRESS  0x50
/******************************************************************************************************/
static const char *TAG = "main";                                // переменная для либы ошибок
/******************************************************************************************************/
uint8_t rd_value[20] = {0};                                     // массивы записи и чтения
uint8_t wr_value[20] = {0x14,0x13,0x12,0x11,0x10,
                        0x0F,0x0E,0x0D,0x0C,0x0B,
                        0x0A,0x09,0x08,0x07,0x06,
                        0x05,0x04,0x03,0x02,0x01};
/******************************************************************************************************/
void app_main(void)
{
	i2c_port_t i2c_port = I2C_NUM_0;
	esp_err_t ret;                                              // создание переменной статуса (ошибки)
	ret = i2c_master_driver_initialize(i2c_port, I2C_ADDRESS, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO);
	ESP_LOGI(TAG, "Init: %d", ret);                             // какой-то хитрый обработчик ошибок, который ее выплевывает в терминал
	AT24C_WriteBytes (i2c_port, 0x0580, wr_value, 20);          // запись
	AT24C_ReadBytes  (i2c_port, 0x0580, rd_value, 20);          // чтение
	for(uint16_t i=0; i<20; i++)                                // выплевывание всего прочитанного в терминал в одну строчку
	{
		printf("%02X ",rd_value[i]);
	}
	printf("\r\n");
	while (1)
	{
		vTaskDelay(10 / portTICK_PERIOD_MS);
	}
}
