
#pragma once

#include <string>
#include <vector>
#include <thread>
#include <atomic>

#include "publish_pipeline/joint_cmd_pos_pipeline.h"
#include "publish_pipeline/pipeline_map.h"

namespace joint_command_publisher
{
    class JointCommandPublisher
    {
        public :
            using ModelName = std::string;
            using JointName = std::string;
            using JointNames = std::vector<JointName>;

            JointCommandPublisher(const ModelName &);
            JointCommandPublisher(const ModelName &, const JointName &);
            JointCommandPublisher(const ModelName &, const JointNames &);

            ~JointCommandPublisher();

            void model_name(const ModelName &);
            ModelName model_name();

            std::string topic(const JointName &);
            void angle_pos(const JointName &, const double &radian);

            void async_closer();

            void sync_publish();
            void async_publish();

        private :
            ModelName model_name_identity;

            ignition::transport::Node node;

            std::atomic_bool terminate_async_publish;
            std::unique_ptr<std::thread> async_thread;

            publish_pipeline::PipelineMap<publish_pipeline::JointCmdPosPipeline> cmd_pos;

            void add_cmd_pos(const JointName &);
            void add_cmd_pos(const JointNames &);

    };
}

