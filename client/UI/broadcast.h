#ifndef BROADCAST_H
#define BROADCAST_H

#include <QDialog>

namespace Ui {
class Broadcast;
}

class Broadcast : public QDialog
{
    Q_OBJECT

public:
    explicit Broadcast(QWidget *parent = nullptr);
    ~Broadcast();

private:
    Ui::Broadcast *ui;
};

#endif // BROADCAST_H
