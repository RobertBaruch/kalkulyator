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
#include "FRDMK64F.h"

namespace kalk {

/**
 * Class for using the LEDs. Depends on Board. Get instances using red(), green() or blue().
 */
class Led {
private:
  /**
   * Volatile dependency so the compiler doesn't optimize it away and not initialize the
   * board.
   */
  volatile const FRDMK64F& board_;

  GPIO_Type *gpio_base_;
	uint32_t pin_;

	Led(PORT_Type *port_base, GPIO_Type *gpio_base, uint32_t pin);

public:
	/**
	 * Gets the singleton instance of the red LED.
	 */
	static const Led& red();

  /**
   * Gets the singleton instance of the green LED.
   */
	static const Led& green();

  /**
   * Gets the singleton instance of the blue LED.
   */
	static const Led& blue();

	/**
	 * Turns the LED on.
	 */
	void on() const { GPIO_ClearPinsOutput(gpio_base_, 1 << pin_); }

	/**
	 * Turns the LED off.
	 */
	void off() const { GPIO_SetPinsOutput(gpio_base_, 1 << pin_); }

	/**
	 * Toggles the state of the LED.
	 */
	void toggle() const { GPIO_TogglePinsOutput(gpio_base_, 1 << pin_); }

  Led(const Led&) = delete; /**< Disallows copying. */
  Led(Led&&) = delete; /**< Disallows copying. */
  void operator=(Led&&) = delete; /**< Disallows copying. */
  void operator=(const Led&) = delete; /**< Disallows copying. */
};

} // namespace kalk

#endif /* SOURCE_LED_H_ */
