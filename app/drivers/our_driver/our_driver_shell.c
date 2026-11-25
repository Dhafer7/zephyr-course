#include <zephyr/shell/shell.h>
#include <zephyr/drivers/sensor.h>

static int cmd_channel_get_handler(const struct shell* sh , int argc, char** argv)
{
    const struct device* dev = shell_device_get_binding(argv[1]); 
    if(!dev){
        shell_error(sh, "could not find device %s", argv[1]);
        return -EFAULT;
    }


    struct sensor_value val;
    int ret = sensor_channel_get(dev, SENSOR_CHAN_ACCEL_X, &val);

    if(ret != 0){
        shell_error(sh, "could not  fetch channel, got %d", ret);
        return -EFAULT;
    }
    shell_info(sh, "%d", val.val1);
    return 0;

}


SHELL_STATIC_SUBCMD_SET_CREATE(our_driver_subcmd,
    SHELL_CMD_ARG(channel_get, NULL, "Get channel of our driver", cmd_channel_get_handler, 2, 0),
    SHELL_SUBCMD_SET_END,
);

SHELL_CMD_ARG_REGISTER(our_driver, &our_driver_subcmd, "our driver set of commands", NULL, 1, 0);