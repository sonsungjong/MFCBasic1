#ifndef MQTT_MANAGER_H_
#define MQTT_MANAGER_H_

#include <mqtt/async_client.h>

class MqttManager : public virtual mqtt::callback
{
private:

public:
	const char* m_broker_ip_port = "tcp://localhost:1883";				// ���Ŀ�� IP�� Port
	const char* m_client_id = "cbm_plus_mqtt_id";						// ������ ���̵�(�ߺ� �Ұ�)
	const char* m_topic_sensor = "sensor";
	const char* m_topic_linker = "linker";
	const char* m_topic_ai = "ai";
	const int m_qos = 2;				// �ܰ� 0~2
	const int m_timeout = 10000;
	std::string m_search_item_ai;
	std::string m_search_item_linker[5];					// ����ź�ø���, ����ð�, �߻��, �ٱ�ɷ��̴�, ADOC
	std::string m_search_item_sensor[9];					// ����źsn, ����sn, �ð�, �µ�, ����, ����, ����, �浵, �м���
	std::string m_recv_sensor_msg = "";
	std::string m_recv_linker_msg = "";
	std::string m_recv_ai_msg = "";

	mqtt::async_client m_client;

	void message_arrived(mqtt::const_message_ptr msg) override;
	MqttManager();
	void SendMsg(const std::string& a_topic, const std::string& a_msg);
	
};

#endif
