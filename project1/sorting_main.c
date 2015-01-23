#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


long *Load_File(char *Filename, int *Size);
int Print_Seq(char *Filename, int Size);
int Save_File(char *Filename, long *Array, int Size);
void Shell_Insertion_Sort(long *Array, int Size, double *N_Comp, double *N_Move);
void Shell_Selection_Sort(long *Array, int Size, double *N_Comp, double *N_Move);


int main(int argc, char * * argv)
{
  clock_t load_begin, load_end, save_begin, save_end, Sorting_begin, Sorting_end;
  double IO_time, Sorting_time;
  
  load_begin = clock();
  char * filename1 = argv[2];
  int size = 0; 
  long * arr;
  arr = Load_File(filename1, &size);
  load_end = clock();

  double N_Comp = 0;
  double N_Move = 0;
  
  Sorting_begin = clock();
  if(*argv[1] == 'i')
  {
    Shell_Insertion_Sort(arr, size, &N_Comp, &N_Move);
  }
  else if(*argv[1] == 's')
  {
    Shell_Selection_Sort(arr, size, &N_Comp, &N_Move);
  }
  Sorting_end = clock();
 
  char * filename2 = argv[3];
  Print_Seq(filename2, size);
  
  save_begin = clock();
  char * filename3 = argv[4];
  Save_File(filename3, arr, size);
  save_end = clock();

  free(arr);

  IO_time = (double)(load_end - load_begin + save_end - save_begin);
  Sorting_time = (double)(Sorting_end - Sorting_begin);
  
  
  printf("Number of comparisions: %le\n", N_Comp);
  printf("Number of moves: %le\n", N_Move);
  printf("I/O time: %le\n", IO_time/CLOCKS_PER_SEC);
  printf("Sorting time: %le\n", Sorting_time/CLOCKS_PER_SEC);
  return 0;
}
