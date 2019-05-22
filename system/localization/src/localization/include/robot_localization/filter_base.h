#ifndef ROBOT_LOCALIZATION_FILTER_BASE_H
#define ROBOT_LOCALIZATION_FILTER_BASE_H

#include "filter_utilities.h"
#include "filter_common.h"

#include <Eigen/Dense>

#include <algorithm>
#include <limits>
#include <map>
#include <ostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

namespace RobotLocalization
{
struct Measurement
{
    double latestControlTime_;

    double mahalanobisThresh_;

    double time_;

    std::string topicName_;

    std::vector<int> updateVector_;

    Eigen::VectorXd latestControl_;

    Eigen::VectorXd measurement_;
    Eigen::MatrixXd covariance_;

    bool operator()(const boost::shared_ptr<Measurement> &a, const boost::shared_ptr<Measurement> &b)
    {
        return (*this)(*(a.get()), *(b.get()));
    }

    bool operator()(const Measurement &a, const Measurement &b)
    {
        return a.time_ > b.time_;
    }

    Measurement() : latestControlTime_(0.0),
                    mahalanobisThresh_(std::numeric_limits<double>::max()),
                    time_(0.0),
                    topicName_("")
    {
    }
};
typedef boost::shared_ptr<Measurement> MeasurementPtr;

struct FilterState
{

    double lastMeasurementTime_;


    double latestControlTime_;


    Eigen::VectorXd latestControl_;


    Eigen::VectorXd state_;


    Eigen::MatrixXd estimateErrorCovariance_;


    bool operator()(const FilterState &a, const FilterState &b)
    {
        return a.lastMeasurementTime_ < b.lastMeasurementTime_;
    }

    FilterState() : lastMeasurementTime_(0.0),
                    latestControlTime_(0.0)
    {
    }
};
typedef boost::shared_ptr<FilterState> FilterStatePtr;

class FilterBase
{
public:

    FilterBase();

    virtual ~FilterBase();

    void reset();

    void computeDynamicProcessNoiseCovariance(const Eigen::VectorXd &state, const double delta);

    virtual void correct(const Measurement &measurement) = 0;

    const Eigen::VectorXd &getControl();

    double getControlTime();

    bool getDebug();

    const Eigen::MatrixXd &getEstimateErrorCovariance();

    bool getInitializedStatus();

    double getLastMeasurementTime();

    const Eigen::VectorXd &getPredictedState();

    const Eigen::MatrixXd &getProcessNoiseCovariance();

    double getSensorTimeout();

    const Eigen::VectorXd &getState();

    virtual void predict(const double referenceTime, const double delta) = 0;

    virtual void processMeasurement(const Measurement &measurement);

    void setControl(const Eigen::VectorXd &control, const double controlTime);

    void setControlParams(const std::vector<int> &updateVector, const double controlTimeout,
                          const std::vector<double> &accelerationLimits, const std::vector<double> &accelerationGains,
                          const std::vector<double> &decelerationLimits, const std::vector<double> &decelerationGains);

    void setDebug(const bool debug, std::ostream *outStream = NULL);

    void setUseDynamicProcessNoiseCovariance(const bool dynamicProcessNoiseCovariance);

    void setEstimateErrorCovariance(const Eigen::MatrixXd &estimateErrorCovariance);

    void setLastMeasurementTime(const double lastMeasurementTime);

    void setProcessNoiseCovariance(const Eigen::MatrixXd &processNoiseCovariance);

    void setSensorTimeout(const double sensorTimeout);

    void setState(const Eigen::VectorXd &state);

    void validateDelta(double &delta);

protected:

    inline double computeControlAcceleration(const double state, const double control, const double accelerationLimit,
                                             const double accelerationGain, const double decelerationLimit, const double decelerationGain)
    {
        FB_DEBUG("---------- FilterBase::computeControlAcceleration ----------\n");

        const double error = control - state;
        const bool sameSign = (::fabs(error) <= ::fabs(control) + 0.01);
        const double setPoint = (sameSign ? control : 0.0);
        const bool decelerating = ::fabs(setPoint) < ::fabs(state);
        double limit = accelerationLimit;
        double gain = accelerationGain;

        if (decelerating)
        {
            limit = decelerationLimit;
            gain = decelerationGain;
        }

        const double finalAccel = std::min(std::max(gain * error, -limit), limit);

        FB_DEBUG("Control value: " << control << "\n"
                                   << "State value: " << state << "\n"
                                   << "Error: " << error << "\n"
                                   << "Same sign: " << (sameSign ? "true" : "false") << "\n"
                                   << "Set point: " << setPoint << "\n"
                                   << "Decelerating: " << (decelerating ? "true" : "false") << "\n"
                                   << "Limit: " << limit << "\n"
                                   << "Gain: " << gain << "\n"
                                   << "Final is " << finalAccel << "\n");

        return finalAccel;
    }

    virtual void wrapStateAngles();

    virtual bool checkMahalanobisThreshold(const Eigen::VectorXd &innovation,
                                           const Eigen::MatrixXd &invCovariance,
                                           const double nsigmas);

    void prepareControl(const double referenceTime, const double predictionDelta);

    bool initialized_;

    bool useControl_;

    bool useDynamicProcessNoiseCovariance_;

    double lastMeasurementTime_;

    double latestControlTime_;

    double controlTimeout_;

    double sensorTimeout_;

    std::vector<int> controlUpdateVector_;

    std::vector<double> accelerationGains_;

    std::vector<double> accelerationLimits_;

    std::vector<double> decelerationGains_;

    std::vector<double> decelerationLimits_;

    Eigen::VectorXd controlAcceleration_;

    Eigen::VectorXd latestControl_;

    Eigen::VectorXd predictedState_;

    Eigen::VectorXd state_;

    Eigen::MatrixXd covarianceEpsilon_;

    Eigen::MatrixXd dynamicProcessNoiseCovariance_;

    Eigen::MatrixXd estimateErrorCovariance_;

    Eigen::MatrixXd identity_;

    Eigen::MatrixXd processNoiseCovariance_;

    Eigen::MatrixXd transferFunction_;

    Eigen::MatrixXd transferFunctionJacobian_;

    std::ostream *debugStream_;

private:
    bool debug_;
};

} // namespace RobotLocalization

#endif