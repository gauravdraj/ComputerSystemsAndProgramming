#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/* This program implements a sparse matrix using a linked list
of tuple nodes and a structure that contains the rows, columns, and the
number of non zero values in the matrix, as well as a pointer to the head
node. It first loads the tuples in from a file. This is done by creating a
sp_tuples struct and initializing the number of rows, columns, and non zero
values to 0, and the head pointer is set to NULL. It then gets the row and col
values from the first line of the file and then keeps scanning and setting tuples
until it hits the end of the file. gv_tuples iterates through the linked list until
it finds a matching row and column, and then returns the value at that node. If not
found, it will return 0. remove_node is a helper function that will remove the node
from the linked list if the value is 0 and it exists within thelinked list already. 
It will iterate through the list until it finds the right row/col and frees the pointer
that points to the node. set_tuples calls remove_node if the value is 0 and the row/col
exists in the list or just ignores it if it doesn't exist. If it's not a 0, it will
create a new tuple node and iterate through the list and find the right place to put it,
determined via row-major order. If the row/col already exists, the value is updated.
save_tuples goes through the linked list of tuples nodes and prints them to a file, with
the rows and columns printed as the first line. add_tuples takes in two tuples structures
to add them. If they don't have the same number of rows and columns then it returns NULL.
If not, it initializes a new tuples structure and adds the contents of matrix A to it,
then add the contents of matrix B to the updated structure, and then returns it.
destroy_tuples iterates through the list and frees the next node to to the current node,
then frees the current node and the tuples structures. 

partner: pranay2
*/

sp_tuples * load_tuples(char* input_file) {
    sp_tuples* tupPtr = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate tuples structure
    tupPtr -> m = 0; //initialize all variables in tuples structure
    tupPtr -> n = 0;
    tupPtr -> nz = 0;
    tupPtr -> tuples_head = NULL;
    FILE* data = fopen(input_file, "r"); //open file for reading
    fscanf(data, "%d %d", &(tupPtr->m), &(tupPtr->n)); //scan to get row and column
    int row = 0; //initialize row col and val variables
    int col = 0;
    double val = 0.0;
    while (fscanf(data, "%d %d %lf", &row, &col, &val) != EOF) { //keep scanning until end of file
        set_tuples(tupPtr, row, col, val); //set tuples accordingly
    }
    fclose(data); //close file
    return tupPtr; //return tuples structure
}



double gv_tuples(sp_tuples * mat_t,int row,int col) {
    sp_tuples_node* current = mat_t -> tuples_head; //initialize iteration node to head
    while (current != NULL) { //iterate until null
        if (current -> row == row && current -> col == col) return current -> value; //if row and col match, return val
        current = current -> next; //update iterator
    }
    return 0; //if not found, return 0
}


void remove_node(sp_tuples* mat_t, int row, int col) {
    sp_tuples_node* current = mat_t -> tuples_head; //initialize iteration node to head
    sp_tuples_node* temp = NULL; //initialize temp pointer to null
    while (current != NULL) { //iterate until null
        if ((current -> next) -> row == row && (current -> next) -> col == col) { //if next one matches
            temp = current -> next; 
            current -> next = (current -> next) -> next; //next is next's next
            free(temp); //free node
            --(mat_t -> nz); //decrement non zero
            return;
        }
        current = current -> next; //increment iteration pointer
    }  
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value) {
    if (value == 0 && gv_tuples(mat_t, row, col) !=0) remove_node(mat_t, row, col); //if 0 and exists, remove
    if (value == 0) return; //if 0 and doesn't exist, ignore
    sp_tuples_node* tuple = (sp_tuples_node*)malloc(sizeof(sp_tuples_node)); //allocate tuple node
    tuple -> row = row; //initialize all variables in tuple node
    tuple -> col = col;
    tuple -> value = value;
    tuple -> next = NULL;
    int tupIndex = row * (mat_t -> n) + col; //convert row/col to row major order index
    if (mat_t -> tuples_head == NULL) { //if no head, then tuple is new head
        mat_t -> tuples_head = tuple;
        ++(mat_t -> nz);
        return;
    }
    sp_tuples_node* current = mat_t -> tuples_head; //initialize iteration node to head
    while (current != NULL) { //iterate until null
        int curIndex = (current -> row) * (mat_t -> n) + (current -> col); //convert current row/col to row major order index
        if (current == mat_t -> tuples_head) { //if at head
            if (tupIndex < curIndex) { //if new index is smaller than head index
                tuple -> next = mat_t -> tuples_head; //place before head
                mat_t -> tuples_head = tuple; //update head
                ++(mat_t -> nz); //increment non zero
                return; 
            }
        }
        if (tupIndex == curIndex) { //if index already exists and at index
            current -> value = value; //update value
            free(tuple); //free allocated tuple
            return;
        }
        if (current -> next == NULL){ //if at tail
            current -> next = tuple; //next is automatically inputted node
            ++(mat_t -> nz); //increment non zero
            return;
        }
        int nextIndex = (current -> next -> row) * (mat_t -> n) + (current -> next -> col); //next index in row major order
        if (nextIndex > tupIndex && tupIndex > curIndex) { //if in right spot
            tuple -> next = current -> next; //update next
            current -> next = tuple;
            ++(mat_t -> nz); //increment non zero
            return;
        }
        current = current -> next; //incrememnt interation node
    }
}


void save_tuples(char * file_name, sp_tuples * mat_t) {
    FILE* data = fopen(file_name, "w"); //open file in write mode
    fprintf(data, "%d %d\n", mat_t -> m, mat_t -> n); //print row and col to first line
    sp_tuples_node* current = mat_t -> tuples_head; //initialize iteration node to head
    while (current != NULL) { //iterate until null
        fprintf(data, "%d %d %lf\n", current -> row, current -> col, current -> value); //print each row/col/val to file
        current = current -> next; //increment iteration node
    }
    fclose(data); //close file
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB) {
    if (matA -> m != matB -> m || matA -> n != matB -> n) return NULL; //if rows/cols don't match, return NULL
    sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples)); //allocate tuples struct memory
    retmat -> m = matA -> m; //intialize all variables in tuples struct
    retmat -> n = matB -> n;
    retmat -> nz = 0;
    retmat -> tuples_head = NULL;
    sp_tuples_node* currentA = matA -> tuples_head; //initialize matrix A iteration node to A's head
    while(currentA != NULL) { //iterate through A until null
        set_tuples(retmat, currentA -> row, currentA -> col, currentA -> value); //set row/col at C to row/col at A
        currentA = currentA -> next; //increment matrix A iteration node
    }
    sp_tuples_node* currentB = matB -> tuples_head; //initialize matrix B iteration node to B's head
    while (currentB != NULL) { //iterate through B until null
        double valInB = gv_tuples(matB, currentB -> row, currentB -> col); //get val in row/col from matrix B
        double valInC = gv_tuples(retmat, currentB -> row, currentB -> col); //get val in B's row/col from C
        set_tuples(retmat, currentB -> row, currentB -> col, valInB + valInC); //update row/col in C to sum
        currentB = currentB -> next; //increment matrix B iteration node
    }
	return retmat; //return matrix C
}


// Optional (not graded)
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
  return NULL;
}


	
void destroy_tuples(sp_tuples * mat_t) {
	sp_tuples_node* current = mat_t -> tuples_head; //initialize iteration node to head
    sp_tuples_node* temp = NULL; //initialize temp to null
    while (current -> next != NULL) { //iterate until null
        temp = current;
        current = current -> next; //set current to next
        free(temp); //free original current
    }
    free(current); //free head
    free(mat_t); //free matrix structure
    return;
}  