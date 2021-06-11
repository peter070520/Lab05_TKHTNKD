#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include <esp_system.h>
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_sntp.h>
#include <esp_pm.h>

#include <nvs_flash.h>

#include <driver/gpio.h>

#include <lwip/err.h>
#include <lwip/sys.h>

#include "config.h"
#include "mqtt.h"
#include "wifi.h"
#include "sensor.h"

#define TAG "main"


#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp32/rom/ets_sys.h"
#include "driver/gpio.h"
#include "string.h"


// Main task
void main_task(void *pvParameter)
{   
    

    while (1)
    {
        int t = DHT11_read().temperature;
        int h = DHT11_read().humidity;
        
        //char* value = "Temp: 30, Humi: 60";
        printf("Temperature is %d \n", DHT11_read().temperature);
        printf("Humidity is %d\n", DHT11_read().humidity);
        printf("\n");
        mqtt_handler_publish_values(t, h);
        printf("\n\n\n");
        vTaskDelay(2000 / portTICK_RATE_MS);
    }
}

void app_main(void)
{
    // initialize NVS
    ESP_ERROR_CHECK(nvs_flash_init());
    // initialize NETIF
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    // Start Wi-Fi connection
    ESP_LOGI(TAG, "WiFi init");
    wifi_init();

    // Init and connect to MQTT
    ESP_LOGI(TAG, "Connecting to MQTT...");
    mqtt_init();
    mqtt_handler_start();
    
    // start the main task
    DHT11_init(GPIO_NUM_4);
    xTaskCreate(&main_task, "main_task", 2048, NULL, 5, NULL);
}
