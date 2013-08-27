#include<stdio.h>
#include"functions.h"
#include"play_game.h"
void main()
{
	system("color f0");
	system("mode con: lines=18 cols=68");
	system("title ∑±¿”∆—∆Æ");
	srand((unsigned int)time(NULL));
	jmp=20;
	spd=100;
	time_ip=100;
	time_use_ip=30;
	Nocursor();
	play();
}