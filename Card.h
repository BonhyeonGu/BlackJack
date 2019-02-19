#include"Default.h"
#include"Util.h"
#pragma once
class CCard
{
	int win = 0, lose = 0;
	string sc1, sc2, sc3, sc4, sc5, sc6, sc7, sc8, sc9, sc10, sc11;
public:
	int card[5][14] = { 0, }, player_hand[17] = { 0, }, player2_hand[17] = { 0, }, ai_hand[17] = { 0, };
	int player_hand_i = 0, player2_hand_i = 0, ai_hand_i = 0;
	bool player_giveup = false, player2_giveup = false, ai_giveup = false;
	int card_num[14];
	int player_card_num = 0, player2_card_num = 0, ai_card_num = 0;
	void sc_reset();
	void card_sc(int num);
	void card_show();
	int card_drow();
	void P2start(int r);
	void AIstart(int r, int f);


	CCard();
	~CCard();
};

