 #include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct node{
  long value;
  struct node *next;
}Node;


long maxk(long n);
long maxq(long n);
long powtwo(long p);
long powthree(long q);
Node *Shell_Sort(Node *list);
Node *traverse(Node *list, int i);

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
  while(cp_list -> next)
  {
    cp_list = cp_list -> next;
    Size++;
  }
  Size++;
   //printf("%d",Size);
  long k = maxk(Size);// finding the max k
  //printf("%d\n",k);
 // printf("k=%d\n",k);
  long q = maxq(Size);// finding the max q
  //printf("q=%d\n",q);
  long p = 0;
  long n = (q+2) * (q+1) / 2;// finding the number of elements in the pyramid sequence
  //printf("n=%d\n",n);
  long maxn = n;
  //int *seq_arr = (int *)malloc(sizeof(int) * n);
  int ind = 0;
  Node *sequence = NULL;
  for(ind = 0; ind <n; ind++)
  {
     //sequence = List_create(sequence, k);// putting each k into an array
     sequence = reverce_list_create(sequence, k);
     printf("k = %ld\n",sequence -> value);
    
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
  long temp;
  for(ind = 0; ind <maxn; ind++)
  {
    k = sequence -> value;
    printf("ks = %ld\n",k);
    sequence = sequence -> next;
    //printf("%d\n",k);
    
    for(j = k; j < Size; j++)
    {
      Node *head = traverse(list, j);
    
      temp = head -> value;
      i = j;
      while(i >= k && traverse(list, i-k) -> value > temp)
      {
        //i = i - k;
       
        
        
	  //temp = head -> value;
	  head -> value = traverse(list, i-k) -> value;
	  i = i - k;
	  traverse(list, i) -> value = temp;
        
      }
    }
  }
  return list;
}
  


int Save_File(char *Filename, Node *list)
{
  FILE *pfile;
  pfile = fopen(Filename, "w");
  int count = 0;
  Number_node(list, &count);
  int i = 0;
  Node * head = list;
  while(i <count)
  {
    fprintf(pfile, "%ld\n",list -> value);
    //printf("fuck you %ld\n", list -> value);
    list = list -> next;
     i++;
  }
  fclose(pfile);
  List_destroy(list);
  return count;
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
  int q = 0;
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
  
  
  
  
  
    
    