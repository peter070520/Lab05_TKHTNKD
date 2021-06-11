#include <stdbool.h>
#include <string.h>
#include <esp_log.h>
#include <mqtt_client.h>

#include "mqtt.h"
#include "config.h"

#define MQTT_TAG "MQTT"

static mqtt_handler_config_t mqtt_handler_config;
static esp_mqtt_client_handle_t mqtt_client = NULL;

void tostring(char str[], int num)
{
    int i, rem, len = 0, n;

    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void mqtt_init(void)
{
    mqtt_handler_config_t config;
    config.host = MQTT_HOSTNAME;
    config.topic = MQTT_TOPIC;
    mqtt_handler_init(config);
}

/**
 * Handle MQTT events.
 */
static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event)
{
    int msg_id;
    switch (event->event_id)
    {
    case MQTT_EVENT_CONNECTED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_CONNECTED");
        break;
    case MQTT_EVENT_DISCONNECTED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_DISCONNECTED");
        break;
    case MQTT_EVENT_PUBLISHED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_SUBSCRIBED:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
        break;
    case MQTT_EVENT_ERROR:
        ESP_LOGI(MQTT_TAG, "MQTT_EVENT_ERROR");
        break;
    default:
        break;
    }
    return ESP_OK;
}

esp_err_t mqtt_handler_init(const mqtt_handler_config_t config)
{
    esp_mqtt_client_config_t mqtt_cfg;
    memset((void *)&mqtt_cfg, 0, sizeof(esp_mqtt_client_config_t));
    mqtt_cfg.host = MQTT_HOSTNAME,
    mqtt_cfg.port = MQTT_PORT,
    mqtt_cfg.username = MQTT_USERNAME,

    mqtt_cfg.event_handle = mqtt_event_handler;
    mqtt_cfg.keepalive = 180;
    mqtt_client = esp_mqtt_client_init(&mqtt_cfg);
    if (mqtt_client == NULL)
    {
        return ESP_FAIL;
    }
    mqtt_handler_config = config;
    return ESP_OK;
}

void mqtt_handler_deinit(void)
{
    esp_mqtt_client_destroy(mqtt_client);
}

esp_err_t mqtt_handler_start(void)
{
    return esp_mqtt_client_start(mqtt_client);
}

void mqtt_handler_stop(void)
{
    esp_mqtt_client_stop(mqtt_client);
}

esp_err_t mqtt_handler_publish_values(int t, int h)
{
    //Transfer the temp and hud from int to char
    char t2[10], h2[10];
    char kq[10] = {};
    tostring(t2, t);
    tostring(h2, h);
    //then, merge them into a single char to publish
    strcat(kq, t2);
    strcat(kq, " ");
    strcat(kq, h2);

    // Publish values to the configured topic
    esp_mqtt_client_publish(mqtt_client, MQTT_TOPIC, kq, 11, 1, false);
    //esp_mqtt_client_publish(mqtt_client, MQTT_TOPIC, "temp:38, humi: 70", 21, 1, false);

    return ESP_OK;
}
