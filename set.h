#include <vector>
using std::vector;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cstring>
using std::strlen;
using std::strcmp;

#define ELMMAX 91 
#define ENTRYMAX 151 

class Elem
{
  public:
    Elem();
    Elem(char to_add[]);
    Elem(int);
    ~Elem();

    void disp();
    void make_elm(char[]);
  private:
    char* elm;
    int int_elm;
};

struct Node
{
  Node();
  Node(char[]);
  ~Node();
  bool is_match(char[]);
  Node* next;
  char* elm;
};

class Set
{
  public:
    Set();
    ~Set();
    int create_set(char[]); // For custom set
    int create_set(int, int); // For integer set
    void add_to_set(char[]);
    void display();
    //virtual int subtract_from_set(char[]);

  private:
    vector<Elem*> set_vx = {};
    Node* tally[ELMMAX];
    int cardinality;
    void destroy_nodes(Node* head);
    void destroy_elems();

    int add_to_tally(char[], int);
    int add_to_tally(char[], Node* &);
    int check_elem_len(char[]);
    int hasher(char[]);
};
