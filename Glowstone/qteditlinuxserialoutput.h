#ifndef QTEDITLINUXSERIALOUTPUT_H
#define QTEDITLINUXSERIALOUTPUT_H

#include "ioifmanager.h"
#include "linuxserialoutput.h"
#include "basetypes.h"

#include <QDialog>
#include <QPushButton>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

namespace Ui {
class EditLinuxSerialOutput;
}

class qtEditLinuxSerialOutput : public QDialog
{
    Q_OBJECT

public:
    explicit qtEditLinuxSerialOutput(QWidget *parent = nullptr);
    ~qtEditLinuxSerialOutput();
    void trigger(int id, ioif_attr attributes);
    ioifManager * ioif_manager;

private slots:
    void on_EditLinuxSerialOutput_accepted();
    void on_list_itemSelectionChanged();

private:
    void scanForDevices(std::string selected_device="");

    int id;
    QPushButton * OKButton;
    Ui::EditLinuxSerialOutput *ui;
    std::vector<std::string> list_entries;
    const std::filesystem::path devpath{"/dev"};
};

#endif // QTEDITLINUXSERIALOUTPUT_H
