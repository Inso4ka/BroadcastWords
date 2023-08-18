#include "servercommunication.h"

MessageHandler::MessageHandler(QObject *parent, const QString &ip, int port)
    : QObject(parent)
    , m_ip{ip}
    , m_port{port}
{
    m_udpSocket = new QUdpSocket(this);
    bool bindSuccess = m_udpSocket->bind(QHostAddress::AnyIPv4, m_port);
    if (!bindSuccess) {
        qDebug() << "Failed to bind socket to port." << m_port;
    }
    connect(m_udpSocket, &QUdpSocket::readyRead, this, &MessageHandler::processPendingDatagrams);
}

void MessageHandler::sendPacket(const QByteArray &packet)
{
    if (m_ip.isEmpty() || m_port == 0) {
        qDebug() << "IP address and/or port not set.";
        return;
    }

    m_udpSocket->writeDatagram(packet, QHostAddress(m_ip), m_port);
}

void MessageHandler::processPendingDatagrams()
{
    while (m_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        qDebug() << "Received response from the server:" << datagram;
    }
}

MessageHandler::~MessageHandler() = default;
