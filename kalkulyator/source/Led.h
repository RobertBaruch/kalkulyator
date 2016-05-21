/*
 * Led.h
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

#ifndef SOURCE_LED_H_
#define SOURCE_LED_H_

using namespace std;
#include <cstdint>
#include "fsl_gpio.h"

class Led {
private:
	static Led global_red_instance_;
	static Led global_green_instance_;
	static Led global_blue_instance_;

	GPIO_Type *gpio_base_;
	uint32_t pin_;

	Led(PORT_Type *port_base, GPIO_Type *gpio_base, uint32_t pin);

public:
	static Led const& red() { return global_red_instance_; }
	static Led const& green() { return global_green_instance_; }
	static Led const& blue() { return global_blue_instance_; }

	void on() const { GPIO_ClearPinsOutput(gpio_base_, 1 << pin_); }
	void off() const { GPIO_SetPinsOutput(gpio_base_, 1 << pin_); }
	void toggle() const { GPIO_TogglePinsOutput(gpio_base_, 1 << pin_); }

	Led(Led const&) = delete;
    void operator=(Led const&) = delete;
};

#endif /* SOURCE_LED_H_ */
