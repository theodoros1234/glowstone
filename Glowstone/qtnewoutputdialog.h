#ifndef QTNEWOUTPUTDIALOG_H
#define QTNEWOUTPUTDIALOG_H

#include "qtoifuiedithandler.h"
#include <QPushButton>
#include <QDialog>

namespace Ui {
class NewOutputDialog;
}

class qtNewOutputDialog : public QDialog {
    Q_OBJECT

public:
    explicit qtNewOutputDialog(QWidget *parent = nullptr);
    ~qtNewOutputDialog();
    void populate(std::vector< std::pair<int,const char *> > &devlist);
    qtOifUiEditHandler * oif_edit_handler;

private slots:
    void on_buttonBox_accepted();

    void on_list_itemSelectionChanged();

private:
    Ui::NewOutputDialog *ui;
    QPushButton * OKButton;
};

#endif // QTNEWOUTPUTDIALOG_H
