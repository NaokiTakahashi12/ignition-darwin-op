
/**
  Demo
  ```shell
  $ demo_joint_commnad_publisher_node <joint angle>
  ```
  **/

#include <exception>
#include <iostream>
#include <thread>
#include <chrono>

#include <joint_command_publisher/joint_command_publisher.h>

int main(int argc, char **argv)
{
    using namespace joint_command_publisher;

    std::cout << "Start joint_commnad_publisher node" << std::endl;
    try
    {
        std::vector<std::string> joint_names;
        joint_names.push_back("head_pan");
        joint_names.push_back("head_tilt");
        joint_names.push_back("l_hip_yaw");
        joint_names.push_back("l_hip_roll");
        joint_names.push_back("l_hip_pitch");
        joint_names.push_back("l_knee");
        joint_names.push_back("l_ank_pitch");
        joint_names.push_back("l_ank_roll");
        joint_names.push_back("l_sho_pitch");
        joint_names.push_back("l_sho_roll");
        joint_names.push_back("l_el");
        joint_names.push_back("r_hip_yaw");
        joint_names.push_back("r_hip_roll");
        joint_names.push_back("r_hip_pitch");
        joint_names.push_back("r_knee");
        joint_names.push_back("r_ank_pitch");
        joint_names.push_back("r_ank_roll");
        joint_names.push_back("r_sho_pitch");
        joint_names.push_back("r_sho_roll");
        joint_names.push_back("r_el");

        JointCommandPublisher joint_command{"darwin_op", joint_names};

        std::cout << "Publish topics" << std::endl;
        for(auto &&joint_name : joint_names)
        {
            std::cout << joint_command.topic(joint_name) << std::endl;
        }
        std::cout << std::endl;

        double write_joint_angle = 0.001234;

        if(argc == 2)
        {
            write_joint_angle = std::atof(argv[1]);
        }

        for(const auto &joint_name : joint_names)
        {
            joint_command.angle_pos(joint_name, write_joint_angle);
        }

        std::cout << "Now sync publish" << std::endl;
        for(auto i = 0; i < 10; i ++)
        {
            joint_command.sync_publish();
        }
        std::cout << "Finish sync publish" << std::endl;

        std::cout << "Now async publish" << std::endl;
        joint_command.async_publish();

        const auto wait_time = 5;
        std::cout << "Wait " << wait_time << "[sec]" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(wait_time));
        std::cout << "Finish async publish" << std::endl;

    }
    catch(const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }
    std::cout << "Finish joint_commnad_publisher node" << std::endl;

    return 0;
}

