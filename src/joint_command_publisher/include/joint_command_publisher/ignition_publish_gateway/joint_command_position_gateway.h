
#pragma once

#include "ignition_publish_gateway.h"

namespace joint_command_publisher
{
    namespace ignition_publish_gateway
    {
        using JointCommandPositionGateway = IgnitionPublishGateway<ignition::msgs::Double, double>;
    }
}

