#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);

    mSocket = new QTcpSocket(this);

    connect (ui->bFind, &QPushButton::clicked, this, &Client::onFindPressed);
    connect (ui->bSend, &QPushButton::clicked, this, &Client::onSendPressed);
    connect (ui->bConnect, &QPushButton::clicked, this, &Client::doConnection);
    connect (mSocket, &QTcpSocket::connected, this, &Client::connected);
    connect (mSocket, &QTcpSocket::disconnected, this, &Client::disconnected);
    //connect (mSocket, &QTcpSocket::readyRead, this, &Client::received);


}

Client::~Client()
{
    delete ui;
}

void Client::onFindPressed()
{
    filePath = QFileDialog::getOpenFileName(this, "Select a file to send...", QDir::homePath());
    ui->ePath->setText(filePath.remove(0, filePath.lastIndexOf("/") + 1));
}

void Client::onSendPressed()
{
    mSocket->write(QString("c:::m" + ui->te_input->toPlainText()).toUtf8());
}


void Client::connected()
{
    ui->stackedWidget->setCurrentIndex(1);

}

void Client::disconnected()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Client::doConnection()
{
    QString host = ui->eIp->text();
    int port = ui->sPort->value();
    mSocket->connectToHost(host, port);
}




//void Client::onConnected()
//{
//    QByteArray block;
//    QDataStream stream(&block, QIODevice::WriteOnly);
//    stream.setVersion(QDataStream::Qt_5_0);
//    QFile file(filePath);
//    file.open(QIODevice::ReadOnly);
//    QByteArray buf = file.readAll();
//    stream << quint64(file.size());
//    stream << buf;
//    mSocket->write(block);
//    mSocket->flush();
//}
