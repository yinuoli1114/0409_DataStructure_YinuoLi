#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
typedef struct node{
  long value;
  struct node *next;
}Node;

void Number_node(Node *list, int *count);
Node *Load_File(char *Filename);
int Save_File(char *Filename, Node *list);
Node *Shell_Sort(Node *list);
void List_destroy(Node * head);

int main(int argc, char * * argv)
{
  clock_t load_begin, load_end, save_begin, save_end, Sorting_begin, Sorting_end;
  char * filename1 = argv[1];
  double IO_time = 0;
  double Sorting_time = 0;
  
  load_begin = clock();
  Node * list = Load_File(filename1);
  load_end = clock();
  
  Sorting_begin = clock();
  list = Shell_Sort(list);
  Sorting_end = clock();
  char * filename2 = argv[2];
  
  int count = 0;
  Number_node(list, &count);
 // printf("count = %d\n",count);
  
  
  int num_node = 0;
  save_begin = clock();
  num_node = Save_File(filename2, list);
  save_end = clock();
  
  
  IO_time = (double)(load_end - load_begin + save_end - save_begin);
  Sorting_time = (double)(Sorting_end - Sorting_begin);
  printf("I/O time: %le\n", IO_time/CLOCKS_PER_SEC);
  printf("Sorting time: %le\n", Sorting_time/CLOCKS_PER_SEC);
  List_destroy(list);
  
  return 0;
}