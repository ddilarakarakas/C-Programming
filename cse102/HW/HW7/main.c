#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define PROPERTY_COUNT 13
typedef enum block_type{start=0,property,fortune,tax,punish}b_type;
typedef enum player_type{none=-1,car,cap}player_type;

typedef struct
{
	player_type type;
	int current_block_id;
	int owned_blocks[PROPERTY_COUNT];
	int account;
	int turn_to_wait;
	char *player_name;
} player;

typedef struct
{
    int id;
    char * name;
    int price;
    int rent;
    int rent_1;
    int rent_2;
    int rent_3;
    int house_price;
    int h_count;
    player owner;
    b_type type;
} block;

int roll_dice()
{

    int i=rand()%6+1;
    return i;
}

void show_property_deed(block board[20])
{
    int exit_flag=0,i,selection;
    while (exit_flag==0)
    {
        printf("Please select a property to see details:\n");
        for (i = 0; i < 20; ++i) {
            if (board[i].type==property)
                printf("%d -\t%s \n",board[i].id,board[i].name);
        }
        printf("0 -\tExit\n");
        scanf("%d",&selection);
        if (selection==0)
            exit_flag=1;
        else {
            if (selection > 0 && selection < 20 && board[selection].type == property) {
                printf("\n\n---------------------------------\n");
                if (strlen(board[selection].name) < 8)
                    printf("|\t\t%s\t\t|\n", board[selection].name);
                else
                    printf("|\t    %s\t\t|\n", board[selection].name);
                printf("---------------------------------\n");
                printf("|\tRent \t\t%d$\t|\n", board[selection].rent);
                printf("|\tRent 1 H \t%d$\t|\n", board[selection].rent_1);
                printf("|\tRent 2 H \t%d$\t|\n", board[selection].rent_2);
                printf("|\tRent 3 H \t%d$\t|\n", board[selection].rent_3);
                printf("---------------------------------\n");
                printf("|\tHouse Price \t%d$\t|\n", board[selection].house_price);
                printf("|\tHouse count \t%d\t|\n", board[selection].h_count);
                printf("---------------------------------\n\n\n");
            } else printf("\nWrong Selection! Please Try Again.\n\n");
        }
    }
}

void show_board(block board[20], player player_one, player player_two)
{
	printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
	int i=0,space_flag=0;
	for (i=0;i<6;i++)
	{
        if (strlen(board[i].name)<8)
		    printf("|\t%s\t\t",board[i].name);
        else
            printf("|\t%s\t",board[i].name);
	}
	printf("|\n");
	for (i=0;i<6;i++)
	{
		if (board[i].type==property || board[i].type==tax)
		    printf("|\t%d$ \t\t",board[i].price);
		else if (strlen(board[i].name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");
	}
    printf("|\n");
    for (i=0;i<6;i++)
    {
        space_flag=0;
        printf("|\t");
        if (i==player_one.current_block_id && i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {
            if (i == player_one.current_block_id) {
                printf("%s \t\t", player_one.player_name);
                space_flag = 1;
            }
            if (i == player_two.current_block_id) {
                printf("%s \t\t", player_two.player_name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(board[i].name)<8)
                printf("     \t\t");
            else
                printf(" \t\t");
        }
    }
    printf("|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");

    //Middle
    for (i=0;i<4;i++)
    {
        //Names

        if (strlen(board[19-i].name)<8)
            printf("|\t%s\t\t|",board[19-i].name);
        else
            printf("|\t%s\t|",board[19-i].name);
        printf("\t\t\t\t\t\t\t\t\t\t\t\t");

        if (strlen(board[i+6].name)<8)
            printf("|\t%s\t\t|",board[i+6].name);
        else
            printf("|\t%s\t|",board[i+6].name);
        printf("\n");
        //prices
        if (board[19-i].type==property || board[19-i].type==tax)
            printf("|\t%d$ \t\t|",board[19-i].price);
        else if (strlen(board[19-i].name)<8)
            printf("|\t     \t|");
        else
            printf("|\t\t \t|");


        printf("\t\t\t\t\t\t\t\t\t\t\t\t");

        if (board[6+i].type==property || board[6+i].type==tax)
            printf("|\t%d$ \t\t",board[6+i].price);
        else if (strlen(board[6+i].name)<8)
            printf("|\t     \t");
        else
            printf("|\t\t \t");

        printf("|\n");
        //spaces

        space_flag=0;
        printf("|\t");
        if (19-i==player_one.current_block_id && 19-i==player_two.current_block_id)
        {
            printf("%s, %s \t|",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {
            if (19 - i == player_one.current_block_id) {
                printf("%s \t\t|", player_one.player_name);
                space_flag = 1;
            }
            if (19 - i == player_two.current_block_id) {
                printf("%s \t\t|", player_two.player_name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(board[19-i].name)<8)
                printf("\t\t|");
            else
                printf("    \t\t|");
        }

        printf("\t\t\t\t\t\t\t\t\t\t\t\t");
        space_flag=0;
        printf("|\t");
        if (6+i==player_one.current_block_id && 6+i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {

            if (6+i==player_one.current_block_id)
            {
                printf("%s \t\t",player_one.player_name);
                space_flag=1;
            }
            if (6+i==player_two.current_block_id)
            {
                printf("%s \t\t",player_two.player_name);
                space_flag=1;
            }
        }

        if (space_flag==0) {
            if (strlen(board[6+i].name)<8)
                printf("\t\t");
            else
                printf("    \t\t");
        }

        printf("|\n");
        if (i!=3) {
            printf("-------------------------");
            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            printf("-------------------------");
            printf("\n");
        }

    }

    //bottom row
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
    for (i=15;i>=10;i--)
    {
        if (strlen(board[i].name)<8)
            printf("|\t%s\t\t",board[i].name);
        else
            printf("|\t%s\t",board[i].name);
    }
    printf("|\n");
    for (i=15;i>=10;i--)
    {
        if (board[i].type==property || board[i].type==tax)
            printf("|\t%d$ \t\t",board[i].price);
        else if (strlen(board[i].name)<8)
            printf("|\t     \t\t");
        else
            printf("|\t\t \t");
    }
    printf("|\n");
    for (i=15;i>=10;i--)
    {
        space_flag=0;
        printf("|\t");
        if (i==player_one.current_block_id && i==player_two.current_block_id)
        {
            printf("%s, %s \t",player_one.player_name,player_two.player_name);
            space_flag=1;
        }
        else {
            if (i == player_one.current_block_id) {
                printf("%s \t\t", player_one.player_name);
                space_flag = 1;
            }
            if (i == player_two.current_block_id) {
                printf("%s \t\t", player_two.player_name);
                space_flag = 1;
            }
        }
        if (space_flag==0) {
            if (strlen(board[i].name)<8)
                printf("     \t\t");
            else
                printf(" \t\t");
        }

    }
    printf("|\n");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void init_board(block board[20])
{
    block temp;
	player temp_player;
	temp_player.type=none;

    temp.id=0;
    temp.name="Start";
    temp.price=0;
    temp.rent=0;
    temp.rent_1=0;
    temp.rent_2=0;
    temp.rent_3=0;
    temp.owner=temp_player;
    temp.house_price=0;
    temp.h_count=0;
    temp.type=start;
    board[temp.id]=temp;
    temp.type=tax;
    temp.name="Car park";
    temp.id=2;
    temp.price=1500;
    board[temp.id]=temp;
    temp.name="Car fix";
    temp.id=8;
    temp.price=1750;
    board[temp.id]=temp;
    temp.name="Bills";
    temp.id=10;
    temp.price=2000;
    board[temp.id]=temp;
    temp.name="Oil";
    temp.id=12;
    temp.price=2250;
    board[temp.id]=temp;
	temp.name="Vocation";
    temp.id=18;
    temp.price=5000;
    board[temp.id]=temp;

	temp.type=punish;
	temp.name="Wait 2 turn";
	temp.price=2;
    temp.id=5;
    board[temp.id]=temp;
	temp.name="Wait 1 turn";
	temp.price=1;
    temp.id=15;
    board[temp.id]=temp;


    temp.type=property;

    temp.id=1;
    temp.name="Esenyurt";
    temp.price=16000;
    temp.rent=800;
    temp.rent_1=4000;
    temp.rent_2=9000;
    temp.rent_3=25000;
    temp.house_price=10000;
    temp.h_count=0;
    board[temp.id]=temp;

    temp.id=3;
    temp.name="Tuzla";
    temp.price=16500;
    temp.rent=850;
    temp.rent_1=4250;
    temp.rent_2=9500;
    temp.rent_3=26000;
    temp.house_price=12000;
    temp.h_count=0;
    board[temp.id]=temp;

    temp.id=4;
    temp.name="Arnavutkoy";
    temp.price=17000;
    temp.rent=850;
    temp.rent_1=4500;
    temp.rent_2=10000;
    temp.rent_3=28000;
    temp.house_price=12000;
    temp.h_count=0;
    board[temp.id]=temp;

    temp.id=6;
    temp.name="Catalca";
    temp.price=20000;
    temp.rent=1000;
    temp.rent_1=5000;
    temp.rent_2=12000;
    temp.rent_3=30000;
    temp.house_price=13000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=7;
    temp.name="Beykoz";
    temp.price=23000;
    temp.rent=1100;
    temp.rent_1=5500;
    temp.rent_2=12500;
    temp.rent_3=33000;
    temp.house_price=13000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=9;
    temp.name="Maltepe";
    temp.price=30000;
    temp.rent=1350;
    temp.rent_1=7000;
    temp.rent_2=15000;
    temp.rent_3=40000;
    temp.house_price=15000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=11;
    temp.name="Sisli";
    temp.price=33000;
    temp.rent=1500;
    temp.rent_1=8000;
    temp.rent_2=16000;
    temp.rent_3=42000;
    temp.house_price=16000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=13;
    temp.name="Atasehir";
    temp.price=35000;
    temp.rent=1600;
    temp.rent_1=8500;
    temp.rent_2=17000;
    temp.rent_3=45000;
    temp.house_price=17000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=14;
    temp.name="Sariyer";
    temp.price=40000;
    temp.rent=1750;
    temp.rent_1=9500;
    temp.rent_2=19000;
    temp.rent_3=48000;
    temp.house_price=19000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=16;
    temp.name="Kadikoy";
    temp.price=43000;
    temp.rent=1900;
    temp.rent_1=11000;
    temp.rent_2=21500;
    temp.rent_3=55000;
    temp.house_price=23000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=17;
    temp.name="Besiktas";
    temp.price=60000;
    temp.rent=2500;
    temp.rent_1=15000;
    temp.rent_2=28000;
    temp.rent_3=60000;
    temp.house_price=30000;
    temp.h_count=0;
    board[temp.id]=temp;

	temp.id=19;
    temp.name="Bebek";
    temp.price=70000;
    temp.rent=3500;
    temp.rent_1=20000;
    temp.rent_2=35500;
    temp.rent_3=65000;
    temp.house_price=35000;
    temp.h_count=0;
    board[temp.id]=temp;
}

void show_player_properties(block board[20], player current_player)
{
    int i,counter=0,selection;
    while (selection!=0) {
        printf("----------------------------------------\n");
        for (i = 0; i < PROPERTY_COUNT; i++) {
            if (current_player.owned_blocks[i] != -1) {
                printf("%d - %s\n", board[current_player.owned_blocks[i]].id,
                       board[current_player.owned_blocks[i]].name);
                counter++;
            }

        }
        if (counter == 0)
        {
            printf("You have not owned any property yet.\n");
            printf("----------------------------------------\n");
            selection=0;
        }
        else
        {

            printf("0 - Back \n");
            printf("----------------------------------------\n");
            printf("Please select an property to see details.\n");
            scanf("%d", &selection);

            if (selection!=0) {
                if (board[selection].owner.type != current_player.type)
                    printf("You made a wrong selection!\n");
                else {
                    printf("\n\n---------------------------------\n");
                    if (strlen(board[selection].name) < 8)
                        printf("|\t\t%s\t\t|\n", board[selection].name);
                    else
                        printf("|\t    %s\t\t|\n", board[selection].name);
                    printf("---------------------------------\n");
                    printf("|\tRent \t\t%d$\t|\n", board[selection].rent);
                    printf("|\tRent 1 H \t%d$\t|\n", board[selection].rent_1);
                    printf("|\tRent 2 H \t%d$\t|\n", board[selection].rent_2);
                    printf("|\tRent 3 H \t%d$\t|\n", board[selection].rent_3);
                    printf("---------------------------------\n");
                    printf("|\tHouse Price \t%d$\t|\n", board[selection].house_price);
                    printf("|\tHouse count \t%d\t|\n", board[selection].h_count);
                    printf("---------------------------------\n\n\n");
                }
            }
        }


    }

}

int build_house(block* current_block, player* current_player)
{
    int flag=0;
    if (current_player->type==current_block->owner.type)
    {
        if (current_block->h_count<3)
        {
            if (current_block->house_price<=current_player->account)
            {
                flag=1;
                current_player->account-=current_block->house_price;
                current_block->h_count+=1;
            }
            else
                printf("You don't have enough money to build house!\n");
        }
        else
            printf("You can't buy more than 3 houses in a property!\n");
    }
    else
        printf("You don't have permission to build house on this property!\n ");
    return flag;
}

int count_properties(player current_player)
{
    int i,count=0;
    for (i=0;i<PROPERTY_COUNT;i++)
    {
        if (current_player.owned_blocks[i]!=-1)
            count++;
    }
    return count;
}

void sell_property(block board[20], player* current_player)
{
    int property_id,flag=0,is_owned=-1,i,index,counter=0;
        if (count_properties(*current_player)!=0)
        {
            for (i = 0; i < PROPERTY_COUNT; i++) {
                if (current_player->owned_blocks[i] != -1) {
                    printf("%d - %s\n", board[current_player->owned_blocks[i]].id,
                           board[current_player->owned_blocks[i]].name);
                    counter++;
                }

            }
            printf("0 - Back\n");
            printf("Please select to sell the property:\n");

            scanf("%d",&property_id);
            if (property_id!=0)
            {
                for(i=0;i<PROPERTY_COUNT;i++)
                {
                    if (current_player->owned_blocks[i]==property_id)
                    {
                        is_owned=1;
                        index=i;
                        break;
                    }
                }
                if(is_owned!=-1)
                {
                    current_player->owned_blocks[index]=-1;
                    player temp;
                    board[property_id].owner.type=none;
                    if(board[property_id].h_count==0)current_player->account+=board[property_id].price/2;
                    if(board[property_id].h_count==1)
                    {
                        current_player->account+=(board[property_id].price+board[property_id].house_price)/2;
                    }
                    if(board[property_id].h_count==2)
                    {
                        current_player->account+=(board[property_id].price+(2*board[property_id].house_price))/2;
                    }
                    if(board[property_id].h_count==3)
                    {
                        current_player->account+=(board[property_id].price+(3*board[property_id].house_price))/2;
                    }
                }
            }
        } else
        {
            printf("You don't have any property to sell.\n");
        }

}

int insufficient_fund(block board[20], player* current_player,int required_money)
{
    int selection,flag=1;
    while (selection!=4 && current_player->account<required_money && count_properties(*current_player)!=0)
    {
        printf("You don't have enough money to continue your transaction.You need %d$ more. Please select an option to continue: \n",required_money-current_player->account);
        printf("1- Sell Property\n");
        printf("2- Show my Properties\n");
        printf("3- Show my Account\n");
        printf("0- Back\n");
        scanf("%d",&selection);
        switch (selection)
        {
            case 1:
                sell_property(board,current_player);
                break;
            case 2:
                show_player_properties(board,*current_player);
                break;
            case 3:
                printf("\n\nThere are %d $ in your account.\n\n",current_player->account);
                break;
            case 0:
                flag=0;
                break;
            default:
                printf("You made a wrong selection!\n");
                break;

        }
    }
    return flag;

}

void pay_rent(block board[20], player* current_player,player * owner)
{
    int rent=0,owned_property_count;
    rent=board[current_player->current_block_id].rent;
    if (board[current_player->current_block_id].h_count==1)rent=board[current_player->current_block_id].rent_1;
    if (board[current_player->current_block_id].h_count==2)rent=board[current_player->current_block_id].rent_2;
    if (board[current_player->current_block_id].h_count==3)rent=board[current_player->current_block_id].rent_3;
    if (rent>current_player->account)
    {
        owned_property_count=count_properties(*current_player);
        while(rent>current_player->account && owned_property_count!=0)
        {
            insufficient_fund(board,current_player,rent);
            owned_property_count=count_properties(*current_player);
        }
    }
    if (rent<current_player->account)
    {
        current_player->account-=rent;
        owner->account+=rent;
    } else
        current_player->account=0;
}

void add_to_owned(player* current_player)
{
    for (int i = 0; i < PROPERTY_COUNT; ++i) {
        if (current_player->owned_blocks[i]==-1) {
            current_player->owned_blocks[i] = current_player->current_block_id;
            printf("Current block id %d\n",current_player->current_block_id);
            break;
        } else
            printf("%d ",current_player->owned_blocks[i]);
    }
    printf("\n");
}

void copy_owner(player* old, player* new)
{
    old->type=new->type;
    old->account=new->account;
    old->turn_to_wait=new->turn_to_wait;
    old->player_name=new->player_name;
    old->current_block_id=new->current_block_id;
    for (int i = 0; i < PROPERTY_COUNT; ++i) {
        old->owned_blocks[i]=new->owned_blocks[i];
    }
}

void buy_property(block* current_block, player* current_player)
{
    if (current_block->price<=current_player->account)
    {
        current_player->account-=current_block->price;
        copy_owner(&current_block->owner,current_player);
        add_to_owned(current_player);

        printf("Congratiulations! You have buy %s.\n",current_block->name);
        printf("You left %d$ in your account.\n",current_player->account);

    }
    else
        printf("You don't have enough money to buy this property!\n");
}

void house_dialog(block board[20], player* current_player)
{
    int house_flag=1,selection,insuf_flag=1,build_flag=1;
    while (house_flag && build_flag) {
        printf("Do you want to build house on %s ?\n",
               board[current_player->current_block_id].name);
        printf("1- Yes\n");
        printf("2- No\n");
        scanf("%d", &selection);
        if (selection == 1) {

            if (current_player->account < board[current_player->current_block_id].house_price) {
                while (count_properties(*current_player)!=0 && current_player->account<board[current_player->current_block_id].house_price && insuf_flag==1)
                    insuf_flag=insufficient_fund(board,current_player,board[current_player->current_block_id].house_price);
            }
            if (current_player->account >= board[current_player->current_block_id].house_price)
                build_flag=build_house(&board[current_player->current_block_id], current_player);
            else
                house_flag=0;


        } else
            house_flag=0;
    }
}

void after_dice_menu(block board[20], player* current_player, player* other)
{
    int selection,insuf_flag=1;
    switch (board[current_player->current_block_id].type)
    {
        case property:
            printf("%s has arrived %s \n",current_player->player_name,board[current_player->current_block_id].name);
            if (board[current_player->current_block_id].owner.type==none)
            {
                printf("Do you want to buy %s ?\n",board[current_player->current_block_id].name);
                printf("1- Yes\n");
                printf("2- No\n");
                scanf("%d",&selection);
                if (selection==1)
                {

                    if (current_player->account<board[current_player->current_block_id].price)
                    {
                        while (count_properties(*current_player)!=0 && current_player->account<board[current_player->current_block_id].price && insuf_flag==1 )
                        {
                            insuf_flag=insufficient_fund(board,current_player,board[current_player->current_block_id].price);
                        }
                    }
                    buy_property(&board[current_player->current_block_id],current_player);
                    if (current_player->type==board[current_player->current_block_id].owner.type)
                    {
                        house_dialog(board,current_player);
                    }

                }

            } else
            {
                pay_rent(board,current_player,other);
            }
            break;
        case tax:
            printf("%s has arrived tax block(%s)\n",current_player->player_name,board[current_player->current_block_id].name);
            while (count_properties(*current_player)!=0 && current_player->account<board[current_player->current_block_id].price) {
                insuf_flag = insufficient_fund(board, current_player,
                                               board[current_player->current_block_id].price);
                if (insuf_flag == 0 && current_player->account < board[current_player->current_block_id].price)
                    printf("You must pay your tax!\n");
            }
            if (current_player->account>board[current_player->current_block_id].price)
                current_player->account=current_player->account-board[current_player->current_block_id].price;
            else
            {
                current_player->account=0;
            }
            break;
        case punish:
            printf("%s has punished for %d turn. \n",current_player->player_name,board[current_player->current_block_id].price);
            current_player->turn_to_wait+=board[current_player->current_block_id].price;
            break;
    }
}

void turn(block board[20], player* current_player, player * other)
{
    int flag=1,next_block;
    while(flag)
    {
        int selection;
        printf("1 - Roll the dice\n");
        printf("2 - Show my account\n");
        printf("3 - Show my properties\n");
        printf("4 - Show property deeds\n");
        printf("5 - Buy Property\n");
        printf("6 - Buy house \n");
        printf("7 - Sell property\n");
        printf("Please select an option to continue (%s):\n",current_player->player_name);
        scanf("%d",&selection);
        switch(selection)
        {
            case 1:
                if (current_player->turn_to_wait==0) {
                    next_block=(current_player->current_block_id + roll_dice());
                    if (next_block>=20)current_player->account+=10000;
                    current_player->current_block_id = next_block % 20;
                    after_dice_menu(board,current_player,other);
                    flag = 0;
                } else
                {
                    printf("You need to wait %d turn to continue.\n",current_player->turn_to_wait);
                    current_player->turn_to_wait-=1;
                    flag=0;
                }
                break;
            case 2:
                printf("\n\nThere are %d $ in your account.\n\n",current_player->account);
                break;
            case 3:
                show_player_properties(board,*current_player);
                break;
            case 4:
                show_property_deed(board);
                break;
            case 5:
                if (board[current_player->current_block_id].type==property && board[current_player->current_block_id].owner.type==-1)
                buy_property(&board[current_player->current_block_id],current_player);
                else
                {

                    printf("You don't have permission to buy this block!\n");
                }

                break;
            case 6:
                if (current_player->type==board[current_player->current_block_id].owner.type) {
                    house_dialog(board,current_player);
                }else
                {
                    printf("You don't have permission to build house on this block!\n");
                }
                break;
            case 7:
                sell_property(board,current_player);
                break;
            default:
                printf("Wrong selection!\n");
        }
    }
}

int check_end(player current_player)
{
    int owned_property_count=count_properties(current_player);
    if (current_player.account<=0 && owned_property_count==0)return 1;
    else return 0;
}

void play_game(block board[20], player* player_one, player* player_two)
{
    int is_end=0;
    printf("Welcom to Monopoly! %s will roll the dice first.\n",player_one->player_name);
    while(is_end!=1)
    {
        printf("%s :%d$ , %s:%d$\n",player_one->player_name,player_one->account,player_two->player_name,player_two->account);
        turn(board,player_one,player_two);
        show_board(board,*player_one,*player_two);
        is_end=check_end(*player_one);
        if (is_end==0)
        {
            printf("%s :%d$ , %s:%d$\n",player_one->player_name,player_one->account,player_two->player_name,player_two->account);
            turn(board,player_two,player_one);
            show_board(board,*player_one,*player_two);
            is_end=check_end(*player_two);
            if (is_end==1)
                printf("%s don't have enough money to payment, unfortunately %s lost the game!\n",player_two->player_name,player_two->player_name);
        } else
            printf("%s don't have enough money to payment, unfortunately %s lost the game!\n",player_one->player_name,player_one->player_name);

    }

}

void init_owned(player* current_player)
{
    int i;
    for (i=0;i<PROPERTY_COUNT;i++)
    {
        current_player->owned_blocks[i]=-1;
    }

}

int main() {
    block board[20];
    init_board(board);
    srand(time(NULL));
    player player_one,player_two;

    player_one.player_name="Cap";
	player_one.type=cap;
	player_one.current_block_id=0;
    player_one.turn_to_wait=0;
	player_one.account=100000;
    init_owned(&player_one);

	player_two.player_name="Car";
	player_two.type=car;
	player_two.current_block_id=0;
    player_two.turn_to_wait=0;
	player_two.account=100000;
    init_owned(&player_two);

    show_board(board,player_one,player_two);
    play_game(board,&player_one,&player_two);

    return 0;
}