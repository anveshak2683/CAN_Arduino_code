#ifndef _ROS_navigation_enc_feed_h
#define _ROS_navigation_enc_feed_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navigation
{

  class enc_feed : public ros::Msg
  {
    public:
      typedef int16_t _vel_type;
      _vel_type vel;
      typedef int16_t _angle_type;
      _angle_type angle;

    enc_feed():
      vel(0),
      angle(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_vel;
      u_vel.real = this->vel;
      *(outbuffer + offset + 0) = (u_vel.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_vel.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->vel);
      union {
        int16_t real;
        uint16_t base;
      } u_angle;
      u_angle.real = this->angle;
      *(outbuffer + offset + 0) = (u_angle.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_angle.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->angle);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_vel;
      u_vel.base = 0;
      u_vel.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_vel.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->vel = u_vel.real;
      offset += sizeof(this->vel);
      union {
        int16_t real;
        uint16_t base;
      } u_angle;
      u_angle.base = 0;
      u_angle.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_angle.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->angle = u_angle.real;
      offset += sizeof(this->angle);
     return offset;
    }

    virtual const char * getType() override { return "navigation/enc_feed"; };
    virtual const char * getMD5() override { return "c7d324c5346393c6bc385a7a281fa92c"; };

  };

}
#endif
