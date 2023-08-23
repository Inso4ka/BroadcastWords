#include "servercommunication.h"

MessageHandler::MessageHandler(QObject *parent, const QHostAddress &ip, quint16 port)
    : QObject(parent)
    , m_ip(ip)
    , m_port(port)
{
    qDebug() << m_ip << " " << m_port;
    m_udpSocket = new QUdpSocket(this);
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &MessageHandler::receiveMessage);
}

void MessageHandler::sendPacket(const QByteArray &packet)
{
    if (m_ip.isNull() || m_port == 0) {
        qDebug() << "IP address and/or port not set.";
        return;
    }

    m_udpSocket->writeDatagram(packet, m_ip, m_port);
}

void MessageHandler::receiveMessage()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        m_udpSocket->readDatagram(datagram.data(), datagram.size());

        qDebug() << "Received message from server:" << datagram;
    }
}
bool MessageHandler::isConnectedToServer() const
{
    return m_udpSocket->state() == QAbstractSocket::UnconnectedState;
}

MessageHandler::~MessageHandler()
{
    if (m_udpSocket) {
        m_udpSocket->close();
        delete m_udpSocket;
    }
}
