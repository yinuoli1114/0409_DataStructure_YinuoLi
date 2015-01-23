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

int maxk(int n);
int maxq(int n);
int powtwo(int p);
int powthree(int q);
Node *Shell_Sort(Node *list);
Node *traverse(Node *list, int i);
List *dummynode_create(Node *node);
List *dummy_traverse(List *dummy, int i);
List *dummy_sort(List *dummy, int dummynum);

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

Node *Shell_Sort(Node *list)
{
  
  int Size = 0;
  //printf("%d",Size);
  Node *cp_list = list;
  if(cp_list -> next)
  {
    while(cp_list -> next)
    {
      cp_list = cp_list -> next;
      Size++;
    }
  }
  Size++;
   //printf("%d",Size);
  int k = maxk(Size);// finding the max k
  //printf("%d\n",k);
 // printf("k=%d\n",k);
  int q = maxq(Size);// finding the max q
  //printf("q=%d\n",q);
  int p = 0;
  int n = (q+2) * (q+1) / 2;// finding the number of elements in the pyramid sequence
  //printf("n=%d\n",n);
  int maxn = n;
  int *seq_arr = (int *)malloc(sizeof(int) * n);
  int ind = 0;
  for(ind = 0; ind <n; ind++)
  {
    seq_arr[ind] = k;// putting each k into an array
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
     //printf("q=%d\n",q);
     // printf("p=%d\n",p);
    if(q >= 0 && p >= 0)
    {
    k = powtwo(p) * powthree(q);// determine every k
    }
    //printf("k=%d\n",k);
    //n--;
  }
  
  int j;
  int i;
 
  //long temp;
 
  for(ind = 0; ind <maxn; ind++)
  {
    k = seq_arr[ind];
    //printf("k = %d\n",k);
    j = 0;
    Node *head = list;
    List *dummy = NULL;
    List *temp = NULL;
     int dummynum = 0;
     do
    {
      dummy = dummylist_create(dummy, head);
      dummynum++;
      //printf("dummynum = %d\n",dummynum);
      //printf("%ld\n",dummy -> node -> value);
      //ja = jb;
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
       //printf("dummy = %ld\n",dummy -> node -> value);
       int dum_num = dummynum;
       if(temp -> node -> next == NULL)
       {
	 temp = temp -> next;
	 //printf("temp = %ld\n",temp -> node -> value);
	 dum_num--;
       }
       for(l = 0; l < dum_num; l++)
       {
	 temp -> node = temp -> node ->next;
	 //printf("temp = %ld\n",temp -> node -> value);
	 if(temp -> next)
	 {
	  temp = temp -> next;
	 }
       }
       dummy = dummy_sort(dummy, dum_num);
     }
     
  
  
  }//for
      
      
    
  
  
  return list;
}
  


int Save_File(char *Filename, Node *list)
{
  FILE *pfile;
  pfile = fopen(Filename, "w");
  int count = 0;
  Number_node(list, &count);
  int i = 0;
  while(i <count)
  {
    fprintf(pfile, "%ld\n",list -> value);
    //printf("fuck you %ld\n", list -> value);
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
    //printf("temp = %ld\n",temp);
    i = j;
    //printf("dvalue(i - 1) = %ld\n",dummy_traverse(dummy, i - 1) -> node -> value);
    while(i > 0 && dummy_traverse(dummy, i - 1) -> node -> value > temp)
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
      //printf("%ld\n", list -> value);
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
  
int maxk(int n)
{
  int q = 0;
  while(powthree(q) <= n)
  {
    q++;
  }
  q--;
  return powthree(q);
}

int maxq(int n)
{
  int q = 0;
  while(powthree(q) <= n)
  {
    q++;
  }
  q--;
  return q;
}

int powtwo(int p) // calculate the power of two
{
  int answer;
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
  
int powthree(int q) // calculate the power of three
{
  int answer;
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
  
  
  
  
  
    
    