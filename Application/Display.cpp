#include "Display.h"
#include "ui_display.h"

namespace app {

Display::Display(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Display)
{
    ui->setupUi(this);

    connect(ui->launchButton, &QPushButton::clicked,
            this, &Display::launchButtonClicked);
}

Display::~Display()
{
    delete ui;
}

QString Display::getAddress() const
{
    return ui->addressEdit->text();
}

QString Display::getPort() const
{
    return ui->portEdit->text();
}

QString app::Display::getLogin() const
{
    return ui->loginEdit->text();
}

QString app::Display::getPassword() const
{
    return ui->passwordEdit->text();
}

void Display::setStatus(QString status)
{
    ui->statusLable->setText(status);
}

void Display::dissableLaunchButton()
{
    ui->launchButton->setEnabled(false);
}

void Display::enableLaunchButton()
{
    ui->launchButton->setEnabled(true);
}

}
