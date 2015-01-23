#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct Ver{
  int colum;
  int start;
  int end;
  int dist;
  struct Edge *next;
}Ver;

typedef struct Edge{
  int ind;
  int weight;
  struct Edge *next;
}Edge;


int ** Load_File(char *Filename, int *num);
Ver **Varr_build(int **arr, int n, int *ip);
int get_divr(int astart, int aend, int bstart, int bend);
int get_cost(int c, int r, int d);
Ver **Edge_build(Ver **arr, int nv);
Edge *List_create(Edge *head, int ind, int weight);
int BellFord(Ver **arr, int n);
int find_w(Ver **arr, int i, int j);
int find_ind(Ver **arr, int i, int j);
//void arr_free(Ver **arr, int n);
//void list_free(Edge *head);

int main(int argc, char * * argv)
{
  char *filename1 = argv[1];
  int **arr = NULL;
  Ver **varr = NULL;
  int num = 0;
  int ip = 0;
  int mini_w = 0;
  arr = Load_File(filename1, &num);
  varr = Varr_build(arr, num, &ip);
  //printf("ippp = %d\n", ip);
  varr = Edge_build(varr, ip + 1);
  mini_w = BellFord(varr, ip + 1) - 1;
  printf("mini_w = %d\n", mini_w);
  
  //arr_free(varr, ip + 1);
  
  
  //printf("arr[1][2] = %d\n",arr[1][2]);
  //printf("fffff\n");
  return 0;
}

Ver *Ver_create(int colum, int start, int end)
{
  Ver *v = NULL;
  v = (Ver *)malloc(sizeof(Ver));
  v -> colum = colum;
  v -> start = start;
  v -> end = end;
  v -> next = NULL;
  v -> dist = 0;
  return v;
}

Edge *Edge_create(int ind, int weight)
{
  Edge *e = (Edge*)malloc(sizeof(Edge));
  e -> ind = ind;
  e -> weight = weight;
  e -> next = NULL;
  return e;
}

Edge *List_create(Edge *head, int ind, int weight)
{
  if(head == NULL)
  {
    return Edge_create(ind, weight);
  }
  else
  {
    Edge *p = Edge_create(ind, weight);
    p -> next = head;
    return p;
  }
}



int ** Load_File(char *Filename, int *num)
{
  FILE *pfile;
  if( !(pfile = fopen(Filename,"r")))
  {
    return NULL;
  }
  
  char temp = 0;
  int n = 0;
  int i = 0;
  int j = 0;
  
  
  fscanf(pfile, "%d", &n);
  //printf("n = %d\n", n);
  *num = n;
  int **arr = (int**)malloc(sizeof(int*) * (n - 1));
  temp = fgetc(pfile);
  for(i = 0; i < n - 1; i++)
  {
    arr[i] = (int*)malloc(sizeof(int) * n);
    for(j = 0; j < n; j++)
    {
      temp = fgetc(pfile);
      
      arr[i][j] = temp - 48;
      //printf("temp = %d\n", arr[i][j]);
    }
    temp = fgetc(pfile);
  }
  fclose(pfile);
  return arr;
}

Ver **Varr_build(int **arr, int n, int *ip)
{
  //int ip = 0;
  int i = 0;
  int j = 0;
  int start = 0;
  int end = 0;
  //int ifv = 1;
  
  Ver **p = NULL;
  for(i = 0; i < n - 1; i++)
  {
    for(j = 0; j < n; j++)
    {
      start = i;
      end = i;
      if(i != 0)
      {
	if(arr[i - 1][j] == 0)
	{
	  if(arr[i][j] == 1)
	  {
	    while( ((end + 1) < n - 1) && arr[end + 1][j] == 1)
	    {
	      end++;
	    }
	    *ip = *ip + 1;
	  }
	}
      }
      if(i == 0)
      {
	if(arr[i][j] == 1)
	{
	  if(arr[i][j] == 1)
	  {
	    while( ((end + 1) < n - 1) && arr[end + 1][j] == 1)
	    {
	      end++;
	    }
	    *ip = *ip + 1;
	  }
	}
      }
    }
  }
 // printf("ip = %d\n", *ip);
  p = (Ver **)malloc(sizeof(Ver) * (*ip + 2));
  p[0] = Ver_create(-1, 0, n - 2);
  printf("p[%d] -> colum = %d ", 0, p[0] -> colum);
  printf("p[%d] -> start = %d ", 0, p[0] -> start);
  printf("p[%d] -> end = %d\n", 0, p[0] -> end);
  *ip = 1;
   for(i = 0; i < n - 1; i++)
  {
    for(j = 0; j < n; j++)
    {
      start = i;
      end = i;
      if(i != 0)
      {
	if(arr[i - 1][j] == 0)
	{
	  if(arr[i][j] == 1)
	  {
	    while( ((end + 1) < n - 1) && arr[end + 1][j] == 1)
	    {
	      end++;
	    }
	    p[*ip] = Ver_create(j, start, end);
	    printf("p[%d] -> colum = %d ", *ip, p[*ip] -> colum);
            printf("p[%d] -> start = %d ", *ip, p[*ip] -> start);
            printf("p[%d] -> end = %d\n", *ip, p[*ip] -> end);
	    *ip = *ip + 1;
	  }
	}
      }
      if(i == 0)
      {
	if(arr[i][j] == 1)
	{
	  if(arr[i][j] == 1)
	  {
	    while( ((end + 1) < n - 1) && arr[end + 1][j] == 1)
	    {
	      end++;
	    }
	    p[*ip] = Ver_create(j, start, end);
	    printf("p[%d] -> colum = %d ", *ip, p[*ip] -> colum);
            printf("p[%d] -> start = %d ", *ip, p[*ip] -> start);
            printf("p[%d] -> end = %d\n", *ip, p[*ip] -> end);
	    *ip = *ip + 1;
	  }
	}
      }
    }
  }
  p[*ip] = Ver_create(n, 0, n - 2);
  printf("p[%d] -> colum = %d ", *ip, p[*ip] -> colum);
  printf("p[%d] -> start = %d ", *ip, p[*ip] -> start);
  printf("p[%d] -> end = %d\n", *ip, p[*ip] -> end);
  return p;
}
      
Ver **Edge_build(Ver **arr, int nv) 
{
  
  int i = 0;
  int j = 0;
  int c = 0;
  int r = 0;
  int d = 0;
  int cost = 0;
  int a;
  int b;
  Edge *list = NULL;
  
  for(i = 0; i < nv; i++)
  {
    for(j = nv - 1; j >= 0; j--)
    {
      if(i != j)
      {
	if(i == 0 && j == 1)
	{
	  a = arr[i] -> colum;
	  b = arr[j] -> colum;
	  
	  c = abs(a - b);
	  r = get_divr(arr[i] -> start, arr[i] -> end, arr[j] -> start, arr[j] -> end);
	  d = c - r;
	  cost = get_cost(c, r, d);
	  //Edge *p = Edge_create(j, cost);
	  arr[i] -> next = List_create(list, j, cost);
	  printf("c = %d, r = %d, d = %d ", c, r, d);
	  printf("e -> ind = %d ", arr[i] -> next -> ind);
	  printf("e[%d][%d] -> cost = %d\n", i, j, arr[i] -> next -> weight);
	}
	else if(j == 0)
	{
	  c = abs(arr[i] -> colum - arr[j] -> colum);
	  r = get_divr(arr[i] -> start, arr[i] -> end, arr[j] -> start, arr[j] -> end);
	  d = c - r;
	  cost = get_cost(c, r, d);
	  //Edge *p = Edge_create(j, cost);
	  arr[i] -> next = List_create(list, j, cost);
	  printf("c = %d, r = %d, d = %d ", c, r, d);
	  printf("e -> ind = %d ", arr[i] -> next -> ind);
	  printf("e[%d][%d] -> cost = %d\n", i, j, arr[i] -> next -> weight);
	}
	else
	{
	  c = abs(arr[i] -> colum - arr[j] -> colum);
	  r = get_divr(arr[i] -> start, arr[i] -> end, arr[j] -> start, arr[j] -> end);
	  d = c - r;
	  cost = get_cost(c, r, d);
	  list = List_create(list, j, cost);
	  printf("c = %d, r = %d, d = %d ", c, r, d);
	  printf("e -> ind = %d ", list -> ind);
	  printf("e[%d][%d] -> cost = %d\n", i, j, list -> weight);
	}
      }
    }
  }
  
  return arr;
}
	  
	    
int BellFord(Ver **arr, int n)  
{
  int go = 0;
  int i;
  int j;
  int w = 0;
  int maximum = 10000;
  int ei = 0;
  
  arr[0] -> dist = 0;
  for(go = 1; go < n; go++)
  {
    arr[go] -> dist = maximum;
  }
  for(go = 1; go < n; go++)
  {
    for(i = 0; i < n; i++)
    {
      for(j = 1; j < n; j++)
      {
	w = find_w(arr, i, j);
	ei = find_ind(arr, i, j);
	//printf("arr[%d] -> d = %d   ",i, arr[i] -> dist);
	//printf("arr[%d] -> d = %d ",j, arr[j] -> dist);
	//printf("w = %d\n", w);
	if(arr[i] -> dist > arr[ei] -> dist + w)
	{
	  arr[i] -> dist = arr[ei] -> dist + w;
	}
      }
    }
  }
  return arr[n - 1] -> dist;
}

int find_ind(Ver **arr, int i, int j)
{
  Edge *e = NULL;
  int m = 0;
  e = arr[i] -> next;
  if(j == 1)
  {
    return e -> ind;
  }
  else
  {
    for(m = 1; m < j; m++)
    {
      e = e -> next;
    }
    return e -> ind;
  }
}

int find_w(Ver **arr, int i, int j)
{
  Edge *e = NULL;
  int m = 0;
  e = arr[i] -> next;
  if(j == 1)
  {
    return e -> weight;
  }
  else
  {
    for(m = 1; m < j; m++)
    {
      e = e -> next;
    }
    return e -> weight;
  }
}
  
  
  
  
  
 
int get_divr(int astart, int aend, int bstart, int bend)
{
  if(bstart - aend >= 2)
  {
    return (bstart - aend - 1);
  }
  else if(astart - bend >= 2)
  {
    return (astart - bend - 1);
  }
  else{
    return 0;
  }
}

int get_cost(int c, int r, int d)
{
  
 
    if(d == 0)
    {
      return 2 * c;
    }
    if(d > 0)
    {
      return (2*r + 2*d - 1);
    }
    else
    {
      return (2*c + 2*abs(d));
    }
}















