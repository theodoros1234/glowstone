#ifndef EDITLINUXSERIALOUTPUT_H
#define EDITLINUXSERIALOUTPUT_H

#include <QDialog>
#include "ioifmanager.h"

#include <filesystem>

namespace Ui {
class EditLinuxSerialOutput;
}

class EditLinuxSerialOutput : public QDialog
{
    Q_OBJECT

public:
    explicit EditLinuxSerialOutput(QWidget *parent = nullptr);
    ~EditLinuxSerialOutput();
    void trigger(linuxSerialOutput *item = nullptr);
    ioifManager * ioif_manager;

private:
    void scanForDevices(std::string selected_device="");
    Ui::EditLinuxSerialOutput *ui;

    const std::filesystem::path devpath{"/dev"};
};

#endif // EDITLINUXSERIALOUTPUT_H
