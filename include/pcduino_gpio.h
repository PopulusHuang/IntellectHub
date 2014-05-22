#ifndef _PCDUINO_GPIO_H_
#define _PCDUINO_GPIO_H_

#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_PIN_PATH  "/sys/devices/virtual/misc/gpio/pin/"
/* pin value */
#define LOW  0
#define HIGH 1
/* pin mode */
#define INPUT  0
#define OUTPUT 1
#define INPUT_PULL_UP 8 /* with a pull-up resistor*/
int gpio_pinMode(int pinID,int mode);
int gpio_setPin(int pinID,int value);
int gpio_pinStat(int pinID);
#endif
