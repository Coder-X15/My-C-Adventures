# include <stdio.h>
# include <stdlib.h>
// code updated on 18/10/2023
// creating my first game in C!!
// just a game with a raw CMD-like interface (fok it, BS!! I wished to have some GUI)

// some required functions:
void check_catch(char *location, int *score_var){
	// the objective check: did you pick up a star??
	if(*location == '*'){
		++*score_var;
		*location = ' ';
	}
}

void check_eog(char *map_end, int *eog_flag){
	// checks for end of game
	if(*map_end=='A'){
		++*eog_flag;
	} 
}

void swap_places(char *locA, char *locB){
	// swaps places unless the 'to' location is not a wall
	if(*locB != '|' && *locA == 'A'){
		char temp;
		temp = *locA;
		*locA = *locB;
		*locB = temp;
	} else {
		printf("ERROR:swap impossible\n");
	}
}
//
int main(){
	char keypress; // a variable to capture keypresses
	char map[5][5] = {{' ','*','*','*',' '},
					  {' ','|',' ','|',' '},
					  {'A','|',' ','|','*'},
					  {' ','|',' ','|','*'},
					  {' ','|',' ','*',' '}}; // the map
	int eog_flag = 0; // end-of-game flag, 0 = false, 1 = true
	int score = 0; // score variable
	int i, j; // counters
	int pos[2] = {2, 0}; // position currently in
	int prev[2] = {2, 0}; // position previously in
	game_loop:
		// task 1: print the map, then task 2: check for movements, execute them
		system("cls");
		printf("\nYour score:%d\n", score);
		for(i = 0; i < 5; i++){
			for(j = 0;j < 5;j++){
				printf("%c",map[i][j]);
			}
			printf("\n");
		}
		printf("\n Press W for up, S for down, A for left and D for right.");
		printf("\n Previously at: (%d, %d))",prev[0],prev[1]);
		printf("\n Currently at: (%d, %d)",pos[0],pos[1]);
		keypress = getch();
		prev[0] = pos[0]; prev[1] = pos[1]; // keeping track of the previous position
		switch(keypress){
			case 'w':
				if(pos[0] != 0 && map[pos[0] - 1][pos[1]] != '|'){
					--pos[0]; // going up = current - 1 on y - axis
				}
				break;
			case 'a':
				if(pos[1] != 0 && map[pos[0]][pos[1]-1] != '|'){
					--pos[1]; // going left = current - 1 on x axis
				}
				break;
			case 's':
				if(pos[0]!=4 && map[pos[0]+1][pos[1]] != '|'){
					++pos[0]; // going down = current + 1 on y axis
				}
				break;
			case 'd':
				if(pos[1] != 4 && map[pos[0]][pos[1]+1] != '|'){
					++pos[1]; // going right = current + 1 on x axis
				}
				break;
			default:
				goto game_loop;
				break;
		}
		// we have to do the checks before we actually swap places
		check_catch(&map[pos[0]][pos[1]],&score); // checking if the new location has a star
		swap_places(&map[prev[0]][prev[1]], &map[pos[0]][pos[1]]); // swapping places
		check_eog(&map[4][4],&eog_flag); // checking if the agent has reached extraction point/ end point
		if(eog_flag != 0){
			system("cls");
			printf("\nYour score:%d\n", score);
			for(i = 0; i < 5; i++){
				for(j = 0;j < 5;j++){
					printf("%c",map[i][j]);
				}
				printf("\n");
			}
			printf("\nTHE END");
		} else {
			goto game_loop;
		}
}


