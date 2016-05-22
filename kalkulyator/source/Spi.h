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
#include "FRDMK64F.h"
#include "Timer.h"

namespace kalk {

// Class for using SPI. Depends on Board and Timer.
class Spi {
 private:
  volatile const FRDMK64F& board_;  // dependency
  const Timer& timer_;

  Spi();

 public:
  static const Spi& instance();

  void send_blocking(size_t size, uint8_t *data) const;

  // No copy
  Spi(const Spi&) = delete;
  Spi(Spi&&) = delete;
  void operator=(const Spi&) = delete;
  void operator=(Spi&&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_SPI_H_ */
