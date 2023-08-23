#include "broadcast.h"
#include <QDebug>
#include "Network/servercommunication.h"
#include "ui_broadcast.h"

Broadcast::Broadcast(const QHostAddress &serverIP, quint16 port, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Broadcast)
    , m_ip(serverIP)
    , m_port(port)
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

void Broadcast::on_m_send_clicked()
{
    QByteArray packet;                                 // Создаем пустой пакет
    QDataStream stream(&packet, QIODevice::WriteOnly); // Создаем поток данных для записи в пакет

    // Записываем данные в пакет в соответствии с указанными требованиями
    quint16 word1 = 0;
    quint16 word2 = 0;
    quint16 word3 = 0;
    quint16 word4 = 0;

    // Запись в 1 слово
    quint8 word1_part1 = ui->m_x6->text()
                             .toUInt(); // Некоторое беззнаковое значение от 0 до 63 (для примера)
    qint8 word1_part2 = ui->m_y6->text()
                            .toInt(); // Некоторое знаковое значение от -32 до 31 (для примера)
    word1 |= word1_part1; // Записываем младшие 6 битов в биты 5-0
    word1 |= (static_cast<quint16>(word1_part2 & 0x3F) << 8);

    /*qDebug() << word1 << "\n";
    std::bitset<16> bits(word1);
    for (int i = 15; i >= 0; i--) {
        qDebug() << bits[i];
    }
    qDebug() << "\n";*/

    // Запись во 2 слово
    quint8 word2_part1 = ui->m_v8->text().toUInt(); // Значение от 0 до 255 (для примера)
    quint8 word2_part2 = ui->m_m2->text().toUInt(); // Значение от 0 до 3 (для примера)
    quint8 word2_part3 = ui->m_s2->text().toUInt(); // Значение от 0 до 3 (для примера)
    word2 |= word2_part1;        // Записываем младшие 8 битов в биты 7-0
    word2 |= (word2_part2 << 8); // Записываем младшие 2 бита в биты 9-8
    word2 |= (word2_part3 << 12); // Записываем младшие 2 бита в биты 12-13

    // Запись в 3 слово
    float word3_part1
        = ui->m_a8->text()
              .toFloat(); // Значение от -12.7 до 12.8 (для примера, преобразуем в фиксированную точку)
    quint8 word3_part2 = ui->m_p8->text().toUInt(); // Значение от 0 до 130 (для примера)
    qint16 fixed_point_value = static_cast<qint16>(
        word3_part1 * 10); // Преобразуем в фиксированную точку (умножаем на 10)
    word3 |= (word3_part2 & 0xFF); // Записываем младшие 8 битов в биты 8-15
    word3 |= (fixed_point_value << 8); // Записываем младшие 8 битов в биты 0-7

    quint8 numBits = 16; // Количество битов для записи

    if (!ui->m_unsigned->isChecked()) {
        qint32 signedValue = ui->m_r16->text().toInt();
        if (numBits < 16) {
            signedValue &= (1 << numBits) - 1; // Ограничиваем число указанным количеством битов
        }
        word4 = static_cast<quint16>(signedValue); // Записываем значение в 4 слово
    } else {
        quint32 unsignedValue = ui->m_r16->text().toUInt();
        if (numBits < 16) {
            unsignedValue &= (1 << numBits) - 1; // Ограничиваем число указанным количеством битов
        }
        word4 = static_cast<quint16>(unsignedValue); // Записываем значение в 4 слово
    }

    // Записываем слова данных в пакет
    stream << word1 << word2 << word3 << word4;
    MessageHandler message(nullptr, m_ip, m_port);
    message.sendPacket(packet);
}
