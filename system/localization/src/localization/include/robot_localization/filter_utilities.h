#ifndef ROBOT_LOCALIZATION_FILTER_UTILITIES_H
#define ROBOT_LOCALIZATION_FILTER_UTILITIES_H

#include <Eigen/Dense>

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#define FB_DEBUG(msg)         \
    if (getDebug())           \
    {                         \
        *debugStream_ << msg; \
    }

std::ostream &operator<<(std::ostream &os, const Eigen::MatrixXd &mat);
std::ostream &operator<<(std::ostream &os, const Eigen::VectorXd &vec);
std::ostream &operator<<(std::ostream &os, const std::vector<size_t> &vec);
std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec);

namespace RobotLocalization
{
namespace FilterUtilities
{

double clampRotation(double rotation);

void appendPrefix(std::string tfPrefix, std::string &frameId);

} // namespace FilterUtilities
} // namespace RobotLocalization

#endif