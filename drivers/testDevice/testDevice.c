/**
 * @file testDevice.c
 * @author Jeff Hatton
 * @brief Implementation for testDevice
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// Register sensor driver for DTS match
#define DT_DRV_COMPAT hatronic_testdevice

#include "testDevice.h"
#include <drivers/gpio.h>
#include <logging/log.h>
LOG_MODULE_REGISTER(testDevice, CONFIG_TEST_DEVICE_LOG_LEVEL);

// Private Types ****************************************

typedef struct {
    int64_t ChangeDelay;
    const struct gpio_dt_spec Pin;
} TestDeviceConfig_t;

typedef struct {
    int64_t LastChangeTime;
    bool CurrentState;
} TestDeviceData_t;

// Constants ********************************************

// Macros ***********************************************

// Functions Prototypes *********************************

// Private Variables ************************************

// Private Functions *************************************

static int TestDevice_init(const struct device *dev)
{
	const TestDeviceConfig_t *config = dev->config;

	int ret;

	if (!device_is_ready(config->Pin.port)) {
		LOG_ERR("Input GPIO not ready");
		return -ENODEV;
	}

	ret = gpio_pin_configure_dt(&config->Pin, GPIO_OUTPUT);
	if (ret < 0) {
		LOG_ERR("Could not configure input GPIO (%d)", ret);
		return ret;
	}

	return 0;
}

// Public Functions *************************************


void TestDevice_Update(const struct device *dev)
{
    TestDeviceConfig_t* conf = (TestDeviceConfig_t*)dev->config;
    TestDeviceData_t *data = dev->data;

    int64_t now = k_uptime_get();
    if (now - data->LastChangeTime > conf->ChangeDelay)
    {
        data->CurrentState = !data->CurrentState;        
        data->LastChangeTime = now;
        gpio_pin_set_dt(&conf->Pin, data->CurrentState);
    }
}

#define TESTDEVICE_INIT(i)	\
	static const TestDeviceConfig_t testDevice_config_##i = {  \
		.Pin = GPIO_DT_SPEC_INST_GET(i, gpios), \
        .ChangeDelay = DT_INST_PROP(i, changedelay) \
	}; \
    static TestDeviceData_t testDevice_data_##i; \
									       \
	DEVICE_DT_INST_DEFINE(i, TestDevice_init, NULL,		       \
			      &testDevice_data_##i,			       \
			      &testDevice_config_##i, APPLICATION,	       \
			      80, NULL);


DT_INST_FOREACH_STATUS_OKAY(TESTDEVICE_INIT)


#ifdef testDevice_config_0

#pragma message "Defined"

#else

#pragma message "Not Defined"

#endif