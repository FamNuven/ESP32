#ifndef MAIN_AT24C_H_
#define MAIN_AT24C_H_
/******************************************************************************************************/
#include "esp_err.h"
#include "driver/i2c.h"
#include <unistd.h>
/******************************************************************************************************/
#define I2C_FREQUENCY   100000
#define ACK_CHECK_EN    0x1
/******************************************************************************************************/
esp_err_t i2c_master_driver_initialize(i2c_port_t i2c_port, int chip_addr, int i2c_gpio_sda, int i2c_gpio_scl);
void AT24C_WriteBytes (i2c_port_t i2c_port, uint16_t addr,uint8_t *buf, uint16_t bytes_count);
void AT24C_ReadBytes (i2c_port_t i2c_port, uint16_t addr, uint8_t *buf, uint16_t bytes_count);
/******************************************************************************************************/
#endif /* MAIN_AT24C_H_ */
