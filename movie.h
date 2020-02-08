#ifndef MOVIE_H
#define MOVIE_H

#include <QWidget>

namespace Ui {
class Movie;
}

class Movie : public QWidget
{
    Q_OBJECT

public:
    explicit Movie(QWidget *parent = nullptr, QString desc=QString(), QString pathToImage=QString(), int id=-1 );
    ~Movie();
    void SetItemToCombo(QString h);
    int GetId();
    QString GetCurrentHour();
    QString GetCurrentDate();
    void SetState(bool);
    void SetFirstItem();

signals:
    void SendButtonSignal( int );

private slots:
    void on_pushButton_clicked();
    void onDataComboBoxChanged( int );

private:
    Ui::Movie *ui;
    int m_id;
};

#endif // MOVIE_H
