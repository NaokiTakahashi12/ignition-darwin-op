
#pragma once

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>

#include "publish_pipeline.h"

namespace joint_command_publisher
{
    namespace publish_pipeline
    {
        template <class Pipeline>
        class PipelineMap
        {
            public :
                using Strings = std::vector<std::string>;

                void add(ignition::transport::Node &node, const std::string &model_name, const std::string &joint_name)
                {
                    map[joint_name] = std::make_unique<Pipeline>(node, model_name, joint_name);
                }

                void add(ignition::transport::Node &node, const std::string &model_name, const Strings &joint_names)
                {
                    for(const auto &joint_name : joint_names)
                    {
                        add(node, model_name, joint_name);
                    }
                }

                void publish()
                {
                    for(auto &&[topic, pipeline_ptr] : map)
                    {
                        pipeline_ptr->publish();
                    }
                }

                Pipeline &access_pipeline(const std::string &joint_name)
                {
                    return *(map[joint_name]);
                }

            protected :
                using Topic = std::string;
                using PipelinePtr = std::unique_ptr<Pipeline>;
                using Map = std::unordered_map<Topic, PipelinePtr>;

                Map map;

        };
    }
}

