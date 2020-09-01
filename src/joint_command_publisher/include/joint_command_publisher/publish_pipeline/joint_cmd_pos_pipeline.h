
#include "publish_pipeline.h"

namespace joint_command_publisher
{
    namespace publish_pipeline
    {
        using JointCmdPosPipeline = PublishPipeline<
            data_resource::JointCommandPosition,
            ignition_publish_gateway::JointCommandPositionGateway
        >;
    }
}

