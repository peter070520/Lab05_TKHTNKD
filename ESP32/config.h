#ifndef __CONFIG_H_
#define __CONFIG_H_

/**
 * Wi-Fi SSID
 */
#ifndef WIFI_SSID
#define WIFI_SSID "Redmi"
#endif

/**
 * Wi-Fi password
 */
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "doanxem#0705" //`````````````````````````````````````````````````````````````````````````````````````````````
#endif

/**
 * MQTT broker hostname or IP
 */
#ifndef MQTT_HOSTNAME
#define MQTT_HOSTNAME "mqtt.flespi.io"
#endif

/**
 * MQTT port
 */
#ifndef MQTT_PORT
#define MQTT_PORT 1883
#endif

/**
 * MQTT token - MQTT username
 */
#ifndef MQTT_USERNAME
#define MQTT_USERNAME "FlespiToken dk6hQ7z9nUjk1S3qATNDb08oULyZ1E82M47s2updezl5fejFYX8XL4btFyhu2fmE"
#endif

/**
 * Topic name for MQTT published
 */
#ifndef MQTT_TOPIC
#define MQTT_TOPIC "crawldata"
#endif

/**
 * Unique ID of this device in the system
 */
#ifndef DEVICE_ID
#define DEVICE_ID "SENSOR1"
#endif

/**
 * Measurement period in ms
 */
#ifndef MEASUREMENT_INTERVAL
#define MEASUREMENT_INTERVAL 60000
#endif

/**
 * Offset in ms to measurement period calculated as: sample_utc_ms % MEASUREMENT_INTERVAL
 */
#ifndef MEASUREMENT_OFFSET
#define MEASUREMENT_OFFSET 0
#endif

#endif /* MAIN_CONFIG_H_ */