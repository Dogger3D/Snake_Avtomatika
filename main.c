    #include <stdio.h>
    #include <windows.h>
    #include <conio.h>
    #include <stdlib.h>

//--------Player Variables-------//
    char playerName[50];
    int Score = 0;
    char YN_input = ' ';
    char playerInput;
//-----Game Map coordinates------//
    int Max_Rows = 24;
    int Max_Columns = 24;
    int bodyLength = 5;                                                                                                 //min is 2 (head = 1 first tail = 2)
    int Snake_X[50] = {5};
    int Snake_Y[50] = {5};
    int Food_X;
    int Food_Y;
    int Row = 0;
    int Column = 0;
//--------Game Variables--------//
    int Difficulty = 0;
    char Direction = 'd';
    int New_game = 0;
    int Game = 1;
    int G_Over = 0;
    int i = 0;
    int piecePrinted = 0;

void New_Game_Creation();
void Food_Generation();
void Game_Generation();
void Snake_Movement();
void Collision_detection();
void yes_or_no();
void Game_Over();

int main() {
    SetConsoleOutputCP(CP_UTF8);
        while(Game == 1){
            New_Game_Creation();
            Food_Generation();
                while(New_game == 1) {
                    system("cls");
                    Game_Generation();
                    Snake_Movement();
                    Sleep(300);
                    Collision_detection();
                    }
                    while(G_Over == 1){
                        Game_Over();
                    }
        }
    return 0;
    }

    void New_Game_Creation(){
        printf("Please write your name here : ");
        scanf_s("%s", playerName);
        printf(" %s Welcome to my little Game!!\n", playerName);
        printf("\n            Please choose a Difficulty\n");
        printf("For 'Easy' please write 1  and for 'Hard' please write 2 :\n");
        scanf_s("%d",&Difficulty);
        system("cls");
        Snake_X[0] = 5;                                                                                                         // reset the position of the head cause of problems when you play a new game
        Snake_Y[0] = 5;                                                                                                         // reset the position of the head cause of problems when you play a new game
        for(int l = 1 ; l < bodyLength ;l++){
            Snake_X[l] = 0;
            Snake_Y[l] = 0;
        }
        Direction = 'd';
        Score = 0;
        New_game = 1;
    }


    void Food_Generation(){
        int illegalFood = 1;
        while (illegalFood == 1) {
            Food_X = rand() % (24 - 2) + 1;
            Food_Y = rand() % (24 - 2) + 1;
            illegalFood = 0;

            for (int j = 0; j < bodyLength; j++) {
                if (Snake_X[j] == Food_X && Snake_Y[j] == Food_Y) {
                    illegalFood = 1;
                    break;
                }
            }
        }
    }

    void Game_Generation() {
        for (Row = 0; Row <= Max_Rows; Row++) {
            for (Column = 0; Column <= Max_Columns; Column++) {
                piecePrinted = 0;

                if (Row == 0 && Column == 0) {
                    printf("◢");
                    piecePrinted = 1;
                }
                else if (Row == Max_Rows && Column == 0) {
                    printf("◥");
                    piecePrinted = 1;
                }
                else if (Row == 0 && Column == Max_Columns) {
                    printf("◣");
                    piecePrinted = 1;
                }
                else if (Row == Max_Rows && Column == Max_Columns) {
                    printf("◤");
                    piecePrinted = 1;
                }
                else if (Row == 0 || Row == Max_Rows || Column == 0 || Column == Max_Columns) {
                    printf("◼");
                    piecePrinted = 1;
                }
                else if(Score == 1058){
                    if (Row % 2 == 0 || Column % 2 == 0){
                        printf("o");
                    }
                    else{
                        printf("x");
                    }
                    piecePrinted = 1;
                G_Over = 1;
                }
                else if (Row == Food_Y && Column == Food_X) {
                    printf("¤");
                    piecePrinted = 1;
                }
                else if (Row == Snake_Y[0] && Column == Snake_X[0]) {
                    printf("ӫ");
                    piecePrinted = 1;
                }
                else {                                                                                                  //variable was necessary to force the game gen to continue instead of stop on print or noprint
                    for (i = 1; i < bodyLength; i++) {
                        if (Snake_X[i] == Column && Snake_Y[i] == Row) {
                            printf("o");
                            piecePrinted = 1;
                            break;
                        }
                    }
                }
                if(piecePrinted == 0){
                    printf(" ");
                }
            }
            printf("\n");                                                                                                // End of Line beginning yof new line
        }
    }



    void Snake_Movement() {                                                                                                 // tried using other libs but in the end this one was supported by windows, and it was too much of a hustle to change up
        if (_kbhit()) {
            playerInput = (char) _getch();                                                                                  // get character couldn't be simpler
            while (_kbhit()) _getch();                                                                                      //added because I had issue with keys buffering and essentially blocking the game

            if (playerInput == 'w' && Direction != 's' || playerInput == 's' && Direction != 'w' ||                         // filter going back into snake itself
                playerInput == 'a' && Direction != 'd' || playerInput == 'd' && Direction != 'a') {
                Direction = playerInput;
            }
        }

        for (i = bodyLength - 1 ; i > 0; i--) {                                                                            // tail relocation | -1 because the array start at index 0 ....
            Snake_X[i] = Snake_X[i - 1];
            Snake_Y[i] = Snake_Y[i - 1];
        }

        switch (Direction) {                                                                                            //break resets the switch in a way of stopping other instances
            case 'w' : Snake_Y[0]--; break;
            case 's' : Snake_Y[0]++; break;
            case 'a' : Snake_X[0]--; break;
            case 'd' : Snake_X[0]++; break;
            default:;
        }
    }
    void Collision_detection() {
        if(Snake_X[0] == Food_X && Snake_Y[0] == Food_Y){
            bodyLength++;
            Score = Score + 2;
            Food_Generation();
        }
        for(int k = 1 ; k < bodyLength ; k++){
            if(Snake_X[0] == Snake_X[k] && Snake_Y[0] == Snake_Y[k]){
                New_game = 0;
                G_Over = 1;
            }
        }
        if (Difficulty == 1) {
            if(Snake_X[0] >= Max_Rows){
                Snake_X[0] = 1;
            }
            if( Snake_X[0] <= 0){
                Snake_X[0] = Max_Rows - 1;
            }
            if(Snake_Y[0] >= Max_Columns){
                Snake_Y[0] = 1;
            }
            if(Snake_Y[0] <= 0){
                Snake_Y[0] = Max_Columns - 1;
            }
        }
        else if (Snake_X[0] <= 0 || Snake_X[0] >= Max_Rows || Snake_Y[0] <= 0 || Snake_Y[0] >= Max_Columns) {
            New_game = 0;
            G_Over = 1;
        }
    }

    void yes_or_no(){
        YN_input = (char)_getch();

    }

    void Game_Over(){
        system("cls");
    if(Score == 1058){
        printf("Congratulations %s\n",playerName);
        printf("          You Won!!!\n");
        printf("Would you like to Play Again ?\n");
        printf("         'Y' or 'N'\n");
    }
    else {
        printf("        Game over %s\n", playerName);
        printf("  Your Score was :%d\n", Score);
        printf("Would you like to Try Again ?\n");
        printf("         'Y' or 'N'\n");
    }
        yes_or_no();

        if(YN_input == 'Y' || YN_input == 'y'){
            G_Over = 0;
            system("cls");
        }
        else if (YN_input == 'N' || YN_input == 'n'){
            printf("Good bye , %s" , playerName);
            Sleep(1000);
            Game = 0;
            G_Over = 0;
        }
        else{
            printf("Invalid input please try again.");
            Sleep(200);
        }
    }
