#include "broadcast.h"
#include "ui_broadcast.h"

Broadcast::Broadcast(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Broadcast)
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint
                   | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);
}

Broadcast::~Broadcast()
{
    delete ui;
}

void Broadcast::on_m_quit_clicked()
{
    close();
}

void Broadcast::on_m_assistance_clicked()
{
    QMessageBox::information(nullptr,
                             "Assistance",
                             "X - coordinate (6 bits): 0 - 63 int\n"
                             "Y - coordinate (6 bits): -32 - 31 unint\n"
                             "V - speed (8 bits): 0 - 255 int\n"
                             "M - operating mode (2 bits): 0 - 3 int\n"
                             "S - condition (2 bits): 0 - 3 int\n"
                             "A - boost (8 bits): -12.7 - 12.8 double\n"
                             "P - power (8 bits): 0 - 130 int\n"
                             "R - reserve (16 bits)");
}
