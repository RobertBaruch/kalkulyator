/*
 * I2C.h
 *
 *  Created on: Feb 23, 2016
 *      Author: rober
 */

#ifndef SOURCE_I2C_H_
#define SOURCE_I2C_H_

#include "fsl_common.h"
#include "clock_config.h"
#include "fsl_port.h"
#include "FRDMK64F.h"
#include <cstdint>

namespace kalk {

class I2C {
 private:
  static constexpr clock_ip_name_t kPort = kCLOCK_PortE;
  static constexpr PORT_Type *kPortBase = PORTE;
  static constexpr uint32_t kSclPin = 24;
  static constexpr uint32_t kSdaPin = 25;

  volatile const FRDMK64F& board_;  // dependency

  I2C();

 public:
  static const I2C& instance();

  status_t send(uint8_t address, uint8_t *txBuff, size_t txSize) const;
  status_t recv(uint8_t address, uint8_t *rxBuff, size_t rxSize) const;

  I2C(I2C&&) = delete;
  I2C(const I2C&) = delete;
  void operator=(I2C&&) = delete;
  void operator=(const I2C&) = delete;
};

}  // namespace kalk
#endif /* SOURCE_I2C_H_ */
