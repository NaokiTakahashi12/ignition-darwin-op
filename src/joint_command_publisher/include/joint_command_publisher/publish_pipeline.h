
#pragma once

#include <string>
#include <memory>

#include <joint_command_publisher/data_resource/joint_command_position.h>
#include <joint_command_publisher/ignition_publish_gateway/joint_command_position_gateway.h>

namespace joint_command_publisher
{
    template <class DataResource, class DataGateway>
    class PublishPipeline
    {
        public :
            PublishPipeline(ignition::transport::Node &node, const std::string &model_identity, const std::string &topic_identity)
            {
                resource = std::make_unique<DataResource>(model_identity, topic_identity);
                gateway = std::make_unique<DataGateway>(node, resource->topic);
            }

            DataResource &data_resource()
            {
                return *resource;
            }

            DataGateway &data_gateway()
            {
                return *gateway;
            }

            void publish()
            {
                gateway->msg_data(resource->data);
                gateway->publish();
            }

        private :
            std::string topic_identity;
            std::unique_ptr<DataResource> resource;
            std::unique_ptr<DataGateway> gateway;
    };
}

