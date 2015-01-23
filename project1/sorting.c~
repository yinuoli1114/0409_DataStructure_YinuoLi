#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move);

int Print_Seq(char *Filename, int Size);
int Save_File(char *Filename, long *Array, int Size);
int determinek(int p, int q);
int maxk(int n);
int maxq(int n);
int powtwo(int p);
int powthree(int q);

long *Load_File(char *Filename, int *Size)
{
  FILE *pfile;
  int i = 0;
  if( !(pfile = fopen(Filename,"r")))
  {
    return NULL;
  }
  if(fscanf(pfile,"%d",Size) != 1)
  {
    return NULL;
  }
  //printf("a=%d\n",*Size);
  long *arr = malloc(sizeof(long) * (*Size));
  i = 0;
  while(fscanf(pfile,"%ld",&arr[i]) == 1)
  {
    //printf("a=%ld\n",arr[i]);
    i++;
  }
  fclose(pfile);
  return arr;
}


void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
  //N_Comp = 0;
  //N_Move = 0;
  int k = maxk(Size);// finding the max k
  int q = maxq(Size);// finding the max q
 // printf("q=%d\n",q);
  int p = 0;
  int n = (q+2) * (q+1) / 2;// finding the number of elements in the pyramid sequence
 // printf("n=%d\n",n);
  int maxn = n;
  int *seq_arr = malloc(sizeof(int) * n);
  int ind = 0;
  for(ind = 0; ind < n; ind++)
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
    // printf("q=%d\n",q);
     // printf("p=%d\n",p);
   if(q >= 0 && p >= 0)
    {
    k = powtwo(p) * powthree(q);// determine every k
    }
    //n--;
  }
  
  int j;
  int i;
  long temp;
  
  for(ind = 0; ind <maxn; ind++)
  {
    k = seq_arr[ind];
    for(j = k; j <= Size-1; j++)
    {
      //printf("k=%d\n",k);
      temp = Array[j];
      (*N_Move)++;
      i = j;
      //(*N_Comp)++;
      while((i >= k) && (Array[i-k] > temp))
      {
	    (*N_Comp)++;
	    Array[i] = Array[i-k];
	    (*N_Move)++;
	    i = i - k;
	    Array[i] = temp;
	    (*N_Move)++;
      }
      if(i >= k)
      {
	 (*N_Comp)++;
      }
    }
    //(*N_Comp)--;
  }
  free(seq_arr);

}

void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move)
{
 // N_Comp = 0;
  //N_Move = 0;
  int k = maxk(Size);// finding the max k
 // printf("k=%d\n",k);
  int q = maxq(Size);// finding the max q
  //printf("q=%d\n",q);
  int p = 0;
  int n = (q+2) * (q+1) / 2;// finding the number of elements in the pyramid sequence
  //printf("n=%d\n",n);
  int maxn = n;
  int *seq_arr = malloc(sizeof(int) * n);
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
  long temp;
  int min;
  //Sorting_begin = clock();
   for(ind = 0; ind <maxn; ind++)
  {
    k = seq_arr[ind];
    for(j = 0; j < Size; j++)
    {
      min = j;// assume the min is the first element for each j
      i = j+k;
      while(i < Size)
      {
      	*N_Comp = *N_Comp + 1;
	if(Array[i] < Array[min])
	{
	  
	  min = i;// find new min, remember its index
	}
	i = i+k;
      }
      if(min != j)// swap it min with the current position
      {
	  temp = Array[j];
	  Array[j] = Array[min];
	  Array[min] = temp;
	  *N_Move = *N_Move + 3;
	
      }
     // printf("Number of comparisions: %le\n", *N_Comp);
     }
  }
  free(seq_arr);
  //Sorting_end = clock();
  //printf("Number of comparisions: %le\n", &N_Comp);
  //printf("Number of moves: %le\n", &N_Move);
}


int Save_File(char *Filename, long *Array, int Size)
{
  FILE *pfile;
  int i = 0;
  pfile = fopen(Filename,"w");
  fprintf(pfile,"%d\n",Size);
   while(i < Size)
  {
    fprintf(pfile,"%ld\n",Array[i]);
    i++;
    //printf("a=%ld\n",Array[i]);
  }
  fclose(pfile);
  return Size;
}

int Print_Seq(char *Filename, int Size)
{
  FILE *pfile;
  int i = 0;
  int k = maxk(Size);// finding the max k
  //printf("k=%d\n",k);
  int q = maxq(Size);// finding the max q
  //printf("q=%d\n",q);
  int p = 0;
  int n = (q+2) * (q+1) / 2;// finding the number of elements in the pyramid sequence
  //printf("n=%d\n",n);
  int maxn = n;
  int *seq_arr = malloc(sizeof(int) * n);
  while((n >= 1) )
  {
    seq_arr[n-1] = k;// putting each k into an array
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
     if(q >= 0 && p >= 0)
    {
    k = powtwo(p) * powthree(q);// determine every k
    }
   // printf("k=%d\n",k);
    n--;
  }
  pfile = fopen(Filename,"w");
  fprintf(pfile,"%d\n",maxn);
  while(i < maxn)
  {
    fprintf(pfile,"%d\n",seq_arr[i++]);
  }
  fclose(pfile);
  free(seq_arr);
  return 0;
}

/*int determinek(int *p, int *q)
{
  int k;
  if(q > 0)
  {
    q--;
    p++;
  }
  if(q == 0)
  {
    q = p-1;
    p = 0;
  }
  k = powtwo(p) * powthree(q);
  return k;
}*/
  

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
  
  
