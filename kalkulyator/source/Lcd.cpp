/*
 * Lcd.cpp adapted from the Adafruit Liquid Crystal library.
 */

#include "Lcd.h"

namespace kalk {

Lcd Lcd::global_instance_;

void Lcd::begin() {
  backpack_.begin(0);

  for (uint8_t pin = 1; pin <= 7; pin++) {
    backpack_.pinmode(pin, MCP23008::Direction::kOutput);
  }

  backlightOn();

  // SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
  // according to datasheet, we need at least 40ms after power rises above 2.7V
  // before sending commands.
  Timer::instance().delayMsec(50);

  // Now we pull RS low to begin commands
  setRsState(MCP23008::Signal::kLow);
  setEnableState(MCP23008::Signal::kLow);

  // Put the LCD driver into 4-bit mode.
  // this is according to the hitachi HD44780 datasheet
  // figure 24, pg 46

  // we start in 8bit mode, try to set 4 bit mode
  write4bits(0b0011);
  Timer::instance().delayUsec(4500);  // wait min 4.1ms

  // second try (redundant?)
  write4bits(0b0011);
  Timer::instance().delayUsec(4500);  // wait min 4.1ms

  // third go!
  write4bits(0b0011);
  Timer::instance().delayUsec(150);  // wait min 100us

  // finally, set to 4-bit interface
  write4bits(0b0010);

  write8bits(0b00101000);  // 4-bit interface, 2 lines, 5x8 characters 0x20
  displayOn();
  cursorOn();
  blinkOff();
  cursorMoveIncrement();
  clear();
  //home();
}

void Lcd::write4bits(uint8_t data) {
  uint8_t out = backpack_.readGpio();

  out = (out & kData_mask) | ((data & 0x0F) << kData_shift);

  backpack_.writeGpio(out);
  Timer::instance().delayUsec(1);

  // pulse enable
  out |= kEnable_mask;
  backpack_.writeGpio(out);
  Timer::instance().delayUsec(1);
  out &= ~kEnable_mask;
  backpack_.writeGpio(out);
  Timer::instance().delayUsec(100);  // wait min 100us
}

void Lcd::write8bits(uint8_t data) {
  write4bits(data >> 4);
  write4bits(data);
}

}  // namespace kalk
