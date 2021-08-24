#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf2pose/tf2req.h>

using namespace std;

namespace ObjectGlobalVars {
   //Put all of your global variables here
   tf2_ros::Buffer tfBuffer;
}

bool callback(tf2pose::tf2req::Request  &req,
              tf2pose::tf2req::Response &res)
{

    string tf_target_frame = "world";
    ros::param::get("tf2srv/map_id", tf_target_frame);

    geometry_msgs::TransformStamped transformStamped;
    try{
      transformStamped = ObjectGlobalVars::tfBuffer.lookupTransform(tf_target_frame, req.header.frame_id,
                               req.header.stamp);
    }
    catch (tf2::TransformException &ex) {
      ROS_WARN("%s",ex.what());
      return false;
    }
    
    res.pose.position.x = transformStamped.transform.translation.x;
    res.pose.position.y = transformStamped.transform.translation.y;
    res.pose.position.z = transformStamped.transform.translation.z;

    res.pose.orientation.x = transformStamped.transform.rotation.x;
    res.pose.orientation.y = transformStamped.transform.rotation.y;
    res.pose.orientation.z = transformStamped.transform.rotation.z;
    res.pose.orientation.w = transformStamped.transform.rotation.w;
    return true;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "tf2srv");

  tf2_ros::TransformListener tfListener(ObjectGlobalVars::tfBuffer);

  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("request_tf2", callback);
  ros::spin();

  return 0;
};
