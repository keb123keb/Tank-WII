#include"Battlefield.h"
using namespace std;

Battlefield::Battlefield()
	:Mmax(6),pp(new player),score(0), mwidth(width), mheight(height)
	{
		Mlist.resize(Mmax);
		for(int i = 0; i < Mmax; i++) 
			Mlist[i].born(*this); 
		
		Tlist.resize(20);
		for(int i = 0;i < 20;i++) Tlist[i].settrap(width/2, height/2);
	}

bool Battlefield::gotone(player &p, trap &t){
	if(p.getx()==t.getx()&&p.gety()==t.gety()){
		return true;
	}
	else
		return false;
}

bool Battlefield::BshotM(bullet &B)
{
	bool haveshoot =  false;
	int size = Mlist.size();
	for(int i = Mlist.size() - 1; i >= 0; i--)
		if( Mlist[i].mx == B.bx && Mlist[i].my == B.by)
		{
			if(!Mlist.size()) break;
			Mlist[i].killed();
			Mlist.erase( Mlist.begin() + i );
			haveshoot = true;
			score++;
		}

	if(haveshoot) return true;
	return false;
}


void Battlefield::Mmove(player &P)
{
	for(int i = 0; i < Mlist.size(); i++)
	{
		int gseed =rand() % 32;
		if(gseed > 10 && Mlist.size() < Mmax)
		{
			Mlist.push_back(monster());
			Mlist[ Mlist.size()-1 ].born(*this);
		}	
		if( Mlist[i].move_death_check(P) )
		{
			Mlist[i].killed();
			Mlist.erase( Mlist.begin() + i );
			score++;
		}
	}
}	

void Battlefield::monster_show()
{
	for(int i = 0; i < Mlist.size(); i++)
		Mlist[i].show = true;
}

void Battlefield::leave_player(int &mx, int &my)
{
	player &p = *pp;
	if (mx - 10 < p.getx() && mx >= p.getx() )
		mx += 15;
	else if (mx + 10 > p.getx() && mx < p.getx() )
		mx -= 15;
	if (my - 10 < p.gety() && my >= p.gety() )
		my += 15;
	else if (my + 10 > p.gety() && my < p.gety())
		my -= 15;
}

int Battlefield::eventUserInput(player &p, bool &PBmove, Battlefield &BF, int cond)
{
	if(!cond)return false;
	char ch = getch();

	if(ch == 'X')
		return 1;

	p.PBrenew(ch, PBmove, BF);

	fflush(stdout);

	return 0;
}

void Battlefield::battlestart()
{
	set_conio_terminal_mode();
	int i = 0; 
	long long start = clock(), MBTcounter = 0;
	bool PBmove = false;
	clearScreen();
	hideCursor();
	fflush(stdout);

	gotoxy(mwidth/2 - 10 < 0 ? 0 : mwidth/2 - 10, mheight/2);
	cout << " Press any key to start" << endl;
	while(1) 
		if(kbhit()){ 
			clearScreen();
			break;
		}
	player &p = *pp;
	p.printh();
printf("\033[1;36m");
	for(int i = 1 ; i < mwidth + 1; i++)	
	{
		gotoxy(1+i,2);
		cout << '-';
		gotoxy(1+i,mheight+1);		cout << '-';
	}
printf("\033[1;35m");
	for(int i = 2; i < mheight; i++)
	{
		gotoxy(2, 1+i);
		cout << '|';
		gotoxy(width+1, i+1);
		cout << '|';
	}


	start = clock();
	long long subsor = clock();
	
	long long ttime[3];
	ttime[0] = 0;ttime[1] = 0;ttime[2] = 0;
	bool flag[3];
	flag[0] = false; flag[1] = false; flag[2] = false;
	
	while(p.gg()==false&&score<score_target)
	{
		if( kbhit() ){
			if((flag[0]||flag[1]||flag[2])){
				getchar();
			}
			if( eventUserInput(p, PBmove, *this, (!flag[0]&&!flag[1]&&!flag[2])) )
				break;
		}
		for(int i = 0;i < 3;i++){
			if(gotone(p, Tlist[i])){
				if(!flag[i]){
					ttime[i] = clock();
					flag[i] = true;
					Tlist[i].show();
				}
				if((int)((clock()-ttime[i])/CLOCKS_PER_SEC) >= 3){
					fflush(stdin);
					gotoxy(Tlist[i].getx()+1, Tlist[i].gety());
					cout << " ";
					gotoxy(Tlist[i].getx()-1, Tlist[i].gety());
					cout << " ";
					gotoxy(Tlist[i].getx(), Tlist[i].gety()+1);
					cout << " ";
					gotoxy(Tlist[i].getx(), Tlist[i].gety()-1);
					cout << " ";
					Tlist[i].settrap(p.getx(), p.gety());
					ttime[i] = 0;
					flag[i] = false;
					p.show();
				}
			}
		}

		for(int i=0;i<Mlist.size();i++){
			if(Mlist[i].getx()==p.getx()&&Mlist[i].gety()==p.gety()){
				gotoxy(Mlist[i].getx(),Mlist[i].gety());
				cout<<"C";
				p.mhealth();
				p.mhurt(Mlist[i].getdir());
//				p,emerge();
			}
		}
		
		
		if( clock() - start > 1000)
		{
			MBTcounter++;
			if(MBTcounter >  (1 << 8) ) 
			{
				if(Mlist.size())
				{

					Mmove(p);
					for(int i = 0; i < Mlist.size(); i++)
						Mlist[i].changedir(p);
				}

				MBTcounter = 0;

				gotoxy(40, 0);
				printf("\033[0;33m""score: %d", score);
				printf("\033m");
				p.bullet_renew(*this);
			}

			gotoxy(0, 0);
			printf("\033[1;33m" "%d   seconds""\033[m", (clock() - subsor)/ CLOCKS_PER_SEC);			
		
			fflush(stdout);
			start += 1000;
		}
	}

	if(p.gg()==true){
		clearScreen();
		printf("\033[1;31m");
		gotoxy(width/2 - 4 < 0 ? 0 : width/2 - 4, height/2);
		cout << " GAMEOVER" << endl;
		printf("\033[m");
	}
	if(score>=score_target){
		clearScreen();
		printf("\033[1;33m");
		gotoxy(width/2 - 3 < 0 ? 0 : width/2 - 3, height/2);
		cout << "YOU WIN!!" << endl;
		printf("\033[m");
        reset_terminal_mode();
	}

}
