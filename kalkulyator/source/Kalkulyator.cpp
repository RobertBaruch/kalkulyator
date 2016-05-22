/*
 * Kalkulyator.cpp
 *
 *  Created on: Mar 12, 2016
 *      Author: rober
 */

#include <cstdio>
#include <mpfr.h>
#include "Kalkulyator.h"
#include "Led.h"
#include <cstdarg>

namespace kalk {

const Kalkulyator& Kalkulyator::instance() {
  static Kalkulyator instance;
  return instance;
}

void Kalkulyator::run() const {
  timer_.delayMsec(500);

  /*
  lcd_.begin();

  char str[512];
  push_pi();
  str_of_stack(str, 0);
  printf("%s\n", str);

  push("2");
  div();
  str_of_stack(str, 0);
  printf("%s\n", str);

  sin();
  str_of_stack(str, 0);
  printf("%s\n", str);

  for (int i = 0; i < 80 && str[i] != 0; i++) {
    lcd_.write(str[i]);
  }
  */

  // txData[0] is sent last, with MSb first. txData[1] is sent first with 13th bit first.
  //
  // 01000 01011000 11111 11111111
  // uint8_t txData[] = { 0b01011000, 0b00001000, 0b11111111, 0b00011111 };
  uint16_t c = 0;
  for (;;) {
    uint8_t data[] = { uint8_t((~c)&0xFF), uint8_t((~c)>>8) };
    spi_.send_blocking(2, data);
    timer_.delayMsec(500);
    if (c == 0) {
      c = 1;
    } else {
      c = (c << 1) & 0b1111111111111;
    }
    Led::red().toggle();
  }

//  uint8_t c = 0;
//  for (;;) {
//    timer_.delayMsec(5);
//    Led::red().toggle();
//    lcd_.write(c);
//    ++c;
//  }
}

}  // namespace kalk
