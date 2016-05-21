/*
 * Timer.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

#include "Timer.h"
#include "fsl_pit.h"
#include "fsl_clock.h"

namespace kalk {

const Timer& Timer::instance() {
  static Timer instance;
  return instance;
}

volatile bool Timer::timer_went_off_ = false;

// This name is mangled by C++, which means it doesn't override
// the global PIT0_IRQHandler. Thus, the Timer constructor has
// to explicitly install the handler.
void PIT0_IRQHandler() {
	PIT_StopTimer(PIT, kPIT_Chnl_0);
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	Timer::timer_went_off_ = true;
}

Timer::Timer() : board_(Board::instance()) {
	CLOCK_EnableClock(kCLOCK_Pit0);
	pit_config_t timerConfig {true};
	PIT_Init(PIT, &timerConfig);
	InstallIRQHandler(PIT0_IRQn, reinterpret_cast<uint32_t>(PIT0_IRQHandler));
	EnableIRQ(PIT0_IRQn);
	PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
}

void Timer::delayMsec(uint32_t msec) const {
	timer_went_off_ = false;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, (uint32_t) MSEC_TO_COUNT(msec, CLOCK_GetBusClkFreq()));
	PIT_StartTimer(PIT, kPIT_Chnl_0);
	while (!timer_went_off_);
}

void Timer::delayUsec(uint32_t usec) const {
	timer_went_off_ = false;
	PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, (uint32_t) USEC_TO_COUNT(usec, CLOCK_GetBusClkFreq()));
	PIT_StartTimer(PIT, kPIT_Chnl_0);
	while (!timer_went_off_);
}

} // namespace kalk
