#ifndef _ROS_navigation2_imu_angle_h
#define _ROS_navigation2_imu_angle_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace navigation2
{

  class imu_angle : public ros::Msg
  {
    public:
      typedef float _Roll_type;
      _Roll_type Roll;
      typedef float _Pitch_type;
      _Pitch_type Pitch;
      typedef float _Yaw_type;
      _Yaw_type Yaw;

    imu_angle():
      Roll(0),
      Pitch(0),
      Yaw(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Roll;
      u_Roll.real = this->Roll;
      *(outbuffer + offset + 0) = (u_Roll.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Roll.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Roll.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Roll.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Roll);
      union {
        float real;
        uint32_t base;
      } u_Pitch;
      u_Pitch.real = this->Pitch;
      *(outbuffer + offset + 0) = (u_Pitch.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Pitch.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Pitch.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Pitch.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Pitch);
      union {
        float real;
        uint32_t base;
      } u_Yaw;
      u_Yaw.real = this->Yaw;
      *(outbuffer + offset + 0) = (u_Yaw.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Yaw.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_Yaw.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_Yaw.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->Yaw);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_Roll;
      u_Roll.base = 0;
      u_Roll.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Roll.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Roll.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Roll.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Roll = u_Roll.real;
      offset += sizeof(this->Roll);
      union {
        float real;
        uint32_t base;
      } u_Pitch;
      u_Pitch.base = 0;
      u_Pitch.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Pitch.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Pitch.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Pitch.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Pitch = u_Pitch.real;
      offset += sizeof(this->Pitch);
      union {
        float real;
        uint32_t base;
      } u_Yaw;
      u_Yaw.base = 0;
      u_Yaw.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Yaw.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_Yaw.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_Yaw.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->Yaw = u_Yaw.real;
      offset += sizeof(this->Yaw);
     return offset;
    }

    virtual const char * getType() override { return "navigation2/imu_angle"; };
    virtual const char * getMD5() override { return "d8aec502c207f580f351d8f6036c0af0"; };

  };

}
#endif
