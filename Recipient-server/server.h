#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QMainWindow
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();

private slots:

    void onFindPressed();
    void onStartPressed();
    void newUser();
    void readyRead();
    void messageReceived(QByteArray msg);

private:
    Ui::Server *ui;
    QString folderPath;
    QTcpServer *tcpServer;
    int server_status;
    QMap<int,QTcpSocket *> SClients;
    QVector <QTcpSocket *> m_clients;

    void log(QString msg) { qDebug() << "[Server]: " << msg;}
    void err(QString msg) { qDebug() << "ERROR "  + msg; }



};
#endif // SERVER_H
