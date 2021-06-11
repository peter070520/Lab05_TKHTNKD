#ifndef __SENSOR_H_
#define __SENSOR_H_

#include <esp_err.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32/rom/ets_sys.h"
#include "driver/gpio.h"

struct dht11_reading
{
    int status;
    int temperature;
    int humidity;
};

void DHT11_init(gpio_num_t gpio_num);

struct dht11_reading DHT11_read();



#endif /* __SENSOR_H_ */