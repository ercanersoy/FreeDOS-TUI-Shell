/*********************************
 * FreeDOS TUI Shell Source File *
 *********************************/

#include <fdostui.hpp>
#include <stdio.h>
#include <stdlib.h>

// Bar

window *bar = new window(0, 0, _video_cols, 3);
menubar *bar_menus= new menubar(0, 0, _video_cols, 1);

// File Manager

window *file_manager = new window(5, 6, 68, 15);
menubar *file_manager_menus= new menubar(0, 0, _video_cols, 1);

// Menu Functions

void application_file_manager(menuitem *, void *)
{
   file_manager->draw();
   return;
}

void application_edit(menuitem *, void *)
{
   system("EDIT");
   return;
}

void application_edlin(menuitem *, void *)
{
   system("EDLIN");
   return;
}

void reboot(menuitem *, void *)
{
   wm_deinit();
   system("FDAPM WARMBOOT");
   return;
}

void poweroff(menuitem *, void *)
{
   wm_deinit();
   system("FDAPM POWEROFF");
   return;
}

// Bar Menus

struct menuitem internal_applications_menu[] =
{
   {reinterpret_cast<unsigned char const*>("File Manager"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, application_file_manager, 0},
   {0}
};

struct menuitem dos_applications_menu[] =
{
   {reinterpret_cast<unsigned char const*>("EDIT"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, application_edit, 0},
   {reinterpret_cast<unsigned char const*>("EDLIN"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, application_edlin, 0},
   {0}
};

struct menuitem exit_menu[] =
{
   {reinterpret_cast<unsigned char const*>("Reboot"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, reboot, 0},
   {reinterpret_cast<unsigned char const*>("Power Off"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, poweroff, 0},
   {0}
};

struct menuitembar menus_of_bar[] =
{
   {reinterpret_cast<unsigned char const*>("Internal Apps"), 0, SCAN_NONE, internal_applications_menu},
   {reinterpret_cast<unsigned char const*>("DOS Apps"), 0, SCAN_NONE, dos_applications_menu},
   {reinterpret_cast<unsigned char const*>("Exit"), 0, SCAN_NONE, exit_menu},
   {0}
};

// File Manager Menus

struct menuitem file_menu[] =
{
   {reinterpret_cast<unsigned char const*>("Open"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, MENUITEM_SEPERATOR, 0, 0},
   {reinterpret_cast<unsigned char const*>("New Folder"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {0}
};

struct menuitem edit_menu[] =
{
   {reinterpret_cast<unsigned char const*>("Cut"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("Copy"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("Paste"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, MENUITEM_SEPERATOR, 0, 0},
   {reinterpret_cast<unsigned char const*>("Delete"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {0}
};

struct menuitem view_menu[] =
{
   {reinterpret_cast<unsigned char const*>("Refresh"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, MENUITEM_SEPERATOR, 0, 0},
   {reinterpret_cast<unsigned char const*>("Show Hidden Files"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, MENUITEM_CHECKBOX | MENUITEM_SEPERATOR, 0, 0},
   {reinterpret_cast<unsigned char const*>("Sort"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE,  MENUITEM_SUBMENU, 0, 0},
   {reinterpret_cast<unsigned char const*>("By Name"), MENUITEM_MNEMONIC_NONE, 0,  SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("By Size"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("By Type"), MENUITEM_MNEMONIC_NONE, 0,  SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("By Date"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {0},
   {0}
};

struct menuitem go_menu[] =
{
   {reinterpret_cast<unsigned char const*>("Back"), MENUITEM_MNEMONIC_NONE, 0,  SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("Foward"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {reinterpret_cast<unsigned char const*>("Up"), MENUITEM_MNEMONIC_NONE, 0, SCAN_NONE, 0, 0, 0},
   {0}
};
struct menuitembar menus_of_file_manager[] =
{
   {reinterpret_cast<unsigned char const*>("File"), 0, SCAN_NONE, file_menu},
   {reinterpret_cast<unsigned char const*>("Edit"), 0, SCAN_NONE, edit_menu},
   {reinterpret_cast<unsigned char const*>("View"), 0, SCAN_NONE, view_menu},
   {reinterpret_cast<unsigned char const*>("Go"), 0, SCAN_NONE, go_menu},
   {0}
};

// Main Function

int main(void)
{
   wm_error error= wm_init();

   if (error)
   {
      puts("Unable to initialze FDOSTUI subsystem.");
      return error;
   }

   // Bar

   wm_register_window(bar);
   bar->set_attributes(window::EMPTY);

   bar_menus->set_menu(menus_of_bar);

   bar->add(bar_menus);

   // File Manager

   wm_register_window(file_manager);
   file_manager->set_title((unsigned char *)"File Manager");

   file_manager_menus->set_menu(menus_of_file_manager);

   file_manager->add(file_manager_menus);

   // Draw bar
   
   wm_draw_widget(bar);
   
   // Run Window Manager

   wm_run();

   // Exit Window Manager

   wm_deinit();

   return 0;
}
