#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
  long value;
  struct node *next;
}Node;

typedef struct list{
  Node *node;
  struct list *next;
}List;

long maxk(long n);
long maxq(long n);
long powtwo(long p);
long powthree(long q);
Node *Shell_Sort(Node *list);
Node *traverse(Node *list, int i);
List *dummynode_create(Node *node);
List *dummy_traverse(List *dummy, int i);
List *dummy_sort(List *dummy, int dummynum);


void List_destroy(Node * head)
{
  if(head == NULL)
  {
    return;
  }
  List_destroy(head -> next);
  free(head);
}
void dummy_destroy(List * head)
{
  if(head == NULL)
  {
    return;
  }
  dummy_destroy(head -> next);
  free(head);
}

Node *Node_create(long value)
{
  Node *node = (Node*)malloc(sizeof(Node));
  node -> value = value;
  node -> next = NULL;
  return node;
}

Node *List_create(Node *head, long value)
{
  if(head == NULL)
  {
    return Node_create(value);
  }
  else
  {
    Node *p = Node_create(value);
    p -> next = head;
    return p;
  }
}

List *dummynode_create(Node *node)
{
  List *dummy = (List *)malloc(sizeof(List));
  dummy -> node = node;
  dummy -> next = NULL;
  return dummy;
}

List *dummylist_create(List *dummy, Node *node)
{
  if(dummy == NULL)
  {
    return dummynode_create(node);
  }
  else
  {
    List *p = dummynode_create(node);
    p -> next = dummy;
    return p;
  }
}
void Number_node(Node *list, int *count)
{
  if(list  == NULL)
  {
    *count = 0;
  }
  else
  {
    while(list -> next)
    {
      list = list -> next;
      (*count)++;
    }
    (*count)++; 
  }
}

Node *reverce_list_create(Node *head, long value)
{
  if(head == NULL)
  {
    return Node_create(value);
  }
  else
  {
    Node *q = head;
    while(head -> next)
    {
      head = head -> next;
    }
      Node *p = Node_create(value);
      head -> next = p;
      return q;
  }
}    
  

Node *Load_File(char *Filename)
{
  FILE *pfile;
 
  if( !(pfile = fopen(Filename,"r")))
  {
    return NULL;
  }
  long value = 0;
  //Node *head = NULL;
  Node *list = NULL;
  while(fscanf(pfile,"%ld",&value) == 1)
  {
    
    list = List_create(list, value);
    //printf("%ld\n", list -> value);
  }
  fclose(pfile);
  return list;
}

int count_node(Node *list)
{
  int size = 0;
  while(list -> next != NULL)
  {
    list = list -> next;
    size++;
  }
  size++;
  return size;
}

Node *Shell_Sort(Node *list)
{
  
  int Size = 0;
  Size = count_node(list);
  long k = maxk(Size);// finding the max k
 
  long q = maxq(Size);// finding the max q
  
  long p = 0;
  long n = (q+2) * (q+1) / 2;// finding the number of elements in the pyramid sequence
  
  long maxn = n;
  //int *seq_arr = (int *)malloc(sizeof(int) * n);
  int ind = 0;
  Node *sequence = NULL;
  for(ind = 0; ind <n; ind++)
  {
     sequence = reverce_list_create(sequence, k);
     //printf("k = %ld\n",sequence -> value);// putting each k into an array
    if(q > 0)
    {
      q--;
      p++;
    }
    else 
    {
      q = p-1;
      p = 0;
    }
    
    if(q >= 0 && p >= 0)
    {
    k = powtwo(p) * powthree(q);// determine every k
    }
   
  }
  
  int j;
  int i;
 
  Node *seq = sequence;
  List *dummy = NULL;
  List *temp = NULL;
  for(ind = 0; ind <maxn; ind++)
  {
    //k = seq_arr[ind];
    k = sequence -> value;
    //printf("ks = %ld\n",k);
    sequence = sequence -> next;
    j = 0;
    Node *head = list;
    //dummy = NULL;
    temp = NULL;
     int dummynum = 0;
     do
    {
      
      dummy = dummylist_create(dummy, head);
      dummynum++;
      
      if(j < Size)
      {
	
        for(i = 0; i < k; i++)
        {
	  j++;
	  if(j < Size)
	  {
	    head = head -> next;
	  }
        }
      }
      //jb++;
     }while(j < Size);
     
     dummy = dummy_sort(dummy, dummynum);
     int m;
     int l;
     for(m = 0; m < k -1; m++)
     {
       temp = dummy;
       
       int dum_num = dummynum;
       if(temp -> node -> next == NULL)
       {
	 temp = temp -> next;
	 
	 dum_num--;
       }
       for(l = 0; l < dum_num; l++)
       {
	 temp -> node = temp -> node ->next;
	 
	 if(temp -> next)
	 {
	  temp = temp -> next;
	 }
       }
       dummy = dummy_sort(dummy, dum_num);
      
     }  
  
  }//for
  List_destroy(seq);
  dummy_destroy(dummy);
  dummy_destroy(temp);
  return list;
}
  


int Save_File(char *Filename, Node *list)
{
  FILE *pfile;
  pfile = fopen(Filename, "w");
  int count = 0;
  Number_node(list,&count);
  int i = 0;
  while(i <count)
  {
    fprintf(pfile, "%ld\n",list -> value);
    
    list = list -> next;
     i++;
  }
  fclose(pfile);
  return count;
}

List *dummy_sort(List *dummy, int dummynum)
{
  int j;
  int i;
  long temp;
  for(j = 1; j < dummynum; j++)
  {
    temp = dummy_traverse(dummy, j) -> node -> value;
    
    i = j;
   
    while(i > 0 && dummy_traverse(dummy, i - 1) -> node -> value < temp)
    {
      dummy_traverse(dummy,i) -> node -> value = dummy_traverse(dummy, i - 1) -> node -> value;
      i = i -1;
      dummy_traverse(dummy, i) -> node -> value = temp;
    }
  }
  return dummy;
}
 
Node *traverse(Node *list, int i)
{
  int m;
  
  if(i == 0)
  {
    return list;
  }
  
  else
  {
    for(m = 0; m < i; m++)
    {
      list = list -> next;
    }
    return list;
  }
}
List *dummy_traverse(List *dummy, int i)
{
  int m;
  if(i == 0)
  {
    return dummy;
  }
  else
  {
    for(m = 0; m < i; m++)
    {
      dummy = dummy -> next;
    }
    return dummy;
  }
}
  
long maxk(long n)
{
  long q = 0;
  while(powthree(q) <= n)
  {
    q++;
  }
  q--;
  return powthree(q);
}

long maxq(long n)
{
  long q = 0;
  while(powthree(q) <= n)
  {
    q++;
  }
  q--;
  return q;
}

long powtwo(long p) // calculate the power of two
{
  long answer;
  if(p == 0)
  {
    return 1;
  }
  else
  {
  answer = 2 * powtwo(p-1);
  return answer;
  }
}
  
long powthree(long q) // calculate the power of three
{
  long answer;
  if(q == 0)
  {
    return 1;
  }
  else
  {
  answer = 3 * powthree(q-1);
  return answer;
   }
  
}  
  
  
  
  
  
    
    