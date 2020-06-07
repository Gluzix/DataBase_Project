#include "bookwidget.h"
#include "ui_bookwidget.h"

BookWidget::BookWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BookWidget)
{
    ui->setupUi(this);
    connect(ui->removeButton, SIGNAL(clicked()), SLOT(OnRemoveButtonClick()));
}

BookWidget::~BookWidget()
{
    delete ui;
}

void BookWidget::SetID(int id)
{
    m_BookId = id;
}

void BookWidget::SetDesc(QString info)
{
    ui->reservationInfo->setText(info);
}

int BookWidget::GetID()
{
    return m_BookId;
}

void BookWidget::OnRemoveButtonClick()
{
    emit RemoveCurrentWidget( m_BookId );
}
