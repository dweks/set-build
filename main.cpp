#include "ui.h"

int main()
{
  Menu menu;
  bool done = false;
  
  do
  {
    switch(menu.menu_choice())
    {
      case 0: done = true; break;
      case 1: menu.integer_set(); break;
      case 2: menu.custom_set(); break;
    }
  }while(!done);

  cout << endl;
  return 0;
}
