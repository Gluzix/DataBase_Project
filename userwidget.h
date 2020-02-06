#ifndef USERWIDGET_H
#define USERWIDGET_H
#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr);
    ~UserWidget();

    void SetName(QString name );

signals:
    void SendWidgetChangeSignal();

private slots:
    void OnLogoutButtonClick();

private:
    Ui::UserWidget *ui;

};

#endif // USERWIDGET_H
