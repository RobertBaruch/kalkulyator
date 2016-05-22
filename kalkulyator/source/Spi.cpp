/*
 * Spi.cpp
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

#include "Spi.h"
#include "fsl_clock.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "Timer.h"

namespace kalk {

const Spi& Spi::instance() {
  static Spi instance;
  return instance;
}

Spi::Spi()
    : board_(FRDMK64F::instance()),
      timer_(Timer::instance()) {
  CLOCK_EnableClock(kCLOCK_PortC);
  CLOCK_EnableClock(kCLOCK_PortD);
  CLOCK_EnableClock(kCLOCK_Spi1);
  PORT_SetPinMux(PORTD, 4u, kPORT_MuxAlt7);  // PCS
  PORT_SetPinMux(PORTD, 5u, kPORT_MuxAlt7);  // SCK
  PORT_SetPinMux(PORTD, 6u, kPORT_MuxAlt7);  // SOUT
  PORT_SetPinMux(PORTD, 7u, kPORT_MuxAlt7);  // SIN
  PORT_SetPinMux(PORTC, 18u, kPORT_MuxAsGpio);  // LOAD

  gpio_pin_config_t gpioConfig { kGPIO_DigitalOutput, 0 };
  GPIO_PinInit(GPIOC, 18, &gpioConfig);
  GPIO_WritePinOutput(GPIOC, 18, 0);
  DSPI_Enable(SPI1, true);

  dspi_master_config_t spiConfig { kDSPI_Ctar1,  // whichCtar
      { 100000,  // baudRate
          13,  // bitsPerFrame
          kDSPI_ClockPolarityActiveHigh,  // cpol
          kDSPI_ClockPhaseFirstEdge,  // cpha
          kDSPI_MsbFirst,  // direction
          10000,  // pcsToSckDelayInNanoSec
          10000,  // lastSckToPcsDelayInNanoSec
      }, kDSPI_Pcs0,  // whichPcs
      kDSPI_PcsActiveLow,  // pcsActiveHighOrLow
      false,  // enableContinuousSCK
      false,  // enableRxFifoOverWrite
      false,  // enableModifiedTimingFormat
      kDSPI_SckToSin0Clock  // samplePoint
  };
  DSPI_MasterInit(SPI1, &spiConfig, CLOCK_GetBusClkFreq());
}

void Spi::send_blocking(size_t size, uint8_t *data) const {
  dspi_transfer_t spiTransfer { data, nullptr, size, kDSPI_MasterCtar1
      | kDSPI_MasterPcs0 | kDSPI_MasterPcsContinuous };
  DSPI_MasterTransferBlocking(SPI1, &spiTransfer);
  GPIO_WritePinOutput(GPIOC, 18, 1);
  timer_.delayUsec(10);
  GPIO_WritePinOutput(GPIOC, 18, 0);
  timer_.delayUsec(10);
}

}  // namespace kalk
