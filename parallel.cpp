#include <omp.h>
#include "my_timer.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <cstddef>

typedef struct grid {
  //two boards needed for testing boards and correct answers
  //originally was a class called SudokuGrid in the serial version
  short **guesses;
  short **fixed;
} SUDOKUGRID;

//linkedList
struct listElements {
   SUDOKUGRID grid;
   short i, j;
   struct listElements *next;
};

typedef struct listElements list;
//makes grid size scalable
int l;
int SIZE;
FILE *inputGrid;
SUDOKUGRID solution;
//linked list stuff
list *head;
list *tail;

SUDOKUGRID readStringToBoard(char *filename) {
  int i,j;  
  SUDOKUGRID grid;  
  int element_int;
  inputGrid = fopen(filename, "rt");
  fscanf(inputGrid, "%d", &element_int);
  l = element_int;
  SIZE = l*l;
  grid.guesses = (short**)malloc(SIZE*sizeof(short*));  
  for (i=0;i<SIZE;i++)
    grid.guesses[i] = (short*) malloc (SIZE * sizeof (short));
  grid.fixed = (short**) malloc(SIZE * sizeof(short*));
  for (i=0;i<SIZE;i++)
    grid.fixed[i] = (short*) malloc (SIZE * sizeof (short));  
  // set all to 0 as we did in the SudokuGrid Class to initialize
  for (i=0; i<SIZE; i++) {
    for (j=0; j<SIZE; j++) {     
      grid.fixed[i][j] = 0;
    }
  }
  
  for(i = 0; i < SIZE; i++) {
    for(j = 0; j < SIZE; j++){
      fscanf(inputGrid, "%d", &element_int);
      grid.guesses[i][j] = element_int;
      //set to 1 if filled already
      if (grid.guesses[i][j] != 0)
        grid.fixed[i][j] = 1;
    }  
  }
  fclose(inputGrid);
  return grid;
}


void print(SUDOKUGRID *grid) {
  int col,row;
  printf("\n-------------------\n");
  for (col = 0; col < SIZE; col++) {
    printf("|");
    for (row = 0; row < SIZE; row=row+3) {
      printf("%1d %1d %1d|",grid->guesses[col][row],grid->guesses[col][row+1],grid->guesses[col][row+2]);
    }
    if((col+1)%3==0){
      printf("\n-------------------\n");
    } else {
      printf("\n");
    }
  }
}


short checkAll(SUDOKUGRID grid, short x_line, short x_col) {
  short line, column;
  short value = grid.guesses[x_line][x_col];

  // Previously checkColumn 
  for (line = 0; line < SIZE; line++) {
    if (grid.guesses[line][x_col] == 0)
      continue;

    if ((x_line != line) && 
        (grid.guesses[line][x_col] == value)) 
      return 0;
  }

  // previously checkRow
  for (column = 0; column < SIZE; column++) {
    if (grid.guesses[x_line][column] == 0)
      continue;

    if (x_col != column && grid.guesses[x_line][column] == value)
      return 0;
  }
  
  // previously checkBox TODO
  short x_group = (x_line / l) * l;
  short y_group = (x_col / l) * l;
  for (line = x_group; line < x_group+l; line++) {
    for (column = y_group; column < y_group+l; column++) {
      if (grid.guesses[line][column] == 0)
        continue;
      if ((x_line != line) &&
          (x_col != column) &&
          (grid.guesses[line][column] == value)) {
        return 0;
      }
    }
  }
  return 1;
}

void decreasePosition(SUDOKUGRID* grid, short* iPointer, short* jPointer){
      do {
        if (*jPointer == 0 && *iPointer > 0) {
          *jPointer = SIZE - 1;
          (*iPointer)--;
        } else
          (*jPointer)--;
      } while (*jPointer >= 0 && (*grid).fixed[*iPointer][*jPointer] == 1);
}

void increasePosition(SUDOKUGRID* grid, short* iPointer, short* jPointer){
  
  do{
    if(*jPointer < SIZE-1)
      (*jPointer)++;
    else {
      *jPointer = 0;
      (*iPointer)++;
    }
  } while (*iPointer < SIZE && (*grid).fixed[*iPointer][*jPointer]);
}

//linked list stuff
void freeListElement(list *node) {
  int i;
  for (i = 0; i < SIZE; i++) {
    free(node->grid.guesses[i]);
    free(node->grid.fixed[i]);
  }
  free(node->grid.guesses);
  free(node->grid.fixed);
  free(node);
}

//linked list stuff
list* createList(SUDOKUGRID grid, short i, short j){
  list * curr = (list *)malloc(sizeof(list));
  int m;
  short x, y;
  /* allocate memory for new copy */
  curr->grid.guesses = (short**)malloc(SIZE*sizeof(short*));
  for (m=0;m<SIZE;m++)
    curr->grid.guesses[m] = (short*) malloc (SIZE * sizeof (short));  
  curr->grid.fixed = (short**) malloc(SIZE * sizeof(short*));
  for (m=0;m<SIZE;m++)
    curr->grid.fixed[m] = (short*) malloc (SIZE * sizeof (short));
  for(x = 0; x < SIZE; x++){
    for(y = 0; y < SIZE; y++){
      curr->grid.guesses[x][y] = grid.guesses[x][y];
      curr->grid.fixed[x][y] = grid.fixed[x][y]; 
    }
  }
  curr->i = i;
  curr->j = j;
  curr->next = NULL; 
  return curr;
}

//linked list stuff
void attachItem(list* newItem){
  if(head == NULL){
    head = newItem;
    tail = newItem;
  } else {
    tail->next = newItem;
    tail = newItem;
  }
}
  

//linked list stuff
list* removeItem(){
  list* result = NULL;
  if(head != NULL){
    result = head;
    head = result->next;
    if(head == NULL){
      tail = NULL;
    }
  }
  return result;
}

void initializeBruteForce(SUDOKUGRID* grid){
  short i = 0;
  short j = 0;

  if ((*grid).fixed[i][j] == 1)
    increasePosition(grid, &i, &j);

  short num=0;
  list* current = NULL;

  while(1) {
    ((*grid).guesses[i][j])++;    
    //check to make sure it is valid  
    if (grid->guesses[i][j] <= SIZE && checkAll(*grid, i, j) == 1) {
      list* newPath = createList(*grid, i, j);
      attachItem(newPath);
      num++;
    } else if(grid->guesses[i][j] > SIZE) {
      if(current != NULL){
        freeListElement(current);
      }      
      if(num >= SIZE){
        break;
      }
      list* current = removeItem();
      if(current == NULL){
        break;
      }
      grid = &(current->grid);
      i = current->i;
      j = current->j;
      if(i == SIZE-1 && j == SIZE-1){
        //solved
        attachItem(current);
        break;
      }

      num--;

      increasePosition(grid, &i, &j);
    }
 }
 if(current != NULL){
    freeListElement(current);
 }
}

short bruteForceParallel(SUDOKUGRID grid) {

  head = NULL;
  tail = NULL;
  initializeBruteForce(&grid);

  short found = 0;
  short i, j;
  list* current;
  int level;

#pragma omp parallel shared(found) private(i,j, current, level)
{
  #pragma omp critical (deadlocks)
  current = removeItem();
  while(current != NULL && found == 0){
    SUDOKUGRID currentGrid = current->grid;
    i = current->i;
    j = current->j;

    increasePosition(&currentGrid, &i, &j);
    level = 1;
    while (level > 0 && i < SIZE && found == 0) {
      if (currentGrid.guesses[i][j] < SIZE) {    
        // increase cell value and run checks
        currentGrid.guesses[i][j]++;
        if (checkAll(currentGrid, i, j) == 1) {
          increasePosition(&currentGrid, &i, &j);
          level++;
        }
      } else {
        currentGrid.guesses[i][j] = 0;
        decreasePosition(&currentGrid, &i, &j);
        level--;
      }
    }
    if(i == SIZE){
      found = 1;
      solution = currentGrid;
      continue;
    }
    free(current);
    #pragma omp critical (deadlocks)
    current = removeItem();
   }
}
  return found;
}

int main(int argc, char* argv[]) {
	//parallel testpuzzle.txt threadNumber
  myTimer_t t0;  
  int thread_count = atoi(argv[2]);
  int max_threads = omp_get_max_threads();


    printf("omp_get_max_threads = %d\n", omp_get_max_threads());
    printf(" %d threads going\n", thread_count);

    if (thread_count > 1)
    {
        //Static assignment to get consistent usage across trials
        int max_threads = omp_get_max_threads();
            printf("%d threads going", atoi(argv[2]));
            omp_set_num_threads(thread_count);
            SUDOKUGRID m = readStringToBoard(argv[1]);
            printf("testBoard:");
            print(&m);
            
            //TODO START TIMER
            t0 = getTimeStamp();

            //sending the input grid to the bruteForceParallel method which would return 1 if a solution is found
            short hasSolution = bruteForceParallel(m);
            if(hasSolution == 0){
              printf("invalidBoard\n");
              return 1;
            }


    }
    else
    {
        //Set thread count
        printf("SERIAL WE DO NOT WANT TO BE HERE");
}
  //TODO END TIMER
  myTimer_t t1 = getTimeStamp();
  printf("Solved:");
  std::cout << getElapsedTime(t0,t1) << std::endl;
  print(&solution);


  //MEMORY Cleanup From Linked List algorithm code
  list* node = head;
  while (node != NULL) {
    list* next = node->next;
    freeListElement(node);
    node = next;
  }
 
  return 0;

}
