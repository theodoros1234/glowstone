#ifndef NEWOUTPUTDIALOG_H
#define NEWOUTPUTDIALOG_H

#include "ioifmanager.h"
#include "oifuiedithandler.h"
#include <QDialog>

namespace Ui {
class NewOutputDialog;
}

class NewOutputDialog : public QDialog {
    Q_OBJECT

public:
    explicit NewOutputDialog(QWidget *parent = nullptr);
    ~NewOutputDialog();
    void populate(std::vector< std::pair<int,const char *> > &devlist);
    oifUiEditHandler * oif_edit_handler;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewOutputDialog *ui;
};

#endif // NEWOUTPUTDIALOG_H
