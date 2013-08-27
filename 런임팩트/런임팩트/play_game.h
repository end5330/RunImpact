void play()
{
	int i,j,tmp_rand,tmp_high;
	char key;
	printf("\n");
	printf("\n");
	printf("\n");
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	printf("┃                                                                ┃");
	printf("┃                         < Run Impact >  2013.3.24 ~ 2013.3.31  ┃");
	printf("┃  [제작자] 조영인                                               ┃");
	printf("┃  [E-MAIL] choyi0521@naver.com & hanmail.net                    ┃");
	printf("┃                                                                ┃");
	printf("┃  [조작] 임팩트 : Space Bar / 이동 : 방향키 (시작하려면 Enter)  ┃");
	printf("┃                                                                ┃");
	printf("┃                                                                ┃");
	printf("┣━━━━━┯━━━┯━━━━┳━━━━━━━━━━━━━┳━━━┫");
	printf("┃IP[                        ]┃    SCORE[ 0          ]   ┃LV.0  ┃");
	printf("┗━━━━━┷━━━┷━━━━┻━━━━━━━━━━━━━┻━━━┛");
	x=7;
	y=16;
	print_me();
	do
	{
		key=getch();
	}while(key!=13);
	spd_l=clock();
	tmp_ip=clock();
	while(1)
	{
		if(y==31||!ip_mode&&(!spd_act&&(clock()-spd_l>=lev_spd[level]||y>=24&&clock()-spd_l>=lev_spd[level]/2)||spd_act&&(clock()-spd_l>=lev_spd[level]/4||y>=24&&clock()-spd_l>=lev_spd[level]/8))||ip_mode&&clock()-tmp_run_ip>=spd/10)
		{
			spd_cnt++;
			if(spd_cnt==4)
			{
				spd_cnt=0;
				spd_act=!spd_act;
				SetColor(0,level+(spd_act?8:0));
				gotoxy(0,0);
				printf("                                                                    ");
				printf("                                                                    ");
				printf("                                                                    ");
				gotoxy(0,15);
				printf("                                                                    ");
				printf("                                                                    ");
				printf("                                                                   ");
			}
			score+=level;
			gotoxy(43,13);
			SetColor(0,15);
			printf("%d",score);
			spd_l=clock();
			for(i=0; i<=7; i++)
			{
				for(j=0; j<=31; j++)
				{
					map[i][j]=map[i][j+1];
					print_map(i,j);
				}
			}
			y--;
			if(y<0)
			{
				break;
			}
			print_me();
			tmp_high=7;
			do
			{
				tmp_rand=rand()%100+1;
				if(tmp_rand<=lev_word[level][0])
				{
					break;
				}
				tmp_rand-=lev_word[level][0];
				for(i=1; i<=3; i++)
				{
					if(tmp_rand<=lev_word[level][i])
					{
						map[tmp_high][31]=i;
						print_map(tmp_high,31);
						break;
					}
					tmp_rand-=lev_word[level][i];
				}
				tmp_high--;
			}while(tmp_high>=0);
		}
		if(ip_max<24&&clock()-tmp_ip>=time_ip)
		{
			tmp_ip=clock();
			ip_max++;
			gotoxy(4+ip_max,13);
			SetColor(0,8);
			printf(" ");
		}
		if(KEY_DOWN(VK_SPACE)&&!ck_ip&&!ck_stop)
		{
			ck_ip=true;
			tmp_use_ip=clock();
		}
		else if(KEY_DOWN(VK_SPACE)&&clock()-tmp_use_ip>=time_use_ip&&ip<ip_max&&!ck_stop)
		{
			ip++;
			gotoxy(4+ip,13);
			if(ip<=8)
			{
				SetColor(0,4);
			}
			else if(ip<=16)
			{
				SetColor(0,1);
			}
			else
			{
				SetColor(0,5);
			}
			printf(" ");
			tmp_use_ip=clock();
		}
		else if(!KEY_DOWN(VK_SPACE)&&ck_ip&&!ck_stop)
		{
			tmp_ip=clock();
			level_ip=(ip-1)/8+1;
			ck_stop=true;
			tmp_run_ip=clock();
			StopMusic(0);
			PlayMusic(0);
		}
		else if(ck_stop&&clock()-tmp_run_ip>=spd/6||ip_mode&&clock()-tmp_run_ip>=spd/10)
		{
			if(ip!=0)
			{
				tmp_run_ip=clock();
				if(!ip_mode)
				{
					gotoxy(4+ip,13);
					SetColor(0,8);
					printf(" ");
					gotoxy(4+ip_max,13);
					SetColor(0,15);
					printf(" ");
				}
				ip--;
				ip_max--;
				if(y!=31&&map[x][y+1]<=level_ip)
				{
					gotoxy(2+y*2,4+x);
					if(!ip_mode)
					{
						SetColor(0,12);
					}
					else
					{
						SetColor(0,8);
					}
					printf("  ");
					y++;
					up(x,y);
					gotoxy(2+y*2,4+x);
					if(!ip_mode)
					{
						SetColor(0,12);
					}
					else
					{
						SetColor(0,8);
					}
					printf("%s",me[dir]);
					for(i=-1; i>-1*level_ip; i--)
					{
						if(x+i<0||map[x+i][y]>level_ip) break;
						up(x+i,y);
						gotoxy(2+y*2,4+x+i);
						if(i==-1)
						{
							if(!ip_mode)
							{
								SetColor(0,9);
							}
							else
							{
								SetColor(0,7);
							}
						}
						else
						{
							if(!ip_mode)
							{
								SetColor(0,8);
							}
							else
							{
								SetColor(0,7);
							}
						}
						printf("  ");
					}
					for(i=1; i<level_ip; i++)
					{
						if(x+i>7||map[x+i][y]>level_ip) break;
						up(x+i,y);
						gotoxy(2+y*2,4+x+i);
						if(i==1)
						{
							if(!ip_mode)
							{
								SetColor(0,9);
							}
							else
							{
								SetColor(0,7);
							}
						}
						else
						{
							if(!ip_mode)
							{
								SetColor(0,8);
							}
							else
							{
								SetColor(0,7);
							}
						}
						printf("  ");
					}
					if(y!=31&&level_ip>=2&&map[x][y+1]<=2)
					{
						up(x,y+1);
						gotoxy(4+y*2,4+x);
						if(!ip_mode)
						{
							SetColor(0,9);
						}
						else
						{
							SetColor(0,7);
						}
						printf(" ");
						if(x!=0&&map[x-1][y+1]<=2)
						{
							up(x-1,y+1);
							gotoxy(4+y*2,3+x);
							printf(" ");
						}
						if(x!=7&&map[x+1][y+1]<=2)
						{
							up(x+1,y+1);
							gotoxy(4+y*2,5+x);
							printf(" ");
						}
						if(y<=29&&level_ip==3)
						{
							up(x,y+2);
							gotoxy(6+y*2,4+x);
							if(!ip_mode)
							{
								SetColor(0,8);
							}
							else
							{
								SetColor(0,7);
							}
							printf(" ");
							if(x!=0)
							{
								up(x-1,y+2);
								gotoxy(6+y*2,3+x);
								printf(" ");
							}
							if(x!=7)
							{
								up(x+1,y+2);
								gotoxy(6+y*2,5+x);
								printf(" ");
							}
							if(x>=2)
							{
								up(x-2,y+1);
								gotoxy(4+y*2,2+x);
								printf(" ");
							}
							if(x<=5)
							{
								up(x+2,y+1);
								gotoxy(4+y*2,6+x);
								printf(" ");
							}
						}
					}
				}
			}
			else
			{
				ck_stop=ck_ip=false;
				if(x!=7&&map[x+1][y]==0)
				{
					v_0=0;
					ck_jmp=true;
					tmp_jmp=clock();
					tmp_1=0;
				}
				if(ip_mode)
				{
					ip_mode=false;
					ip_max=24;
					gotoxy(5,13);
					SetColor(0,8);
					printf("                        ");
				}
			}
		}
		if(KEY_DOWN(VK_UP)&&!ck_jmp)
		{
			v_0=jmp;
			ck_jmp=true;
			tmp_jmp=clock();
			tmp_1=0;
		}
		if(KEY_DOWN(VK_LEFT)&&!KEY_DOWN(VK_RIGHT)&&!ck_stop)
		{
			if(dir==1)
			{
				dir=0;
				print_me();
				ck_spd=false;
			}
			else if(y==0||map[x][y-1]!=0)
			{
				ck_spd=false;
			}
			else if(!ck_spd)
			{
				ck_spd=true;
				tmp_spd=clock();
			}
			else if(clock()-tmp_spd>=spd)
			{
				tmp_spd=clock();
				delete_me();
				y--;
				print_me();
				if(x!=7&&map[x+1][y]==0&&!ck_jmp)
				{
					v_0=0;
					ck_jmp=true;
					tmp_jmp=clock();
					tmp_1=0;
				}
			}
		}
		else if(!KEY_DOWN(VK_LEFT)&&KEY_DOWN(VK_RIGHT)&&!ck_stop)
		{
			if(dir==0)
			{
				dir=1;
				print_me();
				ck_spd=false;
			}
			else if(y==31||map[x][y+1]!=0)
			{
				ck_spd=false;
			}
			else if(!ck_spd)
			{
				ck_spd=true;
				tmp_spd=clock();
			}
			else if(clock()-tmp_spd>=spd)
			{
				tmp_spd=clock();
				delete_me();
				y++;
				print_me();
				if(x!=7&&map[x+1][y]==0&&!ck_jmp)
				{
					v_0=0;
					ck_jmp=true;
					tmp_jmp=clock();
					tmp_1=0;
				}
			}
		}
		else if(ck_spd)
		{
			ck_spd=false;
		}
		if(ck_jmp&&!ck_stop)
		{
			tmp_2=(double)v_0*(clock()-tmp_jmp)/1000-(double)(clock()-tmp_jmp)*(clock()-tmp_jmp)/50000+0.5;
			if(tmp_1<tmp_2)
			{
				if(x==0||map[x-1][y]!=0)
				{
					v_0=0;
					tmp_jmp=clock();
				}
				else
				{
					tmp_1=tmp_2;
					delete_me();
					x--;
					print_me();
				}
			}
			else if(tmp_1>tmp_2)
			{
				if(x==7||map[x+1][y]!=0)
				{
					ck_jmp=false;
				}
				else
				{
					tmp_1=tmp_2;
					delete_me();
					x++;
					print_me();
				}
			}
		}
	}
	gotoxy(0,15);
	SetColor(0,15);
	printf("  Game Over! (Enter : 종료)");
	do
	{
		key=getch();
	}while(key!=13);
}