#ifndef _PCDUINO_GPIO_H_
#define _PCDUINO_GPIO_H_

#define GPIO_MODE_PATH "/sys/devices/virtual/misc/gpio/mode/"
#define GPIO_PIN_PATH  "/sys/devices/virtual/misc/gpio/pin/"
/* pin value */
#define HIGH 1
#define LOW  0
/* pin mode */
#define INPUT  0
#define OUTPUT 1
#define INPUT_PULL_UP 8 /* with a pull-up resistor*/
int gpio_pinMode(int pinID,int mode);
int gpio_open(int pinID,char *gpio_path);
int gpio_setPin(int pinID,int value);
int gpio_pinStat(int pinID);
int gpio_write(int fd,int value);
char gpio_read(int fd);
#endif
