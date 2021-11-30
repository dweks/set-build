#include "set.h"

////////////////////////////////////////////////// Node

Node::Node(): next(NULL), elm(NULL) { }
Node::~Node() { if(elm) { delete [] elm; elm = NULL; } }

Node::Node(char to_add[])
{
  elm = new char[strlen(to_add) + 1];
  strcpy(elm, to_add);
}


bool Node::
is_match(char to_check[])
{
  if(strcmp(to_check, elm) != 0)
    return false;
  return true;
}

////////////////////////////////////////////////// Elem

Elem::Elem(): elm(NULL) { }
Elem::Elem(char to_add[]) { make_elm(to_add); }
Elem::Elem(int to_add) { int_elm = to_add; elm = NULL; }
Elem::~Elem() { if(elm) { delete [] elm; elm = NULL; int_elm = 0; } }

void Elem:: disp() 
{ 
    ((elm) ? (cout << elm):(cout << int_elm));
}

void Elem::
make_elm(char cpy_from[])
{
  elm = new char[strlen(cpy_from) + 1];
  strcpy(elm, cpy_from);
}

////////////////////////////////////////////////// Set

Set::Set()
{
  set_vx = {}; cardinality = 0;
  for(int x = 0; x < ELMMAX; ++x)
    tally[x] = NULL;
}

Set::~Set()
{
  destroy_elems();
  set_vx = {};
  for(int i = 0; i < ELMMAX; ++i)
    destroy_nodes(tally[i]);
}

void Set::
destroy_nodes(Node* head)
{
  if(!head) return;
  destroy_nodes(head->next);
  delete head;
  head = NULL;
}

void Set::
destroy_elems()
{
  int i = 0;
  while(set_vx[i] != NULL)
  {
    delete set_vx[i]; 
    set_vx[i] = NULL;
  }
}

int Set::
create_set(char entry[])
{
  int check_len = check_elem_len(entry);
  if(check_len != 0) return check_len;
    
  char* parse = new char[strlen(entry) + 1];
  strcpy(parse, entry);

  for(int i = 0; parse[i] != '\0'; ++i)
  {
    if(parse[i] != ' ')
    {
      char temp_elm[ELMMAX] = {};
      int tmp_ix = 0;
      while(parse[i] != ' ' && parse[i] != '\0') 
      {
        temp_elm[tmp_ix] = parse[i];
        ++tmp_ix;
        ++i;
      }
      if(hasher(temp_elm) == 0)
        add_to_set(temp_elm);
    }
  }
  delete [] parse;
  parse = NULL;
  return cardinality;
}

int Set::
create_set(int start, int end)
{
  for(int i = start; i <= end; ++i)
  {
    set_vx.push_back(new Elem(i));
    ++cardinality;
  }
  return cardinality;
}

void Set::
add_to_set(char to_add[])
{
  set_vx.push_back(new Elem(to_add));
  ++cardinality;
}

void Set:: 
display()
{
  cout << "{";
  for(int i = 0; i < cardinality; ++i)
  {
    set_vx[i]->disp();
    if(i + 1 != cardinality)
      cout << ", ";
  }
  cout << "}\n";
}

int Set:: 
check_elem_len(char entry[])
{
  int len = strlen(entry);
  int ch_count = 0;

  for(int i = 0; i < len; ++i)
  {
    while(entry[i] != ' ' && entry[i] != '\0') 
    {
      ++ch_count;
      ++i;
    }
    if(ch_count > ELMMAX)
      return ch_count;
    else
      ch_count = 0;
  }

  return 0;
}

int Set::
hasher(char to_hash[])
{
  int hash = 0;
  int i = 0;
  int ix = 0;

  while(to_hash[i] != ' ' && to_hash[i] != '\0')
  {
    hash += (int)to_hash[i];
    ++i;
  }

  ix = hash % ELMMAX;
  return add_to_tally(to_hash, ix);
}

int Set:: 
add_to_tally(char to_add[], int ix)
{
  if(tally[ix] == NULL)
  {
    tally[ix] = new Node(to_add);
    return 0;
  }
  return add_to_tally(to_add, tally[ix]);
}

int Set:: 
add_to_tally(char to_add[], Node* & head)
{
  int ret = 0;
  if(!head) return 0;
  if(head->is_match(to_add)) return 1;
  ret += add_to_tally(to_add, head->next);
  if(!head)
    head = new Node(to_add);
  return ret;
}

