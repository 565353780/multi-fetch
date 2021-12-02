#include <ros/ros.h>
#include <std_msgs/String.h>
#include <message_filters/subscriber.h>
#include <message_filters/synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/time_synchronizer.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <string>
#include <vector>

#define PI 3.14159265358979

using namespace sensor_msgs;
using namespace message_filters;
using namespace nav_msgs;

class GSMTopicSync
{
public:
  GSMTopicSync()
  {
    sub_queue_size_ = 1;
    pub_rate_ = 100;

    setPubTopic();
  }

  bool setPubTopic();

  bool setRobotParam(
      const std::string &world_name,
      const std::string &robot_name,
      const size_t &robot_num);

  bool startSync();

private:
  void tfOnlyCallback(
      const OdometryConstPtr& camera_ground_truth,
      size_t robot_idx);
    

  void unionCallback(
      const CameraInfoConstPtr& camera_depth_camera_info,
      const ImageConstPtr& camera_depth_image_raw,
      const CameraInfoConstPtr& camera_rgb_camera_info,
      const ImageConstPtr& camera_rgb_image_raw,
      const OdometryConstPtr& camera_ground_truth,
      size_t robot_idx);

public:
    ros::NodeHandle nh;
    
private:
    size_t sub_queue_size_;
    size_t pub_rate_;
    
    ros::Publisher camera_depth_camera_info_pub_;
    ros::Publisher camera_depth_image_raw_pub_;
    ros::Publisher camera_rgb_camera_info_pub_;
    ros::Publisher camera_rgb_image_raw_pub_;
    tf2_ros::TransformBroadcaster tf_pub_;

    std::string world_name_;
    size_t robot_num_;
    std::string robot_name_;
};

