/*
 * Reader.hpp
 *
 *  Created on: 23 July 2026
 *      Author: rw123
 */

#ifndef SERLINK_HPP_
#define SERLINK_HPP_

#include "Frame.hpp"

namespace SerLink {

  class FrameMsg {
    public:
      static const uint8_t TYPE_RX = 0;
      static const uint8_t TYPE_ACK = 1;

      Frame frame;
      uint8_t type;
  };
}

#endif /* SERLINK_HPP_ */