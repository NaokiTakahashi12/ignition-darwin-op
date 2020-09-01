
#pragma once

#include <string>

namespace joint_command_publisher
{
    namespace data_resource
    {
        template <typename T>
        class DataResource
        {
            public :
                const std::string command_type;

                T data;
                std::string topic;

                virtual void construct_topic(const std::string &model_identity, const std::string &topic_identity) = 0;
        };
    }
}

