#include "pch.h"
#include "Session.h"
#include "RecvBuffer.h"
/*-------------------
	Session
--------------------*/
Session::Session() : m_recvBuffer(BUFFER_SIZE,this)
{
	m_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
}

Session::~Session()
{
	::closesocket(m_socket);
}

void Session::Send(SendBuffer* sendBuffer)
{
	::send(m_socket, reinterpret_cast<char*>(sendBuffer->Buffer()), sendBuffer->WriteSize(), 0);
}

bool Session::Recv()
{
	return m_recvBuffer.OnRead();
}

bool Session::Connect()
{
	m_connected = true;

	// ÄÁÅÙÃ÷ ÄÚµå¿¡¼­ »ç¿ë
	OnConnected();

	return true;
}

void Session::Disconnect(const WCHAR* cause)
{
}

/*-------------------
	PacketSession
--------------------*/
PacketSession::PacketSession()
{
}

PacketSession::~PacketSession()
{
}

int32 PacketSession::OnRecv(BYTE* buffer, int32 len)
{
	int32 processLen = 0;

	while (true) 
	{
		int32 dataSize = len - processLen;

		if (dataSize < sizeof(PacketHeader))
			break;

		PacketHeader header = *(reinterpret_cast<PacketHeader*>(buffer));
		
		if (dataSize < header.size)
			break;

		OnRecvPacket(&buffer[processLen], header.size);

		processLen += header.size;
	}

	return processLen;
}
