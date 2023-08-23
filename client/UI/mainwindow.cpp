#include "mainwindow.h"
#include "Network/servercommunication.h"
#include "broadcast.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint
                   | Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_m_connect_qp_clicked()
{
    QString serverIP = ui->m_ip_le->text();
    QString serverPort = ui->m_port_le->text();
    int port = serverPort.toInt();

    QHostAddress address(serverIP);
    bool isIPValid = address.toIPv4Address() != 0; // Проверяем правильность IP-адреса
    bool isPortValid = port > 0 && port <= 65535; // Проверяем правильность порта
    qDebug() << address << " " << port;

    if (isIPValid && isPortValid) {
        MessageHandler socket(this, address, port);

        if (socket.isConnectedToServer()) {
            QMessageBox::information(this,
                                     "Success",
                                     "Connection to the server has been successful.");
            Broadcast *window = new Broadcast(address, port);
            window->show();
            close();
        } else {
            QMessageBox::critical(
                this,
                "Error",
                "Failed to connect to the server. Please check the IP address and port.");
        }
    } else {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid IP address and port.");
    }
}

void MainWindow::on_m_joke_qp_clicked()
{
    QMessageBox::information(nullptr, "Additional information", "I'm to lazy to do it workable.");
}
