#include "ui.h"

int Menu::
menu_choice()
{
  int choice = 0;
  cout 
    << "\n0: Quit\n"
    << "1: Integer Set \n"
    << "2: Custom Set\n"
    << "\nChoice > ";

  cin >> choice; cin.ignore();

  return choice;
}

int Menu::
integer_set()
{
  using std::isdigit;
  Set set;
  int start, end, set_ret = 0;

  cout << "\nProvide integer range from: ";
  cin >> start; cin.ignore();
  cout << "to: ";
  cin >> end; cin.ignore();

  if(!isdigit(start) || !isdigit(end))
  {
    cout << "\nEntry contains non-integers.";
    return 0;
  }
  set_ret = set.create_set(start, end);

  cout << "\nNew set, cardinality " << set_ret << endl;
  set.display();
  cout << "\nPress ENTER to continue.";
  cin.ignore();
  return 1;
}

int Menu::
custom_set()
{
  Set set;
  char entry[ENTRYMAX] = {};
  int set_ret = 0;

  cout << "\nEnter elements > ";
  cin.get(entry, ENTRYMAX, '\n'); cin.ignore(100, '\n');
  cout << "ENTRY: " << entry << endl;
  set_ret = set.create_set(entry);

  if(set_ret > ELMMAX) 
    cout << "\nExceeds max element length: \n" << set_ret;
  else
  {
    cout << "\nNew set, cardinality " << set_ret << endl;
    set.display();
  }
  cout << "\nPress ENTER to continue.";
  cin.ignore();
  return 1;
}

