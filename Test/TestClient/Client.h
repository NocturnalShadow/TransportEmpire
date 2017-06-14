#pragma once

#include <QUrl>
#include <QString>
#include <QObject>
#include <QWebSocket>
#include <QSignalSpy>

namespace test {

class Client : public QObject
{
    Q_OBJECT
private:
    QWebSocket socket;
    QSignalSpy responseQueue;

public:
    Client(QObject* parent = nullptr);

public:
    void connect(QUrl url);
    void sendMessage(QString message);
    QString takeFirstMessage(int timeout = 500);

signals:
    void disconnected();
    void textMessageReceived(QString message);

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);

};

} // namespace test
