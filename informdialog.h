#ifndef INFORMDIALOG_H
#define INFORMDIALOG_H

#include <QDialog>

namespace Ui {
class InformDialog;
}

class InformDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InformDialog(QDialog *parent = nullptr, QString header=QString(), QString content=QString());
    ~InformDialog();

static void ExecInformDialog(QString, QString);

private slots:
    void OnConfirmButtonClick();

private:
    Ui::InformDialog *ui;
};

#endif // INFORMDIALOG_H
