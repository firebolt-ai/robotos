#ifndef ROBOT_LOCALIZATION_NAVSAT_TRANSFORM_H
#define ROBOT_LOCALIZATION_NAVSAT_TRANSFORM_H

#include <robot_localization/SetDatum.h>

#include <ros/ros.h>

#include <nav_msgs/Odometry.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <tf2/LinearMath/Transform.h>
#include <tf2_ros/static_transform_broadcaster.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>

#include <Eigen/Dense>

#include <string>

namespace RobotLocalization
{

class NavSatTransform
{
  public:
    NavSatTransform(ros::NodeHandle nh, ros::NodeHandle nh_priv);

    ~NavSatTransform();

  private:

    void periodicUpdate(const ros::TimerEvent& event);

    void computeTransform();

    bool datumCallback(robot_localization::SetDatum::Request& request, robot_localization::SetDatum::Response&);

    void getRobotOriginUtmPose(const tf2::Transform &gps_utm_pose,
                               tf2::Transform &robot_utm_pose,
                               const ros::Time &transform_time);

    void getRobotOriginWorldPose(const tf2::Transform &gps_odom_pose,
                                 tf2::Transform &robot_odom_pose,
                                 const ros::Time &transform_time);


    void gpsFixCallback(const sensor_msgs::NavSatFixConstPtr& msg);

    void imuCallback(const sensor_msgs::ImuConstPtr& msg);

    void odomCallback(const nav_msgs::OdometryConstPtr& msg);

    bool prepareFilteredGps(sensor_msgs::NavSatFix &filtered_gps);

    bool prepareGpsOdometry(nav_msgs::Odometry &gps_odom);

    void setTransformGps(const sensor_msgs::NavSatFixConstPtr& msg);

    void setTransformOdometry(const nav_msgs::OdometryConstPtr& msg);

    bool broadcast_utm_transform_;

    bool broadcast_utm_transform_as_parent_frame_;

    bool gps_updated_;

    bool has_transform_gps_;

    bool has_transform_imu_;

    bool has_transform_odom_;

    bool odom_updated_;

    bool publish_gps_;

    bool transform_good_;

    bool use_manual_datum_;

    bool use_odometry_yaw_;

    bool zero_altitude_;

    double magnetic_declination_;

    double utm_meridian_convergence_;

    double utm_odom_tf_yaw_;

    double yaw_offset_;

    std::string base_link_frame_id_;

    std::string gps_frame_id_;

    std::string utm_zone_;

    std::string world_frame_id_;

    Eigen::MatrixXd latest_odom_covariance_;

    Eigen::MatrixXd latest_utm_covariance_;

    ros::Time gps_update_time_;

    ros::Time odom_update_time_;

    ros::Duration transform_timeout_;

    ros::Timer periodicUpdateTimer_;

    tf2::Quaternion transform_orientation_;

    tf2::Transform latest_utm_pose_;

    tf2::Transform latest_world_pose_;

    tf2::Transform transform_utm_pose_;

    tf2::Transform transform_world_pose_;

    tf2::Transform utm_world_transform_;

    tf2::Transform utm_world_trans_inverse_;

    ros::Publisher filtered_gps_pub_;

    ros::Subscriber gps_sub_;

    ros::Subscriber imu_sub_;

    ros::Subscriber odom_sub_;

    ros::Publisher gps_odom_pub_;

    ros::ServiceServer datum_srv_;

    tf2_ros::Buffer tf_buffer_;

    tf2_ros::TransformListener tf_listener_;

    tf2_ros::StaticTransformBroadcaster utm_broadcaster_;
};

} 

#endif 