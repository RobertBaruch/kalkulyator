/*
 * Board.h
 *
 *  Created on: Mar 5, 2016
 *      Author: rober
 */

#ifndef SOURCE_BOARD_H_
#define SOURCE_BOARD_H_

#include "clock_config.h"
#include "fsl_port.h"
#include "fsl_debug_console.h"
#include "board.h"

namespace kalk {

class Board {
 private:
  Board() {
    /* Initialize UART1 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Affects PORTB_PCR16 register */
    PORT_SetPinMux(PORTB, 16u, kPORT_MuxAlt3);
    /* Affects PORTB_PCR17 register */
    PORT_SetPinMux(PORTB, 17u, kPORT_MuxAlt3);

    BOARD_BootClockRUN();

    uint32_t uartClkSrcFreq = CLOCK_GetCoreSysClkFreq();
    DbgConsole_Init((uint32_t) UART0, 115200, DEBUG_CONSOLE_DEVICE_TYPE_UART, uartClkSrcFreq);
  }
 public:
  static const Board& instance();

  Board(Board&&) = delete;
  Board(const Board&) = delete;
  void operator=(Board&&) = delete;
  void operator=(const Board&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_BOARD_H_ */
