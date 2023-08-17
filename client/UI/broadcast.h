#ifndef BROADCAST_H
#define BROADCAST_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class Broadcast;
}

class Broadcast : public QDialog
{
    Q_OBJECT

public:
    explicit Broadcast(QWidget *parent = nullptr);
    ~Broadcast();

private slots:
    void on_m_quit_clicked();

    void on_m_assistance_clicked();

private:
    Ui::Broadcast *ui;
};

#endif // BROADCAST_H
