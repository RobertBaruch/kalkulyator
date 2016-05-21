/*
 * Board.cpp
 *
 *  Created on: Mar 5, 2016
 *      Author: rober
 */

#include "Board.h"

namespace kalk {

const Board& Board::instance() {
  static Board instance;
  return instance;
}

}  // namespace kalk
