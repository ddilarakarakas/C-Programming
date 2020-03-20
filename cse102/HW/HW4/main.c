
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef enum pokemons{Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby} pokemon;
typedef enum attack_types{linear,quadratic} attack_type;
#define USER 0
#define AI 1
#define POKEBALL_COUNT 4
#define ALL_POKEMONS_COUNT 10
#define ARENA_SIZE 8
#define EMPTY -1
// Part-1
void pokedex(char Pokemon_name[ALL_POKEMONS_COUNT][11], int range[], attack_type type[], int attack_power[], int stamina[])
{

    int i,j,flag,exit_flag;
    int is_exist,dummy_flag=0;
    printf("Welcome to Pokedex!\n");
    while(1)
    {
        printf("Please type name of the Pokemon:\n");
        i=0;
        char pokemon_name[20],ch;
        while ( i < 19 )
        {
            pokemon_name[i]='\0';
            i++;
        }
        i=0;
        if (dummy_flag==0)
        {
            ch=getchar();
            dummy_flag=1;
        }
        while ( (ch=getchar())!='\n')
        {
            pokemon_name[i]=ch;
            i++;
        }
        for (i=0;i<ALL_POKEMONS_COUNT;i++)
        {
            j=0;
            flag=0;
            while(pokemon_name[j]!='\0')
            {
                if(Pokemon_name[i][j]!=pokemon_name[j])
                {
                    flag=0;
                    break;
                }
                else flag=1;
                j++;
            }
            if (flag==1)
            {
                printf("*********************************\n");
                printf("Name : %s\n",Pokemon_name[i]);
                if (type[i]==linear) printf("A. Type : Linear\n");
                else printf("A. Type : Quadratic\n");
                printf("Range : %d block\n",range[i]);
                printf("A. Power : %d \n",attack_power[i]);
                printf("Stamina : %d \n",stamina[i]);
                printf("*********************************\n");
                is_exist=1;
                break;
            }
            else is_exist=0;
        }
        if (is_exist==0)
        {
            j=0;
            char *s_exit="exit";
            while(pokemon_name[j]!='\0')
            {
                if(s_exit[j]!=pokemon_name[j])
                {
                    exit_flag=0;
                    j++;
                    break;
                }
                else exit_flag=1;
                j++;
            }
            if (exit_flag==1) break;
            else
            {
                if (j==0)printf("The pokemon name can't be empty! ");
                else printf("There is no pokemon which is named %s\n",pokemon_name);
            }

        }

    }


}
//Part-1

//Part-2
void show_Pokemons(char Pokemon_name[ALL_POKEMONS_COUNT][11], pokemon Pokemons[],int pokemon_count)
{
    int i,j,print_count=0;
    for (i=0;i<pokemon_count;i++)
    {
        if (Pokemons[i]!=EMPTY)
        {
            print_count++;
            printf("%d - ",Pokemons[i]);
            j=0;
            while (Pokemon_name[Pokemons[i]][j]!='\0')
            {
                printf("%c",Pokemon_name[Pokemons[i]][j]);
                j++;
            }
            printf("\n");

        }
    }
    if (print_count==0)printf("No pokemon to show, your pocket is empty.\n");
}

void catch_a_pokemon(char Pokemon_name[ALL_POKEMONS_COUNT][11], pokemon Pokemons[], pokemon *user_pokemon_pocket)
{
    int i,j,is_full_flag=1,is_exist_flag=0,selected_pokemon,is_valid=0;
    for (i=0;i<POKEBALL_COUNT;i++)
    {
        if (user_pokemon_pocket[i]==EMPTY)
        {
            is_full_flag=0;
            break;
        }
    }
    if (is_full_flag==0)
    {
        show_Pokemons(Pokemon_name,Pokemons,ALL_POKEMONS_COUNT);
        printf("Please type the ID of the pokemon to catch it: ");
        scanf("%d",&selected_pokemon);
        j=0;
        is_valid=0;
        while (is_valid==0 && j<ALL_POKEMONS_COUNT)
        {
            if(Pokemons[j]==selected_pokemon) is_valid=1;
            j++;
        }
        if (is_valid==1) {
            for (i = 0; i < POKEBALL_COUNT; i++) {
                if (user_pokemon_pocket[i] == selected_pokemon) {
                    is_exist_flag = 1;
                    break;
                }
            }
            if (is_exist_flag == 0) {
                for (i = 0; i < POKEBALL_COUNT; i++) {
                    if (user_pokemon_pocket[i] == EMPTY) {
                        user_pokemon_pocket[i] = selected_pokemon;
                        printf("Selected pokemon catched!\n");
                        break;
                    }
                }
            } else {
                printf("This pokemon is already in your pocket!\n");
            }
        } else
        {
            printf("There are no pokemon that has the %d ID\n",selected_pokemon);
        }

    }
    else
    {
        printf("Your pocket is full!\n");
    }
}

void release_a_pokemon(char Pokemon_name[ALL_POKEMONS_COUNT][11], pokemon Pokemons[], pokemon *user_pokemon_pocket)
{
    int i,selected_pokemon,is_deleted_flag=0;
    show_Pokemons(Pokemon_name,user_pokemon_pocket,POKEBALL_COUNT);
    printf("Please type the ID of the pokemon to release it: ");
    scanf("%d",&selected_pokemon);
    for (i=0;i<POKEBALL_COUNT;i++)
    {
        if (user_pokemon_pocket[i]==selected_pokemon)
        {
            user_pokemon_pocket[i]=EMPTY;
            is_deleted_flag=1;
            break;
        }
    }
    if (is_deleted_flag==1) printf("The selected pokemon released.\n");
    else printf("Selected pokemon not in your pocket!\n");
}



void print_oak_menu()
{
    printf("-----------------------\n");
    printf("1) Show Pokemons\n");
    printf("2) Catch a Pokemon\n");
    printf("3) Release a Pokemon\n");
    printf("4) Show my pocket\n");
    printf("5) Back\n");
    printf("-----------------------\n");

}

void oaks_laboratory(char Pokemon_name[ALL_POKEMONS_COUNT][11], pokemon Pokemons[], pokemon *user_pokemon_pocket)
{
    int selection=0;
    while(selection!=5)
    {
        print_oak_menu();
        printf("Please make your choice: ");
        scanf("%d",&selection);
        switch(selection)
        {
            case 1: show_Pokemons(Pokemon_name,Pokemons,ALL_POKEMONS_COUNT);
                break;
            case 2: catch_a_pokemon(Pokemon_name,Pokemons,user_pokemon_pocket);
                break;
            case 3: release_a_pokemon(Pokemon_name,Pokemons,user_pokemon_pocket);
                break;
            case 4: show_Pokemons(Pokemon_name,user_pokemon_pocket,POKEBALL_COUNT);
                break;
            case 5:   break;
            default: printf("Wrong choice!\n");

        }
    }
}

//Part-2
//Part-3

void opening_ceremony()
{
    printf("-----------------------------------------------Welcome to the Battle!--------------------------------------------------------\n");
    printf("Gameplay notices:\n");
    printf("- Each trainer can only attack with one pokemon on each turn.\n");
    printf("  -> Type pokemon ID to select the pokemon which is you want to attack with.\n");
    printf("- The AI will respond your attack automatically.\n");
    printf("- You need to select and move a pokemon to attack.\n");
    printf("- After the selected pokemon has moved, it will attacks to enemy pokemons that are in its attack range according to its attack type.\n");
    printf("- You can move a pokemon 0,1 and 2 block at most in a round and the blocks must be on the same row or same column.\n");
    printf("  -> Type the direction codes that are shown below to move your pokemon:\n");
    printf("\t\t\t\t | ( 88 ) |\n");
    printf("\t\t\t\t |  2xUP  |\n");
    printf("\t\t\t\t ----------\n");
    printf("\t\t\t\t | ( 8 )  |\n");
    printf("\t\t\t\t |   UP   |\n");
    printf("|( 44 )  2xLEFT | ( 4 )  LEFT | No Move ( 5 ) | RIGHT  ( 6 ) | 2xRIGHT  ( 66 )|\n");
    printf("\t\t\t\t |  DOWN  |\n");
    printf("\t\t\t\t |  ( 2 ) |\n");
    printf("\t\t\t\t ----------\n");
    printf("\t\t\t\t | 2xDOWN |\n");
    printf("\t\t\t\t | ( 22 ) |\n");
    printf("- The battle will be start after you locate your pokemons. Remember that you can locate your pokemons only first two rows.\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
}

void init_arena(int array[ARENA_SIZE][ARENA_SIZE])
{
    for (int i = 0; i < ARENA_SIZE; ++i) {
        for (int j = 0; j < ARENA_SIZE; ++j) {
            array[i][j]=EMPTY;
        }
    }
}

void get_first_two(char *name,char *return_string)
{
    int i=0;
    while(i<2)
    {
        return_string[i]=name[i];
        i++;
    }
}

int pokemon_counter(pokemon pocket[],int pocket_size)
{
    int count=0;
    for (int i = 0; i < pocket_size; ++i) {
        if (pocket[i]!=EMPTY)count++;
    }
    return count;

}

void show_area(char Pokemon_name[ALL_POKEMONS_COUNT][11],int area[ARENA_SIZE][ARENA_SIZE],int pokemon_staminas[ARENA_SIZE][ARENA_SIZE])
{
    int i,j,selected_index;
    printf("\n---------------------------------------------------------------------------------------------------------------------------------\n");
    for (i=0;i<ARENA_SIZE;i++)
    {
        printf("|");
        for (j=0;j<ARENA_SIZE;j++)
        {
            if (area[i][j]==EMPTY)
                printf("\t  \t|");
            else
            {
                char first_two[2];
                get_first_two(Pokemon_name[area[i][j]],first_two);
                printf("\t%s\t|",first_two);
            }
        }
        printf("\n");
        printf("|");
        for (j=0;j<ARENA_SIZE;j++)
        {
            if (pokemon_staminas[i][j]==EMPTY)
                printf("\t\t|");
            else
            {
                printf("     (%d)\t|",pokemon_staminas[i][j]);
            }
        }
        printf("\n---------------------------------------------------------------------------------------------------------------------------------\n");
    }
}

int find_pokemon_index(pokemon user_pokemon_pocket[], pokemon wanted)
{
    int i,pokemon_pack_index=EMPTY;
    for (i=0;i<POKEBALL_COUNT;i++)
    {
        if(user_pokemon_pocket[i]==wanted)
        {
            pokemon_pack_index=i;
            break;
        }
    }
    return pokemon_pack_index;
}

int is_block_empty(int area[ARENA_SIZE][ARENA_SIZE],int user_y,int user_x,pokemon selected_pokemon)
{
    if (area[user_y][user_x]!=selected_pokemon)
    {
        if(area[user_y][user_x]==EMPTY)
            return 1;
        else return 0;
    }else return 1;
}

int move_helper(int direction,int current_x,int current_y,int *new_x,int *new_y)
{
    int is_correct=1;
    switch (direction)
    {
        case 4:if (current_x-1>=0)
            {
                *new_x=current_x-1;
                *new_y=current_y;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 6:if (current_x+1<=7)
            {
                *new_x=current_x+1;
                *new_y=current_y;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 8:if (current_y-1>=0)
            {
                *new_y=current_y-1;
                *new_x=current_x;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 2:if (current_y+1<=7)
            {
                *new_y=current_y+1;
                *new_x=current_x;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 44:if (current_x-2>=0)
            {
                *new_x=current_x-2;
                *new_y=current_y;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 66:if (current_x+2<=7)
            {
                *new_x=current_x+2;
                *new_y=current_y;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 88:if (current_y-2>=0)
            {
                *new_y=current_y-2;
                *new_x=current_x;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 22:if (current_y+2<=7)
            {
                *new_y=current_y+2;
                *new_x=current_x;
            }
            else {
                is_correct=0;
                printf("Pokemon can't move to out of the battle arena!\n");
            }
            break;
        case 5:
                *new_x=current_x;
                *new_y=current_y;
                is_correct=1;
            break;

        default:printf("Wrong Selection.\n");
                *new_x=current_x;
                *new_y=current_y;
                is_correct=0;
    }
    return is_correct;
}

pokemon move(int pokemon_y_locations[],int pokemon_x_locations[],int arena[ARENA_SIZE][ARENA_SIZE],int pokemon_staminas_view[ARENA_SIZE][ARENA_SIZE],int pokemon_staminas[],char Pokemon_name[ALL_POKEMONS_COUNT][11],pokemon pokemon_pocket[],int player)
{
    int is_move_correct=0,selected_pokemon,selected_pokemon_index,user_y,user_x,is_pokemon_alive=0,rnd_direction,rnd_move_count;
    int directions[9]={4,6,8,2,5,44,66,88,22};
    if (player==USER)
    {
        while(is_pokemon_alive==0)
        {
            printf("Select your pokemon to move (type your pokemon id): \n");
            scanf("%d",&selected_pokemon);
            selected_pokemon_index=find_pokemon_index(pokemon_pocket,selected_pokemon);
            if (selected_pokemon_index!=EMPTY)
                is_pokemon_alive=1;

        }

    }else
    {
        srand(time(NULL));
        while(is_pokemon_alive==0)
        {
            selected_pokemon_index=rand()%POKEBALL_COUNT;
            if (pokemon_pocket[selected_pokemon_index]!=EMPTY)
            {
                selected_pokemon=pokemon_pocket[selected_pokemon_index];
                is_pokemon_alive=1;
            }
        }
    }

    while (is_move_correct==0)
    {
        if (player==USER)
        {
            printf("Please enter direction to move %s ",Pokemon_name[pokemon_pocket[selected_pokemon_index]]);
            scanf("%d",&rnd_direction);
            is_move_correct=move_helper(rnd_direction,pokemon_x_locations[selected_pokemon_index],pokemon_y_locations[selected_pokemon_index],&user_x,&user_y);
        }
        else
        {
            rnd_direction=rand()%9;
            rnd_direction=directions[rnd_direction];
            is_move_correct=move_helper(rnd_direction,pokemon_x_locations[selected_pokemon_index],pokemon_y_locations[selected_pokemon_index],&user_x,&user_y);
        }
        if (is_move_correct==1)
        {
            is_move_correct=is_block_empty(arena,user_y,user_x,selected_pokemon);
            if (is_move_correct==0 && player==USER)printf("The block is not empty!\n");
        }

    }
    arena[pokemon_y_locations[selected_pokemon_index]][pokemon_x_locations[selected_pokemon_index]]=EMPTY;
    pokemon_staminas_view[pokemon_y_locations[selected_pokemon_index]][pokemon_x_locations[selected_pokemon_index]]=EMPTY;
    arena[user_y][user_x]=(int)pokemon_pocket[selected_pokemon_index];
    pokemon_x_locations[selected_pokemon_index]=user_x;
    pokemon_y_locations[selected_pokemon_index]=user_y;
    pokemon_staminas_view[pokemon_y_locations[selected_pokemon_index]][pokemon_x_locations[selected_pokemon_index]]=pokemon_staminas[selected_pokemon_index];
    return selected_pokemon;
}

void attack(int attacker_x,int attacker_y,attack_type type, int range,int attack_power, int enemy_x[],int enemy_y[],int * enemy_pokemon_staminas,int stamina_view[ARENA_SIZE][ARENA_SIZE],int area[ARENA_SIZE][ARENA_SIZE])
{
    int i,current_range,attack_to_linear[POKEBALL_COUNT]={10,10,10,10},min_range=5;
    if (type==quadratic)
    {

        for (i=0;i<POKEBALL_COUNT;i++)
        {
            if (((enemy_x[i]<=attacker_x+range && enemy_x[i]>=attacker_x-range)&&(enemy_y[i]<=attacker_y+range && enemy_y[i]>=attacker_y-range)))
            {
                enemy_pokemon_staminas[i]=enemy_pokemon_staminas[i]-attack_power;
                if(enemy_pokemon_staminas[i]<0)
                {
                    enemy_pokemon_staminas[i]=0;
                    stamina_view[enemy_y[i]][enemy_x[i]]=EMPTY;
                    area[enemy_y[i]][enemy_x[i]]=EMPTY;
                }
                else stamina_view[enemy_y[i]][enemy_x[i]]=enemy_pokemon_staminas[i];

            }
        }
    }
    else
    {
        for (i=0;i<POKEBALL_COUNT;i++)
        {
            if (((enemy_x[i]<=attacker_x+range && enemy_x[i]>=attacker_x-range)&& attacker_y==enemy_y[i])||((enemy_y[i]<=attacker_y+range && enemy_y[i]>=attacker_y-range)&& attacker_x==enemy_x[i]))
            {
                if (enemy_y[i]==attacker_y)
                {
                    current_range=attacker_x-enemy_x[i];
                }else current_range=attacker_y-enemy_y[i];
                if (current_range<0)current_range*=-1;
                attack_to_linear[i]=current_range;
            }
        }
        for (i=0;i<POKEBALL_COUNT;i++)
        {
            if (attack_to_linear[i]<min_range && enemy_pokemon_staminas[i]!=0)min_range=attack_to_linear[i];
        }
        for (i=0;i<POKEBALL_COUNT;i++)
        {
            if (attack_to_linear[i]==min_range)
            {
                enemy_pokemon_staminas[i]=enemy_pokemon_staminas[i]-attack_power;
                if(enemy_pokemon_staminas[i]<=0)
                {
                    enemy_pokemon_staminas[i]=0;
                    stamina_view[enemy_y[i]][enemy_x[i]]=EMPTY;
                    area[enemy_y[i]][enemy_x[i]]=EMPTY;

                }
                else stamina_view[enemy_y[i]][enemy_x[i]]=enemy_pokemon_staminas[i];
            }
        }

    }


}

void check_is_anybody_dead(int stamina[],pokemon pokemon_pocket[],char pokemon_names[ALL_POKEMONS_COUNT][11])
{
    int i;
    for (i=0;i<POKEBALL_COUNT;i++)
    {
        if (stamina[i]==0 && pokemon_pocket[i]!=EMPTY)
        {
            printf("%s has dead!\n",pokemon_names[pokemon_pocket[i]]);
            pokemon_pocket[i]=EMPTY;
        }
    }
}

int check_is_battle_end(pokemon user_pokemons[],pokemon AI_pokemons[])
{
    int pokemon_count,result=0;
    pokemon_count=pokemon_counter(user_pokemons,POKEBALL_COUNT);
    if (pokemon_count==0)
        result=0;
    else
        result=pokemon_counter(AI_pokemons,POKEBALL_COUNT);
    return result;
}

void battle(char Pokemon_name[ALL_POKEMONS_COUNT][11], int range[], attack_type type[], int attack_power[], int stamina[], pokemon user_pokemon_pocket[])
{
    opening_ceremony();
    int arena[ARENA_SIZE][ARENA_SIZE];
    int pokemon_staminas_view[ARENA_SIZE][ARENA_SIZE];
    int pokemon_staminas[2][POKEBALL_COUNT];
    init_arena(arena);
    init_arena(pokemon_staminas_view);
    pokemon AI_pokemons[POKEBALL_COUNT]={EMPTY,EMPTY,EMPTY,EMPTY}, selected_pokemon;
    int i,k,random_pokemon_id,random_x,random_y,user_x,user_y,is_exist=1,selected_pokemon_index,is_end=1,alive_user_pokemon_count;
    int pokemon_x_locations[2][POKEBALL_COUNT];
    int pokemon_y_locations[2][POKEBALL_COUNT];
    int is_box_empty;
    srand(time(NULL));
    for (i=0;i<POKEBALL_COUNT;i++)
    {
        is_exist=1;
        is_box_empty=0;
        while(is_exist==1)
        {
            random_pokemon_id=rand()%ALL_POKEMONS_COUNT;
            is_exist=0;
            for (k=0;k<POKEBALL_COUNT;k++)
            {
                if (random_pokemon_id==AI_pokemons[k])
                {
                    is_exist=1;
                }
            }

        }
        while (is_box_empty==0)
        {
            random_x=rand()%ARENA_SIZE;
            random_y=(rand()%2)+ARENA_SIZE-3;
            if(arena[random_y][random_x]!=EMPTY)
                is_box_empty=0;
            else
                is_box_empty=1;
        }
        AI_pokemons[i]=(pokemon)random_pokemon_id;
        pokemon_x_locations[AI][i]=random_x;
        pokemon_y_locations[AI][i]=random_y;
        arena[random_y][random_x]=(int)AI_pokemons[i];
        is_box_empty=0;
        while (is_box_empty==0)
        {
            printf("Please enter %s location (in format location_x location_y):\n",Pokemon_name[user_pokemon_pocket[i]]);
            scanf("%d %d",&user_y,&user_x);
            if ((user_y>=0 && user_y<2)&&(user_x>=0 && user_x<ARENA_SIZE))
            {
                if(arena[user_y][user_x]!=EMPTY)
                {
                    is_box_empty=0;
                    printf("Selected block is not empty, please select another block to locate %s.\n\n",Pokemon_name[user_pokemon_pocket[i]]);
                }
                else
                    is_box_empty=1;
            } else
            {
                printf("Selected block is not permitted for %s, you can locate your pokemon empty blocks that are stated first and second row of the arena.\n ",Pokemon_name[user_pokemon_pocket[i]]);
            }


        }

        pokemon_x_locations[USER][i]=user_x;
        pokemon_y_locations[USER][i]=user_y;
        arena[user_y][user_x]=(int)user_pokemon_pocket[i];
        pokemon_staminas_view[user_y][user_x]=stamina[user_pokemon_pocket[i]];
        pokemon_staminas_view[random_y][random_x]=stamina[AI_pokemons[i]];
        pokemon_staminas[USER][i]=stamina[user_pokemon_pocket[i]];
        pokemon_staminas[AI][i]=stamina[AI_pokemons[i]];
    }
    show_area(Pokemon_name,arena,pokemon_staminas_view);
    printf("The Battle is ready to begin!\n");
    while(is_end!=0)
    {
        show_Pokemons(Pokemon_name,user_pokemon_pocket,POKEBALL_COUNT);
        selected_pokemon=move(pokemon_y_locations[USER],pokemon_x_locations[USER],arena, pokemon_staminas_view,pokemon_staminas[USER],Pokemon_name,user_pokemon_pocket,USER);
        selected_pokemon_index=find_pokemon_index(user_pokemon_pocket,selected_pokemon);
        attack(pokemon_x_locations[USER][selected_pokemon_index],pokemon_y_locations[USER][selected_pokemon_index],type[selected_pokemon],range[selected_pokemon],attack_power[selected_pokemon],pokemon_x_locations[AI],pokemon_y_locations[AI],pokemon_staminas[1],
               pokemon_staminas_view,arena);
        check_is_anybody_dead(pokemon_staminas[1],AI_pokemons,Pokemon_name);
        show_area(Pokemon_name,arena,pokemon_staminas_view);
        is_end=check_is_battle_end(user_pokemon_pocket,AI_pokemons);
        if (is_end!=0) {
            selected_pokemon = move(pokemon_y_locations[AI], pokemon_x_locations[AI], arena, pokemon_staminas_view,pokemon_staminas[AI], Pokemon_name, AI_pokemons, AI);
            selected_pokemon_index = find_pokemon_index(AI_pokemons, selected_pokemon);
            printf("->The AI has attacked with %s \n", Pokemon_name[AI_pokemons[selected_pokemon_index]]);
            attack(pokemon_x_locations[AI][selected_pokemon_index], pokemon_y_locations[AI][selected_pokemon_index],
                   type[selected_pokemon], range[selected_pokemon], attack_power[selected_pokemon],
                   pokemon_x_locations[USER], pokemon_y_locations[USER], pokemon_staminas[0],
                   pokemon_staminas_view, arena);
            check_is_anybody_dead(pokemon_staminas[0], user_pokemon_pocket, Pokemon_name);
            show_area(Pokemon_name, arena, pokemon_staminas_view);
            is_end = check_is_battle_end(user_pokemon_pocket, AI_pokemons);

        }
    }
    alive_user_pokemon_count=pokemon_counter(user_pokemon_pocket,POKEBALL_COUNT);
    printf("****************************************\n");
    if(alive_user_pokemon_count==0)printf("You lost, the AI won the game!\n");
    else printf("Congratulations!, you won the game!\n");
    printf("****************************************\n");

}

void show_main_menu(char Pokemon_name[ALL_POKEMONS_COUNT][11], pokemon Pokemons[], int range[], attack_type type[], int attack_power[], int stamina[], pokemon *user_pokemon_pocket)
{
    int selection,pokemon_count;
    while(1)
    {
        printf("----------------------------------------\n");
        printf("|1) Open Pokedex\t\t\t|\n");
        printf("|2) Go to Oak's Laboratory\t\t|\n");
        printf("|3) Enter the Tournament\t\t|\n");
        printf("|\t\t------\t\t\t|\n");
        printf("|Please select an option to continue:\t| \n");
        printf("----------------------------------------\n");
        scanf("%d",&selection);
        switch(selection)
        {
            case 1:
                pokedex(Pokemon_name, range, type, attack_power, stamina);
                break;
            case 2:
                oaks_laboratory(Pokemon_name, Pokemons, user_pokemon_pocket);
                break;
            case 3:
                pokemon_count=pokemon_counter(user_pokemon_pocket,POKEBALL_COUNT);
                if(pokemon_count==POKEBALL_COUNT)
                battle(Pokemon_name, range, type, attack_power, stamina, user_pokemon_pocket);
                else
                    printf("You can enter the battle only with four pokemon!\n");
                break;
            default:printf("Wrong selection!\n");
                break;
        }

    }
}

int main()
{
    char pokemon_names[ALL_POKEMONS_COUNT][11] = {"Charmander","Pikachu","Squirtle","Bulbasaur","Pidgeotto","Ratata","Mug","Caterpie","Zubat","Krabby"};
    pokemon pokemon_list[ALL_POKEMONS_COUNT] = {Charmander,Pikachu,Squirtle,Bulbasaur,Pidgeotto,Ratata,Mug,Caterpie,Zubat,Krabby};
    int pokemon_ranges[ALL_POKEMONS_COUNT] = {1,3,4,3,2,2,1,2,3,2};
    int pokemon_attack_powers[ALL_POKEMONS_COUNT] = {500,350,300,400,250,250,350,200,350,300};
    int pokemon_staminas[ALL_POKEMONS_COUNT] = {2200,1500,1700,2500,1900,2500,3000,1200,1250,2600};
    attack_type pokemon_atack_types[ALL_POKEMONS_COUNT] = {quadratic,linear,linear,linear,quadratic,linear,quadratic,quadratic,linear,linear};
    pokemon user_pokemon_pocket[POKEBALL_COUNT]={EMPTY,EMPTY,EMPTY,EMPTY};
    show_main_menu(pokemon_names, pokemon_list, pokemon_ranges, pokemon_atack_types, pokemon_attack_powers, pokemon_staminas, user_pokemon_pocket);
    return 0;
}