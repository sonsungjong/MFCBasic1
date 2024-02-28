/*
<���̺귯�� ���� ���(Release x64)>
Git Bash �� ��ġ�Ѵ�.
CMake�� ��ġ�Ѵ�.
Visual Studio�� ��ġ�Ѵ� (Visual Studio 17 2022, Visual Studio 16 2019 ��)
C����̺꿡 git bash�� ������ �������� �����ϰ�
git clone https://github.com/eclipse/paho.mqtt.c.git
git clone https://github.com/eclipse/paho.mqtt.cpp.git
�� ���� �Է��Ͽ� ������Ʈ�� ��ġ�Ѵ�.

CMake�� ���� sln ������ �����Ѵ�.
mkdir paho.mqtt.c/build
cd paho.mqtt.c/build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Release
cmake --install .

cd paho.mqtt.cpp
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 -DPAHO_MQTT_C_LIBRARIES="C:/paho.mqtt.c/build/src/Release" -DPAHO_MQTT_C_INCLUDE_DIRS="C:/paho.mqtt.c/src" ..
cmake --build . --config Release
cmake --install .

����, 64��Ʈ�� �����ϰ� 32��Ʈ�� �����ϰ��� �ϸ� ���� ���� ���ϰ� CMake ĳ�ø� �����ؾ��Ѵ�.
cd C:/paho.mqtt.c/build
rm -rf CMakeCache.txt CMakeFiles/
cmake -G "Visual Studio 17 2022" -A Win32 ..

cd C:/paho.mqtt.cpp/build
rm -rf CMakeCache.txt CMakeFiles/
cmake -G "Visual Studio 17 2022" -A Win32 -DPAHO_MQTT_C_LIBRARIES="C:/paho.mqtt.c/build/src/Release" -DPAHO_MQTT_C_INCLUDE_DIRS="C:/paho.mqtt.c/src" ..

<���� ���丮>
C:\paho.mqtt.c\src
C:\paho.mqtt.cpp\src

<���̺귯�� ���丮 : ������ ����>
C:\paho.mqtt.c\build\src\Release
C:\paho.mqtt.cpp\build\src\Release

<Linker �� Input : ������ ����>
paho-mqtt3a.lib
paho-mqtt3c.lib
paho-mqttpp3-static.lib

<dll ����>
Project -> Properties -> Configuration Properties -> Debugging -> Environment ���ٰ�

PATH=C:\paho.mqtt.c\build\src\Release;
%PATH%;

<MQTT���̵�>
https://mosquitto.org/download/ ���� mosquitto ����(���Ŀ) �� ��ġ�Ѵ�.
C:\Program Files\mosquitto �� �ý��� ������ Path �� �����Ѵ�.
�۾������� -> ���� -> mosquitto �� ��Ŭ���ϰ� '����'
cmd ����
mosquitto -p ��Ʈ��ȣ
�� �Է��Ͽ� ���Ŀ�� �����Ѵ�.
C++ �Ǵ� Python�� Ŭ���̾�Ʈ �ڵ带 �����Ͽ� �����Ѵ�.
���Ŀ�� �⺻ ��Ʈ�� 1883

<MQTT IP����>
C:\Program Files\mosquitto\mosquitto.conf
������ ��� �Ʒ� �α����� �����ؾ� IP�� ������ �����ϴ� (���ϸ� localhost �� ����)

<listener ��Ʈ�Ҵ� �� �ּ�����(#listener �κи� ����)>
# listener port-number [ip address/host name/unix socket path]
listener 1883

<allow_anonymous �ּ� ���� �� false�� true�� ���� (#allow_anonymous false �κи� ����)>
# Defaults to false, unless there are no listeners defined in the configuration
# file, in which case it is set to true, but connections are only allowed from
# the local machine.
allow_anonymous true

<���� �� mosquitto �� ���񽺿��� �ٽ� ���� �Ѵ�>
*/

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
