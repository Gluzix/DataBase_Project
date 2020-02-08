#include "bookwidget.h"
#include "ui_bookwidget.h"

BookWidget::BookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWidget)
{
    ui->setupUi(this);
}

BookWidget::~BookWidget()
{
    delete ui;
}

void BookWidget::SetBookId(int id)
{
    m_BookId = id;
}

void BookWidget::SetInfo(QString info)
{
    ui->reservationInfo->setText(info);
}

int BookWidget::returnBookId()
{
    return m_BookId;
}
