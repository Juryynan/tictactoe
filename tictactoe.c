#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
*   Small Tic-Tac-Toe game developed with c.
*   
*/

enum gameState{Play = 1, ShowPlayers, About, Exit};

typedef struct player {
    char name[30];
    char mark;
    int points;
} Player;


void aboutDescription(){

    printf("\nAbout\nAccording to wikipedia: Games played on three-in-a-row boards can be traced back to ancient Egypt,\nwhere such game boards have been found on roofing tiles dating from around 1300 BC.\n");
    printf("\nGame is simple basic tic-tac-toe, players choose number between (1 - 9)\neach number represents square in board\nfirst square from left to right 1-3, second row 2-6 and last row 7-9.\n\n");

}

int checkMove(char map[3][3], int row, int column){

    if(map[row][column] == ' '){
        return 1;
    } else {
        return 0;
    }
}

int setTurn(){
     srand(time(NULL));
     return(rand() % 2);
}

int checkWinner(char map[3][3]){

    for(int i = 0; i < 3; i++){
      
        // Here check rows
        if(map[i][0] == 'X' && map[i][1] == 'X' && map[i][2] == 'X'){
            return 0;
        } else if (map[i][0] == 'O' && map[i][1] == 'O' && map[i][2] == 'O'){
            return 1;

        //Here check columns
        } else if (map[0][i] == 'X' && map[1][i] == 'X' && map[2][i] == 'X') {
            return 0;
        } else if (map[0][i] == 'O' && map[1][i] == 'O' && map[2][i] == 'O') {
            return 1;
        }
    
        //Here check crossed

        else if(map[0][0] == 'X' && map[1][1] == 'X' && map[2][2] == 'X'){
            return 0;
        }
        else if (map[0][0] == 'O' && map[1][1] == 'O' && map[2][2] == 'O'){
            return 1;
        }

        else if(map[0][2] == 'X' && map[1][1] == 'X' && map[2][0] == 'X'){
            return 0;
        }
        else if (map[0][2] == 'O' && map[1][1] == 'O' && map[2][0] == 'O')
        {
            return 1;
        }
    
    }

    return -1;

}

void printMap(char map[3][3]){
    
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(map[i][j] == 'X' || map[i][j] == 'O'){
                 printf("%5c", map[i][j]);
            } else {
                printf("%5s", " ");
            }

            if (j < 2){
                printf("%5s", "|"); 
            }
      
        }
        printf("\n");
        if(i < 2){
            for(int i = 0; i < 30; i++){
                if(i == 9 || i == 19){
                    printf("+");
                } else {
                    printf("-");
                }
            }
            printf("\n");
        }
    
    }
}


void setPlayerMove(char map[3][3], int *turn, Player firstp, Player secondp){
    
    int row, column, choice;
    char message;

    if(*turn == 0){
        printf("\n%5s's turn (1-9) > ", firstp.name);
    } else if (*turn == 1){
        printf("\n%5s's turn (1-9) > ", secondp.name);
    }

    int input_check = scanf("%d", &choice);
    if(choice != 1 && choice < 1 || choice > 9){
        printf("Invalid input!");
        scanf("%d", &choice);
    } else {
    

    printf("\n\n\n\n\n\n\n\n\n\n");

        for(int i = 0; i < choice ; i++){
            if(choice <= 3 ){
                row = 0;
                column = choice - 1;
            } else if(choice >= 4 && choice <= 6){
                row = 1;
                column = choice - 4;
            } else if (choice >= 7 && choice <= 9){
                row = 2;
                column = choice - 7;
            }
        }

    if(*turn == 0 && checkMove(map, row, column)){
        map[row][column] = firstp.mark; // firstplayer is X
        *turn = 1;
    } 
    else if (*turn == 1 && checkMove(map, row, column)){
        map[row][column] = secondp.mark; // second player is O
        *turn = 0;
    } else {
        printf("space %d. already filled.\n\n", choice);
        }
    }
}

void resetBoard(char map[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            map[i][j] = ' ';
        }
    }
}


int mainMenu(int menuChoice){

    char *title = "*Tic-tac-toe*\n";

    printf("%23s\n", title);


    const char *table [] = { 
        "START", 
        "SCORES", 
        "ABOUT", 
        "EXIT"
        };

    for(int i = 0; i < 4; i++){
  
        printf("%10i. %10s\n", i + 1, table[i]);
        
    }

    printf("\n%11s", "> ");
    scanf("%d", &menuChoice);
    
  

    return menuChoice;

}

void writeTofile(Player winner){

    FILE *fp = fopen("Highscore.txt", "a");

    if(fp == NULL){
        printf("No highscores");
    }


    fwrite(&winner, sizeof(winner), 1, fp);

    fclose(fp);

}

void gameLoop(int menuChoice){
    
    Player firstP;
    Player secondP;
    int turn = setTurn();
    int running = 1;
    char play;

    char map[3][3] = {
         {' ', ' ', ' '},
         {' ', ' ', ' '},
         {' ', ' ', ' '}
    };

    printf("\n");

    printf("%23s", "Player 1 name: ");
    scanf("%s", &firstP.name);
    printf("%23s", "Player 2 name: ");
    scanf("%s", &secondP.name);

    firstP.mark = 'X';
    secondP.mark = 'O';

    firstP.points = 0;
    secondP.points = 0;

    printf("\n");

    while(running){
        
        printMap(map);
        setPlayerMove(map, &turn, firstP, secondP);
    
        if(checkWinner(map) == 1 || checkWinner(map) == 0){
           
            printMap(map);
            
            if(checkWinner(map) == 0){
                printf("Player %s wins!", firstP.name);
                firstP.points += 1;
            } 

            else if(checkWinner(map) == 1){
                printf("Player %s wins!", secondP.name);
                secondP.points += 1;
            }

            else if (checkWinner(map) == -1 ){
                printf("Draw!");
            }
            
            printf("Play again? \ny/n > ");

            scanf(" %c", &play);

            if(play == 'n' || play == 'N'){

                if(firstP.points > secondP.points){
                    writeTofile(firstP);
                } else if (secondP.points > firstP.points) {
                    writeTofile(secondP);
                }

                running = 0;
            } else if(play ==  'y' || play == 'Y'){
                resetBoard(map);
                running = 1;
            }
        } 
     
    }

}

void showHighscores(){
    
    FILE *fp = fopen("Highscore.txt", "r");
    Player ptable[5] = {NULL};
    Player p;
    int count = 0;

    if(fp != NULL) {

        printf("\nHighscore\n\n");
        printf("%10s %10s\n\n", "Players", "Wins");
        while(fread(&p, sizeof(p), 1, fp) == 1){
            ptable[count] = p;
            count += 1;
        }


     for(int i = 0; i < count; i++){

        for(int j = 0; j < count - i; j++){
            if(ptable[j + 1].points > ptable[j].points){
            Player temp;
            temp = ptable[j + 1];
            ptable[j + 1] = ptable[j];
            ptable[j] = temp;
        }
        }
             
         if (ptable[i].name != NULL) {
                printf("%d. %10s %7d\n", i + 1, ptable[i].name, ptable[i].points);
         }
      
         if(count == 5){
            break;
         }

    } 

    } else {
        printf("\n%10s", "Not able to open the file.\n\n");
    }

    
    fclose(fp);

}




int main(void){

    int menuChoice;

    while(1){

     switch (mainMenu(menuChoice))
        {
        case Play:
                gameLoop(menuChoice);
            break;

        case ShowPlayers:
                showHighscores();
            break;
        
        case About:
                aboutDescription();
            break;

        case Exit:
                printf("\n\nExiting, Goodbye!");
                return 0;
            break;
        
        default:
            break;
        }

    }
    
    return 0;
}

