#ifndef QTEDITLINUXSERIALOUTPUT_H
#define QTEDITLINUXSERIALOUTPUT_H

#include <QDialog>
#include "ioifmanager.h"

#include <filesystem>

namespace Ui {
class EditLinuxSerialOutput;
}

class qtEditLinuxSerialOutput : public QDialog
{
    Q_OBJECT

public:
    explicit qtEditLinuxSerialOutput(QWidget *parent = nullptr);
    ~qtEditLinuxSerialOutput();
    void trigger(linuxSerialOutput *item = nullptr);
    ioifManager * ioif_manager;

private:
    void scanForDevices(std::string selected_device="");
    Ui::EditLinuxSerialOutput *ui;

    const std::filesystem::path devpath{"/dev"};
};

#endif // QTEDITLINUXSERIALOUTPUT_H
