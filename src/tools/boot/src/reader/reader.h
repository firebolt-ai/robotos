#ifndef KINECTREADER_H
#define KINECTREADER_H

#include <string>

class TcpSocket;
class VolumeCoordinate;

namespace rec
{
namespace robotino
{
namespace api2
{
class Com;
}
} // namespace robotino
} // namespace rec

#define KINECTREADER_NORMAL_EXIT 0
#define KINECTREADER_LOST_CONNECTION 1
#define KINECTREADER_COULD_NOT_CONNECT 2
#define KINECTREADER_UNKNOWN_ERROR 99

#define KINECTREADER_MIN_HEIGHT 0.05

#define KINECTREADER_DEPTH_ADJUSTMENT -0.1

class KinectReader
{
public:
    KinectReader(std::string server, std::string port, rec::robotino::api2::Com *pCom);

    int readPosition(unsigned int average = 1);

    VolumeCoordinate getCoordinate();

    bool isUpdated();

    unsigned int dataAge();

    unsigned int clickAge();

    bool isRunning();

    void stopLoop();

    void setHeight(float height);

private:
    std::string

        port,

        server;

    rec::robotino::api2::Com

        *pCom;

    float

        x,

        y,

        z,

        height;

    unsigned int
        updateTime,
        clickTime;

    bool
        runLoop,
        updated;
};

#endif