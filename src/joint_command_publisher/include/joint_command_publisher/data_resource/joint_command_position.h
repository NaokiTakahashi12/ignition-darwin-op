
#pragma once

#include "data_resource.h"

namespace joint_command_publisher
{
    namespace data_resource
    {
        class JointCommandPosition : public DataResource<double>
        {
            public :
                JointCommandPosition() : command_type("cmd_pos")
                {
                    this->data = 0;
                }

                JointCommandPosition(const std::string &model_identity, const std::string &topic_identity) : JointCommandPosition()
                {
                    this->data = 0;
                    construct_topic(model_identity, topic_identity);
                }

                virtual void construct_topic(const std::string &model_identity, const std::string &topic_identity) override
                {
                    this->topic =
                        "/model/" + model_identity +
                        "/joint/" + topic_identity +
                        "/0/" + this->command_type;
                }

                const std::string command_type;
        };
    }
}

