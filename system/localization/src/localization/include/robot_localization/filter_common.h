#ifndef ROBOT_LOCALIZATION_FILTER_COMMON_H
#define ROBOT_LOCALIZATION_FILTER_COMMON_H

namespace RobotLocalization
{

enum StateMembers
{
    StateMemberX = 0,
    StateMemberY,
    StateMemberZ,
    StateMemberRoll,
    StateMemberPitch,
    StateMemberYaw,
    StateMemberVx,
    StateMemberVy,
    StateMemberVz,
    StateMemberVroll,
    StateMemberVpitch,
    StateMemberVyaw,
    StateMemberAx,
    StateMemberAy,
    StateMemberAz
};

enum ControlMembers
{
    ControlMemberVx,
    ControlMemberVy,
    ControlMemberVz,
    ControlMemberVroll,
    ControlMemberVpitch,
    ControlMemberVyaw
};

const int STATE_SIZE = 15;
const int POSITION_OFFSET = StateMemberX;
const int ORIENTATION_OFFSET = StateMemberRoll;
const int POSITION_V_OFFSET = StateMemberVx;
const int ORIENTATION_V_OFFSET = StateMemberVroll;
const int POSITION_A_OFFSET = StateMemberAx;

const int POSE_SIZE = 6;
const int TWIST_SIZE = 6;
const int POSITION_SIZE = 3;
const int ORIENTATION_SIZE = 3;
const int ACCELERATION_SIZE = 3;

const double PI = 3.141592653589793;
const double TAU = 6.283185307179587;

} // namespace RobotLocalization

#endif