#include "GameObject.h"

namespace Network {

CGameObject::CGameObject(ip::address serverAddress, unsigned short usServerPort, std::string stName) :
m_serverAddress(serverAddress), m_usServerPort(usServerPort), m_stName(stName) {
}

CGameObject::~CGameObject() {
}

std::string CGameObject::getServerIP() {
	return m_serverAddress.to_string();
}

unsigned short CGameObject::getServerPort() {
	return m_usServerPort;
}

std::string CGameObject::getName() {
	return m_stName;
}

}