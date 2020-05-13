#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "helpers.h"



int changeDate(node* head, int custID, int newDate){
//YOUR CODE STARTS HERE
    while (head != NULL) {
        if (head -> cust -> customerID == custID) {
            head -> cust -> orderDate = newDate;
            return 1;
        }
        head = head -> next;
    }
    return 0;
}




void destroyList(node* head){
//YOUR CODE STARTS HERE
    node* headcopy = head;
    while (head != NULL)
    {   
        headcopy = head;
        free (head -> cust);
        head = head -> next;
        free (headcopy);
    }
}
