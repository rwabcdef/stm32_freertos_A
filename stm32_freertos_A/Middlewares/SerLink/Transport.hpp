/*
 * Transport.hpp
 *
 *  Created on: 23 July 2026
 *      Author: rw123
 */

#ifndef TRANSPORT_HPP_
#define TRANSPORT_HPP_

#include "SerLink_config.hpp"
#include "Frame.hpp"
#include "Socket.hpp"
#include "FreeRTOS.h"
#include "queue.h"

namespace SerLink {

  // Only used as a pointer here - forward declared (rather than #included)
  // to avoid a Writer.hpp <-> Transport.hpp circular include.
  class Writer;

  class Transport {
    protected:
      Writer* writer;
      Socket sockets[SERLINK_CONFIG__MAX_SOCKETS];

    public:
      // Fed by Reader's consumerQueue (received frames) and by application
      // code wanting to send a frame directly (see startButtonTask).
      // Created externally (StaticQueue_t/storage owned by the caller,
      // e.g. main.cpp) and handed in via init() - Transport itself never
      // creates it.
      QueueHandle_t queue;

      Transport(Writer* writer);

      // Assigns the (already-created) dispatch queue. Must be called once,
      // before queue is used.
      void init(QueueHandle_t queue);

      // Services one message from queue: routes received (TYPE_RX) frames
      // to whichever acquired socket matches their protocol, and forwards
      // frames to be sent (TYPE_TX) to the writer. Must be called
      // repeatedly (e.g. in an owning task's for(;;) loop); blocks until a
      // message arrives.
      void run();

      // Non-blocking: pushes frame onto queue (as a TYPE_TX FrameMsg) for
      // run() to forward to the writer. Returns whether it was accepted.
      bool sendData(Frame* frame);

      Socket* acquireSocket(char* protocol, onReceiveCallback callback = nullptr);
  };
}

#endif /* TRANSPORT_HPP_ */
