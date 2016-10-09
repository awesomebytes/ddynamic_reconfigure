#include <ros/ros.h>
#include <ddynamic_reconfigure/DDynamicReconfigure.h>


/**
  Topics:
  * /dynamic_tutorials/parameter_descriptions [dynamic_reconfigure/ConfigDescription]
  * /dynamic_tutorials/parameter_updates [dynamic_reconfigure/Config]

  Services:
  * /dynamic_tutorials/set_parameter:  dynamic_reconfigure/Reconfigure
*/

int main(int argc, char **argv) {
  ros::init(argc, argv, "fake_dynamic_reconfigure");

  ros::NodeHandle nh("fake_dyanmic_reconfigure");

  double double_test = 0.0;
  double double_range = 2;
  int int_test = 0;
  bool bool_test = false;
  std::string string_test;

  DDynamicReconfigure ddr(nh);
  DDynamicReconfigure ddr2(ros::NodeHandle(nh, "nh2"));
  DDynamicReconfigure ddr3(ros::NodeHandle(nh, "nh3"));

  ddr.RegisterVariable(&double_test, "double_test");
  ddr.RegisterVariable(&double_range, "double_range_test", 0, 10);
  ddr.RegisterVariable(&int_test, "int_test");
  ddr.RegisterVariable(&bool_test, "bool_test");
  ddr.RegisterVariable(&string_test, "string_test");

  ddr2.RegisterVariable(&double_test, "double_test");
  ddr2.RegisterVariable(&int_test, "int_test");
  ddr2.RegisterVariable(&bool_test, "bool_test");

  ddr.PublishServicesTopics();
  ddr2.PublishServicesTopics();
  ddr3.PublishServicesTopics();

  ddr.setUserCallback([&ddr](){ std::cout << std::endl << ddr; });


  ROS_INFO("Spinning node");

  ros::spin();
  return 0;
}

