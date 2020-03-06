#include"Player.h"

player::player() {
		py = height/2;
		px = width/2;
		maxbullet = 6;
		face = Down;
		health::seth(6, height + 5, "Player");
		emerge();
	}


	void player::action(char act) {
		if(act == ' ' && Blist.size() >= maxbullet) return;
		clear();
		switch (act) {
			
			case 'A': py-=1;	 face = Down;    break;
			case 'B': py+=1;	 face = Up;  break;
			case 'C': px+=1;	 face = Right;  break;
			case 'D': px-=1;	 face = Left; break;
			case ' ': Blist.push_back( bullet(face, px, py));

		}

		determine(px, py);
		emerge();
	}

	void player::PBrenew(char ch, bool Bmove, Battlefield &BF)
	{	
			
		if(ch >= 'A' && ch <= 'D'  || ch == ' ')
		{
			action(ch);
			BF.monster_show();
		}
	}
	void player::bullet_renew(Battlefield &BF)
	{
		for(int i = Blist.size() -1 ; i >= 0; i--)
			if( Blist[i].move_shot(BF) ) Blist.erase( Blist.begin() + i );
	}

	bool player::Bhurt(int mx, int my)
	{
		bool haveshoot = false;
		for(int i = Blist.size()-1; i  >= 0; i--)
			
			if(Blist[i].bx == mx && Blist[i].by == my)
			{	
				if(!Blist.size()) break;
				Blist[i].clear();
				Blist.erase( Blist.begin() + i);
				haveshoot = true;
			}
		if(haveshoot)		return true;
		return false;
	}

