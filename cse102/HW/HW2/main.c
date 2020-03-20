#include <stdio.h>
#include<time.h>
#include<stdlib.h>

void menu(void);
int make_a_guess (int,int,int);
void show_scores(int,int);
void draw_hourglass (int);
void draw_mountain_road (int,int);

int main(){
    srand(time(NULL));
    menu();
    return 0;
}

void menu(){
    int i, ln, distinction_between = 0, distance = 0;
    int choice;
    int counter = 0, temp;
    int flag = 0;
    int trial, max, min, guess = 0, score_human = 0, score_program = 0;
    int height;
    int lenght, max_radius;
    while(counter == 0){
        printf("*****  MENU  *****\n");
        printf("1. Play Lucky Number\n");
        printf("2. Draw Hourglass\n");
        printf("3. Draw Mountain Road\n");
        printf("4. Exit\n");
        printf("Choice:\n");
        scanf("%d",&choice);
        flag = 0;
        switch (choice){
            case 1:
                trial = 1;
                min = 1;
                max = 1024;
                ln = min + rand() % max;
                printf("Trial : 5 and LN : %d\n",ln);
                for(i=1;i<=5;i++){
                    guess = make_a_guess(trial,min,max);
                    trial++;
                    if(guess > ln)
                        distinction_between = guess - ln;
                    else if(guess < ln)
                        distinction_between = ln - guess;
                    else
                        distinction_between = 0;
                    if(distinction_between <= 1023 && distinction_between >= 512)
                        distance = 10;
                    else if(distinction_between <= 511 && distinction_between >= 256)
                        distance = 9;
                    else if(distinction_between <= 255 && distinction_between >= 128)
                        distance = 8;
                    else if(distinction_between <= 127 && distinction_between >= 64)
                        distance = 7;
                    else if(distinction_between <= 63 && distinction_between >= 32)
                        distance = 6;
                    else if(distinction_between <= 31 && distinction_between >= 16)
                        distance = 5;
                    else if(distinction_between <= 15 && distinction_between >= 8)
                        distance = 4;
                    else if(distinction_between <= 7 && distinction_between >= 4)
                        distance = 3;
                    else if(distinction_between == 3 || distinction_between == 2)
                        distance = 2;
                    else if(distinction_between == 1)
                        distance = 1;
                    else
                        distance = 0;
                    printf("Distance : %d\n",distance);
                    if(guess>ln && guess<max)
                        max=guess;
                    if(guess<ln && guess>min)
                        min=guess;
                    if(guess==ln){
                        printf("You win!");
                        break;
                    }
                }
                if(guess == ln)
                    score_human++;
                else
                    score_program++;
                show_scores(score_human, score_program);
                break;
            case 2:
                printf("Enter the height for hourglass\n");
                while(flag == 0){
                    scanf("%d",&height);
                    temp = height % 2;
                    if(temp == 1){
                        draw_hourglass(height);
                        flag = 1;
                    }
                    else
                        printf("Height is invalid and must be odd number\n");
                }
                break;
            case 3:
                printf("Enter the lenght : ");
                scanf("%d",&lenght);
                printf("\nEnter the maximum radius : ");
                scanf("%d",&max_radius);
                draw_mountain_road(lenght, max_radius);
                break;
            case 4:
                counter = 1;
                break;
            default:
                printf("This is an invalid choice. Try again!\n");
                break;
        }
    }
}

int make_a_guess(int trial, int min, int max){
    int guess = 0;
    printf("(Trial: %d) Make a guess between %d and %d: ",trial,min,max);
    scanf("%d",&guess);
    return guess;
}

void show_scores(int score_human, int score_program){
    printf("\nYour score: %d Program score: %d \n\n\n",score_human,score_program);
}

void draw_hourglass(int height){
    int i,j,k;
    int space,star,line;
    space = 0;
    star = height;
    line = (height - 1) / 2 + 1;
    for(i=0;i<line;i++){
        for(k=0;k<space;k++)
            printf(" ");
        for(j=0;j<star;j++)
            printf("*");
        printf("\n");
        star = star - 2;
        space++;
    }
    space = (height - 1) / 2 - 1;
    star = 3;
    line = (height - 1) / 2;
    for(i=0;i<line;i++){
        for(k=0;k<space;k++)
            printf(" ");
        for(j=0;j<star;j++)
            printf("*");
        printf("\n");
        star = star + 2;
        space--;
    }
    printf("\n");
}

void draw_mountain_road (int length, int max_radius){
    int i,j,k;
    int control = 0;
    int radius = 0,space = 1;
    int counter = 0;
    int space2 = 0;                    // Space2 allows drawing from where the previous circle was left
    int max_space = 0;
    int temp_radius = 0;
    for(i=1;i<=length;i++){
        while(control == 0){        //Since I don't use spaces to start drawing, it controls the random radius to avoid accumulation in single circles after circle 2
            radius = 1 + rand() % max_radius;
            if((i % 2 == 1) && (i > 2)){
                radius = 1 + rand() % counter;    //The radius of the next circle is controlled so that it does not cross the radius of the two previous circles.
                if(radius + counter > max_space)       //Counter is the radius of the circle before it
                    radius = 1 + rand() % counter;        //Temp_radius is the radius of two previous circle
                
                else
                    control = -1;
            }
            else
                control = -1;
        }
        if(i == 1){                //Drawing of the first circle
            space = radius;
            for(j=0;j<radius;j++){
                for(k=0;k<space;k++)
                    printf(" ");
                printf("/\n");
                space--;
            }
            printf("|\n");
            space = 1;
            for(k=0;k<radius;k++){
                for(j=0;j<space;j++)
                    printf(" ");
                printf("\\\n");
                space++;
            }
            space2 = space;
            temp_radius = radius;
        }
        else if(i % 2 == 0){        //Drawing of circles with even number
            space = space2;
            for(k=0;k<space;k++)
                printf(" ");
            space++;
            for(j=0;j<radius;j++){
                printf("\\\n");
                for(k=0;k<space;k++)
                    printf(" ");
                space++;
            }
            printf("|\n");
            space = space - 2;
            for(j=0;j<radius;j++){
                for(k=0;k<space;k++)
                    printf(" ");
                printf("/\n");
                space--;
            }
            space2 = space;
            counter = radius;
            max_space = temp_radius + radius;
        }
        else{                        //Drawing of circles with odd number
            space = space2;
            for(j=0;j<radius;j++){
                for(k=0;k<space;k++)
                    printf(" ");
                printf("/\n");
                space--;
            }
            for(j=0;j<space2 - radius;j++)
                printf(" ");
            printf("|\n");
            space = space + 1;
            for(k=0;k<radius;k++){
                for(j=0;j<space;j++)
                    printf(" ");
                printf("\\\n");
                space++;
            }
            space2 = space;
            temp_radius = radius;
        }
        control = 0;
    }
}