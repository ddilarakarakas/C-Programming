#include <stdio.h>

void menu(void);
int common(int, int);
int sortArr(int [],int,int);
void merge(int [],int,int,int);
void operation(int);
int equal_notEqual(int,int);
void first_capital(char *);
int recursivePow(int,int);
int findDigit(int,int);

int main() {
    menu();
    return 0;
}

void menu(){
    int i = 0;
    int choice;
    int control = 0;
    int number1, number2;
    int arr_length, arr[50];
    char capital_string[100];
    int controlForLoop = 0;
    int digit,result;
    while(control == 0){
        printf("******************************************************\n");
        printf("1. Greatest Common Divisor\n");
        printf("2. Sorting Function\n");
        printf("3. Operation Function\n");
        printf("4. Equal or Not Equal Function\n");
        printf("5. The First Capital Letter in the String\n");
        printf("6. Exit\n");
        printf("******************************************************\n");
        scanf("%d",&choice);
        fseek(stdin,0,SEEK_END);
        switch(choice){
            case 1:
                printf("Enter the numbers\n");
                scanf("%d %d",&number1,&number2);
                printf("Output : %d\n",common(number1, number2));
                break;
            case 2:
                printf("Enter the length of list: ");
                scanf("%d",&arr_length);
                printf("\nEnter the element of list:\n");
                for(i=0;i<arr_length;i++)
                    scanf("%d",&arr[i]);
                sortArr(arr,0,arr_length-1);
                printf("Sorted array is :");
                for(i=0;i<arr_length;i++)
                    printf("%d ",arr[i]);
                printf("\n");
                break;
            case 3:
                printf("Enter the number\n");
                scanf("%d",&number1);
                operation(number1);
                printf("\n");
                break;
            case 4:
                printf("Enter the number\n");
                scanf("%d",&number1);
                digit = findDigit(number1, 0);
                result = equal_notEqual(number1,digit);
                if(number1 == result)
                    printf("Equal\n");
                else
                    printf("Not Equal\n");
                break;
            case 5:
                i = 0;
                printf("You should enter a string without space\n");
                while(controlForLoop == 0){
                    scanf("%c",&capital_string[i]);
                    if(capital_string[i] == '\n')
                        controlForLoop = 1;
                    i++;
                }
                controlForLoop = 0;
                first_capital(capital_string);
                break;
            case 6:
                control = 1;
                break;
            default:
                printf("Wrong choice\n");
                break;
        }
    }
}

int common(int num1, int num2){
    if(num1 == 0 && num2 == 0)
        return -1;
    if(num2 != 0)
        return common(num2,num1 % num2);
    else
        return num1;
}

int sortArr(int arr[],int low,int high){ //Low is for left index and high is right index of the sub-array of arr to be sorted
    int mid;
    if(low<high){
        mid=(low+high)/2;
        sortArr(arr,low,mid);
        sortArr(arr,mid+1,high);
        merge(arr,low,mid,high);
    }
    return 0;
}

void merge(int arr[], int low, int mid, int high){
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 =  high - mid;
    int tempArr_1[n1], tempArr_2[n2];
    for (i = 0; i < n1; i++)
        tempArr_1[i] = arr[low + i];
    for (j = 0; j < n2; j++)
        tempArr_2[j] = arr[mid + 1+ j];
    /* Merge the temp arrays back into arr[low..high]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = low; // Initial index of merged subarray
    while (i < n1 && j < n2){
        if (tempArr_1[i] <= tempArr_2[j]){
            arr[k] = tempArr_1[i];
            i++;
        }
        else{
            arr[k] = tempArr_2[j];
            j++;
        }
        k++;
    }
    while (i < n1){ //Copy the remaining elements of tempArr_1[], if there are any
        arr[k] = tempArr_1[i];
        i++;
        k++;
    }
    while (j < n2){ // Copy the remaining elements of tempArr_2[], if there are any
        arr[k] = tempArr_2[j];
        j++;
        k++;
    }
}

void operation(int number){
    int result = number;
    printf("%d  ",result);
    if(number % 2 == 0){
        result = number / 2;
    }
    if(number % 2 == 1){
        result = 3 * number + 1;
    }
    if(result == 1){
        printf("%d  ",result);
        return;
    }
    else
        operation(result);
}

int equal_notEqual(int number, int digit){
    int base;
    int result = 0;
    base = (number % 10);
    result = result + recursivePow(base,digit);
    if(number < 10){
        return result;
    }
    number = (number - (number % 10)) / 10;
    result = result + equal_notEqual(number,digit);
    return result;
}

int recursivePow(int base,int exponent){
    if(exponent == 0)
        return 1;
    else if(exponent == 1)
        return base;
    else
        return  base * recursivePow(base,exponent - 1);
}

int findDigit(int number,int digit){ //Finds the number of digits
    if(number < 10){
        digit++;
        return digit;
    }
    number = (number - (number % 10)) / 10;
    digit++;
    return findDigit(number,digit);
}

void first_capital(char *ptr){
    if(*ptr > 'A' && *ptr < 'Z'){
        printf("First Capital Letter: %c\n",*ptr);
        return;
    }
    first_capital(ptr+1);
}
