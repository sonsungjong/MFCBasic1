#include "pch.h"
#include "MqttManager.h"

#pragma comment(lib, "paho-mqtt3a.lib")
#pragma comment(lib, "paho-mqtt3c.lib")
#pragma comment(lib, "paho-mqttpp3-static.lib")

void MqttManager::message_arrived(mqtt::const_message_ptr msg)
{
	
	std::string recv_topic_name = msg->get_topic();
	std::string recv_msg_payload = msg->get_payload_str();
	std::size_t start_pos = 0;
	std::size_t end_pos = 0;
	std::string search_item = "";

	if (recv_topic_name == m_topic_sensor) {

	}
	else if (recv_topic_name == m_topic_linker) {

	}
	else if (recv_topic_name == m_topic_ai) {
		search_item = "\"ai\":\"";
		start_pos = recv_msg_payload.find(search_item);
		if (start_pos != std::string::npos) 
		{
			start_pos += search_item.size();
			end_pos = recv_msg_payload.find("\"", start_pos);

			if (end_pos != std::string::npos) {
				m_recv_ai_msg = recv_msg_payload.substr(start_pos, end_pos - start_pos);
				if (m_recv_ai_msg == "res") {
					MessageBoxA(NULL, m_recv_ai_msg.c_str(), "메시지 받음", MB_OK);
				}
			}
		}
	}
	
}

MqttManager::MqttManager() : m_client(m_broker_ip_port, m_client_id)
{
	m_client.set_callback(*this);

	mqtt::connect_options conn_opts;
	m_client.connect(conn_opts)->wait();				// 브로커에 연결

	// 토픽 구독
	m_client.subscribe(m_topic_sensor, m_qos)->wait();
	m_client.subscribe(m_topic_linker, m_qos)->wait();
	m_client.subscribe(m_topic_ai, m_qos)->wait();
}

void MqttManager::SendMsg(const std::string& a_topic, const std::string& a_msg)
{
	mqtt::message_ptr msg = mqtt::make_message(a_topic, a_msg);
	msg->set_qos(m_qos);
	m_client.publish(msg)->wait();			// 동기적으로 발행
}
