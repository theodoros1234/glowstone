#ifndef QTMAINWINDOW_H
#define QTMAINWINDOW_H

#include "basetypes.h"
#include "qtnewoutputdialog.h"
#include "ioifmanager.h"
#include "qtoifuiedithandler.h"

#include <string>
#include <vector>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class qtMainWindow : public QMainWindow {
    Q_OBJECT

public:
    qtMainWindow(QWidget *parent = nullptr);
    ~qtMainWindow();
    void setup();
    ioifManager * ioif_manager;
    void addOutput(std::string name, std::string info);
    void editOutput(int row, std::string name, std::string info);
    void removeOutput(int row);

private slots:
    void on_outputAddButton_clicked();
    void on_outputList_itemSelectionChanged();
    void on_outputRemoveButton_clicked();

    void on_outputEditButton_clicked();

private:
    Ui::MainWindow *ui;
    qtNewOutputDialog new_output_dialog;
    qtOifUiEditHandler oif_edit_handler;
    void outputButtonsSetEnabled(bool state);
};
#endif // QTMAINWINDOW_H
