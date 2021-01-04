// Name: Bhavana Laxmi Radharapu
// NetID: bradha5
//CS 211 Project 3

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int debugMode;

typedef struct mazeStruct
{
 char** arr;  /* allows for a maze of size 30x30 plus outer walls */
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

struct nodeStruct
{
    int x_cordinate;
    int y_cordinate;
    struct nodeStruct* next;
};

typedef struct nodeStruct Node;
typedef struct nodeStruct *nodePtr;

struct stackStruct
{
    nodePtr    top;
    int size;
};

typedef struct stackStruct Stack;

Stack init()
{
    Stack s;
    s.top = NULL;
    s.size = 0;
    return s;
}
//-----------------------------------------------------------------
//Checks if the stack is empty
bool isEmpty(Stack s){
    if(s.top == NULL){
        return true;
    }
    else{
        return false;
    }
}
//-----------------------------------------------------------------
//Gives the top of the stack
void top(Stack given, int* x,int* y){
    if (isEmpty(given))
    {
        return;
    }
    *x = (given.top)->x_cordinate;
    *y = (given.top)->y_cordinate;
}

//-----------------------------------------------------------------
//pushed coordinates on to stack
void push(Stack *s, int x, int y){
    Node* ptr = (Node*)malloc(sizeof(Node));
    ptr->x_cordinate = x;
    ptr->y_cordinate = y;
    ptr->next = s->top;
    s->top = ptr;
    (s->size)++;
}
//-----------------------------------------------------------------
//pops the top of the stack
void pop(Stack *s){
    Node* ptr = s->top;
    
    s->top = ptr->next;
    free(ptr);
    (s->size)--;
}
//-----------------------------------------------------------------
//print the solution stack
void printSolution(Stack *solution){
    while (solution->top->next != NULL)
    {
        printf("(%d, %d), ", solution->top->x_cordinate, solution->top->y_cordinate);
        printf("\n");
        
        pop(solution);
    }
    printf("(%d, %d)\n...Done...\n", solution->top->x_cordinate, solution->top->y_cordinate);
    pop(solution);
}
//-----------------------------------------------------------------
//Transfers the values from my_stack to solution stack
void solutionStack(Stack *given, Stack *solution){
    while (given->top != NULL)
    {
        push(solution, given->top->x_cordinate, given->top->y_cordinate);
        pop(given);
    }
}
//-----------------------------------------------------------------
// initializes maze using malloc
void initializeMaze(maze* m)
{
    m->arr = (char**)malloc((m->xsize + 2)*sizeof(char*));
    for (int i = 0; i < m->xsize + 2; i++)
    {
        m->arr[i] = (char*)malloc((m->ysize + 2) * sizeof(char));
    }
}
//-----------------------------------------------------------------
// prints the maze while using debug mode
void printMaze(maze m1)
{
    for (int i = 0; i < m1.xsize + 2; i++)
    {
        for (int j = 0; j < m1.ysize + 2; j++)
            printf("%c", m1.arr[i][j]);
        printf("\n");
    }
}
//-----------------------------------------------------------------
//Delete the maze
void deleteMaze(maze *m){
    for (int i = 0; i < m->xsize + 2; i++)
    {
        free(m->arr[i]);
    }
    free(m->arr);
}
//-----------------------------------------------------------------
//deletes the stack
void deleteStack(Stack *given){
        while (given->top)
    {
        pop(given);
    }
}
//-----------------------------------------------------------------
//main
int main (int argc, char **argv)
{
  maze m1;
  int xpos, ypos;
  int i,j;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc < 2) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
    for(int i=0;i<argc;i++){
    if((strcmp(argv[i], "-d")) == 0){
        debugMode = TRUE;
    }
    }
    
    int File = -1;
    for(int j =0; j<argc ; j++){
        if( (!(strcmp(argv[j], "-d") == 0)) && (!(strcmp(argv[j], "./a.out") == 0)) ){
            File = j;
            break;
        }
    }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[File], "r" )) == NULL )
  {
    fprintf ( stderr, "Can't open input file: %s", argv[File] );
    exit(-1);
  }
    
  /* read in the size, starting and ending positions in the maze */
    // scaning and checking for correct size
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
    if(feof(src)){
        fprintf(stderr, "\nYou have reached EOF without reading all values\n");
        exit(-1);
    }
    while( (m1.xsize <=0) || (m1.ysize <=0) || m1.xsize >30 || m1.ysize >30)
    {
        fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
      if(feof(src))
        {
            fprintf(stderr, "\nYou have reached EOF without reading all values\n");
        exit(-1);
       }
    }
    // scaning and checking for correct start points
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
    if(feof(src)){
        fprintf(stderr, "\nYou have reached EOF without reading all values\n");
        exit(-1);
    }
    while( (m1.xstart <0) || (m1.ystart <0) ||
               (m1.xstart > m1.xsize) ||(m1.ystart > m1.ysize) )
    {
        fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
      if(feof(src))
        {
            fprintf(stderr, "\nYou have reached EOF without reading all values\n");
        exit(-1);
      }
    }
     // scaning and checking for correct end points
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
    if(feof(src)){
        fprintf(stderr, "\nYou have reached EOF without reading all values\n");
        exit(-1);
    }
    while( (m1.xend <0) || (m1.yend <0) ||
               (m1.xend > m1.xsize) ||(m1.yend > m1.ysize) ||
               ( (m1.xend == m1.xstart) && (m1.yend == m1.ystart) ))
    {
        fscanf (src, "%d %d", &m1.xend, &m1.yend);
      if(feof(src))
        {
            fprintf(stderr, "\nYou have reached EOF without reading all values\n");
        exit(-1);
      }
    }
    
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

    initializeMaze(&m1);
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
          
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
         if (xpos < 0 || ypos < 0 ||xpos > 30 || ypos > 30 ||
                 xpos > m1.xsize || ypos > m1.ysize || ( (xpos == m1.xstart) && (ypos == m1.ystart)) ||
                 ( (xpos == m1.xend) && (ypos == m1.yend)) )
             printf("\nTrying to set block position at an invalid position\n");
         else
      m1.arr[xpos][ypos] = '*';
    }
 /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);
     printf("\n");
    }
     
    //initialize
    Stack my_stack = init();
    Stack solution = init();
    //push start position to stack
    push(&my_stack, m1.xstart,m1.ystart);
    // set the start position of start to visited
    m1.arr[m1.xstart][m1.ystart] = 'v';
    
    //current position of x and y
    int x_current = m1.xstart;
    int y_current = m1.ystart;

    // to loop through till the stack is empty or find a ssolution
    while(!isEmpty(my_stack)){
        
        //gets top of the stack
        top(my_stack,&x_current,&y_current);
        
        //checos if there is a solotion by checking for start and end points
        if(x_current == m1.xend && y_current == m1.yend){
            solutionStack(&my_stack, &solution);
            break;
        }
      // checks right side of the current position
      if ((m1.arr[x_current][y_current + 1] != '*') && (m1.arr[x_current][y_current + 1] != 'v'))
      {

            push(&my_stack, x_current, y_current + 1);
          m1.arr[x_current ][y_current + 1] = 'v';
            //debug mode
            if(debugMode == TRUE){
                printf("Cordinates pushed on stack: ");
                printf("%d %d",x_current,y_current + 1);
            }

      }
        // checks down of the current position
        else if((m1.arr[x_current + 1][y_current] != '*') && (m1.arr[x_current + 1][y_current ] != 'v'))
      {
          push(&my_stack, x_current + 1, y_current );
          m1.arr[x_current + 1][y_current] = 'v';
            //debug mode
            if(debugMode == TRUE){
                printf("Cordinates pushed on stack: ");
                printf("%d %d",x_current + 1,y_current);
            }

      }
        //checks for left side of the current position
      else if ((m1.arr[x_current][y_current - 1] != '*') && (m1.arr[x_current][y_current - 1] != 'v'))
      {
          push(&my_stack, x_current, y_current - 1);
          m1.arr[x_current][y_current - 1] = 'v';
            //debug mode
            if(debugMode == TRUE){
                printf("Cordinates pushed on stack: ");
                printf("%d %d",x_current,y_current - 1);
            }
          
      }
        //checks up of the current position
      else if ((m1.arr[x_current - 1][y_current] != '*') && (m1.arr[x_current - 1][y_current] != 'v'))
      {
          push(&my_stack, x_current - 1, y_current);
          m1.arr[x_current - 1][y_current] = 'v';
            //debug mode
            if(debugMode == TRUE){
                printf("Cordinates pushed on stack: ");
                printf("%d %d",x_current - 1,y_current);
            }
          
      }
        //pops in case all directions are visited to blocked and goes back to previous position
      else
      {
          pop(&my_stack);
            //debug mode
            if(debugMode == TRUE){
                printf("Cordinates poped from stack: ");
                printf("%d %d",x_current,y_current);
            }
      }
        //prints the maze while using debug mode
      if (debugMode == TRUE)
      {
          printf("\n\n");
          printMaze(m1);
          printf("\n\n");
      }

  }
    // checks if the stack has the solution or if empty
  if (isEmpty(solution))
  {
      printf("No Solution...\nExiting...\n");
  }
  else
  {
      printf("Solution found!!!\npath:\n");
      printSolution(&solution);
  }
  deleteMaze(&m1);
  deleteStack(&solution);
  fclose(src);
    
    return 0;
}
//end main
