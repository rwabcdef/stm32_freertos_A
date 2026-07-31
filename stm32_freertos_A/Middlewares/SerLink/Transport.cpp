#include "Transport.hpp"
#include "Writer.hpp"

using namespace SerLink;

Transport::Transport(Writer* writer)
: writer(writer)
{
}

void Transport::init(QueueHandle_t queue)
{
  this->queue = queue;
}

void Transport::run()
{
  FrameMsg frameMsg;

  if(xQueueReceive(this->queue, &frameMsg, portMAX_DELAY) == pdTRUE)
  {
    if(frameMsg.type == FrameMsg::TYPE_RX)
    {
      // find the acquired socket this frame's protocol belongs to, if any
      for(uint8_t i = 0; i < SERLINK_CONFIG__MAX_SOCKETS; i++)
      {
        if(this->sockets[i].isAcquired() && this->sockets[i].matchesProtocol(frameMsg.frame.protocol))
        {
          this->sockets[i].deliverReceivedData(frameMsg.frame.data, frameMsg.frame.dataLen);
          break;
        }
      }
    }
    else if(frameMsg.type == FrameMsg::TYPE_TX)
    {
      // send the frame via the writer
      this->writer->sendFrame(&frameMsg.frame);
    }
    // TYPE_ACK: nothing to do here currently - acks are already forwarded
    // directly to the writer by Reader; only reach here for app-level
    // logging, which isn't handled at the Transport level.
  }
}

bool Transport::sendData(Frame* frame)
{
  FrameMsg frameMsg;
  frameMsg.type = FrameMsg::TYPE_TX;
  frameMsg.frame = *frame;

  return (xQueueSend(this->queue, &frameMsg, 0) == pdTRUE);
}

Socket* Transport::acquireSocket(char* protocol, onReceiveCallback callback)
{
  for(uint8_t i = 0; i < SERLINK_CONFIG__MAX_SOCKETS; i++)
  {
    if(!this->sockets[i].isAcquired())
    {
      this->sockets[i].init(protocol, this, callback);
      return &this->sockets[i];
    }
  }

  return nullptr; // no free socket slots
}
