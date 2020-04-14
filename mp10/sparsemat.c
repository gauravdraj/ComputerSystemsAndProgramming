#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
    sp_tuples* tupPtr = (sp_tuples*)malloc(sizeof(sp_tuples));
    tupPtr -> m = 0;
    tupPtr -> n = 0;
    tupPtr -> nz = 0;
    tupPtr -> tuples_head = NULL;
    FILE* data = fopen(input_file, "r");
    fscanf(data, "%d %d", &(tupPtr->m), &(tupPtr->n));
    int row = 0;
    int col = 0;
    double val = 0.0;
    while (fscanf(data, "%d %d %lf", &row, &col, &val) != EOF) {
        set_tuples(tupPtr, row, col, val);
    }
    fclose(data);
    return tupPtr;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)
{
    sp_tuples_node* current = (mat_t -> tuples_head);
    while (current != NULL) {
        if (current -> row != row && current -> col != col) current = (current -> next);
        else return current -> value;
    }
    return 0;
}


void remove_node(sp_tuples* mat_t, int row, int col) {
    sp_tuples_node* current = mat_t -> tuples_head;
    sp_tuples_node* temp = NULL;
    while (current -> next != NULL) {
        if (current -> row == row && current -> col == col) {
            temp = current;
            mat_t -> tuples_head = current -> next;
            free(temp);
            --(mat_t -> nz);
            return;
        }
        else if ((current -> next) -> row == row && (current -> next) -> col == col) {
            temp = current -> next;
            current -> next = (current -> next) -> next;
            free(temp);
            --(mat_t -> nz);
            return;
        }
        current = current -> next;
    }  
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (value == 0 && gv_tuples(mat_t, row, col) !=0) remove_node(mat_t, row, col);
    if (value == 0) return;
    sp_tuples_node* tuple = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    tuple -> row = row;
    tuple -> col = col;
    tuple -> value = value;
    tuple -> next = NULL;
    if (mat_t -> tuples_head == NULL) {
        mat_t -> tuples_head = tuple;
        (mat_t -> nz) = (mat_t -> nz) + 1;
        return;
    }
    sp_tuples_node* current = mat_t -> tuples_head;
    while (current != NULL) {
        if (current == mat_t -> tuples_head && current -> next == NULL) {
            if (row < current -> row || (row == current -> row && col < current -> col)) {
                tuple -> next = mat_t -> tuples_head;
                mat_t -> tuples_head = tuple;
                ++(mat_t -> nz);
                return;
            }
            else {
                (mat_t -> tuples_head) -> next = tuple;
                ++(mat_t -> nz);
                return;
            }
        }
        if (current -> row == row && current -> col == col) {
            current -> value = value;
            free(tuple);
            return;
        }
        if (current -> next == NULL){
            current -> next = tuple;
            ++(mat_t -> nz);
            return;
        }
        /*if (((current -> next) -> row >= row) && (current == mat_t -> tuples_head)) {
             if ((current -> row == row && (current -> next) -> col > col) || (current -> next -> row) > row) {
                tuple -> next = mat_t -> tuples_head;
                mat_t -> tuples_head = tuple;
                ++(mat_t -> nz);
                return;
            }
            else {
                (mat_t -> tuples_head) -> next = tuple;
                ++(mat_t -> nz);
                return;
            }
        } **/
        if ((current -> next) -> row >= row) {
            if ((current -> row == row && (current -> next) -> col > col) || (current -> next -> row) > row) {
                tuple -> next = current -> next;
                current -> next = tuple;
                ++(mat_t -> nz);
                return;
            }
        }
        current = current -> next;
    }
}


void save_tuples(char * file_name, sp_tuples * mat_t)
{
    FILE* data = fopen(file_name, "w");
    fprintf(data, "%d %d\n", mat_t -> m, mat_t -> n);
    sp_tuples_node* current = mat_t -> tuples_head;
    while (current != NULL) {
        fprintf(data, "%d %d %lf\n", current -> row, current -> col, current -> value);
        current = current -> next;
    }
    fclose(data);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
    if (matA -> m != matB -> m || matA -> n != matB -> n) return NULL;
    sp_tuples* retmat = (sp_tuples*)malloc(sizeof(sp_tuples));
    retmat -> m = matA -> m;
    retmat -> n = matB -> n;
    retmat -> nz = 0;
    retmat -> tuples_head = NULL;
    sp_tuples_node* currentA = matA -> tuples_head;
    while(currentA != NULL) {
        set_tuples(retmat, currentA -> row, currentA -> col, currentA -> value);
        currentA = currentA -> next;
    }
    sp_tuples_node* currentB = matB -> tuples_head;
    while (currentB != NULL) {
        double valInB = gv_tuples(matB, currentB -> row, currentB -> col);
        double valInC = gv_tuples(retmat, currentB -> row, currentB -> col);
        set_tuples(retmat, currentB -> row, currentB -> col, valInC + valInB);
        currentB = currentB -> next;
    }
	return retmat;
}


// Optional (not graded)
sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
  return NULL;
}


	
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node* current = mat_t -> tuples_head;
    while (current != NULL) {
        current = current -> next; 
        free(current);
    }
    free(mat_t -> tuples_head);
    free(mat_t);
    return;
}  