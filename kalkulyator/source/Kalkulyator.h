/*
 * Kalkulyator.h
 *
 *  Created on: Mar 12, 2016
 *      Author: rober
 */

#ifndef SOURCE_KALKULYATOR_H_
#define SOURCE_KALKULYATOR_H_

#include "I2C.h"
#include "Lcd.h"
#include "Spi.h"
#include "Timer.h"
#include "GmpMemory.h"
#include "Stack.h"
#include "fsl_debug_console.h"

namespace kalk {

// Debug > kalkulyator_Debug_Segger

/**
 * Class for the Kalkulyator, the main class. Depends on:
 * - I2C
 * - SPI
 * - LCD
 * - Timer
 * - GMP
 * - Stack
 */
class Kalkulyator {
 private:
  const I2C& i2c_;
  const Spi& spi_;
  Lcd& lcd_;
  const Timer& timer_;
  volatile GmpMemory& gmp_;
  Stack& stack_;

  inline Kalkulyator()
      : i2c_(I2C::instance()),
        spi_(Spi::instance()),
        lcd_(Lcd::instance()),
        timer_(Timer::instance()),
        gmp_(GmpMemory::instance()),
        stack_(Stack::instance()) {
  }

 public:
  /**
   * Gets the singleton instance.
   */
  static const Kalkulyator& instance();

  /**
   * Runs the Kalkulator.
   */
  void run() const;

  Kalkulyator(Kalkulyator&&) = delete; /**< Disallows copying. */
  Kalkulyator(const Kalkulyator&) = delete; /**< Disallows copying. */
  void operator=(Kalkulyator&&) = delete; /**< Disallows copying. */
  void operator=(const Kalkulyator&) = delete; /**< Disallows copying. */
};

}  // namespace kalk

#endif /* SOURCE_KALKULYATOR_H_ */
