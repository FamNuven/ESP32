#include "at24c.h"
/******************************************************************************************************/
static int at24c_addr=0;
/******************************************************************************************************/
// Функция инициализации I2C
esp_err_t i2c_master_driver_initialize(i2c_port_t i2c_port, int chip_addr, int i2c_gpio_sda, int i2c_gpio_scl)
{
	esp_err_t ret;
	i2c_config_t conf =                                 // структура для инициализации I2C
	{
		.mode = I2C_MODE_MASTER,
		.sda_io_num = i2c_gpio_sda,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_io_num = i2c_gpio_scl,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		.master.clk_speed = I2C_FREQUENCY
	};
	ret = i2c_param_config(i2c_port, &conf);           // инициализация
	if (ret != ESP_OK) return ret;                     // дальше непонятно, если инициализация не получилась, то
	at24c_addr = chip_addr;
	ret = i2c_driver_install(i2c_port, I2C_MODE_MASTER, 0, 0, 0);   // то инициализация по другому???
	return ret;
}


/******************************************************************************************************/
// Функция записывает байт в микросхему
void AT24C_WriteBytes (i2c_port_t i2c_port, uint16_t addr, uint8_t *buf, uint16_t bytes_count)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);
  i2c_master_write_byte(cmd, at24c_addr << 1 | I2C_MASTER_WRITE, ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (uint8_t) (addr>>8), ACK_CHECK_EN);
  i2c_master_write_byte(cmd, (uint8_t) addr, ACK_CHECK_EN);
  for(uint16_t i=0; i<bytes_count; i++)
  {
    i2c_master_write_byte(cmd, buf[i], ACK_CHECK_EN);
  }
  i2c_master_stop(cmd);
  i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
  usleep(1000*2);
}


/******************************************************************************************************/
void AT24C_ReadBytes (i2c_port_t i2c_port, uint16_t addr, uint8_t *buf, uint16_t bytes_count)
{
  i2c_cmd_handle_t cmd = i2c_cmd_link_create();
  i2c_master_start(cmd);                                                         // по ходу запуск I2C
  i2c_master_write_byte(cmd, at24c_addr << 1 | I2C_MASTER_WRITE, ACK_CHECK_EN);  // отправка адреса шины, сдвинутого на 1 + задается последний бит
  i2c_master_write_byte(cmd, (uint8_t) (addr>>8), ACK_CHECK_EN);                 // отправка старшего байта адреса памяти (внутри микросхемы)
  i2c_master_write_byte(cmd, (uint8_t) addr, ACK_CHECK_EN);                      // отправка младшего байта адреса памяти
  i2c_master_start(cmd);                                                         // опять запуск I2C? может это типа отправка
  i2c_master_write_byte(cmd, at24c_addr << 1 | I2C_MASTER_READ, ACK_CHECK_EN);
  for(uint16_t i=0; i<bytes_count; i++)
  {
    if(i<(bytes_count-1)) i2c_master_read_byte(cmd, buf+i, I2C_MASTER_ACK);
    else  i2c_master_read_byte(cmd, buf+i, I2C_MASTER_LAST_NACK);
  }
  i2c_master_stop(cmd);
  i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
  i2c_cmd_link_delete(cmd);
}
/******************************************************************************************************/
