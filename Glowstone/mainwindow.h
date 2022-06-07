#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basetypes.h"
#include "newoutputdialog.h"
#include "ioifmanager.h"
#include "oifuiedithandler.h"

#include <string>
#include <vector>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setup();
    ioifManager * ioif_manager;
    void ioifUpdate(int a, int b);
    void addOutput(std::string name, std::string info);

private slots:
    void on_outputAddButton_clicked();

private:
    Ui::MainWindow *ui;
    NewOutputDialog new_output_dialog;
    oifUiEditHandler oif_edit_handler;
};
#endif // MAINWINDOW_H
