//singly linked list library for a data structure storing integers by Arjun Mair (TheRubberDucky)

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    long long value; //this is the value the node stores
    long long timestamp; //this is the timestamp in microseconds
    struct node *next; //this is the node the current node points to. this is how the nodes link
}node;

void printList(node *head){
    node *tmp = head;

    while(tmp != NULL){
        printf("Latency: %lld, Timestamp: %lld \n", tmp->value, tmp->timestamp);
        tmp = tmp->next;
    }
}

int len(node *head){
    node *tmp = head;
    int counter = 0;

    while(tmp != NULL){
        counter += 1;
        tmp = tmp->next;
    }
    return counter;
}

node *createNode(long long val, long long timestamp){
    node *result = malloc(sizeof(node));
    result->value = val;
    result->timestamp = timestamp;
    result->next = NULL;
    return result;
}

//to create a list you have to give it an initial value
node *createList(long long initial_value, long long timestamp){
    node *head;
    node *init_val = createNode(initial_value, timestamp);

    head = init_val;
    head->next = NULL;

    return head;
}

node *append(node *head, long long val, long long timestamp){
    node *tmp = head;
    node *createdNode = createNode(val, timestamp);

    while(tmp->next != NULL){
        tmp = tmp->next;
    }

    tmp->next = createdNode;
    return head;
}

node *insert(node *head, int index, long long val, long long timestamp){
    node *tmp = head;
    node *createdNode = createNode(val, timestamp);
    node *nxt; //this stores the index after the one we get from while loop

    //base case for if the index is larger or equal to the length of the head
    if(index >= len(head)){
        return NULL;
    }

    //if the index is intended for the beginning
    if(index == 0){
        nxt = head;
        head = createdNode;
        head->next = nxt;
        return head;
    }

    //if the index is intended for the end
    if(index == -1){
        int count = 0;

        while(count < len(head)-1){
            tmp = tmp->next;
            count += 1;
        }
        tmp->next = createdNode;
        return head;
    }

    while(index-1 != 0){
        tmp = tmp->next;
        index -= 1;
    }

    //this allows for us to access the node once we rewire the prev node to connect to the new node
    nxt = tmp->next;

    tmp->next = createdNode;
    tmp->next->next = nxt;

    return head;
}

node *rmvNode(node *head, int index){
    node *tmp = head;
    node *rmv;
    int count = 0;

    //base case for if the user enters a value greater then or equal to the length of the head
    //base case for if the user enters a value with a list of length 1. because in this library a list MUST contain one value minimum
    if(index >= len(head) || len(head) == 1){
        return NULL;
    }

    //if you want to remove the first value
    if(index == 0){
        rmv = head; //stores the head at this given moment in time
        head = tmp->next; //this jumps the position of the head making sure that the beginning is no longer part of the head
        free(rmv); //this frees the memory given to the initial head
        return head;
    }

    //if you want to remove index position 1
    if(index == 1){
        rmv = head->next;
        head->next = tmp->next->next;
        free(rmv);
        return head;
    }

    //if you want to remove the last value
    if(index == -1){

        while(count < len(head)-2){ //we do -2 because we want to access the node before the last one
            tmp = tmp->next;
            count += 1;
        }
        rmv = tmp->next;
        tmp->next = NULL;
        free(rmv);
        return head;
    }

    //remove anything else
    while(count < index-1){
        tmp = tmp->next;
        count += 1;
    }
    rmv = tmp->next;
    tmp->next = tmp->next->next;
    free(rmv);
    return head;

}

node *ammendValue(node *head, int index, long long val){
    node *tmp = head;
    int count = 0;

    //if the user enters an index greater then the length of the list
    if(index > len(head)){
        return NULL;
    }

    //if the last value needs editing
    if(index == -1){
        while(count < len(head)-1){
            tmp = tmp->next;
            count += 1;
        }
        tmp->value = val;
        return head;
    }

    //if the first value needs editing
    if(index == 0){
        head->value = val;
        return head;
    }

    //for any other case
    while(count < index){
        tmp = tmp->next;
        count += 1;
    }

    tmp->value = val;
    return head;
}

// int main(){
//     node *head;
//     head = createList(20, 0);
//     printf("\nthis is me creating the list\n");
//     printList(head);

//     //get the length of the list
//     printf("\n\nthis is me checking the length of the list\n");
//     printf("%i", len(head));

//     //add values to the end of the list
//     head = append(head, 30);
//     head = append(head, 40);
//     head = append(head, 50);
//     printf("\n\nthis is me appending values to the end of the list 3 times\n");
//     printList(head);

//     //get the length of the list
//     printf("\n\nthis is me checking the length of the list\n");
//     printf("%i", len(head));

//     //add values in between the list
//     head = insert(head, 1, 60);
//     printf("\n\nthis is me inserting a value into index 1 position\n");
//     printList(head);

//     //get the length of the list
//     printf("\n\nthis is me checking the length of the list\n");
//     printf("%i", len(head));

//     //remove values from the list
//     head = rmvNode(head, 1);
//     printf("\n\nthis is me removing the index 2 value from the list\n");
//     printList(head);

//     //get the length of the list
//     printf("\n\nthis is me checking the length of the list\n");
//     printf("%i", len(head));

//     //ammend values
//     printf("\n\nthis is me ammending the values in a list\n");
//     head = ammendValue(head, 2, 1010);
//     printList(head);
//     return 0;
// }
