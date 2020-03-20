#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define SIZE 20

typedef struct stack_k{
    int data;
    struct stack_k *next;
}stack;

typedef struct bst_t{
    int data;
    struct bst_t *left;
    struct bst_t *right;
}bst;

typedef struct queue_t{
    int data;
    struct queue_t *next;
}queue;

void fill_structures(stack **, queue **, bst **, int []);
void ordered_print(stack *, queue *, bst *);
void search(stack *, queue *, bst *, int);
void special_traverse(stack *stack_, queue *queue_, bst *bst_);
void fillStack(stack **, int []);
void fillQueue(queue **,int []);
void fillBST(bst **, int []);
bst *insert(bst *, int);
void sortStack(stack *);
void sortQueue(queue *);
void sortBST(bst *);
int sizeStack(stack *);
int sizeQueue(queue *);
void searchingStack(stack *, int);
void searchingQueue(queue *, int);
void searchingBST(bst *,int, int, int);
void deleteStack(stack **, int);
void special_traverse_stack(stack *);
int maxStack(stack *);
int minStack(stack *);
void deleteQueue(queue **, int);
int maxQueue(queue *);
int minQueue(queue *);
void special_traverse_queue(queue *);
bst *maxBST(bst *);
bst *minBST(bst *);
void special_traverse_BST(bst *);
bst *delete(bst *, int);

int main(){
    int data[SIZE]={5, 2, 7, 8, 11, 3, 21, 7, 6, 15, 19, 35, 24, 1, 8, 12, 17, 8, 23, 4};
    bst *bst_ = NULL;
    queue *queue_ = NULL;
    stack *stack_ = NULL;
    fill_structures(&stack_, &queue_, &bst_, data);
    ordered_print(stack_, queue_, bst_);
    search(stack_, queue_, bst_, 5);
    special_traverse(stack_, queue_, bst_);
    return 0;
}

void fill_structures(stack **stack_, queue **queue_, bst **bst_, int data[SIZE]){
    clock_t time;
    time = clock();
    fillStack(stack_,data);
    time = clock() - time;
    double time_taken_stack = ((double)time) / CLOCKS_PER_SEC;
    
    time = clock();
    fillQueue(queue_, data);
    time = clock() - time;
    double time_taken_queue = ((double)time) / CLOCKS_PER_SEC;
    
    time = clock();
    fillBST(bst_, data);
    time = clock() - time;
    double time_taken_BST = ((double)time) / CLOCKS_PER_SEC;
    
    printf("\nStructers \t Stack \t\t Queue \t\t BST \n");
    printf("Exec.Time \t %f \t %f \t %f \n\n",time_taken_stack,time_taken_queue,time_taken_BST);
}

void fillStack(stack **stack_, int data[SIZE]){
    stack *temp;
    int i;
    for(i=0;i<SIZE;i++){
        temp = (stack *)malloc(sizeof(stack));
        temp->data = data[i];
        temp->next = *stack_;
        *stack_ = temp;
    }
}

void fillQueue(queue **queue_,int data[SIZE]){
    queue *temp;
    queue *head = NULL, *tail = NULL;
    int i;
    for(i=0;i<SIZE;i++){
        temp = (queue *)malloc(sizeof(queue));
        temp->data = data[i];
        temp->next = NULL;
        if(head == NULL){
            head = temp;
            tail = temp;
        }
        else{
            tail->next = temp;
            tail = temp;
        }
    }
    *queue_ = head;
}

void fillBST(bst **bst_, int data[SIZE]){
    int i;
    bst *temp;
    temp = (bst *)malloc(sizeof(bst));
    temp = NULL;
    for(i=0;i<SIZE;i++)
        temp = insert(temp,data[i]);
    *bst_ = temp;
}

bst *insert(bst *node, int data){
    if(node == NULL){
        bst *temp;
        temp = (bst *)malloc(sizeof(bst));
        temp->data = data;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if(data > (node->data))
        node->right = insert(node->right, data);
    if(data < (node->data))
        node->left = insert(node->left, data);
    return node;
}

void ordered_print(stack *stack_, queue *queue_, bst *bst_){
    clock_t time;
    time = clock();
    sortStack(stack_);
    printf("ORDERED STACK\n");
    while(stack_ != NULL){
        printf("%d ",stack_->data);
        stack_ = stack_->next;
    }
    time = clock() - time;
    double time_taken_stack = ((double)time) / CLOCKS_PER_SEC;
    printf("\nTIME : %f\n\n",time_taken_stack);
    
    time = clock();
    sortQueue(queue_);
    printf("ORDERED QUEUE\n");
    while(queue_ != NULL){
        printf("%d ",queue_->data);
        queue_ = queue_->next;
    }
    time = clock() - time;
    double time_taken_queue = ((double)time) / CLOCKS_PER_SEC;
    printf("\nTIME : %f\n\n",time_taken_queue);
    
    printf("ORDERED BST\n");
    time = clock();
    sortBST(bst_);
    time = clock() - time;
    double time_taken_BST = ((double)time) / CLOCKS_PER_SEC;
    printf("\nTIME : %f\n\n",time_taken_BST);
}

void sortBST(bst *head){
    if(head != NULL){
        sortBST(head->right);
        printf("%d ",head->data);
        sortBST(head->left);
    }
}

void sortQueue(queue *head){
    queue *temp, *temp_1, *temp_2;
    int size;
    int i, j, k;
    size = sizeQueue(head);
    temp = (queue *)malloc(sizeof(queue));
    temp_1 = (queue *)malloc(sizeof(queue)*size);
    temp_1 = head;
    for(i=0;i<size-1;i++){
        temp_2 = (queue *)malloc(sizeof(queue)*size);
        temp_2 = head;
        j = i + 1;
        for(k=0;k<j;k++)
            temp_2 = temp_2->next;
        for(j=i+1;j<size;j++){
            if(temp_1->data < temp_2->data){
                temp->data = temp_1->data;
                temp_1->data = temp_2->data;
                temp_2->data = temp->data;
            }
            temp_2 = temp_2->next;
        }
        temp_1 = temp_1->next;
        free(temp_2);
    }
}

void sortStack(stack *head){
    stack *temp, *temp_1, *temp_2;
    int size;
    int i, j, k;
    size = sizeStack(head);
    temp = (stack *)malloc(sizeof(stack));
    temp_1 = (stack *)malloc(sizeof(stack)*size);
    temp_1 = head;
    for(i=0;i<size-1;i++){
        temp_2 = (stack *)malloc(sizeof(stack)*size);
        temp_2 = head;
        j = i + 1;
        for(k=0;k<j;k++)
            temp_2 = temp_2->next;
        for(j=i+1;j<size;j++){
            if(temp_1->data < temp_2->data){
                temp->data = temp_1->data;
                temp_1->data = temp_2->data;
                temp_2->data = temp->data;
            }
            temp_2 = temp_2->next;
        }
        temp_1 = temp_1->next;
        free(temp_2);
    }
}

int sizeStack(stack *head){
    int i = 0;
    while(head != NULL){
        head = head->next;
        i++;
    }
    return i;
}

int sizeQueue(queue *head){
    int i = 0;
    while(head != NULL){
        head = head->next;
        i++;
    }
    return i;
}

void search(stack *stack_, queue *queue_, bst *bst_, int val_to_search){
    clock_t time;
    time = clock();
    searchingStack(stack_, val_to_search);
    time = clock() - time;
    double time_taken_stack = ((double)time) / CLOCKS_PER_SEC;
    printf("TIME : %f\n\n",time_taken_stack);
    
    time = clock();
    searchingQueue(queue_, val_to_search);
    time = clock() - time;
    double time_taken_queue = ((double)time) / CLOCKS_PER_SEC;
    printf("TIME : %f\n\n",time_taken_queue);
    
    time = clock();
    searchingBST(bst_, val_to_search, 1, 0);
    time = clock() - time;
    double time_taken_BST = ((double)time) / CLOCKS_PER_SEC;
    printf("TIME : %f\n\n",time_taken_BST);
}

void searchingStack(stack *head, int value){
    int stepStack[50], resultStack = 0;
    int i = 0, k = 0;
    stack *tempStack;
    tempStack = head;
    while(tempStack != NULL){
        if(tempStack->data == value){
            stepStack[k] = i;
            k++;
            resultStack++;
        }
        i++;
        tempStack = tempStack->next;
    }
    if(resultStack == 0){
        printf("Searching Stack...\nCan't Founded!!!\n");
        return;
    }
    printf("Searching Stack...\n");
    printf("%d result founded on ",resultStack);
    for(k=0;k<resultStack;k++)
        printf("%d. ",stepStack[k]);
    printf("step.\n");
}

void searchingQueue(queue *head,int value){
    int stepQueue[50], resultQueue = 0;
    int i = 0, k = 0;
    queue *tempQueue;
    tempQueue = head;
    while(tempQueue != NULL){
        if(tempQueue->data == value){
            stepQueue[k] = i;
            k++;
            resultQueue++;
        }
        i++;
        tempQueue = tempQueue->next;
    }
    if(resultQueue == 0){
        printf("Searching Queue...\nCan't Founded!!!\n");
        return;
    }
    printf("Searching Queue...\n");
    printf("%d result founded on ",resultQueue);
    for(k=0;k<resultQueue;k++)
        printf("%d. ",stepQueue[k]);
    printf("step.\n");
}

void searchingBST(bst *head, int value, int step, int control){
    bst *tempBST;
    tempBST = head;
    if(tempBST == NULL){
        if(control == 0)
            printf("Searching BST...\nCan't Founded!!!\n");
        return;
    }
    if(tempBST->data == value){
        control = 1;
        printf("Searching BST...\n");
        printf("1 result founded on %d. step.\n",step);
    }
    if(tempBST->data > value){
        step++;
        searchingBST(tempBST->left, value, step, control);
    }
    if(tempBST->data < value){
        step++;
        searchingBST(tempBST->right, value, step, control);
    }
}

void special_traverse(stack *stack_, queue *queue_, bst *bst_){
    clock_t time;
    time = clock();
    special_traverse_stack(stack_);
    time = clock() - time;
    double time_taken_stack = ((double)time) / CLOCKS_PER_SEC;
    printf("\nTIME : %f\n\n",time_taken_stack);
    
    time = clock();
    special_traverse_queue(queue_);
    double time_taken_queue = ((double)time) / CLOCKS_PER_SEC;
    printf("\nTIME : %f\n\n",time_taken_queue);
    
    time = clock();
    special_traverse_BST(bst_);
    double time_taken_BST = ((double)time) / CLOCKS_PER_SEC;
    printf("\nTIME : %f\n\n",time_taken_BST);
}

void special_traverse_stack(stack *head){
    int min, max;
    printf("Special Traverse Stack...\n");
    while(head != NULL){
        max = maxStack(head);
        printf("%d ",max);
        deleteStack(&head, max);
        min = minStack(head);
        printf("%d ",min);
        deleteStack(&head, min);
    }
}

int maxStack(stack *head){
    int max;
    max = head->data;
    head = head->next;
    while(head != NULL){
        if(max < head->data)
            max = head->data;
        head = head->next;
    }
    return max;
}

int minStack(stack *head){
    int min;
    min = head->data;
    head = head->next;
    while(head != NULL){
        if(min > head->data)
            min = head->data;
        head = head->next;
    }
    return min;
}

void deleteStack(stack **head,int data){
    stack *temp, *prev = NULL;
    temp = *head;
    if (temp != NULL && temp->data == data){
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}

void special_traverse_queue(queue *head){
    int max, min;
    printf("Special Traverse Queue...\n");
    while(head != NULL){
        max = maxQueue(head);
        printf("%d ",max);
        deleteQueue(&head, max);
        min = minQueue(head);
        printf("%d ",min);
        deleteQueue(&head, min);
    }
}

void deleteQueue(queue **head, int data){
    queue *temp, *prev = NULL;
    temp = *head;
    if (temp != NULL && temp->data == data){
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->data != data){
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
        return;
    prev->next = temp->next;
    free(temp);
}
int maxQueue(queue *head){
    int max;
    max = head->data;
    head = head->next;
    while(head != NULL){
        if(max < head->data)
            max = head->data;
        head = head->next;
    }
    return max;
}

int minQueue(queue *head){
    int min;
    min = head->data;
    head = head->next;
    while(head != NULL){
        if(min > head->data)
            min = head->data;
        head = head->next;
    }
    return min;
}

void special_traverse_BST(bst *head){
    printf("Special Traverse BST...\n");
    while(head != NULL){
        bst *temp_1, *temp_2;
        temp_1 = (bst *)malloc(sizeof(bst));
        temp_2 = (bst *)malloc(sizeof(bst));
        temp_1 = maxBST(head);
        if(temp_1 != NULL){
            printf("%d ",temp_1->data);
            head = delete(head, temp_1->data);
        }
        temp_2 = minBST(head);
        if(temp_2 != NULL){
            printf("%d ",temp_2->data);
            head = delete(head, temp_2->data);
        }
    }
}

bst *delete(bst *head, int data){
    if(head == NULL)
        return NULL;
    if (data > head->data)
        head->right = delete(head->right, data);
    else if(data < head->data)
        head->left = delete(head->left, data);
    else{
        //No Children
        if(head->left == NULL && head->right == NULL){
            free(head);
            return NULL;
        }
        //One Child
        else if(head->left == NULL || head->right == NULL){
            bst *temp;
            if(head->left == NULL)
                temp = head->right;
            else
                temp = head->left;
            free(head);
            return temp;
        }
        //Two Children
        else{
            bst *temp = NULL;
            temp = (bst *)malloc(sizeof(bst));
            temp = minBST(head->right);
            head->data = temp->data;
            head->right = delete(head->right, temp->data);
        }
    }
    return head;
}

bst *maxBST(bst *head){
    if(head == NULL)
        return NULL;
    else if(head->right != NULL) // node with maximum value will have no right
        return maxBST(head->right); // right most element will be max
    return head;
}

bst *minBST(bst *head){
    if(head == NULL)
        return NULL;
    else if(head->left != NULL) // node with minimum value will have no left
        return minBST(head->left); // left most element will be min
    return head;
}
