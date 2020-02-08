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
    void SetBookId( int );
    void SetInfo( QString );
    int returnBookId();

private:
    Ui::BookWidget *ui;
    int m_BookId;
};

#endif // BOOKWIDGET_H
