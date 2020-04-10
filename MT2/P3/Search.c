#include <stdio.h>
#include "Search.h"

//Your implementation of this function must be recursive
//return 1 if item found in data; otherwise, return 0
int Search(int item, int data[ROW][COL], int start_row, int end_row, int start_col, int end_col){
    //Your code starts here
    if ((start_row > end_row) || (start_col > end_col)) return 0;
    if (start_col != end_col) {
        int mid = (end_col+start_col)/2;
        if (item >= data[0][mid]) {
            start_col = mid;
        } else {
            end_col = mid;
        }
        if (end_col - 1 == start_col && data[0][end_col] > item) end_col = start_col;
        if (end_col - 1 == start_col && data[0][end_col] <= item) start_col = end_col;
        return Search(item, data, start_row, end_row, start_col, end_col);
    }
    int mid = (end_row+start_row)/2;
    if (item == data[mid][start_col]) return 1;
    if (item < data[mid][start_col]) {
        return Search(item, data, start_row, mid - 1, start_col, end_col);
    }
    if (item > data[mid][start_col]) {
        return Search(item, data, mid + 1, end_row, start_col, end_col);
    }
    return 0;
}


