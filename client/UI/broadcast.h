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
    explicit Broadcast(const QString &serverIP, int port, QWidget *parent = nullptr);
    ~Broadcast();

private slots:
    void on_m_quit_clicked();

    void on_m_assistance_clicked();

    void on_m_send_clicked();

private:
    Ui::Broadcast *ui;
    QString m_ip;
    int m_port;
};

#endif // BROADCAST_H
