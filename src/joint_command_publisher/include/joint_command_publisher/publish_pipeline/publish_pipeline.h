
#pragma once

#include <string>
#include <memory>
#include <mutex>

#include <joint_command_publisher/data_resource/joint_command_position.h>
#include <joint_command_publisher/ignition_publish_gateway/joint_command_position_gateway.h>

namespace joint_command_publisher
{
    namespace publish_pipeline
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
                    std::lock_guard<std::mutex> lock(resource_mutex);
                    return *resource;
                }

                DataGateway &data_gateway()
                {
                    std::lock_guard<std::mutex> lock(gateway_mutex);
                    return *gateway;
                }

                void publish()
                {
                    std::lock_guard<std::mutex> resource_lock(resource_mutex);
                    std::lock_guard<std::mutex> gateway_lock(gateway_mutex);

                    gateway->msg_data(resource->data);
                    gateway->publish();
                }

            private :
                std::mutex resource_mutex;
                std::mutex gateway_mutex;

                std::unique_ptr<DataResource> resource;
                std::unique_ptr<DataGateway> gateway;
        };
    }
}

