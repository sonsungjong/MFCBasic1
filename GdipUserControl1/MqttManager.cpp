#include "pch.h"
#include "MqttManager.h"

#pragma comment(lib, "paho-mqtt3a.lib")
#pragma comment(lib, "paho-mqtt3c.lib")
#pragma comment(lib, "paho-mqttpp3-static.lib")

/*
MQTT ��Ű�� ���ź�
*/
void MqttManager::message_arrived(mqtt::const_message_ptr msg)
{
	
	std::string recv_topic_name = msg->get_topic();
	std::string recv_msg_payload = msg->get_payload_str();
	std::size_t start_pos = 0;
	std::size_t end_pos = 0;

	if (recv_topic_name == m_topic_sensor) {
		//m_recv_sensor_msg = recv_msg_payload;
		
	}
	else if (recv_topic_name == m_topic_linker) {
		
	}
	else if (recv_topic_name == m_topic_ai) {
		start_pos = recv_msg_payload.find(m_search_item_ai);
		if (start_pos != std::string::npos) 
		{
			start_pos += m_search_item_ai.size();
			end_pos = recv_msg_payload.find("\"", start_pos);

			if (end_pos != std::string::npos) {
				m_recv_ai_msg = recv_msg_payload.substr(start_pos, end_pos - start_pos);
				if (m_recv_ai_msg == "res") {
					MessageBoxA(NULL, m_recv_ai_msg.c_str(), "�޽��� ����", MB_OK);			// AI �κ��� �޽��� ����

				}
			}
		}
	}
	
}

MqttManager::MqttManager() : m_client(m_broker_ip_port, m_client_id)
{
	m_client.set_callback(*this);

	mqtt::connect_options conn_opts;
	m_client.connect(conn_opts)->wait();				// ���Ŀ�� ����

	// ���� ����
	m_client.subscribe(m_topic_sensor, m_qos)->wait();
	m_client.subscribe(m_topic_linker, m_qos)->wait();
	m_client.subscribe(m_topic_ai, m_qos)->wait();

	m_search_item_linker[0] = "\"sn\":\"";					// ����ź �ø����ȣ
	m_search_item_linker[1] = "\"time\":\"";				// ����ð�
	m_search_item_linker[2] = "\"lchr\":\"";				// �߻��BIT
	m_search_item_linker[3] = "\"mfr\":\"";				// �ٱ�ɷ��̴�BIT
	m_search_item_linker[4] = "\"adoc\":\"";				// ��������ܼ�BIT

	m_search_item_sensor[0] = "\"sn\":\"";				// ����ź �ø����ȣ
	m_search_item_sensor[1] = "\"sensor\":\"";			// ���� �ø����ȣ
	m_search_item_sensor[2] = "\"time\":\"";			// �����ð�
	m_search_item_sensor[3] = "\"temp\":\"";			// �µ�
	m_search_item_sensor[4] = "\"humi\":\"";			// ����
	m_search_item_sensor[5] = "\"vib\":\"";				// ����
	m_search_item_sensor[6] = "\"lat\":\"";				// ����
	m_search_item_sensor[7] = "\"lon\":\"";				// �浵
	m_search_item_sensor[8] = "\"reader\":\"";			// �޴�� ������ �м���

	m_search_item_ai = "\"ai\":\"";
}

void MqttManager::SendMsg(const std::string& a_topic, const std::string& a_msg)
{
	mqtt::message_ptr msg = mqtt::make_message(a_topic, a_msg);
	msg->set_qos(m_qos);
	m_client.publish(msg)->wait();			// ���������� ����
}
