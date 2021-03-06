/*
 * Led.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

using namespace std;
#include "Led.h"
#include "clock_config.h"
#include "fsl_port.h"
#include "fsl_gpio.h"

namespace kalk {

const Led& Led::red() {
  static Led instance(PORTB, GPIOB, 22);
  return instance;
}

const Led& Led::green() {
  static Led instance(PORTE, GPIOE, 26);
  return instance;
}

const Led& Led::blue() {
  static Led instance(PORTB, GPIOB, 21);
  return instance;
}

constexpr uint8_t kLED_on = 0;
constexpr uint8_t kLED_off = 1;
constexpr gpio_pin_config_t led_gpio_config_ {kGPIO_DigitalOutput, kLED_off};
constexpr port_pin_config_t led_port_config_ {
    kPORT_PullDisable,
    kPORT_SlowSlewRate,
    kPORT_PassiveFilterDisable,
    kPORT_OpenDrainDisable,
    kPORT_LowDriveStrength,
    kPORT_MuxAsGpio,
    kPORT_UnlockRegister
};

Led::Led(PORT_Type *port_base, GPIO_Type *gpio_base, uint32_t pin)
    : board_(FRDMK64F::instance()),
		  gpio_base_(gpio_base), pin_(pin) {
  CLOCK_EnableClock(kCLOCK_PortB);
  CLOCK_EnableClock(kCLOCK_PortE);
  PORT_SetPinConfig(port_base, pin, &led_port_config_);
	GPIO_PinInit(gpio_base, pin, &led_gpio_config_);
}

} // namespace kalk
