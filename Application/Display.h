#pragma once

#include <QWidget>

namespace Ui {
    class Display;
}

namespace app {

class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0);
    ~Display();

private:
    Ui::Display *ui;

signals:
    void launchButtonClicked();

public:
    QString getAddress()    const;
    QString getPort()       const;
    QString getLogin()      const;
    QString getPassword()   const;

    void setStatus(QString status);

    void dissableLaunchButton();
    void enableLaunchButton();
};

}
