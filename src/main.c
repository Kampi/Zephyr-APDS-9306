#include <zephyr/kernel.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>

const struct device *const sensor = DEVICE_DT_GET(DT_NODELABEL(apds9306));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    if (!device_is_ready(sensor)) {
        LOG_ERR("Device not ready!");
        return -1;
    }

    while (1) {
        float light;
        struct sensor_value sensor_val;

        if (sensor_sample_fetch(sensor) != 0) {
            return -ENODATA;
        }

        if (sensor_channel_get(sensor, SENSOR_CHAN_LIGHT, &sensor_val) != 0) {
            return -ENODATA;
        }

        light = sensor_value_to_float(&sensor_val);
        LOG_INF("Light: %.2f", light);
    }

    return 0;
}
