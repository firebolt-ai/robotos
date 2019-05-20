#ifndef B_LOCALIZATION_H
#define B_LOCALIZATION_H

#include "blob/imu.h"
#include "blob/baro.h"
#include "blob/task.h"

namespace blob
{

class Loc : public Task
{
public:
    Loc();

    void couple(Imu *imu);
    void couple(Baro *baro);

    void init();
    void update();

    Vector3d<float> getVelFlu();
    Vector3d<float> getVelEnu();
    Vector3d<float> getPos();

    void print(bool ln = true);

protected:
    Imu *_imu;
    Baro *_baro;

    Vector3d<float> _velFlu;
    Vector3d<float> _velEnu;
    Vector3d<float> _pos;
};

} // namespace blob

#endif
