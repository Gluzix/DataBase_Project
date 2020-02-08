#include "movie.h"
#include "ui_movie.h"
#include "informdialog.h"
#include <QtSql>
#include <QSqlQuery>

Movie::Movie( QWidget *parent, QString desc, QString pathToImage, int id, QVector<QString> dates, QVector<QString> hours ) :
    QWidget(parent),
    ui(new Ui::Movie), m_id(id)
{
    ui->setupUi(this);
    ui->image->setStyleSheet(pathToImage);
    ui->description->setText(desc);
    connect(ui->dateBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onDataComboBoxChanged(int)));
}

Movie::~Movie()
{
    delete ui;
}

void Movie::SetItemToCombo(QString h)
{
    ui->dateBox->blockSignals(true);
    ui->dateBox->addItem(h);
    ui->dateBox->blockSignals(false);
}

int Movie::GetId()
{
    return m_id;
}

QString Movie::GetCurrentHour()
{
    return ui->hourBox->currentText();
}

void Movie::SetState( bool state )
{
    ui->hourBox->setEnabled(state);
    ui->pushButton->setEnabled(state);
}

void Movie::on_pushButton_clicked()
{
    emit SendButtonSignal( m_id );
}

void Movie::onDataComboBoxChanged(int index)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./../DataBaseProject/projekt.db");
    QSqlQuery query;

    QString date = ui->dateBox->currentText();

    if(db.open())
    {
        if( !query.exec( "SELECT DISTINCT GodzinaSeansu FROM Terminarz t "
                        "INNER JOIN DataTerminarz dt ON t.IdTerminarz = dt.IdTerminarz "
                        "WHERE Data='"+date+"'" ))
        {
            InformDialog::ExecInformDialog("Error", query.lastError().text());
        }
        else
        {
            while( query.next() )
            {
                ui->hourBox->addItem(query.value("GodzinaSeansu").toString());
            }
        }
        db.close();
    }
}

