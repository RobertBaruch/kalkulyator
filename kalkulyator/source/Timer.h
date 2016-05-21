/*
 * Timer.h
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

#ifndef SOURCE_TIMER_H_
#define SOURCE_TIMER_H_

#include <cstdint>
#include "Board.h"

namespace kalk {

class Timer {
 private:
  static volatile bool timer_went_off_;

  volatile const Board& board_;  // dependency
  friend void PIT0_IRQHandler();

  Timer();

 public:
  static const Timer& instance();

  void delayMsec(uint32_t msec) const;
  void delayUsec(uint32_t usec) const;

  Timer(Timer&&) = delete;
  Timer(const Timer&) = delete;
  void operator=(Timer&&) = delete;
  void operator=(const Timer&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_TIMER_H_ */
