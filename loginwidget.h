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

signals:
    void SendWidgetChangeSignal(QString);

private slots:
    void OnRegisterButtonClick();
    void OnLoginButtonClick();
    void OnCheckBoxStateChanged(int);

private:
    Ui::LoginWidget *ui;
};

#endif // LOGINWIDGET_H
