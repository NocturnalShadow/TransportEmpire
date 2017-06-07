#pragma once

#include <QUrl>
#include <QString>
#include <QObject>
#include <QWebSocket>

namespace test {

class Client : public QObject
{
    Q_OBJECT
private:
    QWebSocket socket;

public:
    Client(const QUrl& url, QObject* parent = nullptr);

public:
    void sendRequest();

signals:
    void disconnected();

private slots:
    void onConnected();
    void onDisconnected();
    void onTextMessageReceived(QString message);
};

} // namespace test