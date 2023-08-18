#pragma once
#include <QtNetwork>

class MessageHandler : public QObject
{
    Q_OBJECT
private:
    QString m_ip;
    int m_port;
    QUdpSocket *m_udpSocket;

public:
    explicit MessageHandler(QObject *parent, const QString &ip, int port);
    void sendPacket(const QByteArray &packet);
    void processPendingDatagrams();
    virtual ~MessageHandler();
};
