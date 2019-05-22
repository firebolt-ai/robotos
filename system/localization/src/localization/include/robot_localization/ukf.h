#ifndef ROBOT_LOCALIZATION_UKF_H
#define ROBOT_LOCALIZATION_UKF_H

#include "filter_base.h"

#include <fstream>
#include <vector>
#include <set>
#include <queue>

namespace RobotLocalization
{

class Ukf : public FilterBase
{
public:
    explicit Ukf(std::vector<double> args);

    ~Ukf();

    void correct(const Measurement &measurement);

    void predict(const double referenceTime, const double delta);

protected:
    std::vector<Eigen::VectorXd> sigmaPoints_;

    Eigen::MatrixXd weightedCovarSqrt_;

    std::vector<double> stateWeights_;

    std::vector<double> covarWeights_;

    double lambda_;

    bool uncorrected_;
};

} // namespace RobotLocalization

#endif