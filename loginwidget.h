#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void GetLoginAndId(QString&, uint&, QString&);

signals:
    void SendWidgetChangeSignal();

private slots:
    void OnRegisterButtonClick();
    void OnLoginButtonClick();
    void OnCheckBoxStateChanged(int);

private:
    Ui::LoginWidget *ui;
    QString login;
    uint    userId;
    QString name;
};

#endif // LOGINWIDGET_H
