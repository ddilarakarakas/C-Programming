#include <stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct stack_person{
    char name[20];
    char surname[20];
    char musical_work[20];
    int age;
    struct stack_person *next;
}person;

void menu(void);
void addNode(person **, char [], char[], char [],int);
void printStack(person *);
void deleteNode(person **);
void sort_alphabetically(person **);
void sort_increasingly_age(person **);
int sizeStack(person *);

int main() {
    menu();
    return 0;
}

void menu(void){
    person *human;
    human = (person *)malloc(sizeof(person));
    char name[20], name_1[20], name_2[20], surname[20], creation[20];
	char name1[20],creation1[20];
    int age, choice, controlForLoop = 0;
    human = NULL;
    while(controlForLoop == 0){
        printf("************** MENU **************\n");
        printf("1. Add a Person to the Stack\n");
        printf("2. Pop a Person from the Stack\n");
        printf("3. Sort Alphabetical Order\n");
        printf("4. Sort Age in Increasing Order\n");
        printf("5. Exit Menu\n");
        printf("**********************************\n");
        printf("Choice : ");
        scanf("%d",&choice);
        fseek(stdin,0,SEEK_END);
        switch(choice){
            case 1:
                printf("\nName : ");
                scanf("%s %s",name,name1);
				int i=0;
				while(name[i] != '\0')
					i++;
				name[i] = ' ';
				name[i+1] = '\0';
				strcat(name,name1);
                printf("Surname : ");
                scanf("%s",surname);
                printf("Creation :");
                scanf("%s %s",creation,creation1);
                i = 0;
                while(creation[i] != '\0')
                    i++;
                creation[i] = ' ';
                creation[i+1] = '\0';
                strcat(creation,creation1);
                printf("Age : ");
                scanf("%d",&age);
                addNode(&human, name, surname, creation,age);
                printStack(human);
                break;
            case 2:
            	if(human == NULL)
            		printf("Stack is NULL\n");
            	else{
                	deleteNode(&human);
            		printStack(human);
            	}
                break;
            case 3:
                sort_alphabetically(&human);
                printStack(human);
                break;
            case 4:
                sort_increasingly_age(&human);
                printStack(human);
                break;
            case 5:
                controlForLoop = 1;
                break;
            default:
                printf("\nWrong choice. TRY AGAIN!!\n\n");
                break;
        }
    }
    free(human);
}

void addNode(person **human, char name[20], char surname[20], char creation[20], int age){
    person *temp;
    temp = (person *)malloc(sizeof(person));
    strcpy(temp->name,name);
    strcpy(temp->surname,surname);
    strcpy(temp->musical_work,creation);
    temp->age = age;
    temp->next = *human;
    *human = temp;
}

void deleteNode(person **head){
    *head = (*head)->next;
}

void sort_alphabetically(person **head){
    person *temp, *temp_1, *temp_2;
    int size;
    int i, j, k;
    size = sizeStack(*head);
    temp = (person *)malloc(sizeof(person));
    temp_1 = (person *)malloc(sizeof(person)*size);
    temp_1 = *head;
    for(i=0;i<size-1;i++){
        temp_2 = (person *)malloc(sizeof(person)*size);
        temp_2 = *head;
        j = i + 1;
        for(k=0;k<j;k++)
            temp_2 = temp_2->next;
        for(j=i+1;j<size;j++){
            if(strcmp(temp_1->name, temp_2->name) > 0){
                strcpy(temp->name,temp_1->name);
                strcpy(temp->surname,temp_1->surname);
                strcpy(temp->musical_work,temp_1->musical_work);
                temp->age = temp_1->age;
                
                strcpy(temp_1->name,temp_2->name);
                strcpy(temp_1->surname,temp_2->surname);
                strcpy(temp_1->musical_work,temp_2->musical_work);
                temp_1->age = temp_2->age;
                
                strcpy(temp_2->name,temp->name);
                strcpy(temp_2->surname,temp->surname);
                strcpy(temp_2->musical_work,temp->musical_work);
                temp_2->age = temp->age;
            }
            temp_2 = temp_2->next;
        }
        temp_1 = temp_1->next;
        free(temp_2);
    }
}

void sort_increasingly_age(person **head){
    person *temp, *temp_1, *temp_2;
    int size;
    int i, j, k;
    size = sizeStack(*head);
    temp = (person *)malloc(sizeof(person));
    temp_1 = (person *)malloc(sizeof(person)*size);
    temp_1 = *head;
    for(i=0;i<size-1;i++){
        temp_2 = (person *)malloc(sizeof(person)*size);
        temp_2 = *head;
        j = i + 1;
        for(k=0;k<j;k++)
            temp_2 = temp_2->next;
        for(j=i+1;j<size;j++){
            if(temp_1->age > temp_2->age){
                strcpy(temp->name,temp_1->name);
                strcpy(temp->surname,temp_1->surname);
                strcpy(temp->musical_work,temp_1->musical_work);
                temp->age = temp_1->age;
                
                strcpy(temp_1->name,temp_2->name);
                strcpy(temp_1->surname,temp_2->surname);
                strcpy(temp_1->musical_work,temp_2->musical_work);
                temp_1->age = temp_2->age;
                
                strcpy(temp_2->name,temp->name);
                strcpy(temp_2->surname,temp->surname);
                strcpy(temp_2->musical_work,temp->musical_work);
                temp_2->age = temp->age;
            }
            temp_2 = temp_2->next;
        }
        temp_1 = temp_1->next;
        free(temp_2);
    }
}

void printStack(person *head){
    person *temp;
    temp = head;
    int i = 1;
    if(temp != NULL){
        printf("\n***Person Stack***\n\n");
        do{
            printf("%d) Name    : %s\n",i,temp->name);
            printf("%d) Surname : %s\n",i,temp->surname);
            printf("%d) Creatin : %s\n",i,temp->musical_work);
            printf("%d) Age     : %d\n\n",i,temp->age);
            temp = temp->next;
            i++;
        }while(temp != NULL);
    }
    else
        printf("***The Stack is empty***\n");
}

int sizeStack(person *head){
    int i = 0;
    while(head != NULL){
        head = head->next;
        i++;
    }
    return i;
}
