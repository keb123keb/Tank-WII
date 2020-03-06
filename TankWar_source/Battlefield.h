#include<vector>
#include<iostream>


using namespace std;

#ifndef BATTLEFIELD_H
#define	BATTLEFIELD_H
class Battlefield;
class monster;
class player;
class bullet;
class trap;
#include"Monster.h"
#include"Bullet.h"
#include"Player.h"
#include"struct.cpp"
#include"Trap.h"
class Battlefield
{
	public:
		Battlefield();
		void battlestart();
		int eventUserInput(player &p, bool &PBmove, Battlefield &BF, int cond);
	bool BshotM(bullet &B);

		bool gotone(player &, trap &);
		void Mmove(player &P);
		void monster_show();
		void leave_player(int &mx, int &my);
	private:
        const int score_target =1;

		vector<monster> Mlist;
		vector<player> Plist;
		vector<trap> Tlist;
		int Mmax;
//		player &p;
		int score;
		int mwidth, mheight;

		player *pp;
		friend class monster;
		friend class player;
		friend class bullet;
		friend class trap;
};
#endif

