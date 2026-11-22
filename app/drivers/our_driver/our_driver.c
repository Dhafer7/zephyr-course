#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include "our_driver_task2.h"

#define DT_DRV_COMPAT  our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);


static int channel_get_my_impl(const struct device *dev,
				    enum sensor_channel chan,
				    struct sensor_value *val){
    
    LOG_INF("Hello from channel get, channel %d",chan);
    return 0;
                    }

 int foo_API(struct device * dev, int newdata)
{
    if(NULL !=  dev){
        dev->data = newdata;
        return 0;
    } 

    return -1;
}      



static DEVICE_API(sensor, api_iomico_lecture) = {
    .channel_get = channel_get_my_impl,
    .get_decoder = foo_API,
};



//init function
static int init(const struct device* dev ){
    LOG_INF("Device Initialized");   
    return 0;  
}

DEVICE_DT_INST_DEFINE(0, init, NULL, NULL, NULL, POST_KERNEL, 80, &api_iomico_lecture);
