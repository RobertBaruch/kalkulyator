/*
 * I2C.cpp
 *
 *  Created on: Feb 23, 2016
 *      Author: rober
 */

#include "I2C.h"
#include "fsl_i2c.h"

namespace kalk {

constexpr port_pin_config_t kI2CPortConfig{
    kPORT_PullDisable,
    kPORT_FastSlewRate, kPORT_PassiveFilterDisable, kPORT_OpenDrainEnable,
    kPORT_LowDriveStrength, kPORT_MuxAlt5, kPORT_UnlockRegister};

const I2C& I2C::instance() {
  static I2C instance;
  return instance;
}

I2C::I2C()
    : board_(FRDMK64F::instance()) {
  i2c_master_config_t config;

  CLOCK_EnableClock(kCLOCK_PortE);
  PORT_SetPinConfig(PORTE, 24, &kI2CPortConfig);
  PORT_SetPinConfig(PORTE, 25, &kI2CPortConfig);

  I2C_MasterGetDefaultConfig(&config);
  config.baudRate_Bps = 400000;
  I2C_MasterInit(I2C0, &config, CLOCK_GetFreq(I2C0_CLK_SRC));
}

status_t I2C::send(uint8_t address, uint8_t *txBuff, size_t txSize) const {
  i2c_master_transfer_t transfer{
      kI2C_TransferDefaultFlag,  // flags: start with START, stop with STOP
      address, kI2C_Write, 0,  // subaddress
      0,  // subaddressSize
      txBuff, txSize};
  return I2C_MasterTransferBlocking(I2C0, &transfer);
}

status_t I2C::recv(uint8_t address, uint8_t *rxBuff, size_t rxSize) const {
  i2c_master_transfer_t transfer{
      kI2C_TransferDefaultFlag,  // flags
      address, kI2C_Read, 0,  // subaddress
      0,  // subaddressSize
      rxBuff, rxSize};
  return I2C_MasterTransferBlocking(I2C0, &transfer);
}

}  // namespace kalk
