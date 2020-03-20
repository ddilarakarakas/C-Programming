#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define PROPERTY_COUNT 13

typedef enum{
    NOONE, CAP, CAR
}player_type;

typedef enum{
    START, PROPERTY, TAX, PUNISH, FORTUNE_CARD
}block_type;

typedef enum{
    FREE_HOUSE, TIME_TRAVEL, GARNISHMENT, GENEROSITY, TREASURE_HUNTER
}fortune_card_type;

typedef struct{
    player_type type;
    int current_block_id;
    int owned_block_ids[11];
    int account;
    int turn_to_wait;
    char *name;
}player;

typedef struct{
    int card_no;
    char *name;
    fortune_card_type type;
}fortune_card;

typedef struct list_block{  // Double Linked List
    int block_id;
    char *name;
    int price;
    int rent;
    int rent_1;
    int rent_2;
    int rent_3;
    int house_price;
    int house_count;
    player owner;
    block_type type;
    struct list_block *next;
    struct list_block *prev;
}block;

void init_the_board(block *);
void init_the_fortune_card(fortune_card []);
void show_board(block *, player, player);
void player_preparation(player *, player *);
void show_property(block *);
int roll_dice(void);
void show_player_properties(block *, player);
int build_house(block *, player *);
void sell_property(block *, player *);
void buy_property(block *, player *);
void gameplay(block *, player, player);
int play_computer(block *, player *, player *);
int play_gamer(block *, player *, player *);

int main(){
    block board;
    player player_one;
    player player_computer;
    srand(time(NULL));
    player_preparation(&player_one, &player_computer);
    init_the_board(&board);
    gameplay(&board, player_one, player_computer);
    return 0;
}

void init_the_fortune_card(fortune_card fortuneCard[4]){
    int i;
    for(i=0;i<4;i++){
        fortuneCard[i].name = (char *)malloc(sizeof(char)*1);
        switch(i){
            case 0:
                fortuneCard[i].name = "Free House";
                fortuneCard[i].card_no = 1;
                fortuneCard[i].type = FREE_HOUSE;
                break;
            case 1:
                fortuneCard[i].name = "Time Travel";
                fortuneCard[i].card_no = 2;
                fortuneCard[i].type = TIME_TRAVEL;
                break;
            case 2:
                fortuneCard[i].name = "Garnishment";
                fortuneCard[i].card_no = 3;
                fortuneCard[i].type = GARNISHMENT;
                break;
            case 3:
                fortuneCard[i].name = "Generosity";
                fortuneCard[i].card_no = 4;
                fortuneCard[i].type = GENEROSITY;
                break;
            case 4:
                fortuneCard[i].name = "Treasure Hunter";
                fortuneCard[i].card_no = 5;
                fortuneCard[i].type = TREASURE_HUNTER;
                break;
            default:
                break;
        }
    }
}

void player_preparation(player *player_one, player *player_two){
    int i;
    player_one->name = (char *)malloc(sizeof(char)*1);
    player_two->name = (char *)malloc(sizeof(char)*1);
    strcpy(player_one->name,"Car");
    strcpy(player_two->name, "Cap");
    player_one->current_block_id = 0;
    player_two->current_block_id = 0;
    player_one->type = CAR;
    player_two->type = CAP;
    for(i=0;i<11;i++){
        player_one->owned_block_ids[i] = 0;
        player_two->owned_block_ids[i] = 0;
    }
    player_one->account = 100000;
    player_two->account = 100000;
    player_one->turn_to_wait = 0;
    player_two->turn_to_wait = 0;
}

void init_the_board(block *board){
    int i;
    block *temp = NULL;
    board->name = (char *)malloc(sizeof(char)*1);
    strcpy(board->name,"START");
    board->block_id = 0;
    board->type = START;
    board->prev = (block *)malloc(sizeof(board)*1);
    board->prev = NULL;
    for(i=1;i<24;i++){
        temp = (block *)malloc(sizeof(block)*1);
        temp->name = (char *)malloc(sizeof(char)*1);
        switch(i){
            case 1:
                strcpy(temp->name,"ESENYURT");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 16000;
                temp->rent = 800;
                temp->rent_1 = 4000;
                temp->rent_2 = 9000;
                temp->rent_3 = 25000;
                temp->house_price = 10000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 2:
                strcpy(temp->name,"CAR PARK");
                temp->block_id = i;
                temp->type = TAX;
                temp->rent = 1500;
                break;
            case 3:
                strcpy(temp->name,"FORTUNE CARD");
                temp->block_id = i;
                temp->type = FORTUNE_CARD;
                break;
            case 4:
                strcpy(temp->name,"TUZLA");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 16500;
                temp->rent = 850;
                temp->rent_1 = 4250;
                temp->rent_2 = 9500;
                temp->rent_3 = 26000;
                temp->house_price = 12000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 5:
                strcpy(temp->name,"ARNAVUTKOY");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 17000;
                temp->rent = 875;
                temp->rent_1 = 4500;
                temp->rent_2 = 10000;
                temp->rent_3 = 28000;
                temp->house_price = 12000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 6:
                strcpy(temp->name,"WAIT 2 TURN");
                temp->block_id = i;
                temp->type = PUNISH;
                temp->rent = 2;
                break;
            case 7:
                strcpy(temp->name,"CATALCA");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 20000;
                temp->rent = 1000;
                temp->rent_1 = 5000;
                temp->rent_2 = 12000;
                temp->rent_3 = 30000;
                temp->house_price = 13000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 8:
                strcpy(temp->name,"BEYKOZ");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 23000;
                temp->rent = 1100;
                temp->rent_1 = 5500;
                temp->rent_2 = 12500;
                temp->rent_3 = 33000;
                temp->house_price = 13000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 9:
                strcpy(temp->name,"FORTUNE CARD");
                temp->block_id = i;
                temp->type = FORTUNE_CARD;
                break;
            case 10:
                strcpy(temp->name,"CAR FIX");
                temp->block_id = i;
                temp->type = TAX;
                temp->rent = 1750;
                break;
            case 11:
                strcpy(temp->name,"MALTEPE");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 30000;
                temp->rent = 1350;
                temp->rent_1 = 7000;
                temp->rent_2 = 15000;
                temp->rent_3 = 40000;
                temp->house_price = 15000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 12:
                strcpy(temp->name,"BILLS");
                temp->block_id = i;
                temp->type = TAX;
                temp->rent = 2000;
                break;
            case 13:
                strcpy(temp->name,"SISLI");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 33000;
                temp->rent = 1500;
                temp->rent_1 = 8000;
                temp->rent_2 = 16000;
                temp->rent_3 = 42000;
                temp->house_price = 16000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 14:
                strcpy(temp->name,"OIL");
                temp->block_id = i;
                temp->type = TAX;
                temp->rent = 2250;
                break;
            case 15:
                strcpy(temp->name,"FORTUNE CARD");
                temp->block_id = i;
                temp->type = FORTUNE_CARD;
                break;
            case 16:
                strcpy(temp->name,"ATASEHIR");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 35000;
                temp->rent = 1600;
                temp->rent_1 = 8500;
                temp->rent_2 = 17000;
                temp->rent_3 = 45000;
                temp->house_price = 17000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 17:
                strcpy(temp->name,"SARIYER");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 40000;
                temp->rent = 1750;
                temp->rent_1 = 9500;
                temp->rent_2 = 19000;
                temp->rent_3 = 48000;
                temp->house_price = 19000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 18:
                strcpy(temp->name,"WAIT 1 TURN");
                temp->block_id = i;
                temp->type = PUNISH;
                temp->rent = 1;
                break;
            case 19:
                strcpy(temp->name,"KADIKOY");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 43000;
                temp->rent = 1900;
                temp->rent_1 = 11000;
                temp->rent_2 = 21500;
                temp->rent_3 = 55000;
                temp->house_price = 23000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 20:
                strcpy(temp->name,"BESIKTAS");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 60000;
                temp->rent = 2500;
                temp->rent_1 = 15000;
                temp->rent_2 = 28000;
                temp->rent_3 = 60000;
                temp->house_price = 30000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
            case 21:
                strcpy(temp->name,"FORTUNE CARD");
                temp->block_id = i;
                temp->type = FORTUNE_CARD;
                break;
            case 22:
                strcpy(temp->name,"VOCATION");
                temp->block_id = i;
                temp->type = TAX;
                temp->rent = 5000;
                break;
            case 23:
                strcpy(temp->name,"BEBEK");
                temp->block_id = i;
                temp->type = PROPERTY;
                temp->price = 70000;
                temp->rent = 3500;
                temp->rent_1 = 20000;
                temp->rent_2 = 35500;
                temp->rent_3 = 65000;
                temp->house_price = 35000;
                temp->house_count = 0;
                temp->owner.type = NOONE;
                break;
        }
        board->next = temp;
        temp->prev = board;
        board = board->next;
    }
}

void show_board(block *board,player player_one,player player_two){
    int i, j, k, counter_left = 23, counter_right = 7;
    block *temp_name, *temp_rent_price, *temp_final_line_name, *temp_final_line_rent_price;
    block *temp_right_name, *temp_right_rent_price, *temp_left_name, *temp_left_rent_price;
    temp_right_rent_price = (block *)malloc(sizeof(block)*1);
    temp_right_name = (block *)malloc(sizeof(block)*1);
    temp_left_name = (block *)malloc(sizeof(block)*1);
    temp_left_rent_price = (block *)malloc(sizeof(block)*1);
    temp_name = (block *)malloc(sizeof(block)*1);
    temp_rent_price = (block *)malloc(sizeof(block)*1);
    temp_final_line_name = (block *)malloc(sizeof(block)*1);
    temp_final_line_rent_price = (block *)malloc(sizeof(block)*1);
    temp_name = board;
    temp_rent_price = board;
    temp_final_line_rent_price = board;
    temp_final_line_name = board;
    temp_left_name = board;
    temp_right_name = board;
    temp_right_rent_price = board;
    temp_left_rent_price = board;
    for(k=0;k<7;k++){
        temp_right_rent_price = temp_right_rent_price->next;
        temp_right_name = temp_right_name->next;
    }
    for(k=0;k<23;k++){
        temp_left_name = temp_left_name->next;
        temp_left_rent_price = temp_left_rent_price->next;
    }
    for(i=0;i<7;i++){
        if(i == 0){
            for(k=0;k<24*7;k++)
                printf("-");
            printf("-\n");
            for(j=0;j<7;j++){
                if(j != 0)
                    temp_name = temp_name->next;
                printf("|\t %8s \t",temp_name->name);
            }
            printf("|\n");
            for(j=0;j<7;j++){
                if(j != 0)
                    temp_rent_price = temp_rent_price->next;
                if(temp_rent_price->type == PROPERTY)
                    printf("|\t% 8d$ \t",temp_rent_price->price);
                else if(temp_rent_price->type == TAX)
                    printf("|\t %8d$ \t",temp_rent_price->rent);
                else
                    printf("|\t\t\t");
            }
            printf("|\n");
            for(j=0;j<7;j++){
                if(player_one.current_block_id == j && player_two.current_block_id == j)
                    printf("|\t cap -- car \t");
                else if(player_one.current_block_id == j)
                    printf("|\t car \t\t");
                else if(player_two.current_block_id == j)
                    printf("|\t cap \t\t");
                else
                    printf("|\t\t\t");
            }
            printf("|\n");
            for(k=0;k<24*7;k++)
                printf("-");
            printf("-\n");
        }
        else if(i == 6){
            for(j=0;j<18;j++){
                temp_final_line_rent_price =temp_final_line_rent_price->next;
                temp_final_line_name = temp_final_line_name->next;
            }
            for(j=0;j<7;j++){
                if(j != 0)
                    temp_final_line_name = temp_final_line_name->prev;
                printf("|\t %8s \t",temp_final_line_name->name);
            }
            printf("|\n");
            for(j=0;j<7;j++){
                if(j != 0)
                    temp_final_line_rent_price = temp_final_line_rent_price->prev;
                if(temp_final_line_rent_price->type == PROPERTY)
                    printf("|\t %8d$ \t",temp_final_line_rent_price->price);
                else if(temp_final_line_rent_price->type == TAX)
                    printf("|\t %8d$ \t",temp_final_line_rent_price->rent);
                else
                    printf("|\t\t\t");
            }
            printf("|\n");
            for(j=0;j<7;j++){
                if(player_one.current_block_id == 3*i-j && player_two.current_block_id == 3*i-j)
                    printf("|\t cap -- car \t");
                else if(player_one.current_block_id == 3*i-j)
                    printf("|\t car \t\t");
                else if(player_two.current_block_id == 3*i-j)
                    printf("|\t cap \t\t");
                else
                    printf("|\t\t\t");
            }
            printf("|\n");
            for(k=0;k<24*7;k++)
                printf("-");
            printf("-\n");
        }
        else{
            printf("|\t %8s \t|",temp_left_name->name);
            for(k=0;k<119;k++)
                printf(" ");
            printf("|\t %8s \t|\n",temp_right_name->name);
            if(temp_left_rent_price->type == PROPERTY)
                printf("|\t %8d$ \t|",temp_left_rent_price->price);
            else if(temp_left_rent_price->type == TAX)
                printf("|\t %8d$ \t|",temp_left_rent_price->rent);
            else
                printf("|\t\t\t|");
            for(k=0;k<119;k++)
                printf(" ");
            if(temp_right_rent_price->type == PROPERTY)
                printf("|\t %8d$ \t|\n",temp_right_rent_price->price);
            else if(temp_right_rent_price->type == TAX)
                printf("|\t %8d$ \t|\n",temp_right_rent_price->price);
            else
                printf("|\t\t\t|\n");
            if(player_one.current_block_id == counter_left && player_two.current_block_id == counter_left)
                printf("|\t cap -- car \t|");
            else if(player_one.current_block_id == counter_left)
                printf("|\t car\t \t|");
            else if(player_two.current_block_id == counter_left)
                printf("|\t cap \t\t|");
            else
                printf("|\t\t\t|");
            for(k=0;k<119;k++)
                printf(" ");
            if(player_one.current_block_id == counter_right && player_two.current_block_id == counter_right)
                printf("|\t cap -- car \t|\n");
            else if(player_one.current_block_id == counter_right)
                printf("|\t car \t\t|\n");
            else if(player_two.current_block_id == counter_right)
                printf("|\t cap \t\t|\n");
            else
                printf("|\t\t\t|\n");
            if(i != 5){
                for(k=0;k<25;k++)
                    printf("-");
                for(k=0;k<119;k++)
                    printf(" ");
                for(k=0;k<25;k++)
                    printf("-");
                printf("\n");
            }
            else{
                for(k=0;k<24*7;k++)
                    printf("-");
                printf("-\n");
            }
            counter_left--;
            counter_right++;
            temp_right_rent_price = temp_right_rent_price->next;
            temp_left_rent_price = temp_left_rent_price->prev;
            temp_left_name = temp_left_name->prev;
            temp_right_name = temp_right_name->next;
        }
    }
}

void show_property(block *board){
    int exit_flag = 0 , i, selection;
    block *temp;
    temp = (block *)malloc(sizeof(block)*1);
    temp = board;
    while(exit_flag == 0){
        printf("Please select a property to see details:\n");
        for(i=0;i<23;i++){
            temp = temp->next;
            if(temp->type == PROPERTY)
                printf("%d -\t%s \n",temp->block_id,temp->name);
        }
        for(i=0;i<23;i++)
            temp = temp->prev;
        printf("0 -\tExit\n");
        scanf("%d",&selection);
        if(selection == 0)
            exit_flag = 1;
        else{
            if(selection > 0 && selection < 24){
                for(i=0;i<selection;i++)
                    temp = temp->next;
                if(temp->type == PROPERTY){
                    printf("\n\n---------------------------------\n");
                    if(strlen(temp->name) < 8)
                        printf("|\t\t%s\t\t|\n",temp->name);
                    else
                        printf("|\t    %s\t\t|\n",temp->name);
                    printf("---------------------------------\n");
                    printf("|\tRent \t\t%d$\t|\n", temp->rent);
                    printf("|\tRent 1 H \t%d$\t|\n", temp->rent_1);
                    printf("|\tRent 2 H \t%d$\t|\n", temp->rent_2);
                    printf("|\tRent 3 H \t%d$\t|\n", temp->rent_3);
                    printf("---------------------------------\n");
                    printf("|\tHouse Price \t%d$\t|\n", temp->house_price);
                    printf("|\tHouse count \t%d\t|\n", temp->house_count);
                    printf("---------------------------------\n\n\n");
                }
                else
                    printf("\nWrong Selection! Please Try Again!\n\n");
                for(i=0;i<selection;i++)
                    temp = temp->prev;
            }
            else
                printf("\nWrong Selection! Please Try Again!\n");
        }
    }
}

int roll_dice(){
    int i = rand()%6 + 1;
    return i;
}

void show_player_properties(block *board, player current_player){
    block *temp;
    int i, j, counter = 0, selection = -1;
    temp = (block *)malloc(sizeof(block)*1);
    temp = board;
    do{
        printf("----------------------------------------\n");
        for(i=0;i<13;i++){
            if(current_player.owned_block_ids[i] != 0){
                for(j=0;j<i;j++)
                    temp = temp->next;
                printf("%d -%s\n",temp->block_id,temp->name);
                counter++;
            }
            for(j=0;j<i;j++)
                temp = temp->prev;
        }
        if(counter == 0){
            printf("You have not owned any property yet.\n");
            printf("----------------------------------------\n");
            selection = 0;
        }
        else{
            printf("0 - Back \n");
            printf("----------------------------------------\n");
            printf("Please select an property to see details.\n");
            scanf("%d", &selection);
            if(selection != 0){
                for(j=0;j<selection;j++)
                    temp = temp->next;
                if(temp->type != current_player.type)
                    printf("You made a wrong selection!\n");
                else{
                    printf("\n\n---------------------------------\n");
                    if(strlen(temp->name) < 8)
                        printf("|\t\t%s\t\t|\n",temp->name);
                    else{
                        printf("|\t    %s\t\t|\n",temp->name);
                        printf("---------------------------------\n");
                        printf("|\tRent \t\t%d$\t|\n",temp->rent);
                        printf("|\tRent 1 H \t%d$\t|\n",temp->rent_1);
                        printf("|\tRent 2 H \t%d$\t|\n",temp->rent_2);
                        printf("|\tRent 3 H \t%d$\t|\n",temp->rent_3);
                        printf("---------------------------------\n");
                        printf("|\tHouse Price \t%d$\t|\n",temp->house_price);
                        printf("|\tHouse count \t%d\t|\n",temp->house_count);
                        printf("---------------------------------\n\n\n");
                    }
                }
            }
        }
    }while(selection != 0);
}

int build_house(block *current_block, player *current_player){
    int flag = 0;
    if(current_player->type == current_block->type){
        if(current_block->house_count < 3){
            if(current_block->house_price <= current_player->account){
                flag = 1;
                current_player->account -= current_block->house_price;
                current_block->house_count += 1;
            }
            else
                printf("You don't have enough money to build house!\n");
        }
        else
            printf("You can't buy more than 3 houses in a property!\n");
    }
    printf("You don't have permission to build house on this property!\n ");
    return flag;
}

void sell_property(block *board, player *current_player){
    int j = 0, k, choice, control = 0, house_sell, temp, house;
    printf("Owned Block ID : ");
    while(current_player->owned_block_ids[j] != 0){
        for(k=0;k<current_player->owned_block_ids[j];k++)
            board = board->next;
        printf("%d - %s",current_player->owned_block_ids[j],board->name);
        for(k=0;k<current_player->owned_block_ids[j];k++)
            board = board->prev;
        j++;
    }
    printf("Which property do you want to sell?");
    scanf("%d",&temp);
    for(k=0;k<temp;k++)
        board = board->next;
    house = board->house_count;
    while(control == 0){
        printf("____________________________________\n\n");
        printf("|   Sell to property for enter 1   |\n");
        printf("|   Sell to house for enter 2      |\n");
        printf("|   Exit for enter 0               |\n");
        printf("____________________________________");
        scanf("%d",&choice);
        if(choice == 0)
            control = 1;
        else if(choice == 1){
            if(board->owner.type != current_player->type){
                printf("You don't have this property.\n");
                control = 1;
            }
            else{
                current_player->account += (board->price / 2);
                current_player->account += ((board->house_price / 2) * house);
                board->owner.type = NOONE;
                board->house_count = 0;
                control = 1;
            }
        }
        else if(choice == 2){
            if(board->house_count == 0){
                printf("There is no house here.\n");
                control = 1;
            }
            else{
                printf("How many houses do you want to sell?\n");
                scanf("%d",&house_sell);
                if(house_sell != board->house_count)
                    printf("There are not %d houses here. ",house_sell);
                else{
                    current_player += ((board->house_price / 2) * house);
                    board->house_count -= house_sell;
                }
            }
        }
        else
            printf("Wrong input!\n");
    }
    for(k=0;k<temp;k++)
        board = board->prev;
}

void buy_property(block *current_block, player *current_player){
    int control = 0, i = 0, count = 0, house_temp;
    char choice;
    printf("Do you want to but property? (Yes : y) (No : n)\n");
    scanf("%c",&choice);
    if(choice == 'y' || choice == 'Y')
        control = 0;
    else if(choice == 'N' || choice == 'n')
        control = 1;
    else{
        printf("Wrong input!\n");
        control = 1;
    }
    while(control == 0){
        if(current_block->block_id != current_player->current_block_id)
            control = 1;
        else{ //Same ID
            if(current_block->type != PROPERTY)
                control = 1;
            else{ // Type is Property
                if(current_block->owner.type != NOONE)
                    control = 1;
                else{ // Property is ownerless
                    if(current_player->account < current_block->price)
                        control = 1;
                    else{ // Enough money
                        if(current_player->type == CAR)
                            current_block->owner.type = CAR;
                        if(current_player->type == CAP)
                            current_block->owner.type = CAP;
                        current_player->account = current_player->account - current_block->price;
                        while(count == 0){
                            if(current_player->owned_block_ids[i] != 0)
                                i++;
                            else
                                count = 1;
                        }
                        current_player->owned_block_ids[i] = current_block->block_id;
                        printf("Congratiulations! You have buy %s.\n",current_block->name);
                        printf("You left %d$ in your account.\n",current_player->account);
                        if(!(current_block->house_count >= 0 && current_block->house_count <= 3))
                            control = 1;
                        else{ // Can Buy House
                            if(current_block->house_count >= 3)
                                control = 1;
                            else{ // Enough money
                                printf("How many houses do you want to build?\nEnter the 1 for one house\nEnter the 2 for two houses\nEnter the 3 for three houses\nEnter the 0 for none house\n");
                                scanf("%d",&house_temp);
                                if(house_temp == 0)
                                    control = 1;
                                else if(!(house_temp <= 3 && house_temp >= 0))
                                    printf("Wrong input! TRY AGAIN!!\n");
                                else{
                                    if(current_player->account < current_block->house_price * house_temp){
                                        printf("You don't have enough money.\n");
                                        control = 1;
                                    }
                                    else{
                                        current_player->account = current_player->account - (house_temp * current_block->house_price);
                                        current_block->house_count = current_block->house_count + house_temp;
                                        control = 1;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int play_computer(block *board, player *player_computer, player *player_one){
	int turn;
    int dice, average_property_cost = 0, i, count = 0, owned_id = 0, house_count, rent, control_fortune = 0;
    int temp_block_id;
    block *temp, *temp_2, *temp_3, *temp_4, *temp_house;
    fortune_card fortune[5];
    temp = (block *)malloc(sizeof(block)*1);
    temp = board;
    temp_2 = (block *)malloc(sizeof(block)*1);
    temp_2 = board;
    temp_3 = (block *)malloc(sizeof(block)*1);
    temp_3 = board;
    temp_4 = (block *)malloc(sizeof(block)*1);
    temp_4 = board;
    temp_house = (block *)malloc(sizeof(block)*1);
    temp_house = board;
    if(player_one->turn_to_wait != 0)
        player_one->turn_to_wait--;
    for(i=0;i<11;i++){
        if(player_computer->owned_block_ids[i] != 0)
            owned_id++;
    }
    for(i=0;i<24;i++){
        if(temp->type == PROPERTY){
            average_property_cost += temp->price;
            count++;
        }
        temp = temp->next;
    }
    average_property_cost = average_property_cost / count;
    dice = 1 + rand() % 5;
    printf("It's your turn to play Computer (CAP)\n");
    printf("Computer rolled the dice: %d.\n",dice);
    player_computer->current_block_id += dice;
    show_board(board, *player_one, *player_computer);
    for(i=0;i<player_computer->current_block_id;i++)
        temp_2 = temp_2->next;
    if(temp_2->block_id == player_computer->current_block_id){
        if(temp_2->type == PROPERTY){
            if(temp_2->owner.type == NOONE){
                if(average_property_cost > temp_2->price){
                    if(temp_2->price <= player_computer->account){
                        player_computer->account -= temp_2->price;
                        temp_2->owner.type = CAP;
                        player_computer->owned_block_ids[owned_id++] = temp_2->block_id;
                        turn = 1;
                    }
                }
                else{
                    dice = 1 + rand() % 5;
                    if(1 <= dice && dice <= 3){
                        if(temp_2->price <= player_computer->account){
                            player_computer->account -= temp_2->price;
                            temp_2->owner.type = CAP;
                            player_computer->owned_block_ids[owned_id++] = temp_2->block_id;
                            turn = 1;
                        }
                    }
                    else{
                        turn = 0;
                    }
                }
            }
            else if(temp_2->owner.type == CAP){
                if(owned_id >= PROPERTY_COUNT / 3){
                    dice = 1 + rand() % 5;
                    if(1 <= dice && dice <= 3){
                        if(temp_2->house_count < 3){
                            if(player_computer->account >= temp_2->house_price){
                                temp_2->house_count++;
                                player_computer->account -= temp_2->house_price;
                                turn = 1;
                            }
                        }
                    }
                    else
                        turn = 1;
                }
            }
            else{
                house_count = temp_2->house_count;
                if(house_count == 0)
                    rent = temp_2->rent;
                else if(house_count == 1)
                    rent = temp_2->rent_1;
                else if(house_count == 2)
                    rent = temp_2->rent_2;
                else
                    rent = temp_2->rent_3;
                if(player_computer->account >= rent){
                    player_computer->account -= rent;
                    turn = 1;
                }
                else{
                    i = 1;
                    temp_block_id = player_computer->owned_block_ids[0];
                    while(player_computer->owned_block_ids[i] != 0){
                        if(temp_block_id > player_computer->owned_block_ids[i])
                            temp_block_id = player_computer->owned_block_ids[i];
                        i++;
                    }
                    if(temp_block_id == 0){
                        printf("Cap don't have enough money to payment, unfortunately Cap lost the game/n");
                        turn = 2;
                    }
                    else{
                        i = 0;
                        while(player_computer->owned_block_ids[i] != 0){
                            if(player_computer->owned_block_ids[i] == temp_block_id)
                                player_computer->owned_block_ids[i] = 0;
                            i++;
                        }
                  
                        for(i=0;i<temp_block_id;i++)
                            temp_3 = temp_3->next;
                        player_computer->account += (temp_3->price / 2);
                        player_computer->account += ((temp_3->house_price * temp_3->house_count) / 2);
                        temp_3->house_count = 0;
                        temp_3->owner.type = NOONE;
                        turn = 1;
                    }
                }
            }
        }
        if(temp_2->type == TAX || temp_2->type == PUNISH){
            if(temp_2->type == TAX){
                if(player_computer->account >= temp_2->rent){
                    player_computer->account -= temp_2->rent;
                    turn = 1;
                }
                else{
                    i = 1;
                    temp_block_id = player_computer->owned_block_ids[0];
                    while(player_computer->owned_block_ids[i] != 0){
                        if(temp_block_id > player_computer->owned_block_ids[i])
                            temp_block_id = player_computer->owned_block_ids[i];
                        i++;
                    }
                    if(temp_block_id == 0){
                        printf("Cap don't have enough money to payment, unfortunately Cap lost the game/n");
                        turn = 2;
                    }
                    else{
                        i = 0;
                        while(player_computer->owned_block_ids[i] != 0){
                            if(player_computer->owned_block_ids[i] == temp_block_id)
                                player_computer->owned_block_ids[i] = 0;
                            i++;
                        }
                        player_computer->account += (temp_4->price / 2);
                        player_computer->account += ((temp_4->house_price * temp_4->house_count) / 2);
                        temp_4->house_count = 0;
                        temp_4->owner.type = NOONE;
                        turn = 1;
                    }
                }
            }
            else{
                player_computer->turn_to_wait = temp->rent;
                turn = 1;
            }
        }
        if(temp_2->type == FORTUNE_CARD){
            i = 0;
            dice = rand() % 5;
            init_the_fortune_card(fortune);
            if(fortune[dice].type == FREE_HOUSE){
                while(player_computer->owned_block_ids[i] != 0 && control_fortune == 0)
                    control_fortune = player_computer->owned_block_ids[i];
                for(i=0;i<control_fortune;i++)
                    temp_house= temp_house->next;
                build_house(temp_house, player_computer);
            }
            else if(fortune[dice].type == TIME_TRAVEL){
                dice = 1 + rand() % 5;
                if(dice <= 3 && dice >= 0)
                    player_computer->current_block_id += 2;
                else
                    player_computer->current_block_id -= 2;
            }
            else if(fortune[dice].type == GARNISHMENT){
                player_computer->account -= 5000;
            }
            else if(fortune[dice].type == GENEROSITY){
                player_computer->account -= 10000;
                player_one->account += 10000;
            }
            else{
                player_computer->account += 20000;
            }
            turn = 1;
        }
    }
    return turn;
}

int play_gamer(block *board, player *player_one, player *player_computer){
	int turn;
    int control = 0, choice, dice, i, counter_own_id = 0, k = 0 , house_count, rent_property, control_fortune = 0;
    block *temp;
    fortune_card fortune[5];
    init_the_fortune_card(fortune);
    temp = (block *)malloc(sizeof(block)*1);
    temp = board;
    if(player_computer->turn_to_wait != 0)
        player_computer->turn_to_wait--;
    printf("It's your turn to play CAR\n");
    while(control == 0){
        printf("********* MENU *********\n");
        printf("1 - Roll The Dice\n");
        printf("2 - Show My Account\n");
        printf("3 - Show My Properties\n");
        printf("4 - Show Property Deeds\n");
        printf("5 - Buy Property\n");
        printf("6 - Buy House\n");
        printf("7 - Sell Property\n");
        printf("************************\n");
        scanf("%d",&choice);
        fseek(stdin,0,SEEK_END);
        switch(choice){
            case 1:
                dice = roll_dice();
                player_one->current_block_id += dice;
                player_one->current_block_id = player_one->current_block_id % 20;
                show_board(board, *player_one, *player_computer);
                for(i=0;i<player_one->current_block_id;i++)
                    temp = temp->next;
                if(temp->type == PROPERTY){
                    if(temp->owner.type == NOONE){
                        buy_property(temp, player_one);
                        turn = 0;
                    }
                    else if(temp->owner.type == player_one->type){
                        build_house(temp, player_one);
                        turn = 0;
                    }
                    else{
                        house_count = temp->house_count;
                        if(house_count == 0)
                            rent_property = temp->rent;
                        else if(house_count == 1)
                            rent_property = temp->rent_1;
                        else if(house_count == 2)
                            rent_property = temp->rent_2;
                        else
                            rent_property = temp->rent_3;
                        if(player_one->account >= rent_property){
                            player_one->account -= rent_property;
                            turn = 0;
                        }
                        else{
                            k = 0;
                            counter_own_id = 0;
                            while(player_one->owned_block_ids[k] != 0){
                                counter_own_id++;
                                k++;
                            }
                            if(counter_own_id == 0){
                                printf("Car don't have enough money to payment, unfortunately Car lost the game/n");
                                turn = 2;
                            }
                            else{
                                sell_property(board, player_one);
                                turn = 0;
                            }
                        }
                    }
                }
                else if(temp->type == TAX){
                    if(player_one->account >= temp->rent){
                        player_one->account -= temp->rent;
                        turn = 0;
                    }
                    else{
                        while(player_one->owned_block_ids[k] != 0){
                            counter_own_id++;
                            k++;
                        }
                        if(counter_own_id == 0){
                            printf("Car don't have enough money to payment, unfortunately Car lost the game/n");
                            turn = 2;
                        }
                        else{
                            sell_property(board, player_one);
                            turn = 0;
                        }
                    }
                }
                else if(temp->type == PUNISH){
                    player_one->turn_to_wait = temp->rent;
                    turn = 0;
                }
                if(temp->type == FORTUNE_CARD){
                    i = 0;
                    dice =rand() % 5;
                    if(fortune[dice].type == FREE_HOUSE){
                        while(player_one->owned_block_ids[i] != 0 && control_fortune == 0)
                            control_fortune = player_one->owned_block_ids[i];
                        for(i=0;i<control_fortune;i++)
                            temp = temp->next;
                        build_house(temp, player_one);
                    }
                    else if(fortune[dice].type == TIME_TRAVEL){
                        dice = 1 + rand() % 5;
                        if(dice <= 3 && dice >= 0)
                            player_one->current_block_id += 2;
                        else
                            player_one->current_block_id -= 2;
                    }
                    else if(fortune[dice].type == GARNISHMENT){
                        player_one->account -= 5000;
                    }
                    else if(fortune[dice].type == GENEROSITY){
                        player_computer->account += 10000;
                        player_one->account -= 10000;
                    }
                    else{
                        player_one->account += 20000;
                    }
                    turn = 0;
                }
                break;
            case 2:
                printf("My Account : %d\n",player_one->account);
                break;
            case 3:
                show_player_properties(board, *player_one);
                break;
            case 4:
                show_property(board);
                break;
            case 5:
                for(i=0;i<player_one->current_block_id;i++)
                    temp = temp->next;
                if(temp->type == PROPERTY)
                    buy_property(temp, player_one);
                else
                    printf("This is not property. You can't buy!\n");
                break;
            case 6:
                for(i=0;i<player_one->current_block_id;i++)
                    temp = temp->next;
                if(temp->owner.type == player_one->type)
                    build_house(temp, player_one);
                else
                    printf("You Can't\n");
            case 7:
                for(i=0;i<player_one->current_block_id;i++)
                    temp = temp->next;
                if(temp->owner.type == player_one->type)
                    sell_property(temp, player_one);
                else
                    printf("You Don't Have This Property. You Can't Sell\n");
                for(i=0;i<player_one->current_block_id;i++)
                    temp = temp->prev;
                break;
            default:
                printf("Wrong Choice! Try Again!\n");
                break;
        }
        if(turn == 2 || turn == 0)
            control = 1;
    }
    while(temp != NULL)
        temp = temp->prev;
    board = temp;
    return turn;
}

void gameplay(block *board, player player_one, player player_computer){
    int control = 0;
    int turn = 1;
    show_board(board, player_one, player_computer);
    while(control == 0){
        if(turn == 1){
            turn = play_gamer(board, &player_one, &player_computer);
        }
        else if(turn == 0){
            turn = play_computer(board, &player_computer, &player_one);
        }
        else
            control = 1;
    }
}
