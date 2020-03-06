#ifndef STRUCTURE
#define STRUCTURE

#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/select.h>
#include<termios.h>
#include<time.h>
#include<cstdio>
using namespace std;

#define height  20
#define width   40
#define minh     3
#define minw     3
static struct termios orig_termios;

 enum edir{Stop,Up,Left,Right,Down,Attack};


void gotoxy(int x, int y)
{
	printf("%c[%d;%df", 0X1B, y, x);
	fflush(stdout);
}

void determine(int &horizon, int &verticle)
{
//cout << "verticle = " << verticle << " horizon = " << horizon << endl;	
		if (horizon < 3)					horizon  =  width;
		else if (horizon > width)			horizon -=  width-2;
		else if (verticle < 3)				verticle  =  height;
		else if (verticle > height)	    verticle -=  height-2 ;
}



int kbhit()
{
	struct timeval tv = { 0L, 0L };
	fd_set fds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	return select(1, &fds, NULL, NULL, &tv);
}

int getch()
{
	int r;
	unsigned char c;
	if( r  = read(0, &c, sizeof(c) ) < 0)
		return r;
	else 
		return c;
}
	

void reset_terminal_mode()
{
    tcsetattr(0, TCSANOW, &orig_termios);
}

void set_conio_terminal_mode()
{
    struct termios new_termios;

    /* take two copies - one for now, one for later */
    tcgetattr(0, &orig_termios);
    memcpy(&new_termios, &orig_termios, sizeof(orig_termios));

    /* register cleanup handler, and set the new terminal mode */
    atexit(reset_terminal_mode);
    cfmakeraw(&new_termios);
    tcsetattr(0, TCSANOW, &new_termios);
}

			
			


void hideCursor()
{
	printf("\e[?25l");
}

void showCursor()
{
	printf("\e[?25h");
}

void clearScreen(void)
{
	printf("\033[H\033[J");
	fflush(stdout);
}


#endif
