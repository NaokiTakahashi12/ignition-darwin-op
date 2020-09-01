
#include <exception>
#include <iostream>

#include <joint_command_publisher/joint_command_publisher.h>

int main(int argc, char **argv) {
    using namespace joint_command_publisher;

    std::cout << "Start joint_commnad_publisher node" << std::endl;

    try
    {
        ignition::transport::Node node;

        PublishPipeline<
            data_resource::JointCommandPosition,
            ignition_publish_gateway::JointCommandPositionGateway
        > publish_pipeline{node, "darwin_op", "head_pan"};

        std::cout << publish_pipeline.data_resource().topic << std::endl;
        std::cout << publish_pipeline.data_resource().data << std::endl;

        if(argc == 2)
        {
            std::cout << argv[1] << std::endl;
            publish_pipeline.data_resource().data = std::atof(argv[1]);
        }

        publish_pipeline.publish();
        publish_pipeline.publish();
    }
    catch(const std::exception &error)
    {
        std::cerr << error.what() << std::endl;
    }
    std::cout << "Finish joint_commnad_publisher node" << std::endl;

    return 0;
}

