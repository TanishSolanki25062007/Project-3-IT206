/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, OCaml, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
#include<fstream>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 50
#define GAP_SIZE 7
#define PIPE_DIF 45
#define MAX_LEADERBOARD 5

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int pipePos[3];
int gapPos[3];
int pipeFlag[3];
int birdPos = 6;
int score = 0, highScore = 0;
int gameSpeed = 100;
int difficulty = 1;
int skinChoice = 0;
bool powerUpActive = false;
int powerUpX = -1, powerUpY = -1;
int level = 1;

char birdSkins[3][2][6] = {
    {
        {'/','-','-','o','\\',' '},
        {'|',' ',' ','_',' ','>'}
    },
    {
        {' ','^','^','O','^','^'},
        {'<','-','-','|','-','-'}

    },
    {
        {'<','o','o','|','o','>'},
        {' ','^','^',' ','^','^'}
    }
};

char currentBird[2][6];

void gotoxy(int x, int y){
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size) {
    if(size == 0) size = 20; 
    CONSOLE_CURSOR_INFO lpCursor; 
    lpCursor.bVisible = visible;
    lpCursor.dwSize = size;
    SetConsoleCursorInfo(console, &lpCursor);
}

void setColor(int color) {
    SetConsoleTextAttribute(console, color);
}

void drawBorder(){ 
    for(int i=0; i<WIN_WIDTH; i++){
        gotoxy(i,0); cout<<"=";
        gotoxy(i,SCREEN_HEIGHT); cout<<"=";
    }
    for(int i=0; i<SCREEN_HEIGHT; i++){
        gotoxy(0,i); cout<<"|";
        gotoxy(SCREEN_WIDTH,i); cout<<"|";
        gotoxy(WIN_WIDTH,i); cout<<"|";
    }
    gotoxy(0,0); cout<<"+";
    gotoxy(SCREEN_WIDTH,0); cout<<"+";
    gotoxy(0,SCREEN_HEIGHT); cout<<"+";
    gotoxy(SCREEN_WIDTH,SCREEN_HEIGHT); cout<<"+";
    gotoxy(WIN_WIDTH,0); cout<<"+";
    gotoxy(WIN_WIDTH,SCREEN_HEIGHT); cout<<"+";

    setColor(11);
    for(int i = 1; i < SCREEN_HEIGHT; i++){
        gotoxy(WIN_WIDTH + 8, i); cout << "|                         |";
    }
    gotoxy(WIN_WIDTH + 8, 0); cout << "+-------------------------+";
    gotoxy(WIN_WIDTH + 8, SCREEN_HEIGHT); cout << "+-------------------------+";
    setColor(15);
}

void genPipe(int ind){
    gapPos[ind] = 3 + rand()%14; 
}

void drawPipe(int ind){
    if(pipeFlag[ind]){
        for(int i=0; i<gapPos[ind]; i++){ 
            gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"*"; 
        }
        for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
            gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"*"; 
        }
    } 
}

void erasePipe(int ind){
    if(pipeFlag[ind]){
        for(int i=0; i<gapPos[ind]; i++){ 
            gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
        }
        for(int i=gapPos[ind]+GAP_SIZE; i<SCREEN_HEIGHT-1; i++){ 
            gotoxy(WIN_WIDTH-pipePos[ind],i+1); cout<<"   "; 
        }
    }
}

void drawBird(){
    setColor(8);
    gotoxy(2, birdPos + 1); cout << "▒";
    setColor(14);
    for(int i=0; i<2; i++){
        for(int j=0; j<6; j++){
            gotoxy(j+2,i+birdPos); cout<<currentBird[i][j];
        }
    }
    setColor(15);
}

void eraseBird(){
    for(int i=0; i<2; i++){
        for(int j=0; j<6; j++){
            gotoxy(j+2,i+birdPos); cout<<" ";
        }
    }
}

int collision(){
    if(pipePos[0] >= 61 && pipePos[0] <= 68){
        if(birdPos < gapPos[0] || birdPos + 1 > gapPos[0] + GAP_SIZE){
            return 1;
        }
    }
    return 0;
}

void gameover(){
    system("cls");
    setColor(12);
    cout<<"\n\t\t--------------------------\n";
    cout<<"\t\t-------- Game Over -------\n";
    cout<<"\t\t--------------------------\n\n";
    cout<<"\t\tYour Score: " << score << endl;
    if(score > highScore){
        highScore = score;
        ofstream out("highscore.txt");
        if(out.is_open()) out << highScore;
        out.close();
        cout<<"\t\tNew High Score!"<<endl;
    }
    cout<<"\n\t\tPress any key to go back to menu.";
    getch();
    setColor(15);
}

void updateScore(){
    gotoxy(WIN_WIDTH + 10, 5);cout<<"Score: "<<score<<"  ";
    gotoxy(WIN_WIDTH + 10, 6);cout<<"Level: "<<level<<"  ";
    if(powerUpActive) {
        setColor(10); gotoxy(WIN_WIDTH + 10, 8); cout << "Power-Up: ACTIVE ";
    } else {
        setColor(12); gotoxy(WIN_WIDTH + 10, 8); cout << "Power-Up: OFF    ";
    }
    setColor(15);
}

void selectSkin() {
    system("cls");
    cout<<"\n\n\t\tSelect Your Bird Skin";
    cout<<"\n\t\t1. Classic Bird";
    cout<<"\n\t\t2. Rocket";
    cout<<"\n\t\t3. UFO";
    cout<<"\n\t\tEnter choice (1-3): ";
    char choice = getche();
    if(choice >= '1' && choice <= '3') {
        skinChoice = (choice - '1');
    } else {
        cout << "\n\t\tInvalid choice! Using default skin.";
        skinChoice = 0;
    }
    memcpy(currentBird, birdSkins[skinChoice], sizeof(currentBird));
    cout << "\n\t\tYou selected: ";
    for(int i=0; i<2; i++) {
        cout << "\n\t\t";
        for(int j=0; j<6; j++) cout << currentBird[i][j];
    }
    getch();
}

void loadHighScore(){
    ifstream in("highscore.txt");
    if(!in.is_open()) {
        highScore = 0;
        return;
    }
    in >> highScore;
    in.close();
}

void instructions(){
    system("cls");
    cout<<"\n\n\t\t=== HOW TO PLAY FLAPPY BIRD ===";
    cout<<"\n\t\t----------------------------";
    cout<<"\n\t\t Game Controls:";
    cout<<"\n\t\t > Press SPACEBAR to make bird fly up";
    cout<<"\n\t\t > Press ESC to exit current game";
    cout<<"\n\t\t > Press P to pause/resume";
    cout<<"\n\n\t\t Game Rules:";
    cout<<"\n\t\t > Bird must pass through the gaps in pipes";
    cout<<"\n\t\t > Each successful pass = 1 point";
    cout<<"\n\t\t > Hitting pipes or ground = Game Over";
    cout<<"\n\n\t\tPress any key to return to menu...";
    getch();
}

void selectDifficulty() {
    system("cls");
    cout<<"\n\n\t\tSelect Difficulty Level";
    cout<<"\n\t\t1. Easy";
    cout<<"\n\t\t2. Medium";
    cout<<"\n\t\t3. Hard";
    cout<<"\n\t\tEnter (1-3): ";
    char diff = getche();
    if(diff == '1') { gameSpeed = 100; difficulty = 1; }
    else if(diff == '2') { gameSpeed = 75; difficulty = 2; }
    else if(diff == '3') { gameSpeed = 50; difficulty = 3; }
}

void animatedTitle() {
    for(int i=0; i<3; i++) {
        system("cls");
        setColor(14);
        gotoxy(25, 10); cout<<"** FLAPPY BIRD DELUXE **";
        setColor(15);
        Sleep(300);
        system("cls");
        Sleep(200);
    }
}

void play(){
    birdPos = 6; score = 0; level = 1;
    pipeFlag[0] = 1; pipeFlag[1] = 0;
    pipePos[0] = pipePos[1] = 4;
    system("cls");
    drawBorder();
    genPipe(0);
    updateScore();
    gotoxy(WIN_WIDTH + 10, 2); cout << "FLAPPY BIRD DELUXE";
    gotoxy(WIN_WIDTH + 10, 14); cout << "Spacebar = Jump";
    gotoxy(WIN_WIDTH + 10, 15); cout << "ESC = Exit, P = Pause";
    gotoxy(10, 5); cout << "Press any key to start"; getch();
    gotoxy(10, 5); cout << "                      ";

    while(1){
        if(kbhit()){
            char ch = getch();
            if(ch == 32){
                if(birdPos > 3) birdPos -= 3;
            }
            if(ch == 27) break;
            if(ch == 'p' || ch == 'P'){
                gotoxy(10, 10); cout << "Game Paused. Press 'r' to resume.";
                while(getch() != 'r');
                gotoxy(10, 10); cout << "                                ";
            }
        }
        drawBird(); drawPipe(0); drawPipe(1);
        if(collision()) { gameover(); return; }
        Sleep(gameSpeed);
        eraseBird(); erasePipe(0); erasePipe(1);
        birdPos += 1;
        if(birdPos > SCREEN_HEIGHT - 2) { gameover(); return; }
        if(pipeFlag[0]) pipePos[0] += 2;
        if(pipeFlag[1]) pipePos[1] += 2;
        if(pipePos[0] >= 40 && pipePos[0] < 42){ pipeFlag[1] = 1; pipePos[1] = 4; genPipe(1); }
        if(pipePos[0] > 68){
            score++;
            if(score % 5 == 0){  
                if(gameSpeed > 30) {
                    gameSpeed -= 5;
                }
                level++; 
            }
            updateScore();
            pipeFlag[1] = 0;
            pipePos[0] = pipePos[1];
            gapPos[0] = gapPos[1];
        }
    }
}

int main() {
    animatedTitle();
    loadHighScore();
    selectSkin();
    while(1) {
        system("cls");
        setColor(14);
        gotoxy(35, 10); cout << "FLAPPY BIRD DELUXE";
        setColor(15);
        gotoxy(35, 12); cout << "1. Start Game";
        gotoxy(35, 13); cout << "2. Difficulty Level";
        gotoxy(35, 14); cout << "3. Instructions";
        gotoxy(35, 15); cout << "4. High Score";
        gotoxy(35, 16); cout << "5. Exit";
        char choice = getche();
        if(choice == '1') play();
        else if(choice == '2') selectDifficulty();
        else if(choice == '3') instructions();
        else if(choice == '4') {
            system("cls");
            cout << "High Score: " << highScore << endl;
            cout << "Press any key to return.";
            getch();
        }
        else if(choice == '5') break;
    }
    return 0;
}
    
 

