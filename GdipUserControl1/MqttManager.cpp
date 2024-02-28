/*
<라이브러리 빌드 방법(Release x64)>
Git Bash 를 설치한다.
CMake를 설치한다.
Visual Studio를 설치한다 (Visual Studio 17 2022, Visual Studio 16 2019 등)
C드라이브에 git bash를 관리자 권한으로 실행하고
git clone https://github.com/eclipse/paho.mqtt.c.git
git clone https://github.com/eclipse/paho.mqtt.cpp.git
를 각각 입력하여 프로젝트를 설치한다.

CMake를 통해 sln 파일을 생성한다.
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

만약, 64비트로 빌드하고 32비트도 빌드하고자 하면 이전 빌드 파일과 CMake 캐시를 제거해야한다.
cd C:/paho.mqtt.c/build
rm -rf CMakeCache.txt CMakeFiles/
cmake -G "Visual Studio 17 2022" -A Win32 ..

cd C:/paho.mqtt.cpp/build
rm -rf CMakeCache.txt CMakeFiles/
cmake -G "Visual Studio 17 2022" -A Win32 -DPAHO_MQTT_C_LIBRARIES="C:/paho.mqtt.c/build/src/Release" -DPAHO_MQTT_C_INCLUDE_DIRS="C:/paho.mqtt.c/src" ..

<포함 디렉토리>
C:\paho.mqtt.c\src
C:\paho.mqtt.cpp\src

<라이브러리 디렉토리 : 릴리즈 기준>
C:\paho.mqtt.c\build\src\Release
C:\paho.mqtt.cpp\build\src\Release

<Linker 의 Input : 릴리즈 기준>
paho-mqtt3a.lib
paho-mqtt3c.lib
paho-mqttpp3-static.lib

<dll 설정>
Project -> Properties -> Configuration Properties -> Debugging -> Environment 에다가

PATH=C:\paho.mqtt.c\build\src\Release;
%PATH%;

<MQTT가이드>
https://mosquitto.org/download/ 에서 mosquitto 서버(브로커) 를 설치한다.
C:\Program Files\mosquitto 를 시스템 변수의 Path 에 저장한다.
작업관리자 -> 서비스 -> mosquitto 를 우클릭하고 '시작'
cmd 에서
mosquitto -p 포트번호
를 입력하여 브로커를 실행한다.
C++ 또는 Python의 클라이언트 코드를 실행하여 연결한다.
브로커의 기본 포트는 1883

<MQTT IP셋팅>
C:\Program Files\mosquitto\mosquitto.conf
파일을 열어서 아래 두군데를 수정해야 IP로 셋팅이 가능하다 (안하면 localhost 만 가능)

<listener 포트할당 후 주석해제(#listener 부분만 변경)>
# listener port-number [ip address/host name/unix socket path]
listener 1883

<allow_anonymous 주석 해제 후 false를 true로 변경 (#allow_anonymous false 부분만 변경)>
# Defaults to false, unless there are no listeners defined in the configuration
# file, in which case it is set to true, but connections are only allowed from
# the local machine.
allow_anonymous true

<저장 후 mosquitto 를 서비스에서 다시 시작 한다>
*/

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
