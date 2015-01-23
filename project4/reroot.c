#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


typedef struct Node{
  struct Node *lcnode;
  struct Node *rcnode;
  char cutline;
  double width;
  double height;
  double xcoord;
  double ycoord;
  
}Node;

typedef struct Stack{
  Node *node;
  struct Stack *next;
}Stack;

Node * Load_File(char *Filename);
void count_xy(Node *cur, double p_w, double p_h, double p_x, double p_y, char p_c, int *lr , int *is_root);
void reroot(Node *p, Node *cur, double sib_w, double sib_h, double *w, double *h, char g_c, double low_w, double low_h);
Node *Node_create(double width, double height, char cutline);
int Save_File(char *Filename, Node* head);
void postorder(Node * cur, FILE *pfile);
void Preorder(Node *cur);
void Inorder(Node *cur);
void Postorder(Node *cur);
void tree_destroy(Node *cur);
void list_destroy(Stack *list);

int main(int argc, char * * argv)
{
  clock_t packing_begin, packing_end, reroot_begin, reroot_end;
  
  char *filename1 = argv[1];
  Node *head = NULL;
  head = Load_File(filename1);
  int lr = 0;
  int is_root = 1;
  
  packing_begin = clock();
  count_xy(head, 0, 0, 0, 0, 'H', &lr, &is_root);
  packing_end = clock();
  
  char *filename2 = argv[2];
  Save_File(filename2, head);
  
  printf("Preorder: ");
  Preorder(head);
  
  printf("\n\nInorder: ");
  Inorder(head);
  
  printf("\n\nPostorder: ");
  Postorder(head);
  
  printf("\n\nWidth: %le\nHeight: %le", head -> width, head -> height);
  
  Node *first = head;
  while(first -> lcnode)
  {
    first = first -> lcnode;
  }
  
  
  
  printf("\n\nX-coordinate: %le\nY-coordinate: %le", first -> xcoord, first -> ycoord);
  
  //printf("\nleft = %le right = %le\n",head -> width, head -> height);
  
  double w = head -> width;
  double h = head -> height;
 
 // int is_root = 1;
 // int lr = 0;
  reroot_begin = clock();
  Node *root = Node_create(0,0,'H');
  Node *sibroot = Node_create(0,0,'H');
  Node *zero1 = Node_create(0,0,-1);
  Node *zero2 = Node_create(0,0,-1);
  root -> lcnode = head;
  root -> rcnode = sibroot;
  sibroot -> lcnode = zero1;
  sibroot -> rcnode = zero2;
  reroot(root , root -> lcnode, root -> rcnode -> rcnode -> width, root-> rcnode -> rcnode -> height, &w, &h, root -> rcnode -> cutline, root->rcnode->lcnode->width,root->rcnode->lcnode->height);
  reroot_end = clock();
  
  double packing_time = (packing_end - packing_begin)/CLOCKS_PER_SEC;
  double reroot_time = (reroot_end - reroot_begin)/CLOCKS_PER_SEC;
  printf("\n\nElapsed time: %le",packing_time);
  
  printf("\n\nBest width: %le\nBest height: %le", w,h);
  
  printf("\n\nElapsed time for re-rooting: %le\n", reroot_time);
  
  tree_destroy(root);
 
  
  return 0;
}

void list_destroy(Stack *list)
{
  if(list == NULL)
  {
    return;
  }
  list_destroy(list -> next);
  //tree_destroy(list -> node);
  free(list);
}
  

void tree_destroy(Node *cur)
{
  if(cur == NULL)
  {
    return;
  }
  tree_destroy(cur -> lcnode);
  tree_destroy(cur -> rcnode);
  free(cur);
}

void Postorder(Node *cur)
{
  if(cur == NULL)
  {
    return;
  }
  
  Postorder(cur -> lcnode);
  Postorder(cur -> rcnode);
  if(cur -> cutline == 'V' || cur -> cutline == 'H')
  {
    printf("%c", cur -> cutline);
  }
  if(cur -> cutline == -1)
  {
    printf("(%le,%le)", cur -> width, cur -> height);
  }
  
  return;
}

void Inorder(Node *cur)
{
  if(cur == NULL)
  {
    return;
  }
  Inorder(cur -> lcnode);
  if(cur -> cutline == 'V' || cur -> cutline == 'H')
  {
    printf("%c", cur -> cutline);
  }
  if(cur -> cutline == -1)
  {
    printf("(%le,%le)", cur -> width, cur -> height);
  }
  
  Inorder(cur -> rcnode);
  return;
}

void Preorder(Node *cur)
{
  if(cur == NULL)
  {
    return;
  }
  if(cur -> cutline == 'V' || cur -> cutline == 'H')
  {
    printf("%c", cur -> cutline);
  }
  if(cur -> cutline == -1)
  {
    printf("(%le,%le)", cur -> width, cur -> height);
  }
  Preorder(cur -> lcnode);
  Preorder(cur -> rcnode);
  return;
}

int Save_File(char *Filename, Node *head)
{
  FILE *pfile;
  pfile = fopen(Filename, "w");
  postorder(head, pfile);
  
  fclose(pfile);
  
  return 0;
}

void postorder(Node * cur, FILE *pfile)
{
  if(cur == NULL)
  {
    return;
  }
  if(cur -> lcnode == NULL)
  {
    fprintf(pfile, "%le ", cur -> width);
    fprintf(pfile, "%le ", cur -> height);
    fprintf(pfile, "%le ", cur -> xcoord);
    fprintf(pfile, "%le\n", cur -> ycoord);
  }
  
  postorder(cur -> lcnode, pfile);
  postorder(cur -> rcnode, pfile);
}

double getbig(double a, double b)
{
  if(a > b)
  {
    return a;
  }
  else
  {
    return b;
  }
}  

Node *Node_create(double width, double height, char cutline)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node -> width = width;
  node -> height = height;
  node -> cutline = cutline;
  node -> lcnode = NULL;
  node -> rcnode = NULL;
  node -> xcoord = 0;
  node -> ycoord = 0;
  return node;
}

Stack *Stack_create(Node * node)
{
  Stack *st = NULL;
  st = (Stack *)malloc(sizeof(Stack));
  st -> node = node;
  st -> next = NULL;
  return st;
}

Stack *Stack_push(Stack *st, Node *node)
{
  Stack *stacktop = Stack_create(node);
  stacktop -> next = st;
  return stacktop;
}

Stack *Stack_pop(Stack *stacktop)
{
  Stack *new_stacktop = stacktop -> next;
  free(stacktop);
  return new_stacktop;
}

Node * Load_File(char *Filename)
{
  FILE *pfile;
  if( !(pfile = fopen(Filename,"r")))
  {
    return NULL;
  }
  int finish = 0;
  char temp = 0;
  double width;
  double height;
  Node * leaf = NULL;
  Node * nodetop = NULL;
  Node * right = NULL;
  Node * left = NULL;
  Stack * stacktop = NULL;
  
  while(finish == 0)
  {
    
    temp = fgetc(pfile);
    if(temp == -1)
    {
      break;
    }
   
    if(temp == '(')
    {
      fscanf(pfile,"%le,%le)", &width, &height);
      leaf = Node_create(width, height,-1);
      stacktop = Stack_push(stacktop, leaf);
      //printf("leaf -> width = %le\n", stacktop -> node -> width);
    }
    if(temp == 'H' || temp == 'V')
    {
      right = stacktop -> node;
      //printf("stacktop -> node -> width = %le\n", stacktop -> node -> width);
      stacktop = Stack_pop(stacktop);
      
      if(stacktop == NULL)
      {
	finish = 1;
      }
      else
      {
	left = stacktop -> node;
	//printf("stacktop -> node -> width = %le\n", stacktop -> node -> width);
	stacktop = Stack_pop(stacktop);
	
	if(temp == 'V')
	{
	  //printf("%c\n",temp);
	  width = left -> width + right -> width;
	  height = getbig(left -> height, right -> height);
	}
	if(temp == 'H')
	{
	  //printf("%c\n",temp);
	  height = left -> height + right -> height;
	  width = getbig(left -> width, right -> width);
	}
	nodetop = Node_create(width, height, temp);
	nodetop -> lcnode = left;
	nodetop -> rcnode = right;
	//printf("nodetop -> lcnode -> width = %le\n", nodetop -> lcnode -> width);
	stacktop = Stack_push(stacktop, nodetop);
      }
    }
    
  }
  
   
    list_destroy(stacktop);
    fclose(pfile);
    return nodetop;
  
} 

void count_xy(Node *cur, double p_w, double p_h, double p_x, double p_y, char p_c, int *lr , int *is_root)
{
  if(cur == NULL)
  {
    return;
  }
  if(*is_root == 1)
  {
    cur -> xcoord = 0;
    cur -> ycoord = 0;
  }
  if(*is_root == 0)
  {
  if(*lr == 0)
  {
    if(p_c == 'H')
    {
      cur -> xcoord = p_x;
      cur -> ycoord = p_h  - cur -> height + p_y;
    }
    if(p_c == 'V')
    {
      cur -> ycoord = p_y;
      cur -> xcoord = p_x;
    }
  }
  if(*lr == 1)
  {
    if(p_c == 'H')
    {
      cur -> xcoord = p_x;
      cur -> ycoord = p_y;
    }
    if(p_c == 'V')
    {
      cur -> ycoord = p_y;
      cur -> xcoord = p_w - cur -> width + p_x;
    }
  }
  }
  *is_root = 0;
  
  //printf("xcoord = %le, ycoord = %le\n", cur -> xcoord, cur -> ycoord);
  *lr = 0;
  count_xy(cur -> lcnode, cur -> width, cur -> height, cur -> xcoord, cur -> ycoord, cur -> cutline, lr, is_root);
  *lr = 1;
  count_xy(cur -> rcnode, cur -> width, cur -> height, cur -> xcoord, cur -> ycoord, cur -> cutline, lr, is_root);
  return;
}

    
    
    
    
void reroot(Node *p, Node *cur, double sib_w, double sib_h, double *w, double *h, char g_c, double low_w, double low_h)
{
  if(cur == NULL)
  {
    //printf("leaf\n");
   // printf("leaf_w = %le leaf_h = %le \n", cur -> width, cur -> height);
    return;
  }
  double new_w;
  double new_h;
  double g_w;
  double g_h;
 

    if(g_c == 'V')
    {
      g_w = low_w + sib_w;
      g_h = getbig(low_h, sib_h);
      
    }
    if(g_c == 'H')
    {
      g_h = low_h + sib_h;
      g_w = getbig(low_w, sib_w);
    }
    if(p -> cutline == 'V')
    {
      new_w = cur -> width + g_w;
      new_h = getbig(cur -> height, g_h);
    }
    if(p -> cutline == 'H')
    {
      new_h = cur -> height + g_h;
      new_w = getbig(cur -> width, g_w);
    }
  
  if(new_w * new_h < (*w) * (*h))
  {
    *w = new_w;
    *h = new_h;
  }
 
  
 if(cur -> rcnode)
 {
  reroot(cur, cur -> lcnode, g_w, g_h, w, h, p -> cutline, cur -> rcnode -> width, cur -> rcnode -> height);
 }
 else
 {
   reroot(cur, cur -> lcnode, g_w, g_h, w, h, p -> cutline, cur ->  width, cur -> height);
 }
  //printf("going to turn right\n");
  //printf("cur_w = %le cur_h = %le \n", cur -> width, cur -> height);
  //*lr = 1;
  if(cur -> lcnode)
  {
  reroot(cur, cur -> rcnode, g_w, g_h, w, h, p -> cutline, cur -> lcnode -> width, cur -> lcnode -> height);
  }
  else
  {
    reroot(cur, cur -> rcnode, g_w, g_h, w, h, p -> cutline, cur -> width, cur -> height);
  }
  return;
}
    
    
    
  
  

  
  
  
  
  
  
  
  
  