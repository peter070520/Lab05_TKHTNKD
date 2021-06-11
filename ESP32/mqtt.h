#ifndef __MQTT_HANDLER_H_
#define __MQTT_HANDLER_H_

#include <esp_err.h>

/**
 * Structure with MQTT configuration data
 */
typedef struct mqtt_handler_config
{
    /**
	 * Hostname or IP of MQTT broker
	 */
    char *host;
    /**
	 * Topic ID for publishing measurements
	 */
    char *topic;
} mqtt_handler_config_t;

/**
 * Initialize MQTT protocol.
 * @param None
 */
void mqtt_init(void);

/**
 * Initialize MQTT handler.
 * @param config  MQTT connection configuration
 */
esp_err_t mqtt_handler_init(mqtt_handler_config_t config);

/**
 * Connect to the broker and start MQTT communication.
 */
esp_err_t mqtt_handler_start(void);

/**
 * Deinitialize MQTT handler to free allocated resources
 */
void mqtt_handler_deinit(void);

/**
 * Stop MQTT communication and disconnect from the broker,
 */
void mqtt_handler_stop(void);

/**
 * Publish measured values serialized into JSON to configured topic.
 * @param values  sensors values
 */
esp_err_t mqtt_handler_publish_values(int, int);

#endif /* __MQTT_HANDLER_H_ */
