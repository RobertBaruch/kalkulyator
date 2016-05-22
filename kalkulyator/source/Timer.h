/*
 * Timer.h
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

#ifndef SOURCE_TIMER_H_
#define SOURCE_TIMER_H_

#include <cstdint>
#include "FRDMK64F.h"

namespace kalk {

// Class for the Timer. Depends on Board.
class Timer {
 private:
  static volatile bool timer_went_off_;

  volatile const FRDMK64F& board_;  // dependency
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
