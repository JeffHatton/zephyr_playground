/**
 * @file main.c
 * @author Jeff Hatton
 * @brief Implementation for main
 * @date 2022-03-06
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 #include <testDevice.h>

#include <device.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

// Private Types ****************************************

// Constants ********************************************

// Macros ***********************************************

// Functions Prototypes *********************************

// Private Variables ************************************

#define NUM_SENSORS 2

// Private Functions *************************************

// Public Functions *************************************

void main()
{
    const struct device* dev0 = DEVICE_DT_GET(DT_NODELABEL(testdevice0));
    printk("Setting up devices\n");
	// if (!device_is_ready(dev0)) {
	// 	LOG_ERR("Device %u not ready", 0);
	// 	return;
	// }

    // // #if NUM_SENSORS >= 2

    // testDevices[1] = DEVICE_DT_GET(DT_NODELABEL(testdevice1));
	// if (!device_is_ready(testDevices[1])) {
	// 	LOG_ERR("Device %u not ready", 1);
	// 	return;
	// }

    // // #endif

    while (1)
    {
        for (uint16_t i = 0; i < NUM_SENSORS; i++)
        {
            TestDevice_Update(dev0);
        }
        
        k_sleep(K_MSEC(1));
    }

    return;
}
