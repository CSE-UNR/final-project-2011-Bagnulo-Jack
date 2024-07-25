//Author: Jack Bagnulo
//Date: 7/22/2024
//CS 135 Final Project: Batship



#include <stdio.h>
//Uncomment line 9 and comment line 10 for testing
//#define FILE_EASY "test.txt"
#define FILE_EASY "easy.txt"
#define FILE_MEDIUM "medium.txt"
#define FILE_HARD "hard.txt"
#define GRID_MAX 10
void DisplayBoard(char grid[][GRID_MAX]);
int LoadBoard(char grid[][GRID_MAX], char diff);
void GetMove(char SHOTS[][GRID_MAX], char SHIPS[][GRID_MAX]);
int checkWin(char SHIPS[][GRID_MAX], char SHOTS[][GRID_MAX]);
void ClearBoard(char grid[][GRID_MAX]);

//MAIN FUNCTION-------------------------
int main(){
	char ships[GRID_MAX][GRID_MAX];
	char shots[GRID_MAX][GRID_MAX];
	char difficulty, replay;
	int win, loaded, valid;
	
	do{//Choose and load difficulty 
		win = 0;
		valid= 0;
		ClearBoard(shots);
		printf("\n     ///BATSHIP///\n\nPlay game?([E]asy, [M]edium, or [H]ard): ");
		while(valid == 0){//check for correct input
			scanf(" %c", &difficulty);
			if(difficulty == 'E' || difficulty == 'e'|| difficulty == 'M' || difficulty == 'm' || difficulty == 'H' || difficulty == 'h'){
				valid = 1;
			}else{
				printf("Invalid input. \n");	
			}
		}
		//Loading the level
		loaded = LoadBoard(ships, difficulty);
		if(loaded == 1){
			printf("ERROR: Failed to load level.\n");
			return 0;
		} 
		while(win == 0){//Playing game
			DisplayBoard(shots);
			GetMove(shots, ships);
			win = checkWin(ships, shots);
		}//Won game. check for replay
		printf("\n   ***YOU WIN***\n\n");
		printf("\nReplay?('y' or 'n'): ");
		valid = 0;
		do{
			scanf(" %c", &replay);
			if(replay == 'y' || replay == 'Y' || replay == 'N' || replay == 'n'){
				valid = 1;
			}else{
				printf("Invalid input.\n");
			}
		}while(valid == 0);
	}while(replay=='y' || replay  == 'Y');
	return 0;
}

//FUNCTION DEFINITIONS------------------------------
void DisplayBoard(char grid[][GRID_MAX]){//Displays the hit and miss locations to the player
	printf("\n   A B C D E F G H I J\n");
	printf("  |====================\n");
	
	for(int row = 0; row < GRID_MAX; row++){
		int num = 1 + row;
		printf("%2d|", num);
		for(int col = 0; col< GRID_MAX; col++){
			printf("%c ", grid[row][col]);
		}
		printf("\n");
	}
}

int LoadBoard(char grid[][GRID_MAX], char diff){//Loads ship placement based on difficulty choice
	FILE* fp;
	if(diff == 'E' || diff == 'e'){
		fp = fopen(FILE_EASY, "r");
	}
	if(diff == 'M' || diff == 'm'){
		fp = fopen(FILE_MEDIUM, "r");
	}
	if(diff == 'H' || diff == 'h'){
		fp = fopen(FILE_HARD, "r");
	}		
	if(fp == NULL){
		return 1;
	}else{
		
		for(int row = 0; row < GRID_MAX; row++){
			for(int col = 0; col < GRID_MAX; col++){
				fscanf(fp, "%c", &grid[row][col]);
				if(grid[row][col]=='\n'){
					fscanf(fp, "%c", &grid[row][col]);
				}
			}
		}
	}
	fclose(fp);
	return 0;
}

void GetMove(char SHOTS[][GRID_MAX], char SHIPS[][GRID_MAX]){//Allows the player to shoot
	char letMove;
	int numMove;
	int valid;
	do{//Getting coordinate from player
		printf("           FIRE!\n(Enter a coordinate like A1): ");
		scanf(" %c%d", &letMove, &numMove);
		if(letMove > 74 || letMove < 41 || numMove < 1 || numMove > 10){
			printf("\nInvalid input.\n\n");
			valid = 0;
		}else{
			valid = 1;
		}
	}while(valid == 0);
	
	//Converting coordinate to array indexs
	numMove = numMove - 1;
	letMove = letMove - 65;
	
	//Hit check
	if(SHIPS[numMove][letMove] == 'S'){
		printf("\n\nHIT!!!\n\n");
		SHOTS[numMove][letMove] = 'X';
	}else{
		printf("\n\nMiss.\n\n");
		SHOTS[numMove][letMove] = 'O';
	}
}

int checkWin(char SHIPS[][GRID_MAX], char SHOTS[][GRID_MAX]){//compares the shots array and ships array
	int wincheck = 1;
	for(int row = 0; row < GRID_MAX; row++){
		for(int col = 0; col < GRID_MAX; col++){
			if(SHIPS[row][col]== 'S' && (SHOTS[row][col] == 'O' || SHOTS[row][col] == ' ')){
				wincheck = 0;
			}
		}
	}
	return wincheck;
}

void ClearBoard(char grid[][GRID_MAX]){//Wipes the shots array
	for(int row = 0;row < GRID_MAX;row++){
		for(int col = 0;col < GRID_MAX;col++){
			grid[row][col] = ' ';
		}
	}
}
