#include "server.h"
#include "ui_server.h"


Server::Server(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Server)
{
    ui->setupUi(this);

    connect (ui->b_select, &QPushButton::clicked, this, &Server::onFindPressed);
    connect (ui->b_start, &QPushButton::clicked, this, &Server::onStartPressed);
}

Server::~Server()
{
    delete ui;
}

void Server::onFindPressed()
{
    folderPath = QFileDialog::getExistingDirectory(this, "Select a folder...", QDir::homePath());
    ui->e_path->setText(folderPath);
}

void Server::onStartPressed()
{
    tcpServer = new QTcpServer(this);

    connect(tcpServer, &QTcpServer::newConnection, this, &Server::newUser);

    if (tcpServer->listen(QHostAddress::Any, 33333)) {
        server_status=1;
        log ("Server started at " + QString::number(33333));
        qDebug() << tcpServer->isListening() << "TCPSocket listen on port " + QString::number(33333);
        ui->l_serverStatus->setText("Server started at " + QString::number(33333));
    } else {
        log ("Server crashed!");
        ui->l_serverStatus->setText(tcpServer->errorString());
        log (tcpServer->errorString());
    }
}

void Server::newUser()
{
    if(server_status == 1){
        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();
        int idUserSocs = clientSocket->socketDescriptor();
        SClients[idUserSocs] = clientSocket;
        ui->l_serverStatus->setText("New connection! [" + clientSocket->localAddress().toString() + "]");
        log("New connection! [" + clientSocket->localAddress().toString() + "]");
        connect(SClients[idUserSocs], &QTcpSocket::readyRead, this, &Server::readyRead);
    }
}

void Server::readyRead()
{
    QTcpSocket *client = (QTcpSocket *)sender();

    QByteArray data = client->readAll();
    if (data.indexOf("c:::m") == 0) {
        log(data);
        messageReceived(data);
        return;
    }

    log(data);

    err("Command cannot be parsed");
}

void Server::messageReceived(QByteArray msg)
{
    msg.remove(0, QByteArray("c:::m").length());
    QByteArray data = msg;

    for (QTcpSocket *socket : m_clients) {
        socket->write(data);
    }
}



