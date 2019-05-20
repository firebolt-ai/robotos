#include "reader.h"

#include "../../../math/geometry/coordinates/vol/vol.h"
#include "../../../tcp/Socket.h"

#include <rec/robotino/api2/Com.h>

#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>

int KinectReader::readPosition(unsigned int average)
{
    std::string input;

    float
        xCurVal = 0.0,
        yCurVal = 0.0,
        zCurVal = 0.0;

    unsigned int
        i = 0,
        endx = 0,
        endy = 0;
    TcpSocket tcpClient(this->port, this->server);

    this->runLoop = true;

    while (this->runLoop)
    {
        xCurVal = 0.0;
        yCurVal = 0.0;
        zCurVal = 0.0;

        i = 0;

        while (tcpClient.read(input))
        {

            if (input == "Click")
            {
                this->clickTime = pCom->msecsElapsed();
                continue;
            }

            endx = input.find(',', 0);
            if (endx == std::string::npos)
                continue;
            endy = input.find(',', endx + 1);
            if (endy == std::string::npos)
                continue;

            xCurVal += (float)std::atof(input.substr(0, endx).c_str());
            yCurVal += (float)std::atof(input.substr(endx + 1, endy).c_str());
            zCurVal += (float)std::atof(input.substr(endy + 1).c_str());

            if ((fabs(xCurVal) + fabs(yCurVal) + fabs(zCurVal)) < 0.1f)
                continue;

            if (++i >= average)
                break;
        }

        if (i < average)
        {
            this->runLoop = false;
            std::cerr << "KinectReader: Connection lost" << std::endl;
            return KINECTREADER_LOST_CONNECTION;
        }

        this->x = ((zCurVal / average) / 1000.0) + KINECTREADER_DEPTH_ADJUSTMENT;
        this->y = ((xCurVal / average) / 1000.0);
        this->z = ((yCurVal / average) / 1000.0) + this->height;

        this->updateTime = this->pCom->msecsElapsed();
        this->updated = true;
    }

    return KINECTREADER_NORMAL_EXIT;
}

KinectReader::KinectReader(std::string server, std::string port, rec::robotino::api2::Com *pCom)
{
    this->server = server;
    this->port = port;
    this->pCom = pCom;

    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;

    this->height = KINECTREADER_MIN_HEIGHT;

    this->updateTime = 0;
    this->clickTime = 0;

    this->runLoop = false;
    this->updated = false;
}

VolumeCoordinate KinectReader::getCoordinate()
{
    this->updated = false;
    return VolumeCoordinate(this->x, this->y, this->z);
}

bool KinectReader::isUpdated()
{
    return this->updated;
}

unsigned int KinectReader::dataAge()
{
    return (this->pCom->msecsElapsed() - this->updateTime);
}

unsigned int KinectReader::clickAge()
{
    return this->pCom->msecsElapsed() - this->clickTime;
}

bool KinectReader::isRunning()
{
    return this->runLoop;
}

void KinectReader::stopLoop()
{
    this->runLoop = false;
}

void KinectReader::setHeight(float height)
{
    if (height > KINECTREADER_MIN_HEIGHT)
    {
        this->height = height;
        std::cout << "Kinect height set to " << height << " meters" << std::endl;
    }
    else
        std::cout << "Could not set kinect height to " << height << " meters, too low" << std::endl;
}
