#include <unistd.h>

#include "gui/gui.h"
#include "common/data.h"

int main(int argc, char **argv) {
    // Launch the main GUI
    DataManager::SetDefaultValues();
    //sleep(3);
    gui_init();
    gui_loadResources();
    gui_start();
    return 0;
}
