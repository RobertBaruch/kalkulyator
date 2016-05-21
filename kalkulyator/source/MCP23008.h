/*
 * MCP23008.h adapted from the Adafruit Liquid Crystal library.
 */

#ifndef SOURCE_MCP23008_H_
#define SOURCE_MCP23008_H_

#include "I2C.h"
#include <cstdint>

namespace kalk {

class MCP23008 {
 public:
  enum class Direction {
    kOutput,
    kInput
  };

  enum class Signal {
    kHigh,
    kLow
  };

 private:
  static MCP23008* global_instance_;
  static constexpr uint8_t kAddr = 0x20;
  static constexpr uint8_t kReg_iodir = 0x00;
  static constexpr uint8_t kReg_gppu = 0x06;
  static constexpr uint8_t kReg_gpio = 0x09;

  const I2C& i2c_;
  uint8_t i2c_addr_;

  MCP23008()
      : i2c_(I2C::instance()) {
  }
  uint8_t read8(uint8_t reg);
  void write8(uint8_t reg, uint8_t data);
  void setBit(uint8_t reg, uint8_t bit, Signal d);
  Signal signalForDirection(Direction d) {
    return d == Direction::kInput ? Signal::kHigh : Signal::kLow;
  }

 public:
  static MCP23008& instance();

  void begin(uint8_t addr);
  void pinmode(uint8_t pin, Direction d) {
    setBit(kReg_iodir, pin, signalForDirection(d));
  }
  void digitalWrite(uint8_t pin, Signal d) {
    setBit(kReg_gpio, pin, d);
  }
  uint8_t digitalRead(uint8_t pin);
  uint8_t readGpio() {
    return read8(kReg_gpio);
  }
  void writeGpio(uint8_t data) {
    write8(kReg_gpio, data);
  }
  void pullUp(uint8_t pin, Signal d) {
    setBit(kReg_gppu, pin, d);
  }

  MCP23008(MCP23008&&) = delete;
  MCP23008(const MCP23008&) = delete;
  void operator=(MCP23008&&) = delete;
  void operator=(const MCP23008&) = delete;
};

}  // namespace kalk

#endif /* SOURCE_MCP23008_H_ */
