/*
 * MCP23008.cpp adapted from the Adafruit Liquid Crystal library.
 */

#include "MCP23008.h"

namespace kalk {

MCP23008* MCP23008::global_instance_;

MCP23008& MCP23008::instance() {
  static MCP23008 instance;
  if (global_instance_ == nullptr) {
    global_instance_ = &instance;
  }
  return *global_instance_;
}

void MCP23008::begin(uint8_t addr) {
  i2c_addr_ = kAddr | (addr & 7);

  uint8_t set_defaults_msg[] = { kReg_iodir, 0xFF,  // set to all inputs
      0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00  // all other registers to zero
      };

  i2c_.send(i2c_addr_, set_defaults_msg, 11);
}

uint8_t MCP23008::read8(uint8_t reg) {
  uint8_t read_reg_msg[] = { reg };
  uint8_t data;

  i2c_.send(i2c_addr_, read_reg_msg, 1);
  i2c_.recv(i2c_addr_, &data, 1);
  return data;
}

void MCP23008::write8(uint8_t reg, uint8_t data) {
  uint8_t write_reg_msg[] = { reg, data };

  i2c_.send(i2c_addr_, write_reg_msg, 2);
}

uint8_t MCP23008::digitalRead(uint8_t pin) {
  // only 8 bits!
  if (pin > 7)
    return 0;
  return (read8(kReg_gpio) >> pin) & 0x1;
}

void MCP23008::setBit(uint8_t reg, uint8_t bit, Signal d) {
  // only 8 bits!
  if (bit > 7)
    return;

  // read the current reg
  uint8_t data = read8(reg);

  // set the pin and direction
  if (d == Signal::kHigh) {
    data |= 1 << bit;
  } else {
    data &= ~(1 << bit);
  }

  // write the new reg
  write8(reg, data);
}

}  // namespace kalk
