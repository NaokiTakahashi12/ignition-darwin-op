
#include <joint_command_publisher/joint_command_publisher.h>

namespace joint_command_publisher
{
    JointCommandPublisher::JointCommandPublisher(const ModelName &model)
    {
        model_name(model);
    }

    JointCommandPublisher::JointCommandPublisher(const ModelName &model, const JointName &joint)
        : JointCommandPublisher(model)
    {
        add_cmd_pos(joint);
    }

    JointCommandPublisher::JointCommandPublisher(const ModelName &model, const JointNames &joints)
        : JointCommandPublisher(model)
    {
        add_cmd_pos(joints);
    }

    JointCommandPublisher::~JointCommandPublisher()
    {
        async_closer();
    }

    void JointCommandPublisher::model_name(const ModelName &name)
    {
        this->model_name_identity = name;
    }

    JointCommandPublisher::ModelName JointCommandPublisher::model_name()
    {
        return model_name_identity;
    }

    std::string JointCommandPublisher::topic(const JointName &joint_name)
    {
        return cmd_pos.access_pipeline(joint_name).data_resource().topic;
    }

    void JointCommandPublisher::angle_pos(const JointName &joint_name, const double &radian)
    {
        cmd_pos.access_pipeline(joint_name).data_resource().data = radian;
    }

    void JointCommandPublisher::async_closer()
    {
        if(async_thread)
        {
            terminate_async_publish.store(true);
            async_thread->join();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            async_thread.reset();
        }
    }

    void JointCommandPublisher::sync_publish() {
        cmd_pos.publish();
    }

    void JointCommandPublisher::async_publish() {
        terminate_async_publish.store(false);

        async_thread = std::make_unique<std::thread>(
            [this](){
                while(!terminate_async_publish.load())
                {
                    sync_publish();
                }
            }
        );
    }

    void JointCommandPublisher::add_cmd_pos(const JointName &joint_name)
    {
        cmd_pos.add(node, model_name_identity, joint_name);
    }

    void JointCommandPublisher::add_cmd_pos(const JointNames &joint_names)
    {
        cmd_pos.add(node, model_name_identity, joint_names);
    }
}
