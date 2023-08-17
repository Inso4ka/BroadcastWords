#include "broadcast.h"
#include "ui_broadcast.h"

Broadcast::Broadcast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Broadcast)
{
    ui->setupUi(this);
}

Broadcast::~Broadcast()
{
    delete ui;
}
