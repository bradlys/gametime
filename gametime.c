/*

The reason for a lot of #define's is because it was faster to manually type in the
information than to write a custom parser and figure out a format.

If you want, you can fork this project and write a parser.

*/

#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NTRIALS     10000
#define DEFAULT_OUTFILE      gametime.csv
#define DEFAULT_RANDOM_SEED time(NULL)

//How often do they possess the ball?
#define TEAM1PLAYER1USG 1224
#define TEAM1PLAYER2USG 2872
#define TEAM1PLAYER3USG 3208
#define TEAM1PLAYER4USG 2118
#define TEAM1PLAYER5USG 578

//How often do they decide to do 2 pt shots?
#define TEAM1PLAYER12PT 3409
#define TEAM1PLAYER22PT 7151
#define TEAM1PLAYER32PT 6254
#define TEAM1PLAYER42PT 7194
#define TEAM1PLAYER52PT 8131

//How often do they decide to do 3 pt shots?
#define TEAM1PLAYER13PT 4590
#define TEAM1PLAYER23PT 460
#define TEAM1PLAYER33PT 1436
#define TEAM1PLAYER43PT 621
#define TEAM1PLAYER53PT 0

//How often do they decide to do free throws?
#define TEAM1PLAYER1FT 770
#define TEAM1PLAYER2FT 1330
#define TEAM1PLAYER3FT 1349
#define TEAM1PLAYER4FT 1195
#define TEAM1PLAYER5FT 599

//How often do they make a 2 pt shot?
#define TEAM1PLAYER1POS2PT 4300
#define TEAM1PLAYER2POS2PT 5210
#define TEAM1PLAYER3POS2PT 5670
#define TEAM1PLAYER4POS2PT 5360
#define TEAM1PLAYER5POS2PT 5120

//How often do they make a 3 pt shot?
#define TEAM1PLAYER1POS3PT 4100
#define TEAM1PLAYER2POS3PT 2580
#define TEAM1PLAYER3POS3PT 4060
#define TEAM1PLAYER4POS3PT 2820
#define TEAM1PLAYER5POS3PT 0

//How often do they make free throws?
#define TEAM1PLAYER1POSFT 7870
#define TEAM1PLAYER2POSFT 7760
#define TEAM1PLAYER3POSFT 7530
#define TEAM1PLAYER4POSFT 7970
#define TEAM1PLAYER5POSFT 7230

//How often do they turn over the ball?
#define TEAM1PLAYER1POSTO 1230
#define TEAM1PLAYER2POSTO 1060
#define TEAM1PLAYER3POSTO 960
#define TEAM1PLAYER4POSTO 990
#define TEAM1PLAYER5POSTO 1270

//Number of average possessions per game for the team
#define TEAM1POSSESSIONS 101

#define TEAM2PLAYER1USG 2765
#define TEAM2PLAYER2USG 1768
#define TEAM2PLAYER3USG 1562
#define TEAM2PLAYER4USG 2552
#define TEAM2PLAYER5USG 1353

#define TEAM2PLAYER12PT 7334
#define TEAM2PLAYER22PT 4216
#define TEAM2PLAYER32PT 5502
#define TEAM2PLAYER42PT 7826
#define TEAM2PLAYER52PT 7240

#define TEAM2PLAYER13PT 546
#define TEAM2PLAYER23PT 3259
#define TEAM2PLAYER33PT 2667
#define TEAM2PLAYER43PT 55
#define TEAM2PLAYER53PT 0

#define TEAM2PLAYER1FT 1180
#define TEAM2PLAYER2FT 1255
#define TEAM2PLAYER3FT 990
#define TEAM2PLAYER4FT 1099
#define TEAM2PLAYER5FT 1669

#define TEAM2PLAYER1POS2PT 5220
#define TEAM2PLAYER2POS2PT 4250
#define TEAM2PLAYER3POS2PT 4980
#define TEAM2PLAYER4POS2PT 5040
#define TEAM2PLAYER5POS2PT 5580

#define TEAM2PLAYER1POS3PT 3480
#define TEAM2PLAYER2POS3PT 3530
#define TEAM2PLAYER3POS3PT 3770
#define TEAM2PLAYER4POS3PT 2860
#define TEAM2PLAYER5POS3PT 0

#define TEAM2PLAYER1POSFT 8450
#define TEAM2PLAYER2POSFT 7960
#define TEAM2PLAYER3POSFT 8240
#define TEAM2PLAYER4POSFT 8180
#define TEAM2PLAYER5POSFT 7280

#define TEAM2PLAYER1POSTO 940
#define TEAM2PLAYER2POSTO 1270
#define TEAM2PLAYER3POSTO 840
#define TEAM2PLAYER4POSTO 1020
#define TEAM2PLAYER5POSTO 1090
 
#define TEAM2POSSESSIONS 104

void runGame (int curr[4][5]);
int random_int(int someint1, int someint2);
void outputResults(int results[4][5]);

int main(int argc, char ** argv) {
	int parameters = DEFAULT_NTRIALS;
	if(argc > 2){
		fprintf(stderr, "Too many arguments were given. Using defaults for everything.");
	}
	else{
		parameters = atoi(argv[1]);
	}
	int ntrials = parameters;
	srand(time(NULL));
	
	int i = 0;
	int k = 0;
	int results[4][5];
	//Clears results
	for(i = 0; i < 5; i++){
		results[0][i] = 0;
		results[1][i] = 0;
		results[2][i] = 0;
		results[3][i] = 0;
	}
	for(k = 0; k < ntrials; k++){
		//Create results
		runGame(results);
		//Output results
		outputResults(results);
		//Clear results
		for(i = 0; i < 5; i++){
			results[0][i] = 0;
			results[1][i] = 0;
			results[2][i] = 0;
			results[3][i] = 0;
		}
	}
	return 0;
}

/**
Simulates a game
*/
void runGame (int curr[4][5]){
	int team1usage[5] = {TEAM1PLAYER1USG, TEAM1PLAYER2USG, TEAM1PLAYER3USG, TEAM1PLAYER4USG, TEAM1PLAYER5USG};
	int team12pt[5] = {TEAM1PLAYER12PT, TEAM1PLAYER22PT, TEAM1PLAYER32PT, TEAM1PLAYER42PT, TEAM1PLAYER52PT};
	int team13pt[5] = {TEAM1PLAYER13PT, TEAM1PLAYER23PT, TEAM1PLAYER33PT, TEAM1PLAYER43PT, TEAM1PLAYER53PT};
	int team1ft[5] = {TEAM1PLAYER1FT, TEAM1PLAYER2FT, TEAM1PLAYER3FT, TEAM1PLAYER4FT, TEAM1PLAYER5FT};
	int team1pos2pt[5] = {TEAM1PLAYER1POS2PT, TEAM1PLAYER2POS2PT, TEAM1PLAYER3POS2PT, TEAM1PLAYER4POS2PT, TEAM1PLAYER5POS2PT};
	int team1pos3pt[5] = {TEAM1PLAYER1POS3PT, TEAM1PLAYER2POS3PT, TEAM1PLAYER3POS3PT, TEAM1PLAYER4POS3PT, TEAM1PLAYER5POS3PT};
	int team1posft[5] = {TEAM1PLAYER1POSFT, TEAM1PLAYER2POSFT, TEAM1PLAYER3POSFT, TEAM1PLAYER4POSFT, TEAM1PLAYER5POSFT};
	int team2usage[5] = {TEAM2PLAYER1USG, TEAM2PLAYER2USG, TEAM2PLAYER3USG, TEAM2PLAYER4USG, TEAM2PLAYER5USG};
	int team22pt[5] = {TEAM2PLAYER12PT, TEAM2PLAYER22PT, TEAM2PLAYER32PT, TEAM2PLAYER42PT, TEAM2PLAYER52PT};
	int team23pt[5] = {TEAM2PLAYER13PT, TEAM2PLAYER23PT, TEAM2PLAYER33PT, TEAM2PLAYER43PT, TEAM2PLAYER53PT};
	int team2ft[5] = {TEAM2PLAYER1FT, TEAM2PLAYER2FT, TEAM2PLAYER3FT, TEAM2PLAYER4FT, TEAM2PLAYER5FT};
	int team2pos2pt[5] = {TEAM2PLAYER1POS2PT, TEAM2PLAYER2POS2PT, TEAM2PLAYER3POS2PT, TEAM2PLAYER4POS2PT, TEAM2PLAYER5POS2PT};
	int team2pos3pt[5] = {TEAM2PLAYER1POS3PT, TEAM2PLAYER2POS3PT, TEAM2PLAYER3POS3PT, TEAM2PLAYER4POS3PT, TEAM2PLAYER5POS3PT};
	int team2posft[5] = {TEAM2PLAYER1POSFT, TEAM2PLAYER2POSFT, TEAM2PLAYER3POSFT, TEAM2PLAYER4POSFT, TEAM2PLAYER5POSFT};
	
	int i = 0;
	int action = 0;
	int coin = 0;
	int playing = 0;
	int team1score = 0;
	int team2score = 0;
	
	//Simulate a possession team1 times
	for(i = 0; i < TEAM1POSSESSIONS; i++){
		coin = random_int(1, 10000);
		//Who gets the ball?
		if(coin > (10000 - team1usage[0])){
			playing = 0;
		}
		else{
			if(coin > (10000 - team1usage[0] - team1usage[1])){
				playing = 1;
			}
			else{
				if(coin > (10000 - team1usage[0] - team1usage[1] - team1usage[2])){
					playing = 2;
				}
				else{
					if(coin > (10000 - team1usage[0] - team1usage[1] - team1usage[2] - team1usage[3])){
						playing = 3;
					}
					else{
						playing = 4;
					}
				}
			}
		}
		
		//Deciding which shot/action to take
		action = 0;
		coin = random_int(1, 10000);
		if(coin > (10000 - team12pt[playing])){
			action = 0;
		}
		else{
			if(coin > (10000 - team12pt[playing] - team13pt[playing])){
				action = 1;
			}
			else{
				if(coin > (10000 - team12pt[playing] - team13pt[playing] - team1ft[playing] )){
					action = 2;
				}
				else{
					action = 3;
				}
			}
		}
		
		//Chance they make a shot
		coin = random_int(1,10000);
		if(action == 0){
			if (coin < team1pos2pt[playing]){
				team1score += 2;
				curr[0][playing] += 2;
			}
		}
		if(action == 1){
			if (coin < team1pos3pt[playing]){
				team1score += 3;
				curr[0][playing] += 3;
			}
		}
		if(action == 2){
			if (coin < team1posft[playing]){
				team1score += 1;
				curr[0][playing] += 1;
			}
			coin = random_int(1,10000);
			if (coin < team1posft[playing]){
				team1score += 1;
				curr[0][playing] += 1;
			}
		}
	}
	
	//Simulating team 2's possessions
	for(i = 0; i < TEAM2POSSESSIONS; i++){
		coin = random_int(1, 10000);
		//Who gets the ball?
		if(coin > (10000 - team2usage[0])){
			playing = 0;
		}
		else{
			if(coin > (10000 - team2usage[0] - team2usage[1])){
				playing = 1;
			}
			else{
				if(coin > (10000 - team2usage[0] - team2usage[1] - team2usage[2])){
					playing = 2;
				}
				else{
					if(coin > (10000 - team2usage[0] - team2usage[1] - team2usage[2] - team2usage[3])){
						playing = 3;
					}
					else{
						playing = 4;
					}
				}
			}
		}
		
		//Deciding which shot/action to take
		action = 0;
		coin = random_int(1, 10000);
		if(coin > (10000 - team22pt[playing])){
			action = 0;
		}
		else{
			if(coin > (10000 - team22pt[playing] - team23pt[playing])){
				action = 1;
			}
			else{
				if(coin > (10000 - team22pt[playing] - team23pt[playing] - team2ft[playing] )){
					action = 2;
				}
				else{
					action = 3;
				}
			}
		}
		
		//Chance they make a shot
		coin = random_int(1,10000);
		if(action == 0){
			if (coin < team2pos2pt[playing]){
				team2score += 2;
				curr[1][playing] += 2;
			}
		}
		if(action == 1){
			if (coin < team2pos3pt[playing]){
				team2score += 3;
				curr[1][playing] += 3;
			}
		}
		if(action == 2){
			if (coin < team2posft[playing]){
				team2score += 1;
				curr[1][playing] += 1;
			}
			coin = random_int(1,10000);
			if (coin < team2posft[playing]){
				team2score += 1;
				curr[1][playing] += 1;
			}
		}
	}
	
	//Put in the score
	curr[3][0] = team1score;
	curr[3][1] = team2score;
}

//Append the results to output.csv in current directory.
void outputResults(int results[4][5]){
	FILE * file;
	file = fopen("output.csv", "a");
	int i = 0;
	char str[32];
	char comma[3] = {',', '\0', '\0'};
	for(i = 0; i < 5; i++){
		sprintf(str, "%d", results[0][i]);
		fputs(str, file);
		fputs(comma, file);
	}
	for(i = 0; i < 5; i++){
		sprintf(str, "%d", results[1][i]);
		fputs(str, file);
		fputs(comma, file);
	}
	sprintf(str, "%d", results[3][0]);
	fputs(str, file);
	fputs(comma, file);
	sprintf(str, "%d", results[3][1]);
	fputs(str, file);
	fputs("\n", file);
	fclose(file);
}
	
/*
* Returns a random integer between someint1 and someint2.
* @param int someint1 - an integer. Includes this number
* @param int someint2 - an integer. Up to and including this.
* @returns int - random number between someint1 and someint2.
*/
int random_int(int someint1, int someint2){
	return ((someint2 - someint1 + 1) * ((double)rand()/(double)(RAND_MAX)) + someint1);
}



