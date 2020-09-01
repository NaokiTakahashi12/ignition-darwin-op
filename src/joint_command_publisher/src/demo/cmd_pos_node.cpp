
/**
  Demo
  ```shell
  $ demo_cmd_pos_node <model name> <joint name> <radian>
  ```
  **/

#include <exception>
#include <iostream>

#include <joint_command_publisher/joint_command_publisher.h>

int main(int argc, char **argv) {
    using namespace joint_command_publisher::publish_pipeline;

    try
    {
        if(argc != 4)
        {
            throw std::runtime_error(
                "\nUsage: \n```shell \n$ demo_publish_pipeline_node <model name> <joint name> <radian> \n```\n"
            );
        }
        ignition::transport::Node node;

        JointCmdPosPipeline publish_pipeline{
            node,
            std::string(argv[1]),
            std::string(argv[2])
        };

        publish_pipeline.data_resource().data = std::atof(argv[3]);

        std::cout << "Topic is " << publish_pipeline.data_resource().topic << std::endl;
        std::cout << "Data is " << publish_pipeline.data_resource().data << std::endl;

        for(auto i = 0; i < 4; i ++)
        {
            publish_pipeline.publish();
        }
    }
    catch(const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }

    return 0;
}

