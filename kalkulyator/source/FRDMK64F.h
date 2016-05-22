/*
 * Board.h
 *
 *  Created on: Mar 5, 2016
 *      Author: rober
 */

#ifndef SOURCE_FRDMK64F_H_
#define SOURCE_FRDMK64F_H_

#include "clock_config.h"
#include "fsl_port.h"
#include "fsl_debug_console.h"
#include "board.h"

namespace kalk {

// The Board is the base of the dependency hierarchy. This contains things
// that are to be set up before anything else.
class FRDMK64F {
 private:
  FRDMK64F() {
    /* Initialize UART1 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Affects PORTB_PCR16 register */
    PORT_SetPinMux(PORTB, 16u, kPORT_MuxAlt3);
    /* Affects PORTB_PCR17 register */
    PORT_SetPinMux(PORTB, 17u, kPORT_MuxAlt3);

    // Freescale library call: start up the clock in non-low power mode.
    BOARD_BootClockRUN();

    uint32_t uartClkSrcFreq = CLOCK_GetCoreSysClkFreq();
    DbgConsole_Init((uint32_t) UART0, 115200, DEBUG_CONSOLE_DEVICE_TYPE_UART, uartClkSrcFreq);
  }
 public:
  static const FRDMK64F& instance();

  FRDMK64F(FRDMK64F&&) = delete;
  FRDMK64F(const FRDMK64F&) = delete;
  void operator=(FRDMK64F&&) = delete;
  void operator=(const FRDMK64F&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_FRDMK64F_H_ */
