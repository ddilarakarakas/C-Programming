#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DICT_SIZE 15
#define WORD_LEN 10
#define LINE_LEN 18

int get_line_size(char *line);
void copy_string(char *source, char *destination);
void remove_newline(char *line);
void print_dictionary(char *dict[]);
void print_coord(int coord[DICT_SIZE][4]) ;
void random_letter(char area[][DICT_SIZE]);
void wordHunter(char area[][DICT_SIZE],char *dict[],int coord[DICT_SIZE][4]);
void game(char area [][DICT_SIZE], char *dict[],int coord[DICT_SIZE][4], int *foundWord);
int strcomp(char a[],char b[]);
void printLast(char area[][DICT_SIZE]);


int main(){
    srand(time(NULL));
    char *dict[DICT_SIZE];
    int coord[DICT_SIZE][4];
    char line[LINE_LEN];
    char area[DICT_SIZE][DICT_SIZE];
    int *foundWord = (int*)malloc(sizeof(int)*1);
    FILE *fp = fopen("word_hunter.dat", "r");
    int line_counter = 0;
    int dict_counter = 0;
    int i=0;
    *foundWord = 0;
    while(fgets(line, LINE_LEN, fp) != NULL) {
        if(line_counter%5 == 0) {
            dict[dict_counter] = (char*) malloc(sizeof(char) * get_line_size(line));
            remove_newline(line);
            copy_string(line, dict[dict_counter]);
            i++;
        } else if (line_counter%5 == 1){
            coord[dict_counter][0] = atoi(line);
        } else if (line_counter%5 == 2){
            coord[dict_counter][1] = atoi(line);
        } else if (line_counter%5 == 3){
            coord[dict_counter][2] = atoi(line);
        } else if (line_counter%5 == 4){
            coord[dict_counter][3] = atoi(line);
            dict_counter++;
        }
        line_counter++;
    }
    fclose(fp);
    wordHunter(area, dict, coord);
    game(area, dict, coord, foundWord);
    printf("\n");
    printLast(area);
    return 0;
}

void game(char area [][DICT_SIZE], char *dict[],int coord[DICT_SIZE][4], int *foundWord){
	char user[15];
	char ignoreMe[10];
	int control= 0;
	int control1 = 0;
	int i,j;
	i=0;
	int dict_length;
	int coord_x, coord_y, coor_x, coor_y;
	while(control == 0){
	
		printf("Please enter a letter for the prediction. If you want to exit, please 'exit'.\n");
		scanf("%s",user);
		if(strcomp(user,"exit") == 1){
			printf("\nGame Ending. The number of words found is %d\n", *foundWord);
			control = 1;
		}
		else if(*foundWord == DICT_SIZE){
			printf("\nAll Words found. Congratulations!!\n");
			control = 1;
			return;
		}
		else{
			printf("Please enter coord1 : ");
			scanf("%d", &coord_x);
			printf("Please enter coord2 : ");
			scanf("%d",&coord_y);

			i=0;
			control1 = 0;
			
			while(control1==0 && i<DICT_SIZE){
				if(dict[i][0] == user[0] && strcomp(dict[i],user) == 1){
							// dict has user's word ?
					control1=1;
					
				}else{
					i++;
				}	
				
			}
			if(control1 == 1){
				if((coord[i][0] == coord_x && coord[i][1] == coord_y) || (coord[i][2] == coord_x && coord[i][3])){ //north and south direction found (first coords or last coords)

					
					if(coord[i][0] == coord[i][2]){ // horizontal direction.. if coords are last, direction is west. Otherwise it is the opposite.
			            dict_length = (coord[i][3] - coord[i][1]) + 1;
			            coor_x = coord[i][0];
			            coor_y = coord[i][1];
			            for(j=0;j<dict_length;j++){
			                area[coor_x][coor_y] = dict[i][j] - 'a' + 'A';
			                coor_y++;
			            }
			        }
			        else if(coord[i][1] == coord[i][3]){  // vertical direction.. if coords are last, direction is north. Otherwise it is the opposite.
			            dict_length = (coord[i][2] - coord[i][0]) + 1;
			            
			            coor_x = coord[i][0];
			            coor_y = coord[i][1];
			            for(j=0;j<dict_length;j++){
			                area[coor_x][coor_y] = dict[i][j] - 'a' + 'A';
			                coor_x++;
			            }
			        }
			        else{			//diagonal direction...
			            dict_length = (coord[i][2] - coord[i][0]) + 1;
			            coor_x = coord[i][0];
			            coor_y = coord[i][1];
			            for(j=0;j<dict_length;j++){
			                area[coor_x][coor_y] = dict[i][j] - 'a' + 'A';
			                coor_x++;
			                coor_y++;
			            }
			        }
			        *foundWord = *foundWord + 1;  //true prediction word count
			        printf("\n");
			        printLast(area);
			        printf("\n");
				}
				else{
					printf("\nWrong guess!\n");
				}
			}
			else{
				printf("\nWrong guess!\n");
			}
		}
	}
}

int strcomp(char a[],char b[]){
    int i = 0,result = 1;
    int controlForLoop = 1;
    int control1 = 0, control2 = 0;
    while(controlForLoop == 1){
        if(a[i] == '\0' || b[i] == '\0'){
            if(a[i] == '\0')
                control1 = 1;
            if(b[i] == '\0')
                control2 = 1;
            controlForLoop = 0;
        }
        else{
            if(a[i] != b[i])
                result = 0;
        }
        i++;
    }
    if(control1 == 1 && control2 == 1 && result == 1){
        return result;
    }
    else{
        result = 0;
        return result;
    }
}

int get_line_size(char *line) {
    char *ch_iter = line; // so as not to lose beginning of line
    int counter = 0;
    // go until you see new line or null char
    while(*ch_iter != '\n' && *ch_iter != '\0') {
        ch_iter++; // next char
        counter++; // increment counter
    }
    return counter;
}

void copy_string(char *source, char *destination) {
    // get iterators over original pointers
    char *src_iter = source;
    char *dst_iter = destination;
    // until null char
    while (*src_iter != '\0') {
        // copy pointers
        *dst_iter = *src_iter;
        // advance to next char
        src_iter++;
        dst_iter++;
    }
    // terminate string
    *dst_iter = '\0';
}

void remove_newline(char *line) {
	char *ch_iter = line; // go until you see new line
	
    while(*ch_iter != '\n') {
        ch_iter++; // next char
    }
    (*(ch_iter-1)) = '\0'; // overwrite new line
	
}

void print_dictionary(char *dict[]) {
    int i;
    for(i = 0 ; i < DICT_SIZE ; i++) {
        printf("%s\n", dict[i]);
    }
}

void print_coord(int coord[DICT_SIZE][4]) {
    int i, j;
    for(i = 0 ; i < DICT_SIZE ; i++) {
        for(j = 0 ; j < 4 ; j++) {
            printf("%d ", coord[i][j]);
        }
        printf("\n");
    }
}

void random_letter(char area[][15]){
    int i,j;
    int random;
    for(i=0;i<DICT_SIZE;i++){
        for(j=0;j<DICT_SIZE;j++){
            random = ('a') + (rand() % ('z' - 'a'));
            area[i][j] = random;
        }
    }
}

void printLast(char area[][DICT_SIZE]){
	int i,j;
	for(i=0;i<DICT_SIZE;i++){
        for(j=0;j<DICT_SIZE;j++){
            printf("%c ",area[i][j]);
        }
        printf("\n");
    }
}

void wordHunter(char area[][DICT_SIZE],char *dict[],int coord[DICT_SIZE][4]){
    int i,j,coor_y,coor_x;
    int dict_length;
    random_letter(area);
    for(i=0;i<DICT_SIZE;i++){
        if(coord[i][0] == coord[i][2]){
            dict_length = (coord[i][3] - coord[i][1]) + 1;
            coor_x = coord[i][0];
            coor_y = coord[i][1];
            for(j=0;j<dict_length;j++){
                area[coor_x][coor_y] = dict[i][j];
                coor_y++;
            }
        }
        else if(coord[i][1] == coord[i][3]){
            dict_length = (coord[i][2] - coord[i][0]) + 1;
            
            coor_x = coord[i][0];
            coor_y = coord[i][1];
            for(j=0;j<dict_length;j++){
                area[coor_x][coor_y] = dict[i][j];
                coor_x++;
            }
        }
        else{
            dict_length = (coord[i][2] - coord[i][0]) + 1;
            coor_x = coord[i][0];
            coor_y = coord[i][1];
            for(j=0;j<dict_length;j++){
                area[coor_x][coor_y] = dict[i][j];
                coor_x++;
                coor_y++;
            }
        }
    }
    printLast(area);
}