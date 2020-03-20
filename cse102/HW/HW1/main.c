
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#define PI 3.14
#define RED 0
#define YELLOW 1
#define BLUE 2
#define BLACK 3
#define WHITE 4
#define RECTENGULAR 1
#define CIRCULAR 2
#define SQUARE 3

double CreateBody(int);
int SetColor(int);
double LoadMoves(int, double);
int SetAttackPower(int, int);
void ShowPokemon(int, double, int, double, int);

int main (){
    int shape, color, attack_power;
    double size_of_body, move_length;
    shape = CIRCULAR;
    size_of_body = CreateBody(shape);
    color = 798;
    color = SetColor(color);
    move_length = LoadMoves(shape, size_of_body);
    attack_power = SetAttackPower(0, 150);
    ShowPokemon(shape, size_of_body, color, move_length, attack_power);
    return 0;
}

double CreateBody(int shape){ 
    double long_edge, short_edge, square_edge;
    double radius;
    double sum;
    if(shape == RECTENGULAR){
        printf("Enter the edges of the rectangle\n");
        scanf("%lf %lf",&long_edge,&short_edge);
        sum = long_edge * short_edge;
    }
    else if(shape == CIRCULAR){
        printf("Enter the radius\n");
        scanf("%lf",&radius);
        sum = radius * radius * PI;
    }
    else if(shape == SQUARE){
        printf("Enter the edge of the square\n");
        scanf("%lf",&square_edge);
        sum = square_edge * square_edge;
    }
    else{
        printf("You can't have a pokemon with this shape!\n");
        return 0;
    }
    return sum;
}

int SetColor(int color){
    if(color <= 1000 && color >= 0){
        color = color % 5;
    }
    else{
        color = 1;
    }
    return color;
}

double LoadMoves(int shape, double body_size){
    double edge,radius;
    double sum;
    if(shape == RECTENGULAR){
        edge = body_size / 5;
        sum = (2 * edge) + 10;
    }
    else if(shape == CIRCULAR){
        radius = body_size / PI;
        radius = sqrt(radius);
        sum = radius * 2 * PI ;
    }
    else{
        edge = sqrt(body_size);
        sum = 4 * edge;
    }
    return sum;
}

int SetAttackPower(int lower_bound, int upper_bound){
    int sum;
    srand(time(NULL));
    sum = lower_bound+rand()%upper_bound;
    return sum;
}

void ShowPokemon (int shape, double body_size, int color, double move_length, int attact_power){
    int i,j,k,l;
    int edge;
    int radius;
    int tabs, tabsforx , space;
    if(shape == RECTENGULAR){
        edge = body_size / 5;
        for(i=0;i<5;i++){
            for(j=0;j<edge;j++){
                printf("x");
            }
            printf("\n");
        }
        printf("Name : Rectangle Pokemon\n");
    }
     if(shape == CIRCULAR){
        radius = body_size / PI;
        radius = sqrt(radius);
        if(radius % 2 == 0){ // Circle illustration of even radius
            tabs = radius / 2;
            tabsforx = 1;
            for(i=0;i<=radius/2;i++){ // It draws the part of the circle up to the diameter.
                if(i == 0){ // It draws the first line of the circle.
                    space = 4;
                    for(k=0;k<tabs-1;k++){
                        printf("\t");
                    }
                    for(l=0;l<space;l++){
                        printf(" ");
                    }
                    printf("X\n");
                }
                else{
                    tabs = tabs - 1;
                    for(k=0;k<tabs;k++){
                        printf("\t");
                    }
                    printf("X");
                    for(l=0;l<tabsforx;l++){
                        printf("\t");
                    }
                    printf("X\n");
                    tabsforx = tabsforx + 2;
                }
            }
            tabs = 1; 
            tabsforx = tabsforx - 2;
            for(j=0;j<radius/2;j++){ // It draws the rest of the circle. 
                if(j == radius/2 - 1){ // It draws the last line of the circle.
                    tabs = radius/2 - 1;
                    for(k=0;k<tabs;k++){
                        printf("\t");
                    }
                    for(l=0;l<space;l++){
                        printf(" ");
                    }
                    printf("X\n");
                }
                else{
                    tabsforx = tabsforx - 2;
                    for(k=0;k<tabs;k++){
                        printf("\t");
                    }
                    printf("X");
                    for(l=0;l<tabsforx;l++){
                        printf("\t");
                    }
                    printf("X\n");
                    tabs = tabs + 1;
                }
            }
        }
        else{ // Circle illustration of odd radius
            tabs = (radius-1)/2;
            tabsforx = 2;
            for(i=0;i<=(radius-1)/2;i++){ // It draws the part of the circle up to the diameter.
                if(i == 0){ // It draws the first line of the circle.
                    for(j=0;j<tabs;j++){
                        printf("\t");
                    }
                    printf("X\n");
                }
                else{
                    tabs--;
                    for(k=0;k<tabs;k++){
                        printf("\t");
                    }
                    printf("X");
                    for(l=0;l<tabsforx;l++){
                        printf("\t");
                    }
                    printf("X\n");
                    tabsforx = tabsforx + 2;
                }
            }
            tabsforx = tabsforx - 4;
            tabs = 1;
            for(i=0;i<(radius-1)/2;i++){ // It draws the rest of the circle.
                if(i == (radius-1)/2-1){ // It draws the last line of the circle.
                    tabs = (radius-1)/2;
                    for(k=0;k<tabs;k++){
                        printf("\t");
                    }
                    printf("X\n");
                }
                else{
                for(k=0;k<tabs;k++){
                    printf("\t");
                }
                printf("X");
                for(k=0;k<tabsforx;k++){
                    printf("\t");
                }
                printf("X\n");
                tabs = tabs + 1;
                tabsforx = tabsforx - 2;
                }
            }
        }
        printf("Name : Circular Pokemon\n");
    }
    if(shape == SQUARE){
        edge = sqrt(body_size);
        for(i=0;i<edge;i++){
            for(j=0;j<edge;j++){
                printf("x");
            }
            printf("\n");
        }
        printf("Name : Square Pokemon\n");
    }
    printf("Size : %.2f\n",body_size);
    if(color == RED)
        printf("Color : Red\n");
    else if(color == YELLOW)
        printf("Color : Yellow\n");
    else if(color == BLUE)
        printf("Color : Blue\n");
    else if(color == BLACK)
        printf("Color : Black\n");
    else
        printf("Color : White\n");
    printf("Move : %.2f\n",move_length);
    printf("Attack Power : %d\n",attact_power);
}
