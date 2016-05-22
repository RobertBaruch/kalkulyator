/*
 * Board.cpp
 *
 *  Created on: Mar 5, 2016
 *      Author: rober
 */

#include "FRDMK64F.h"

namespace kalk {

const FRDMK64F& FRDMK64F::instance() {
  static FRDMK64F instance;
  return instance;
}

}  // namespace kalk
