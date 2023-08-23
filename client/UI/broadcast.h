#ifndef BROADCAST_H
#define BROADCAST_H

#include <QDialog>
#include <QMessageBox>
#include <QUdpSocket>

namespace Ui {
class Broadcast;
}

class Broadcast : public QDialog
{
    Q_OBJECT

public:
    explicit Broadcast(const QHostAddress &serverIP, quint16 port, QWidget *parent = nullptr);
    ~Broadcast();

private slots:
    void on_m_quit_clicked();

    void on_m_assistance_clicked();

    void on_m_send_clicked();

private:
    Ui::Broadcast *ui;
    QHostAddress m_ip;
    quint16 m_port;
};

#endif // BROADCAST_H
