#include <mavros/mavros_plugin.h>

#include <mavros_msgs/ServoOutputRaw.h>

namespace mavros {
namespace extra_plugins {
//! @brief Plugin for SERVO_OUTPUT_RAW msgs from MAVLink API
class ServoOutputRawPlugin : public plugin::PluginBase {
public:
    ServoOutputRawPlugin() : PluginBase(),
        servoOutputRaw_nh("~servo_output_raw")
        { }
    
    void initialize(UAS &uas_)
    {
        PluginBase::initialize(uas_);

        //ros publisher
        servo_output_raw_pub = servoOutputRaw_nh.advertise<mavros_msgs::ServoOutputRaw>("servo_output_raw", 10);
    }

    Subscriptions get_subscriptions() {
		return {
			       make_handler(&ServoOutputRawPlugin::handle_servo_output_raw)
		};
	}

private:
    ros::NodeHandle servoOutputRaw_nh;

    ros::Publisher servo_output_raw_pub;

    /* -*- message handler -*- */

    /**
	 * @brief Handle SERVO_OUTPUT_RAW message.
	 * Message specification: https://mavlink.io/en/messages/common.html#SERVO_OUTPUT_RAW
	 * @param msg	Received Mavlink msg
	 * @param servo_output	SERVO_OUTPUT_RAW msg
	 */
    void handle_servo_output_raw(const mavlink::mavlink_message_t *msg, mavlink::common::msg::SERVO_OUTPUT_RAW &servo_output)
    {
        auto sor_msg = boost::make_shared<mavros_msgs::ServoOutputRaw>();
        sor_msg->header.stamp = m_uas->synchronise_stamp(static_cast<uint64_t>(servo_output.time_usec));
        sor_msg->port = servo_output.port;
        sor_msg->servo1 = servo_output.servo1_raw;
        sor_msg->servo2 = servo_output.servo2_raw;
        sor_msg->servo3 = servo_output.servo3_raw;
        sor_msg->servo4 = servo_output.servo4_raw;
        sor_msg->servo5 = servo_output.servo5_raw;
        sor_msg->servo6 = servo_output.servo6_raw;
        sor_msg->servo7 = servo_output.servo7_raw;
        sor_msg->servo8 = servo_output.servo8_raw;
        sor_msg->servo9 = servo_output.servo9_raw;
        sor_msg->servo10 = servo_output.servo10_raw;
        sor_msg->servo11 = servo_output.servo11_raw;
        sor_msg->servo12 = servo_output.servo12_raw;
        sor_msg->servo13 = servo_output.servo13_raw;
        sor_msg->servo14 = servo_output.servo14_raw;
        sor_msg->servo15 = servo_output.servo15_raw;
        sor_msg->servo16 = servo_output.servo16_raw;

        servo_output_raw_pub.publish(sor_msg);
    }

};
} // namespace extra_plugins
} // namespace mavros

#include <pluginlib/class_list_macros.h>
PLUGINLIB_EXPORT_CLASS(mavros::extra_plugins::ServoOutputRawPlugin, mavros::plugin::PluginBase)
