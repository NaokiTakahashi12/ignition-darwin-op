
#pragma once

#include <string>
#include <thread>
#include <mutex>

#include <ignition/msgs.hh>
#include <ignition/transport.hh>

namespace joint_command_publisher
{
    namespace ignition_publish_gateway
    {
        template <class MessageType, typename DataType>
        class IgnitionPublishGateway
        {
            public :
                IgnitionPublishGateway(ignition::transport::Node &node, const std::string &topic)
                {
                    publisher = node.Advertise<MessageType>(topic);
                    interval_time_us(512);

                    //! Initial publish (not reflected)
                    publish();
                }

                void interval_time_us(const unsigned int &us)
                {
                    message_interval_time_us = us;
                }

                virtual void msg_data(const DataType &data)
                {
                    std::lock_guard<std::mutex> lock(msg_mutex);
                    msg.set_data(data);
                }

                virtual DataType msg_data()
                {
                    std::lock_guard<std::mutex> lock(msg_mutex);
                    return msg.data();
                }

                virtual void clear_msg_data()
                {
                    std::lock_guard<std::mutex> lock(msg_mutex);
                    msg.clear_data();
                }

                bool publish()
                {
                    bool is_success;
                    {
                        std::lock_guard<std::mutex> lock(msg_mutex);
                        is_success = publisher.Publish(msg);
                    }
                    if(is_success)
                    {
                        std::this_thread::sleep_for(std::chrono::microseconds(message_interval_time_us));
                    }

                    return is_success;
                }

            protected :
                unsigned int message_interval_time_us;

                MessageType msg;
                ignition::transport::Node::Publisher publisher;

                std::mutex msg_mutex;
        };
    }
}

