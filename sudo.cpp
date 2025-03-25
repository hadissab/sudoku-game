#include <iostream>
#include <ctime>
#include "clui.h"
#include <string.h>
#include <conio.h> //gech
#include <iomanip> //setw
using namespace std;
int currentrow=0, currentcolm=0;
char savecopy[500][30];
struct savings{
    int s[9][9];
    int plus;
    int minus;
    char* gamename;
    int time;
    int mis;
    int degree;
} save[10];
struct games{
    char* uname;
    int minos;
    int plus;
    int lost;
    int win;
    int score;
    int time;
} fgame[10];
void bubble_sort(games fgame[], int size) {
    games temp;
    for (int i = 0; i < size-1; i++){
        for (int j = 0; j < size-1-i; j++){
            if (fgame[j + 1].score > fgame[j].score){
                temp = fgame[j];
                fgame[j+1] = temp;
                fgame[j]=fgame[j+1];
            }
            else if(fgame[j+1].score== fgame[j].score){
                if (fgame[j + 1].time < fgame[j].time){
                    temp = fgame[j];
                    fgame[j+1] = temp;
                    fgame[j]=fgame[j+1];
                }
            }
                
        }         
    }    
}
int mainmenu(){
    int num;
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 - 2, get_window_cols() /3);
    cout << "MAIN MENU:" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2 - 1 , get_window_cols() /3);
    cout << "1. ";
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 - 1 , get_window_cols() /3 + 3);
    cout << "Start the game" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2 , get_window_cols() /3);
    cout << "2. ";
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 , get_window_cols() /3 + 3);
    cout << "Play a saved game" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2 + 1, get_window_cols() /3);
    cout << "3. ";
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 + 1, get_window_cols() /3 + 3);
    cout << "LeaderBourd" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2 + 2, get_window_cols() /3);
    cout << "4. ";
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 + 2, get_window_cols() /3 + 3);
    cout << "Exit the game" << endl;
    cursor_to_pos(get_window_rows() /2 + 3, get_window_cols() /3);
    cout << "Please enter a number ";
    reset_color();
    cursor_to_pos(get_window_rows() /2 + 3, get_window_cols() /3 + 22);
    cin >> num;
    return num;
}

bool repeted(char username[][30],long long int i){
    bool found=false;
    for(int j=0 ; j < i; j++){
        if(strcmp(username[i], username[j]) == 0){
            clear_screen();
            change_color_rgb(247, 23, 7);
            cursor_to_pos(get_window_rows() /2 , get_window_cols() /3);
            cout << "The username is repeated" << endl;
            cursor_to_pos(get_window_rows() /2 + 1, get_window_cols() /3);
            cout << "please choose another one" << endl;
            reset_color();
            delay(3000);
            clear_screen();
            found=true;
            return found;
        }
    }
    return found;
}

void printsudo(int sudo1[9][9]){
    int row = get_window_rows();
    int col = get_window_cols(); 
    int startRow = row / 2 - 5;  
    int startCol = col / 3;
    int i =0, j=0;
    for (int i = 0; i < 9; i++) {
        cursor_to_pos(startRow + i * 2, startCol);
        if(i != 0 && i % 3 == 0){ 
            change_color_rgb(247, 23, 7);
            cout << " ------------------------------------- " << endl;
            reset_color();
        }
        else {
            cursor_to_pos(startRow + i * 2, startCol);
            cout << " ------------------------------------- " << endl;
        }

        cursor_to_pos(startRow + i * 2 + 1, startCol);
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                change_color_rgb(247, 23, 7); 
                cout << " | ";
                reset_color();
            } else {
                cout << " | ";
            }
            if (currentcolm == j && currentrow == i){
                change_background_color(3);
            }
            if (sudo1[i][j] != 0) {
                change_color_rgb(212, 206, 55); 
                cout << sudo1[i][j];
                reset_color();
            } else {
                cout << sudo1[i][j];
            }
            if(currentcolm == j && currentrow == i){
                reset_color();
            }
        }
        cout << " |" << endl;
    }
    cursor_to_pos(startRow + 18, startCol);
    cout << " ------------------------------------- " << endl;
    return;
}
void pausegame(time_t &start_time, int &elapsedpausedtime){
    clear_screen();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() / 2, get_window_cols() / 3);
    cout << "Your game is paused. press Esc key to continue" ;
    time_t pause_start = time(nullptr);
    while(true){
        char key = getch();
        if (key == 27){
            time_t pause_end = time(nullptr);
            elapsedpausedtime += pause_end - pause_start;
            clear_screen();
            break;
        }
    }
}

void the_sudoku(int sudo1[9][9],long long int &z,long long int &saveindex,int g){
    int esc=0,mistake=0,scorep=0,scorem=0,t;
    bool repeat = true;
    time_t start_time = time(nullptr);
    int elapsedpausedtime = 0;
    unsigned char ch;
    int sudo[9][9]={{1,2,3,4,5,6,7,8,9},{4,5,6,7,8,9,1,2,3},{7,8,9,1,2,3,4,5,6},
                    {3,1,2,6,4,5,9,7,8},{6,4,5,9,7,8,3,1,2},{9,7,8,3,1,2,6,4,5},
                    {2,3,1,5,6,4,8,9,7},{5,6,4,8,9,7,2,3,1},{8,9,7,2,3,1,5,6,4}};
    clear_screen();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 - 2, get_window_cols() /3);
    cout << "choose the level of dificulty" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2 - 1 , get_window_cols() /3);
    cout << "1. " ;
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 - 1, get_window_cols() /3 + 3);
    cout << "easy" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2  , get_window_cols() /3);
    cout << "2. " ;
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 , get_window_cols() /3 + 3);
    cout << "medium" << endl;
    reset_color();
    change_color_rgb(247, 23, 7);
    cursor_to_pos(get_window_rows() /2 + 1 , get_window_cols() /3);
    cout << "3. " ;
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 + 1, get_window_cols() /3 + 3);
    cout << "hard" << endl;
    reset_color();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(get_window_rows() /2 + 2, get_window_cols() /3 );
    cout << "Please inter a number " ;
    reset_color();
    cursor_to_pos(get_window_rows() /2 + 2, get_window_cols() /3 + 22);
    cin >> t;
    clear_screen();
    if(t==1){t= 300;}
    else if(t==2){t=180;}
    else if(t==3){t=120;}
    printsudo(sudo1);
    int cols=0 , rows =0;
    while(true){
        int elapsedtime = time(nullptr) - start_time - elapsedpausedtime;
        clear_screen();
        cursor_to_pos(0, 10);
        change_color_rgb(255, 255, 0); 
        cout << "Time Elapsed: " << elapsedtime << " sec ";
        reset_color();
        printsudo(sudo1);
        ch = getch();
        if( ch == 0){
            ch = getch();
            if(ch == 72 && currentrow>0){
                //up
                currentrow--;
            }    
            if(ch == 80 && currentrow<8){
                //down
                currentrow++;
            }
            if(ch == 75 && currentcolm>0){
                //left
                currentcolm--;
            }
            if(ch == 77 && currentcolm<8){
                //right
                currentcolm++;
            }    
        }
        else if('1' <= ch && ch <= '9'){
            int number = ch - 48;
            int i=currentrow, j=currentcolm; 
            if(sudo1[i][j]== 0){
                if((i >= 0 && j >= 0)){
                    sudo1[i][j] = number;
                    clear_screen();
                    printsudo(sudo1);
                    if(sudo1[i][j] != sudo[i][j]){
                        change_color_rgb(247, 23, 7);
                        cursor_to_pos(get_window_rows() + 19,get_window_cols() /3-2);
                        cout << "Oops!That number doesn't fit there.Try again" << endl;
                        sudo1[i][j]=0;
                        mistake++;
                        scorem++;
                        delay(3000);
                        clear_screen();
                        printsudo(sudo1);
                    }
                    else {
                        scorep++;
                        clear_screen();
                        printsudo(sudo1);
                    }
                    
                }
           }
        
            else {
                change_color_rgb(247, 23, 7);
                    cursor_to_pos(get_window_rows() + 19 ,get_window_cols() /3 -2);
                    cout << "Please do not try to change a constant block" << endl;
                    cursor_to_pos(get_window_rows() + 20 ,get_window_cols() /3 -2);
                    cout << "Move to another block PLease" << endl;
                    reset_color();
                    delay(3000);
                    clear_screen();
                    printsudo(sudo1);
                }
        }
        if(mistake == 3){
            clear_screen();
            change_color_rgb(135, 15, 209);
            cursor_to_pos(get_window_rows() / 2 , get_window_cols() / 3 + 18);
            cout << "YOU LOST" << endl;
            cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 3);
            cout << "You made too many mistakes.Sorry better luck next time";
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 10);
            change_background_color(1);
            cout << "Your score: "<< setw(3) <<scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 10);
            cout << "Correct answers: " << setw(3) <<scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 10);
            cout << "Incorrect answers: " << setw(3) <<scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 10);
            cout << "time: " << setw(3) << elapsedtime << "             " << endl;
            reset_color();
            cin.get();
            delay(6000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedtime;
            fgame[g].score += scorep - scorem;
            fgame[g].lost++;
            break;
        }
        else if(ch == 27){
            pausegame(start_time,elapsedpausedtime);
            continue;
        
        }
        
        else if(ch =='s'){
            clear_screen();
            int row=get_window_rows();
            int col= get_window_cols();
            do {
            change_color_rgb(10, 135, 207);
            cursor_to_pos(row /2 ,col /3 - 3);
            cout << "Please inter a name for your game" << endl;
            cursor_to_pos(row /2 + 1, col /3);
            cout << "---------------------------" << endl;
            cursor_to_pos(row /2 + 2, col /3);
            cout << '|' << endl;
            cursor_to_pos(row /2 + 2, col / 3 + 26);
            cout << '|' << endl;
            cursor_to_pos(row /2 + 3 , col /3);
            cout << "---------------------------" << endl;
            cursor_to_pos(row /2 + 2, col /3 + 1);
            reset_color();
            cin >> savecopy[saveindex];
            repeat = repeted(savecopy,saveindex);
            reset_color();
            clear_screen();
            saveindex++;
            }while(repeat);
            save[z].gamename = savecopy[saveindex-1];
            save[z].degree = t;
            save[z].time = elapsedtime;
            save[z].minus = scorem;
            save[z].plus = scorep;
            save[z].mis = mistake;
            for(int i=0; i < 9;i++){
                for(int j=0; j < 9;j++){
                    save[z].s[i][j]=sudo1[i][j];
                }
            }
            z++;
            break;}
        else if(ch=='q'){
            clear_screen();
            change_color_rgb(135, 15, 209);
            cursor_to_pos(get_window_rows() / 2 , get_window_cols() / 3 + 8);
            cout << "You have exit the game" << endl;
            cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 3 + 7);
            cout << "We wish to see you again";
            change_background_color(1);
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 8);
            cout << "Your score: "<< setw(3) <<scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 8);
            cout << "Correct answers: " << setw(3) <<scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 8);
            cout << "Incorrect answers: " << setw(3) << scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 8);
            cout << "time: " << setw(3) << elapsedtime << "             " << endl;
            reset_color();
            cin.get();
            delay(5000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedtime;
            fgame[g].score += scorep - scorem;
            fgame[g].lost++;
            break;}
        if(scorep == 54){
            int row=get_window_rows();
            int col= get_window_cols();
            clear_screen();
            change_color_rgb(52, 224, 13);
            cursor_to_pos(row / 2 -1, col / 3);
            cout << "WINNER WINNER! CHICKEN DINEER!" << endl;
            cursor_to_pos(row / 2 , col / 3 - 1);
            cout << "Congratulations for your victory." << endl;
            cursor_to_pos(row / 2 + 1, col / 3);
            cout << "Only a few can reach this piont." << endl;
            change_background_color(1);
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 5);
            cout << "Your score: "<< setw(2) << scorep - scorem << "        " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 5);
            cout << "Correct answers: " << setw(2) << scorep << "   " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 5);
            cout << "Incorrect answers: " << setw(2) << scorem << " " << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 5);
            cout << "time: " << setw(3) <<elapsedtime << "             " << endl;
            reset_color();
            cin.get();
            delay(5000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedtime;
            fgame[g].score += scorep - scorem;
            fgame[g].win++;
            return;
        }
        if(elapsedtime >= t){
            int row=get_window_rows();
            int col= get_window_cols();
            clear_screen();
            change_color_rgb(52, 224, 13);
            cursor_to_pos(row / 2 -1, col / 3 + 10);
            cout << "YOU LOST" << endl;
            cursor_to_pos(row / 2 , col / 3 + 6);
            cout << "Sorry time's out!" << endl;
            cursor_to_pos(row / 2 + 1, col / 3 -3);
            cout << "Next time be more carefull about the time" << endl;
            change_background_color(1);
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 5);
            cout << "Your score: "<< setw(3) << scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 5);
            cout << "Correct answers: " << setw(3) << scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 5);
            cout << "Incorrect answers: " << setw(3) <<scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 5);
            cout << "time: " << setw(3) <<elapsedtime << "             " << endl;
            reset_color();
            cin.get();
            delay(5000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedtime;
            fgame[g].score += scorep - scorem;
            fgame[g].lost++;
            return;
        } 
    }   
    return;
}
void the_sudokusave(int sudo1[9][9],int t,int times,long long int &z,long long int &saveindex, int g,int saver){ 
    int right=0,left=0,up=0,down=0,esc=0,mistake=0,scorep=0,scorem=0;
    bool repeat = true;
    time_t start_time = time(nullptr);
    int elapsedpausedtime = 0;
    int eletime = times;
    unsigned char ch;
    int sudo[9][9]={{1,2,3,4,5,6,7,8,9},{4,5,6,7,8,9,1,2,3},{7,8,9,1,2,3,4,5,6},
                    {3,1,2,6,4,5,9,7,8},{6,4,5,9,7,8,3,1,2},{9,7,8,3,1,2,6,4,5},
                    {2,3,1,5,6,4,8,9,7},{5,6,4,8,9,7,2,3,1},{8,9,7,2,3,1,5,6,4}};
    clear_screen();
    printsudo(sudo1);
    int cols=0 , rows =0;
    while(true){
        int elapsedTime =time(0) - start_time + eletime - elapsedpausedtime;
        clear_screen();
        cursor_to_pos(0, 10);
        change_color_rgb(255, 255, 0); 
        cout << "Time Elapsed: " << elapsedTime  << " sec ";
        reset_color();
        printsudo(sudo1);
        ch = getch();
        if( ch == 0){
            ch = getch();
            if(ch == 72 && currentrow>0){
                currentrow--;
            }    
            if(ch == 80 && currentrow<8){
                currentrow++;
            }
            if(ch == 75 && currentcolm>0){
                currentcolm--;
            }
            if(ch == 77 && currentcolm<8){
                currentcolm++;
            }    
        }
        else if('1' <= ch && ch <= '9'){
            int number = ch - 48;
            int i= currentrow, j=currentcolm; 
            if(sudo1[i][j]== 0){
                if((i >= 0 && j >= 0)){
                    sudo1[i][j] = number;
                    clear_screen();
                    printsudo(sudo1);
                    if(sudo1[i][j] != sudo[i][j]){
                        change_color_rgb(247, 23, 7);
                        cursor_to_pos(get_window_rows() + 19,get_window_cols() /3);
                        cout << "Oops!That number doesn't fit there.Try again" << endl;
                        sudo1[i][j]=0;
                        mistake++;
                        scorem++;
                        delay(3000);
                        clear_screen();
                        printsudo(sudo1);
                    }
                    else {
                        scorep++;
                        clear_screen();
                        printsudo(sudo1);
                    }
                    
                }
           }
        
            else {
                change_color_rgb(247, 23, 7);
                    cursor_to_pos(get_window_rows() + 19 ,get_window_cols() /3);
                    cout << "Please do not try to change a constant block" << endl;
                    cursor_to_pos(get_window_rows() + 20 ,get_window_cols() /3);
                    cout << "Move to another block PLease" << endl;
                    reset_color();
                    delay(3000);
                    clear_screen();
                    printsudo(sudo1);
                }
        }
        if(mistake == 3){
            clear_screen();
            change_color_rgb(135, 15, 209);
            cursor_to_pos(get_window_rows() / 2 , get_window_cols() / 3 + 18);
            cout << "YOU LOST" << endl;
            cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 3);
            cout << "You made too many mistakes.Sorry better luck next time";
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 10);
            change_background_color(1);
            cout << "Your score: "<< setw(3) <<scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 10);
            cout << "Correct answers: " << setw(3) <<scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 10);
            cout << "Incorrect answers: " << setw(3) <<scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 10);
            cout << "time: " << setw(3) << elapsedTime << "             " << endl;
            reset_color();
            cin.get();
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedTime;
            fgame[g].score += scorep - scorem;
            fgame[g].lost++;
            break;
        }
        else if(ch == 27){
            pausegame(start_time,elapsedpausedtime); 
            continue;
        }
        else if(ch =='s'){
            clear_screen();
            int row=get_window_rows();
            int col= get_window_cols();
            do {
                change_color_rgb(10, 135, 207);
                cursor_to_pos(row /2 ,col /3 - 3);
                cout << "Please inter a name for your game" << endl;
                cursor_to_pos(row /2 + 1, col /3);
                cout << "---------------------------" << endl;
                cursor_to_pos(row /2 + 2, col /3);
                cout << '|' << endl;
                cursor_to_pos(row /2 + 2, col / 3 + 26);
                cout << '|' << endl;
                cursor_to_pos(row /2 + 3 , col /3);
                cout << "---------------------------" << endl;
                cursor_to_pos(row /2 + 2, col /3 + 1);
                reset_color();
                cin >> savecopy[saveindex];
                repeat = repeted(savecopy,saveindex);
                reset_color();
                clear_screen();
                saveindex++;
            }while(repeat);
            save[z].gamename = savecopy[saveindex-1];
            save[z].degree = t;
            save[z].time = elapsedTime;
            save[z].minus = scorem;
            save[z].plus = scorep;
            save[z].mis = mistake;
            for(int i=0; i < 9;i++){
                for(int j=0; j < 9;j++){
                    save[z].s[i][j]=sudo1[i][j];
                }
            }
            z++;
            break;}
        else if(ch=='q'){
            clear_screen();
            change_color_rgb(135, 15, 209);
            cursor_to_pos(get_window_rows() / 2 , get_window_cols() / 3 + 9);
            cout << "You have exit the game" << endl;
            cursor_to_pos(get_window_rows() / 2 + 1, get_window_cols() / 3 + 8);
            cout << "We wish to see you again";
            change_background_color(1);
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 10);
            cout << "Your score: "<< setw(3) <<scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 10);
            cout << "Correct answers: " << setw(3) <<scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 10);
            cout << "Incorrect answers: " << setw(3) << scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 10);
            cout << "time: " << setw(3) << elapsedTime << "             " << endl;
            reset_color();
            cin.get();
            delay(5000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedTime;
            fgame[g].score += scorep - scorem;
            fgame[g].lost++;
            break;}
        if(scorep == 54){
            int row=get_window_rows();
            int col= get_window_cols();
            clear_screen();
            change_color_rgb(52, 224, 13);
            cursor_to_pos(row / 2 -1, col / 3);
            cout << "WINNER WINNER! CHICKEN DINEER!" << endl;
            cursor_to_pos(row / 2 , col / 3 - 1);
            cout << "Congratulations for your victory." << endl;
            cursor_to_pos(row / 2 + 1, col / 3);
            cout << "Only a few can reach this piont." << endl;
            change_background_color(1);
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 5);
            cout << "Your score: "<< setw(2) << scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 5);
            cout << "Correct answers: " << setw(2) << scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 5);
            cout << "Incorrect answers: " << setw(2) <<scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 5);
            cout << "time: " << setw(3) <<elapsedTime << "             " << endl;
            reset_color();
            cin.get();
            delay(5000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedTime;
            fgame[g].score += scorep - scorem;
            fgame[g].win++;
            return;
        }
        if(elapsedTime == t){
            int row=get_window_rows();
            int col= get_window_cols();
            clear_screen();
            change_color_rgb(52, 224, 13);
            cursor_to_pos(row / 2 -1, col / 3 + 10);
            cout << "YOU LOST" << endl;
            cursor_to_pos(row / 2 , col / 3 + 6);
            cout << "Sorry times out!" << endl;
            cursor_to_pos(row / 2 + 1, col / 3 -3);
            cout << "Next time be more carefull about the time" << endl;
            change_background_color(1);
            cursor_to_pos(get_window_rows() / 2 + 2, get_window_cols() / 3 + 5);
            cout << "Your score: "<< setw(3) << scorep - scorem << "       " << endl;
            cursor_to_pos(get_window_rows() / 2 + 3, get_window_cols() / 3 + 5);
            cout << "Correct answers: " << setw(3) << scorep << "  " << endl;
            cursor_to_pos(get_window_rows() / 2 + 4, get_window_cols() / 3 + 5);
            cout << "Incorrect answers: " << setw(3) <<scorem << endl;
            cursor_to_pos(get_window_rows() / 2 + 5, get_window_cols() / 3 + 5);
            cout << "time: " << setw(3) <<elapsedTime << "             " << endl;
            reset_color();
            cin.get();
            delay(5000);
            clear_screen();
            fgame[g].minos += scorem;
            fgame[g].plus += scorep;
            fgame[g].time += elapsedTime;
            fgame[g].score += scorep - scorem;
            fgame[g].lost++;
            return;
        } 
    }   
    return;
}

int main(){

    
    long long int max = 500, i=0,z=0, g=0,saveindex=0,saver=0;
    bool mput = false;
    char username[max][30], num;
    long int row = get_window_rows();
    long int col = get_window_cols();
    unsigned char ch;
    clear_screen();
    change_color_rgb(212, 206, 55);
    cursor_to_pos(row / 2 , col / 3);
    cout << "Hello and Wellcome to this game" << endl;
    cursor_to_pos(row / 2 + 1 , col / 3 + 7);
    cout << "Let's play Sudoku!" << endl;
    cursor_to_pos(row / 2 + 2, col / 3 - 4);
    cout << "This game is for the bold and brilliant" << endl;
    cursor_to_pos(row / 2 + 3, col / 3 + 7);
    cout << "Ready to play? ;)" << endl;
    cin.get();
    clear_screen();
    reset_color();
    change_color_rgb(10, 135, 207);
    cursor_to_pos(row /2 , col /3);
    cout << "Please inter your user name" << endl;
    cursor_to_pos(row /2 + 1, col /3);
    cout << "---------------------------" << endl;
    cursor_to_pos(row /2 + 2, col /3);
    cout << '|' << endl;
    cursor_to_pos(row /2 + 2, col / 3 + 26);
    cout << '|' << endl;
    cursor_to_pos(row /2 + 3 , col /3);
    cout << "---------------------------" << endl;
    cursor_to_pos(row /2 + 2, col /3 + 1);
    reset_color();
    cin.ignore();
    cin.getline(username[i], 30);
    i++;
    bool repeat= true;
    clear_screen();

    int sudo1[9][9]={{0,2,0,0,5,0,7,8,0},{4,0,0,7,0,9,0,0,3},{0,8,9,1,0,0,4,0,0},
                           {3,0,0,6,0,0,0,7,8},{0,4,0,0,7,8,0,1,2},{9,7,0,0,0,2,0,0,5},
                           {0,0,1,0,0,4,8,0,7},{0,0,4,8,9,0,2,0,0},{8,0,7,0,3,0,0,6,0}};
    int sudocopy[9][9]={{0,2,0,0,5,0,7,8,0},{4,0,0,7,0,9,0,0,3},{0,8,9,1,0,0,4,0,0},
                           {3,0,0,6,0,0,0,7,8},{0,4,0,0,7,8,0,1,2},{9,7,0,0,0,2,0,0,5},
                           {0,0,1,0,0,4,8,0,7},{0,0,4,8,9,0,2,0,0},{8,0,7,0,3,0,0,6,0}};
    fgame[0].uname = username[0];
    while(true){
        int number = mainmenu();
        cin.get();
        clear_screen();
        if(number == 4){
            do {
            z = 0;
            change_color_rgb(10, 135, 207);
            cursor_to_pos(row /2 , col /3);
            cout << "Please inter your user name" << endl;
            cursor_to_pos(row /2 + 1, col /3);
            cout << "---------------------------" << endl;
            cursor_to_pos(row /2 + 2, col /3);
            cout << '|' << endl;
            cursor_to_pos(row /2 + 2, col / 3 + 26);
            cout << '|' << endl;
            cursor_to_pos(row /2 + 3 , col /3);
            cout << "---------------------------" << endl;
            reset_color();
            cursor_to_pos(row /2 + 2, col /3 + 1);
            cin.ignore();
            cin.getline(username[i], 30);
            clear_screen();
            repeat = repeted(username, i);
            i++;
            } while (repeat);
            if(!repeat){
                g++;
                fgame[g].uname = username[i];
                continue;
            }
        }

        if(number == 1){
            for(int k=0; k < 9; k++){
                for(int l=0; l < 9; l++)
                    sudo1[k][l]=sudocopy[k][l];
            }
            the_sudoku(sudo1,z,saveindex,g);
        } 
        if(number == 2){
            mput=false;
            clear_screen();
            if(z==0){
                clear_screen();
                cursor_to_pos(get_window_rows() / 2 , get_window_cols() /3);
                cout << "there is no game saved";
                delay(4000);
                clear_screen();
                continue;
            }
            else {
                for(int j=0; j < z;j++){
                    change_color_rgb(247, 23, 7);
                    cursor_to_pos(get_window_rows() / 2 - 1 + j, get_window_cols() /3);
                    cout << j+1 << ". " ;
                    change_color_rgb(212, 206, 55);
                    cursor_to_pos(get_window_rows() /2 - 1 + j, get_window_cols() /3 + 3);
                    cout << save[j].gamename << endl;
                }
                cursor_to_pos(get_window_rows()/ 2 + z-1, get_window_cols() / 3);
                cout << "Please inter a number";
                cursor_to_pos(get_window_rows()/ 2 + z-1, get_window_cols() / 3 + 24);
                char saver2;
                
                cin >> saver2;
                saver = saver2 - '0';
                if(saver2 == 'm'){
                    mput=true;
                    clear_screen();
                }
                else 
                    the_sudokusave(save[saver-1].s,save[saver-1].degree,save[saver-1].time,z,saveindex,g,saver);
            }
            if(mput){
                continue;
            }

        }
        if(number == 3){
            bubble_sort(fgame,g);
            clear_screen();
            for(int j=0; j <= g;j++){
                change_color_rgb(247, 23, 7);
                cursor_to_pos(get_window_rows() / 2 - 1 + j,1);
                cout << j + 1 << ". " ;
                change_color_rgb(212, 206, 55);
                cursor_to_pos(get_window_rows() /2 - 1 + j,4);
                cout << "Name:" << fgame[j].uname;
                cursor_to_pos(get_window_rows() /2 - 1 + j, 10);
                cout << "- positive score:" << fgame[j].plus;
                cursor_to_pos(get_window_rows() /2 - 1 + j,30);
                cout << "- negative score:" << fgame[j].minos;
                cursor_to_pos(get_window_rows() /2 - 1 + j,50);
                cout << "- won games:" << fgame[j].win;
                cursor_to_pos(get_window_rows() /2 - 1 + j,70);
                cout << "- lost games:" << fgame[j].lost;
                cursor_to_pos(get_window_rows() /2 - 1 + j,90);
                cout << "- total score: " << fgame[j].score << endl;
            }
            ch = getch();
            if(ch == 'm'){
                clear_screen();
            }
        }
    }
    return 0;
}