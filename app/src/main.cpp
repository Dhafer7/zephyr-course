    #include <zephyr/drivers/gpio.h>
    #include <zephyr/kernel.h>
    #include <zephyr/logging/log.h>
    #include <zephyr/drivers/sensor.h>



    /* The devicetree node identifier for the "led0" alias. */
    #define LED_NODE DT_ALIAS(led2)

    static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

    LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


    namespace{
        void test(){
            const struct device* driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));
            struct sensor_value val;
            int new_data;
            auto ret = sensor_channel_get(driver, SENSOR_CHAN_AMBIENT_TEMP, &val);
            LOG_INF("channel ret %d, ret"); 
            auto ret1 = sensor_get_decoder(driver, new_data);
            LOG_INF("foo_API ret %d", ret1);

        }
    }

    
    int main(void)
    {
        bool led_state = true;

        if (!gpio_is_ready_dt(&led)) return 0;

        if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

        while (1) {
            if (gpio_pin_toggle_dt(&led) < 0) return 0;

            led_state = !led_state;
            LOG_INF("LED state: %s", led_state ? "ON" : "OFF");
            k_msleep(CONFIG_APP_HEARTBEAT_PERIOD_MS);
        }
        return 0;
    }
