#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include <QWidget>

namespace Ui {
class BookWidget;
}

class BookWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookWidget(QWidget *parent = nullptr);
    ~BookWidget();
    void    SetID( int );
    void    SetDesc( QString );
    int     GetID();

signals:
    void    RemoveCurrentWidget( int id );

private slots:
    void    OnRemoveButtonClick();

private:
    Ui::BookWidget      *ui;
    int                 m_BookId;
};

#endif // BOOKWIDGET_H
