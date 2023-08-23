#pragma once
#include <QtNetwork>

class MessageHandler : public QObject
{
    Q_OBJECT
private:
    QHostAddress m_ip;
    quint16 m_port;
    QUdpSocket *m_udpSocket;

private slots:
    void receiveMessage();

public:
    explicit MessageHandler(QObject *parent, const QHostAddress &ip, quint16 port);
    void sendPacket(const QByteArray &packet);
    bool isConnectedToServer() const;
    virtual ~MessageHandler();
};
