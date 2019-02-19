#include "Util.h"



CUtil::CUtil()
{
	srand(time(0));
}


CUtil::~CUtil()
{
}

int CUtil::FSelect(char output[100], int n0, int n1, int n2, int n3, int n4, int n5, int n6, int n7, int n8, int n9)
{
	int n[10] = { n0, n1, n2, n3, n4, n5, n6, n7, n8, n9 }, input;
	while (1)
	{
		int o = 0;
		while (output[o] != '\0')
			putchar(output[o++]);
		printf("input :");
		scanf("%d", &input);
		for (int i = 0; i < 10; i++)
		{
			if (n[i] == input)
			{
				return input;
			}
		}
		system("cls");
	}
}
//선택지 반복 함수
int CUtil::luck(int n)
{
	return (rand() % n) + 1;
}
//1부터 n까지 난수 만드는 함수