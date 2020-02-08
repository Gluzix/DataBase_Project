#ifndef USERWIDGET_H
#define USERWIDGET_H
#include "bookwidget.h"
#include <QWidget>

namespace Ui {
class UserWidget;
}

class UserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UserWidget(QWidget *parent = nullptr );
    ~UserWidget();

    void SetInfo(QString name, QString login, int id );

public slots:
    void RemoveReservation( int id );

signals:
    void SendWidgetChangeSignal();

private slots:
    void OnLogoutButtonClick();

private:
    Ui::UserWidget *ui;
    QVector<BookWidget*> bookWidgetContainer;

};

#endif // USERWIDGET_H
