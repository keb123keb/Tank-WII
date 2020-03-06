
#ifndef HEALTH_H
#define HEALTH_H

#include<iostream>
#include<cstring>
#include"struct.cpp"

class health
{
private:
	int y;
	int LP;
	char *c;
public:
	health() {};
	void seth(int h, int p, char *x) {
		LP = h; y = p; c = x;
	}
	void printh() {
		gotoxy(15, 1);
		std::cout << c << ":";
		for (int i = 0; i < LP; i++)
			std::cout << '*';

		std::cout << std::endl;
	}
	void mhealth() {
		LP--;

		gotoxy(14 + (LP + strlen(c) + 2), 1);
		cout<<' ';
	}
	void phealth() {
		LP++;
		gotoxy(15 + (LP + strlen(c) +1), 1);
		cout<<'*';
	}
	bool gg(){
		if(LP<=0)return true;
		else return false;
	}
};

#endif
