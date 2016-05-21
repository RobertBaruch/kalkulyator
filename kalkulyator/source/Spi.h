/*
 * Spi.h
 *
 *  Created on: Feb 20, 2016
 *      Author: rober
 */

#ifndef SOURCE_SPI_H_
#define SOURCE_SPI_H_

#include <cstddef>
#include "fsl_dspi.h"
#include "Board.h"
#include "Timer.h"

namespace kalk {

class Spi {
 private:
  volatile const Board& board_;  // dependency
  const Timer& timer_;

  Spi();

 public:
  static const Spi& instance();

  void send_blocking(size_t size, uint8_t *data) const;

  Spi(Spi const&) = delete;
  void operator=(Spi const&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_SPI_H_ */
