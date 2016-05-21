/*
 * Lcd.h adapted from the Adafruit Liquid Crystal library.
 */

#ifndef SOURCE_LCD_H_
#define SOURCE_LCD_H_

#include "MCP23008.h"
#include "Timer.h"
#include <cstdint>

namespace kalk {

// For the 20x4 LCD from Adafruit, which, to the Hitachi HD44780 driver
// looks like a 40x2 LCD.
// LCD_4BITMODE | LCD_2LINE | LCD_5x8DOTS;
//  // the I/O expander pinout
//  _rs_pin = 1;
//  _rw_pin = 255;
//  _enable_pin = 2;
//  _data_pins[0] = 3;  // really d4
//  _data_pins[1] = 4;  // really d5
//  _data_pins[2] = 5;  // really d6
//  _data_pins[3] = 6;  // really d7
//  backlight = 7

class Lcd {
 private:
  static Lcd global_instance_;
  static constexpr uint8_t kHeight = 4;
  static constexpr uint8_t kWidth = 20;
  static constexpr uint8_t kRs_pin = 1;
  static constexpr uint8_t kEnable_pin = 2;
  static constexpr uint8_t kEnable_mask = 0b00000100;
  static constexpr uint8_t kData_mask = 0b10000111;
  static constexpr uint8_t kData_shift = 3;
  static constexpr uint8_t kBacklight_pin = 7;

  enum class DisplayControl
    : uint8_t {
      kBlinkOn = 0b001,
    kCursorOn = 0b010,
    kDisplayOn = 0b100
  };

  enum class EntryMode
    : uint8_t {
      kDisplayShift = 0b01,
    kCursorMoveIncrement = 0b10
  };

  MCP23008& backpack_;
  uint8_t x_ = 0;
  uint8_t y_ = 0;
  uint8_t display_state_ = 0;
  uint8_t entry_mode_state_ = 0;bool rs_state_known = false;
  MCP23008::Signal rs_state_ = MCP23008::Signal::kLow;

  Lcd()
      : backpack_(MCP23008::instance()) {
  }

  void write4bits(uint8_t data);
  void write8bits(uint8_t data);

  void setRsState(MCP23008::Signal state) {
    if (!rs_state_known || state != rs_state_) {
      backpack_.digitalWrite(kRs_pin, state);
      rs_state_ = state;
      rs_state_known = true;
    }
  }

  void setEnableState(MCP23008::Signal state) {
    backpack_.digitalWrite(kEnable_pin, state);
  }

 public:
  static Lcd& instance() {
    return global_instance_;
  }

  void begin();

  void clear() {
    setRsState(MCP23008::Signal::kLow);
    write8bits(0b00000001);
    Timer::instance().delayMsec(2);  // long command
  }

  void home() {
    setRsState(MCP23008::Signal::kLow);
    write8bits(0b00000010);
    Timer::instance().delayMsec(2);  // long command
  }

  void displayShiftOff() {
    setRsState(MCP23008::Signal::kLow);
    entry_mode_state_ &= ~static_cast<uint8_t>(EntryMode::kDisplayShift);
    write8bits(0b00000100 | entry_mode_state_);
  }

  void displayShiftOn() {
    setRsState(MCP23008::Signal::kLow);
    entry_mode_state_ |= static_cast<uint8_t>(EntryMode::kDisplayShift);
    write8bits(0b00000100 | entry_mode_state_);
  }

  void cursorMoveDecrement() {
    setRsState(MCP23008::Signal::kLow);
    entry_mode_state_ &= ~static_cast<uint8_t>(EntryMode::kCursorMoveIncrement);
    write8bits(0b00000100 | entry_mode_state_);
  }

  void cursorMoveIncrement() {
    setRsState(MCP23008::Signal::kLow);
    entry_mode_state_ |= static_cast<uint8_t>(EntryMode::kCursorMoveIncrement);
    write8bits(0b00000100 | entry_mode_state_);
  }

  void displayOff() {
    setRsState(MCP23008::Signal::kLow);
    display_state_ &= ~static_cast<uint8_t>(DisplayControl::kDisplayOn);
    write8bits(0b00001000 | display_state_);
  }

  void displayOn() {
    setRsState(MCP23008::Signal::kLow);
    display_state_ |= static_cast<uint8_t>(DisplayControl::kDisplayOn);
    write8bits(0b00001000 | display_state_);
  }

  void cursorOff() {
    setRsState(MCP23008::Signal::kLow);
    display_state_ &= ~static_cast<uint8_t>(DisplayControl::kCursorOn);
    write8bits(0b00001000 | display_state_);
  }

  void cursorOn() {
    setRsState(MCP23008::Signal::kLow);
    display_state_ |= static_cast<uint8_t>(DisplayControl::kCursorOn);
    write8bits(0b00001000 | display_state_);
  }

  void blinkOff() {
    setRsState(MCP23008::Signal::kLow);
    display_state_ &= ~static_cast<uint8_t>(DisplayControl::kBlinkOn);
    write8bits(0b00001000 | display_state_);
  }

  void blinkOn() {
    setRsState(MCP23008::Signal::kLow);
    display_state_ |= static_cast<uint8_t>(DisplayControl::kBlinkOn);
    write8bits(0b00001000 | display_state_);
  }

  void backlightOn() {
    backpack_.digitalWrite(kBacklight_pin, MCP23008::Signal::kHigh);
  }

  void backlightOff() {
    backpack_.digitalWrite(kBacklight_pin, MCP23008::Signal::kLow);
  }

  void setCursor(uint8_t x, uint8_t y) {
    if (y > 3 || x > 19) {
      return;
    }
    uint8_t dramAddr = 20 * y + x;
    setRsState(MCP23008::Signal::kLow);
    write8bits(0b01000000 | dramAddr);
  }

  void write(uint8_t c) {
    setRsState(MCP23008::Signal::kHigh);
    write8bits(c);
  }

  Lcd(Lcd&&) = delete;
  Lcd(const Lcd&) = delete;
  void operator=(Lcd&&) = delete;
  void operator=(const Lcd&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_LCD_H_ */
