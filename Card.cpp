#include "Card.h"


CCard::CCard()
{
	for (int i = 0; i <= 13; i++)
		card_num[i] = 4;
}
CCard::~CCard()
{
}

void CCard::sc_reset()
{
	sc1 = ' ';
	sc2 = ' ';
	sc3 = ' ';
	sc4 = ' ';
	sc5 = ' ';
}
//카드쇼에서 사용되는 스트링을 ' '으로 초기화합니다

void CCard::card_sc(int num)
{
	if (num == -1)
	{
		sc1+="********* ";
		sc2+="********* ";
		sc3+="********* ";
		sc4+="********* ";
		sc5+="********* ";
	}
	else
	{
		char m, nn;
		switch (num / 100)
		{
		case 1:
			m = 'S';
			break;
		case 2:
			m = 'D';
			break;
		case 3:
			m = 'C';
			break;
		case 4:
			m = 'H';
			break;
		}
		if (num % 100 == 11)
			nn = 'J';
		else if (num % 100 == 12)
			nn = 'Q';
		else if (num % 100 == 13)
			nn = 'K';
		else if (num % 100 == 1)
			nn = 'A';
		else
		{
			if (num % 100 == 10)
				nn = 'T';
			else
				nn = (num % 100) + 48;
		}
		sc1 += "*"; sc1 += nn; sc1 += "******* ";
		//printf("*%c******* ", nn);
		sc2 += "*       * ";
		//printf("*       * ");
		sc3 += "*   "; sc3 += m; sc3 += "   * ";
		//printf("*   %c   * ",m);
		sc4 += "*       * ";
		//printf("*       * ");
		sc5 += "*******"; sc5 += nn; sc5 += "* ";
		//printf("*******%c* ", nn);
	}
}
//카드를 카드쇼를 위해서 스트링에 넣는 함수, -1를 넣으면 뒷면

void CCard::card_show()
{
	cout << sc1 << endl;
	cout << sc2 << endl;
	cout << sc3 << endl;
	cout << sc4 << endl;
	cout << sc5 << endl;
	putchar('\n');
}
//스트링 11개를 출력하는 함수

int CCard::card_drow()
{
	CUtil u;
	int sum = 0;
	for (int i = 1; i <= 13; i++)//카드가 몇개 있는가?
		sum += card_num[i];
	int l = u.luck(sum);//1~sum까지 난수 하나 생성
	sum = 0;
	for (int i = 1; i <= 13; i++)
	{
		//sum 4 16 20 24
		//많은 숫자가 있는 카드일 수록 뽑히기 쉽게
		sum += card_num[i];
		if (l <= sum)
		{
			//i=뽑을 숫자
			while (1)
			{
				int mark = u.luck(card_num[i]--);
				if (card[mark][i] != 1)
				{
					card[mark][i] = 1;
					return (mark * 100) + i;
				}
			}	
		}
	}
}
//카드를 뽑는 함수, 리턴값은 카드를 정수로 표현한 값

void CCard::P2start(int r)
{
	CUtil u;
	for (int rr = 0; rr < r; rr++)
	{
		int card[5][14] = { 0, }, player_hand[17] = { 0, }, player2_hand[17] = { 0, }, ai_hand[17] = { 0, };
		int player_hand_i = 0, player2_hand_i = 0, ai_hand_i = 0;
		bool player_giveup = false, player2_giveup = false, ai_giveup = false;
		int card_num[14];
		int player_card_num = 0, player2_card_num = 0, ai_card_num = 0;
		printf("플레이어 1은 %d번 이기고 %d번 졌습니다.\n", win, lose);
		printf("플레이어 2은 %d번 이기고 %d번 졌습니다.\n", lose, win);
		printf("%d번째 게임입니다.\n카드를 서로 두장 뽑습니다\n", rr + 1);
		for (int i = 0; i < 2; i++)
		{
			player_hand[player_hand_i] = card_drow();
			if ((player_hand[player_hand_i] % 100) > 10)
			{
				player_card_num += 10;
				player_hand_i++;
			}
			else
				player_card_num += player_hand[player_hand_i++]%100;
			player2_hand[player2_hand_i] = card_drow();
			if ((player2_hand[player2_hand_i] % 100) > 10)
			{
				player2_card_num += 10;
				player2_hand_i++;
			}
			else
				player2_card_num += player2_hand[player2_hand_i++]%100;
		}
		while (!(player_giveup&&player2_giveup))
		{
			if (player_card_num > 21)
			{
				printf("플레이어 1은 21이 넘어 자동 포기 됬습니다.\n");
				player_giveup = true;
			}
			if (player2_card_num > 21)
			{
				printf("플레이어 2은 21이 넘어 자동 포기 됬습니다.\n");
				player2_giveup = true;
			}
			if (!player_giveup)
			{
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(player_hand[i]);
				card_show();
				printf("플레이어 1의 차례입니다.\n");
				switch (u.FSelect("카드를 뽑으시겠습니까. 포기하시겠습니까?\n1)카드를 한장 뽑는다.\n2)포기한다\n", 1, 2))
				{
				case 1:
					printf("카드를 한장 뽑으셨습니다.\n");
					player_hand[player_hand_i] = card_drow();
					if ((player_hand[player_hand_i] % 100) > 10)
					{
						player_card_num += 10;
						player_hand_i++;
					}
					else
						player_card_num += player_hand[player_hand_i++]%100;
					break;
				case 2:
					printf("포기하셨습니다.");
					player_giveup = true;
					break;
				}
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(player_hand[i]);
				card_show();
			}
			if (!player2_giveup)
			{
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(player2_hand[i]);
				card_show();
				printf("플레이어 2의 차례입니다.\n");
				switch (u.FSelect("카드를 뽑으시겠습니까. 포기하시겠습니까?\n1)카드를 한장 뽑는다.\n2)포기한다\n", 1, 2))
				{
				case 1:
					printf("카드를 한장 뽑으셨습니다.\n");
					player2_hand[player2_hand_i] = card_drow();
					if ((player2_hand[player2_hand_i] % 100) > 10)
					{
						player2_card_num += 10;
						player2_hand_i++;
					}
					else
						player2_card_num += player2_hand[player2_hand_i++]%100;
					break;
				case 2:
					printf("포기하셨습니다.");
					player2_giveup = true;
					break;
				}
				Sleep(2000);//2sec
				system("cls");
				sc_reset();
				for (int i = 0; i < player_hand_i; i++)
					card_sc(-1);
				card_show();
				sc_reset();
				for (int i = 0; i < player2_hand_i; i++)
					card_sc(player2_hand[i]);
				card_show();
			}
		}
		if (player_card_num > 21 && player2_card_num > 21)
		{
			printf("플레이어 1의 승리입니다.\n둘 다 초과, 딜러승리\n");
			win++;
		}
		else if (player_card_num > 21)
		{
			printf("플레이어 2의 승리입니다.\n플레이어 1 이 21을 넘어감\n");
			lose++;
		}
		else if (player2_card_num > 21)
		{
			printf("플레이어 1의 승리입니다.\n플레이어 2 가 21을 넘어감\n");
			lose++;
		}
		else if (player_card_num == 21 && player2_card_num == 21)
		{
			printf("플레이어 1의 승리입니다.\n동점, 딜러승리\n");
			win++;
		}
		else if (player_card_num == 21)
		{
			printf("플레이어 1의 승리입니다.\n플레이어 1 카드 총합 21\n");
			win++;
		}
		else if (player2_card_num == 21)
		{
			printf("플레이어 2의 승리입니다.\n플레이어 2 카드 총합 21\n");
			lose++;
		}
		else if (player_card_num > player2_card_num)
		{
			printf("플레이어 1의 승리입니다.\n플레이어 1 가 더 21에 가까움\n");
			win++;
		}
		else
		{
			printf("플레이어 2의 승리입니다.\n플레이어 2 가 더 21에 가까움\n");
			lose++;
		}
		Sleep(5000);//2sec
		system("cls");
	}
}

void CCard::AIstart(int r, int f)
{
	printf("첫 턴입니다.\n 카드를 서로 두장 뽑습니다.\n");
	Sleep(2000);//2sec
	system("cls");
	for (int rr = 0; rr < r; rr++)
	{
		
		Sleep(2000);//2sec
	}
}