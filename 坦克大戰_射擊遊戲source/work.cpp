#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>
#include<time.h>
#include<vector>

#include"battlefield.cpp"
#include"monster.cpp"
#include"player.cpp"
#include"bullet.cpp"
#include"trap.cpp"
using namespace std;


int main() {
	srand(time(NULL));	
	Battlefield M;
//here:
	M.battlestart();

	gotoxy(width/2 - 10 < 0 ? 0 : width/2 - 10, height/2 +1);
	cout << "Press \"" "\033[1;33m" "Backspace" "\033[m" "\" to quit!" << endl;
	while(getchar() != 0X7F) ;
//	if( M.ask_init() ) goto here:
	clearScreen();
	gotoxy(0, 0);
	showCursor();
	return 0;
}












