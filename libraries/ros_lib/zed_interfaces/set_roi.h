#ifndef _ROS_SERVICE_set_roi_h
#define _ROS_SERVICE_set_roi_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace zed_interfaces
{

static const char SET_ROI[] = "zed_interfaces/set_roi";

  class set_roiRequest : public ros::Msg
  {
    public:
      typedef const char* _roi_type;
      _roi_type roi;

    set_roiRequest():
      roi("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_roi = strlen(this->roi);
      varToArr(outbuffer + offset, length_roi);
      offset += 4;
      memcpy(outbuffer + offset, this->roi, length_roi);
      offset += length_roi;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_roi;
      arrToVar(length_roi, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_roi; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_roi-1]=0;
      this->roi = (char *)(inbuffer + offset-1);
      offset += length_roi;
     return offset;
    }

    virtual const char * getType() override { return SET_ROI; };
    virtual const char * getMD5() override { return "f8582525019d538cfd188d29f0c1b797"; };

  };

  class set_roiResponse : public ros::Msg
  {
    public:
      typedef bool _success_type;
      _success_type success;
      typedef const char* _message_type;
      _message_type message;

    set_roiResponse():
      success(0),
      message("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.real = this->success;
      *(outbuffer + offset + 0) = (u_success.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->success);
      uint32_t length_message = strlen(this->message);
      varToArr(outbuffer + offset, length_message);
      offset += 4;
      memcpy(outbuffer + offset, this->message, length_message);
      offset += length_message;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_success;
      u_success.base = 0;
      u_success.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->success = u_success.real;
      offset += sizeof(this->success);
      uint32_t length_message;
      arrToVar(length_message, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_message; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_message-1]=0;
      this->message = (char *)(inbuffer + offset-1);
      offset += length_message;
     return offset;
    }

    virtual const char * getType() override { return SET_ROI; };
    virtual const char * getMD5() override { return "937c9679a518e3a18d831e57125ea522"; };

  };

  class set_roi {
    public:
    typedef set_roiRequest Request;
    typedef set_roiResponse Response;
  };

}
#endif
