#ifndef _BRAIN_H
#define _BRAIN_H

#include "../../geometry/AngularCoordinate.h"
#include "../../geometry/VolumeCoordinate.h"

#include <rec/robotino/api2/Com.h>

#include <string>
#include <thread>

class _Bumper;
class _CompactBha;
class _Odometry;
class _OmniDrive;
class _DistanceSensors;
class _LaserRangeFinder;

class KinectReader;

#define BRAIN_LOOP_TIME 50

#define BRAIN_DATA_MAX_AGE 200

#define BRAIN_FLUSH_COUNT 6

#define BRAIN_EXTERNAL_CONNECTION_RETRIES 5

class Brain : public rec::robotino::api2::Com
{
public:
    Brain(std::string name, std::string robotinoIP);

    ~Brain();

    _OmniDrive *drive();

    _Odometry *odom();

    _CompactBha *cbha();

    _LaserRangeFinder *lrf();

    bool hasLRF();

    KinectReader *kinect();

    int initialize();

    void enableKinect(std::string server, std::string port, float height);

    bool kinectIsAvailable();

    void start();

    void stop();

    bool isRunning();

private:
    std::string

        name,

        robotinoIP;

    bool

        initializationDone,

        runMainLoop,

        runComEventsLoop,

        kinectRunning,

        hasLaserRangeFinder;

    _Bumper

        *pBumper;

    _DistanceSensors

        *pDistSensors;

    _Odometry

        *pOdom;

    _OmniDrive

        *pDrive;

    _CompactBha

        *pCbha;

    _LaserRangeFinder

        *pLRF;

    KinectReader

        *pKinect;

    std::thread

        tBrainMain,

        tKinectReader,

        tComEvents;

    void processComEventsLoop();

    void kinectReader();

    void mainLoop();

    virtual void errorEvent(const char *errorString);

    virtual void connectedEvent();

    virtual void connectionClosedEvent();
    virtual void logEvent(const char *message, int level);
};

#endif
