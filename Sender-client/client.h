#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>

QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = nullptr);
    ~Client();

private:
    Ui::Client *ui;
    QTcpSocket *mSocket;
    QString filePath;

private slots:
    void onFindPressed();
    void onSendPressed();

    void connected();
    void disconnected();
    void doConnection();


//    void send();
//    void received();

};
#endif // CLIENT_H
