#include<vector>
#include<cstdio>
#include<iostream>
using namespace std;
#ifndef PLAYER
#define PLAYER
class Battlefield;
class bullet ;
class monster;
#include"struct.cpp"
#include"health.h"
#include"Battlefield.h"
class player: public health
{
private:
	int px, py;
	int maxbullet;
	vector<bullet> Blist;
	
	edir face;
	void clear()
	{
		gotoxy(px, py);
		printf(" ");
	}
	void emerge()
	{
		gotoxy(px, py);
		putchar('I');
	}

public:
	
	player();

inline int getx() {return px;}
inline int gety() { return py; }
inline int getface() { return face; }

	void action(char act);
	void mhurt(edir d){
		switch(d){
			case Up:
				py-=3;
				break;
			case Down:
				py+=3;
				break;
			case Right:
				px+=3;
				break;
			case Left:
				px-=3;
				break;
		}
		determine(px,py);
		gotoxy(px,py);
		cout<<'G';
	}
	void PBrenew(char ch, bool Bmove, Battlefield &BF);
	void bullet_renew(Battlefield &BF);
	bool Bhurt(int mx, int my);
	void show(){emerge();}

	friend class bullet;
};
#endif

