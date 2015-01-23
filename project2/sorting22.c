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
List *list_traverse(List *dummy, int i);

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
  while(cp_list -> next)
  {
    cp_list = cp_list -> next;
    Size++;
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
  int dummynum;
  long temp;
 
  for(ind = 0; ind <maxn; ind++)
  {
    k = seq_arr[ind];
    //printf("k = %d\n",k);
    j = 0;
    dummynum = 0;
    //printf("%d\n",k);
    List *dummy = NULL;
    Node * head = list;
    int bignum = Size / k + 1;
   int go1 = Size - ((bignum - 1) * k + 1) + 2;
   int go2 = k - go1;
   int ja = 0;
  // int jb = 0;
   int ix;
   int iy;
   for(ix = 0; ix < go1; ix++)
   {
    do
    {
      dummy = dummylist_create(dummy, head);
      dummynum++;
      //printf("dummynum = %d\n",dummynum);
      //printf("%ld\n",dummy -> node -> value);
      //ja = jb;
      if(ja < Size)
      {
	
        for(i = 0; i < k; i++)
        {
	  ja++;
	  if(ja < Size && head -> next)
	  {
	    head = head -> next;
	  }
        }
      }
      //jb++;
      }while(ja < Size);
      
      //int num;
      head = traverse(list, ix + 1);
     for(j = 1; j < dummynum; j++) 
     {
       temp = list_traverse(dummy,j) -> node -> value;
       i = j;
       while(i > 0 && list_traverse(dummy,i - 1) -> node -> value)
       {
	 list_traverse(dummy,i) -> node -> value = list_traverse(dummy,i - 1) -> node -> value;
         i = i - 1;
	 list_traverse(dummy,i) -> node -> value = temp;
       }
     }
   }
   
   for(iy = 0; iy < go2; iy++)
   {
    do
    {
      dummy = dummylist_create(dummy, head);
      dummynum++;
      //printf("dummynum = %d\n",dummynum);
     // printf("%ld\n",dummy -> node -> value);
      //ja = jb;
      if(ja < Size)
      {
	
        for(i = 0; i < k; i++)
        {
	  ja++;
	  if(ja < Size && head -> next)
	  {
	    head = head -> next;
	  }
        }
      }
      //jb++;
      }while(ja < Size);
      
      //int num;
      head = traverse(list, iy + 1);
     for(j = 1; j < dummynum; j++) 
     {
       temp = list_traverse(dummy,j) -> node -> value;
       i = j;
       while(i > 0 && list_traverse(dummy,i - 1) -> node -> value)
       {
	 list_traverse(dummy,i) -> node -> value = list_traverse(dummy,i - 1) -> node -> value;
         i = i - 1;
	 list_traverse(dummy,i) -> node -> value = temp;
       }
     }
   }
     
     /*List *temp1 = NULL;
     List *temp2 = NULL;
     List *first = NULL;
     List *second = NULL;
     //List *second = dummy -> next;
     int dumfirst = dummynum;
     int dumsecond = dummynum - 1;
     int firstnum = 0;
     int secondnum = 0;
     int go1 = Size - ((dummynum - 1) * k + 1);
     printf("go1 = %d ", go1);
     int go2 = k - go1 - 1;
     printf("go2 = %d\n", go2);
     first = dummynode_create(dummy -> node);
     //first -> node = dummy -> node;
     temp1 = dummy;
     //temp1 -> node  = dummy -> node;
     int go = 0;
    printf("enter for1\n");
     do//(go = 0; go < go1; go++)
     {
         //insertion sort
        //temp2 = dummy -> next;
          temp1 -> node = first -> node;
	  dumfirst = dummynum;
	  firstnum = dumfirst;
	  if(temp1 -> node -> next)
	  {
	    while(firstnum > 0 )
	   {
	      temp1 -> node = temp1 -> node -> next;
	      printf("node1 = %ld\n",temp1 -> node -> value);
	      printf("dummy = %ld\n",dummy -> node -> value);
	      if(temp1 -> next)
	      {
	       temp1 = temp1 -> next;
	      }
	      firstnum--;
	   }
	   first -> node = first -> node -> next;
	  }
	  go++;
      }while(go < go1);
       temp1 -> node = first -> node;
       temp2 = temp1 -> next;
       //temp2 -> node  = first -> next -> node;
       //temp2 -> node = temp2 -> node -> next;
       
       second = dummynode_create(temp1 -> next -> node);
       //second -> node  = first -> next -> node;
       printf("enter for2\n");
       go = 0;
       do//(go = 0; go < go2 ; go++)
       {
	  //insertion sort
	  //temp2 = dummy -> next;
	  temp2 -> node = second -> node;
	  printf("dumsecondnum = %d\n",dumsecond);
	  
	  secondnum = dumsecond;
	  while(secondnum > 0)
	  {
	    
	    temp2 -> node = temp2 -> node -> next;
	    printf("node2 = %ld\n",temp2 -> node -> value);
	
	    if(temp2 -> next)
	    {
	      temp2 = temp2 -> next;
	    }
	    secondnum--;
	  }
	  second -> node = second -> node -> next;
	  go++;
	}while(go < go2);*/
       
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

List *list_traverse(List *dummy, int i)
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
  
  
  
  
  
    
    