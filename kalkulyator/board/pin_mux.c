/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "fsl_port.h"
#include "pin_mux.h"
#include "board.h"
#include "fsl_dspi.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Initialize all pins used in this example
 *
 * @param disablePortClockAfterInit disable port clock after pin
 * initialization or not.
 */
void BOARD_InitPins(void)
{
    /* Initialize UART1 pins below */
    /* Ungate the port clock */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Affects PORTB_PCR16 register */
    PORT_SetPinMux(PORTB, 16u, kPORT_MuxAlt3);
    /* Affects PORTB_PCR17 register */
    PORT_SetPinMux(PORTB, 17u, kPORT_MuxAlt3);

    // Initialize SPI1
    /*CLOCK_EnableClock(kCLOCK_PortC);
    CLOCK_EnableClock(kCLOCK_PortD);
    CLOCK_EnableClock(kCLOCK_Spi1);
    PORT_SetPinMux(PORTD, 4u, kPORT_MuxAlt7); // PCS
    PORT_SetPinMux(PORTD, 5u, kPORT_MuxAlt7); // SCK
    PORT_SetPinMux(PORTD, 6u, kPORT_MuxAlt7); // SOUT
    PORT_SetPinMux(PORTD, 7u, kPORT_MuxAlt7); // SIN
    PORT_SetPinMux(PORTC, 18u, kPORT_MuxAsGpio); // LOAD
    DSPI_Enable(SPI1, true);

    dspi_master_config_t spiConfig = {
    	.whichCtar = kDSPI_Ctar1,
		.ctarConfig = {
			.baudRate = 100000,
			.bitsPerFrame = 13,
			.cpol = kDSPI_ClockPolarityActiveHigh,
			.cpha = kDSPI_ClockPhaseFirstEdge,
			.direction = kDSPI_MsbFirst,
			.pcsToSckDelayInNanoSec = 1000,
			.lastSckToPcsDelayInNanoSec = 1000,
		},
		.whichPcs = kDSPI_Pcs0,
		.pcsActiveHighOrLow = kDSPI_PcsActiveLow,
		.enableContinuousSCK = false,
		.enableRxFifoOverWrite = false,
		.enableModifiedTimingFormat = false,
		.samplePoint = kDSPI_SckToSin0Clock,
    };
    DSPI_MasterInit(SPI1, &spiConfig, CLOCK_GetBusClkFreq());*/
}
