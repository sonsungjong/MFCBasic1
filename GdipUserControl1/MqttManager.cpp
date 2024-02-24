#include "pch.h"
#include "MqttManager.h"

#pragma comment(lib, "paho-mqtt3a.lib")
#pragma comment(lib, "paho-mqtt3c.lib")
#pragma comment(lib, "paho-mqttpp3-static.lib")

/*
MQTT 모스키토 수신부
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
					MessageBoxA(NULL, m_recv_ai_msg.c_str(), "메시지 받음", MB_OK);			// AI 로부터 메시지 받음

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

	m_search_item_linker[0] = "\"sn\":\"";					// 유도탄 시리얼번호
	m_search_item_linker[1] = "\"time\":\"";				// 추출시간
	m_search_item_linker[2] = "\"lchr\":\"";				// 발사대BIT
	m_search_item_linker[3] = "\"mfr\":\"";				// 다기능레이더BIT
	m_search_item_linker[4] = "\"adoc\":\"";				// 방공작전콘솔BIT

	m_search_item_sensor[0] = "\"sn\":\"";				// 유도탄 시리얼번호
	m_search_item_sensor[1] = "\"sensor\":\"";			// 센서 시리얼번호
	m_search_item_sensor[2] = "\"time\":\"";			// 측정시간
	m_search_item_sensor[3] = "\"temp\":\"";			// 온도
	m_search_item_sensor[4] = "\"humi\":\"";			// 습도
	m_search_item_sensor[5] = "\"vib\":\"";				// 진동
	m_search_item_sensor[6] = "\"lat\":\"";				// 위도
	m_search_item_sensor[7] = "\"lon\":\"";				// 경도
	m_search_item_sensor[8] = "\"reader\":\"";			// 휴대용 리더기 분석값

	m_search_item_ai = "\"ai\":\"";
}

void MqttManager::SendMsg(const std::string& a_topic, const std::string& a_msg)
{
	mqtt::message_ptr msg = mqtt::make_message(a_topic, a_msg);
	msg->set_qos(m_qos);
	m_client.publish(msg)->wait();			// 동기적으로 발행
}
