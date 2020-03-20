#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

void menu(void);
void simple_calculator(void);
void grade_average(void);
void draw_triangles(void);

int take_grades(int[], int);
int take_exam_grades(int[]);
double calculate_homework(int[]);
double calculate_lab(int[]);
double calculate_all(int, int, int[]);

int addition(int, int);
int subtraction(int, int);
int division(int, int);
int multiplication(int, int);
int power(int, int);
int modulo(int, int);
int doit(int f(int,int),int,int);
int number_conversion(char [], int); // conversion index in char array in to integer

int main(){
    menu();
    return 0;
}

void menu(void){
    int choice = 0;
    int counter = 1;
    while(counter == 1){
        printf("*******  MENU  *******\n");
        printf("1. Simple Calculator Program\n");
        printf("2. Grade Average Calculator\n");
        printf("3. Draw Triangles\n");
        printf("4. Exit\n");
        printf("Choice:\n");
        scanf("%d",&choice);
        fseek(stdin,0,SEEK_END);
        switch(choice){
            case 1:
                simple_calculator();
                break;
            case 2:
                grade_average();
                break;
            case 3:
                draw_triangles();
                break;
            case 4:
                counter = 0;
                break;
            default:
                printf("This is an invalid choice. Try again!\n");
                break;
        }
    }
}

void simple_calculator(void){
    char *arr, *operation, *number1, *number2;
    int result = 0, tempResult = 0;
    int i = 0,j = 0,k = 0;
    int num1, num2,control2 = 0;
    int control = 0, size_number1 = 0, size_number2 = 0, count = 0, flag = 0; 
    printf("*****  Simple Calculator  *****\n");
    printf("Addition for '+' \n");
    printf("Subtraction for '-' \n");
    printf("Division for '/' \n");
    printf("Multiplication for '*' \n");
    printf("Power for '**' \n");
    printf("Modulo for '%%' \n");
    printf("Result and exit for '=' \n");
    printf("\n\nEnter:\n");
    while(flag == 0){
        arr=malloc(sizeof(char)*100);
        operation = malloc(sizeof(char)*2);
        number1 = malloc(sizeof(char)*50);
        number2 = malloc(sizeof(char)*50);
        i=0;
        j=0;k=0;
        size_number1 = 0;
        size_number1 = 0;
        count = 0;
        arr[0] = '\0';
        control = 0;
        while(control == 0){
            scanf("%c",&arr[i]);
            if(arr[i] == '\n')
                control = 1;
            i++;
        }
        i = 0;
        if(control2 == 1){
            while(arr[i] != '\n'){
                if(arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/' || arr[i] == '%' || arr[i] == '='){
                    operation[i] = arr[i];
                    if(arr[i+1] == '*' && arr[i]=='*'){
                        operation[i+1] = arr[i+1];
                    }
                }
                else if(arr[i] <= '9' && arr[i] >= '0' && count == 1){
                    number1[j] = arr[i];
                    size_number1++;
                    j++;
                }
                else
                    count++; //Count increases as space arrives, used to figure out which number.
                i++;
            }
            num1 = number_conversion(number1,size_number1);
            num2 = tempResult;
            free(number1);
            free(number2);
            free(arr);
        }
        else{
            while(arr[i] != '\n'){
                if(arr[i] == '+' || arr[i] == '-' || arr[i] == '*' || arr[i] == '/' || arr[i] == '%' || arr[i] == '='){
                    operation[i] = arr[i];
                    if(arr[i+1] == '*' && arr[i]=='*'){
                        operation[i+1] = arr[i+1];
                    }
                }
                else if(arr[i] <= '9' && arr[i] >= '0'){
                    if(count == 1){
                        number1[j] = arr[i];
                        size_number1++;
                        j++;
                    }
                    else{
                        number2[k] = arr[i];
                        size_number2++;
                        k++;
                    }
                }
                else{
                    count++;
                }
                i++;
            }
            number1[j] = '\0';
            number2[k] = '\0';
            num1 = number_conversion(number1,size_number1);
            num2 = number_conversion(number2,size_number2);
            free(number1);
            free(number2);
            free(arr);
        }
        if(operation[0] == '+'){
            result = doit(addition,num1,num2);
            printf("result : %d\n",result );
        }
        else if(operation[0] == '-'){
            result = doit(subtraction,num1,num2);
            printf("result : %d\n",result );
        }
        else if(operation[0] == '*'){
            if(operation[1] == '*'){
                result = doit(power,num1,num2);
                printf("result : %d\n",result );
            }
            else{
                result = doit(multiplication,num1,num2);
                printf("result : %d\n",result );
            }
        }
        else if(operation[0] == '/'){
            result = doit(division,num1,num2);
            printf("result : %d\n",result );
        }
        else if(operation[0] == '%'){
            result = doit(modulo,num1,num2);
            printf("result : %d\n",result );
        }
        else{
            printf("result : %d\n",result);
            flag = 1;
        }
        tempResult = result;
        control2 = 1;
        free(operation);
    }
}

int addition(int number1, int number2){
    return number1 + number2;
}

int subtraction(int number1, int number2){
    return number1 - number2;
}

int division(int number1, int number2){
    return number1 / number2;
}

int multiplication(int number1, int number2){
    return number1 * number2;
}

int power(int number1, int number2){
    return pow(number1,number2);
}

int modulo(int number1, int number2){
    return number1 % number2;
}

int doit(int f(int a,int b), int num1,int num2){
    int sum;
    sum = f(num1,num2);
    return sum;
}

int number_conversion(char number[],int size_number){ // conversion index in char array in to integer
    int i;
    int temp;
    int num = 0, digit;
    digit = pow(10,(size_number - 1));
    for(i=0;i<size_number;i++){
        temp = number[i] - '0';
        num = temp * digit + num;
        digit = digit / 10;
    }
    return num;
}

void grade_average(void){
    int control = 0;
    int exam_grade[2], lab_grade[10], homework_grade[10];
    double average_homework, average_lab, average_all;
    take_grades(lab_grade, control);
    control++; // to indicate to the user which of the homework notes or lab notes have been entered.
    take_grades(homework_grade, control);
    take_exam_grades(exam_grade);
    average_homework = calculate_homework(homework_grade);
    average_lab = calculate_lab(lab_grade);
    average_all = calculate_all(average_homework, average_lab, exam_grade);
    printf("All average : %.2f\n\n\n\n",average_all);
}

int take_grades(int arr_grades[], int control){
    int i;
    if(control == 0)
        printf("Enter the lab grades: \n");
    else
        printf("Enter the homework grade: \n");
    for(i=0;i<10;i++){
        scanf("%d",&arr_grades[i]);
    }
    return 0;
}

int take_exam_grades(int arr_exam_grade[]){
    printf("Enter the midterm grade : "); //array[0] : midterm grade & array[1] : final grade
    scanf("%d",&arr_exam_grade[0]);
    printf("\nEnter the final grade : ");
    scanf("%d",&arr_exam_grade[1]);
    return 0;
}

double calculate_homework(int arr_homework[]){
    double sum = 0, average;
    int i;
    for(i=0;i<10;i++){
        sum = sum + arr_homework[i];
    }
    average = sum / 10;
    return average;
}

double calculate_lab(int arr_lab[]){
    double sum = 0, average;
    int i;
    for(i=0;i<10;i++){
        sum = sum + arr_lab[i];
    }
    average = sum / 10;
    return average;
}

double calculate_all(int average_homework, int average_lab, int arr_exam[]){ //arr_exam[0] : midterm grade // arr_exam[1] : final grade
    double all_average;
    all_average = ((average_lab * 20) / 100) + ((average_homework * 10) / 100) + ((arr_exam[0] * 30) / 100) + ((arr_exam[1] * 40) / 100);
    return all_average;
}

void draw_triangles(void){
    int i,j,k;
    int input, star, line, space;
    printf("Enter the height of the shape : ");
    scanf("%d",&input);
    space = input - 1;
    star = 2;
    line = input;
    for(i=0;i<line;i++){
        if(i==0){
            for(j=0;j<space;j++){
                printf(" ");
            }
            printf("/\\\n");
            space--;
        }
        else{
            for(j=0;j<space;j++){
                printf(" ");
            }
            printf("/");
            for(k=0;k<star;k++){
                printf("*");
            }
            printf("\\\n");
            space--;
            star = star + 2;
        }
    }
    star = (input - 1) * 2;
    space = 0;
    for(i=0;i<line;i++){
        if(i == line - 1){
            space = input - 1;
            for(j=0;j<space;j++){
                printf(" ");
            }
            printf("\\/\n");
        }
        else{
            for(j=0;j<space;j++){
                printf(" ");
            }
            printf("\\");
            for(k=0;k<star;k++){
                printf("*");
            }
            printf("/\n");
            space++;
            star = star - 2;
        }
    }
    printf("\n\n\n");
}