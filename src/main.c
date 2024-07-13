#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

const struct device *const sensor = DEVICE_DT_GET(DT_NODELABEL(apds_9306));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    struct sensor_value gain;
    struct sensor_value resolution;
    struct sensor_value frequency;

    if (!device_is_ready(sensor)) {
        LOG_ERR("Device not ready!");
        return -1;
    }

    LOG_INF("Device ready!");

    // 20 Bit, gain = 6, 50 ms
    /*
    gain.val1 = 2;
    resolution.val1 = 0;
    frequency.val1 = 1;
    sensor_attr_set(sensor, SENSOR_CHAN_LIGHT, (SENSOR_ATTR_PRIV_START + 1), &gain);
    sensor_attr_set(sensor, SENSOR_CHAN_LIGHT, (SENSOR_ATTR_PRIV_START + 2), &resolution);
    sensor_attr_set(sensor, SENSOR_CHAN_LIGHT, SENSOR_ATTR_SAMPLING_FREQUENCY, &frequency);
    */
    sensor_attr_get(sensor, SENSOR_CHAN_LIGHT, (SENSOR_ATTR_PRIV_START + 1), &gain);
    sensor_attr_get(sensor, SENSOR_CHAN_LIGHT, (SENSOR_ATTR_PRIV_START + 2), &resolution);
    sensor_attr_get(sensor, SENSOR_CHAN_LIGHT, SENSOR_ATTR_SAMPLING_FREQUENCY, &frequency);
    LOG_INF("Gain: %u", gain.val1);
    LOG_INF("Resolution: %u", resolution.val1);
	LOG_INF("Measurement rate: %u", frequency.val1);

    while(1) {
        /*
        struct sensor_value result;

        if (sensor_sample_fetch(sensor) != 0) {
            LOG_ERR("Can not fetch sensor value!");
            return - 1;
        }

        if (sensor_channel_get(sensor, SENSOR_CHAN_LIGHT, &result) != 0) {
            LOG_ERR("Can not read sensor value!");
            return -1;
        }

        LOG_INF("Value 1: %i", result.val1);
        LOG_INF("Value 2: %i", result.val2);
*/
        k_msleep(1000);
    }

    return 0;
}