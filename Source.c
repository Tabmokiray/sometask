#include <stdio.h>
#include <locale.h>
#pragma comment(lib, "winmm.lib")
#include <Windows.h>
#include <MMSystem.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
void gotoxy(int column, int row);
void prepare(int* size, int mode, int x, int y);
void leftup(int size, int mode, int x, int y);
void rightup(int size, int mode, int x, int y);
void leftdown(int size, int mode, int x, int y);
void rightdown(int size, int mode, int x, int y);
void blinkleftup(int size, int mode, int x, int y);
void blinkrightup(int size, int mode, int x, int y);
void blinkleftdown(int size, int mode, int x, int y);
void blinkrightdown(int size, int mode, int x, int y);
int main() {
	srand(time(NULL));
	PlaySound(TEXT("Pixel.wav"), NULL, SND_LOOP | SND_ASYNC);
	int size = 0;
	int answers[200];
	for (int i = 0; i < 200; i++) {
		answers[i] = 0;
	}
	DWORD sleeptime = 1500;
	setlocale(LC_ALL, "Rus");
	while (1) {
		int x = 50, y = 6;
		system("cls");
		gotoxy(50, 5);
		printf_s("Tap Enter to Start\n");
		getchar();
		gotoxy(50, 7);
		printf_s("Choose size of picture between 10 and 20\n");
		scanf_s("%d", &size);
		while ((size < 10) || (size > 20)) {
			printf_s("\nTry again\n");
			scanf_s("%d", &size);
		}
		system("cls");
		prepare(&size, 1, x, y);
		sleeptime = 1500;
		int loose = 0;
		int tip = 0;
		char typ = '0';
		int rounds = 0;
		int score = 0;
		int move = 0;
		gotoxy(50, 3);
		printf_s("Total score: %d  ", score);
		while (loose != 1) {
			int r = 0;
			for (int j = 0; j <= rounds; j++) {
				if (move == 1) {
					prepare(&size, 0, x, y);
					x = rand() % 80 + 25;
					y = rand() % 10 + 6;
				}
				prepare(&size, 1, x, y);
				if (answers[j] == 0)
					r = rand() % 4 + 1;
				else {
					r = answers[j];
				}
				switch (r) {
				case 1: {
					leftup(size, 1, x, y);
					Sleep(sleeptime / 2);
					leftup(size, 0, x, y);
					Sleep(sleeptime / 2);
					break;
				}
				case 2: {
					rightup(size, 1, x, y);
					Sleep(sleeptime / 2);
					rightup(size, 0, x, y);
					Sleep(sleeptime / 2);
					break;
				}
				case 3: {
					leftdown(size, 1, x, y);
					Sleep(sleeptime / 2);
					leftdown(size, 0, x, y);
					Sleep(sleeptime / 2);
					break;
				}
				case 4: {
					rightdown(size, 1, x, y);
					Sleep(sleeptime / 2);
					rightdown(size, 0, x, y);
					Sleep(sleeptime / 2);
					break;
				}
				default: {
					gotoxy(0, 2);
					printf_s("ERROR");
					Sleep(2000);
					exit(1);
				}
				}
				answers[j] = r;
			}
			for (int i = 0; i <= rounds; i++) {
				gotoxy(0, 0);
				typ = getch();
				tip = typ - '0';
				switch (tip) {
				case 1: {
					blinkleftup(size, 1, x, y);
					Sleep(sleeptime / 2);
					blinkleftup(size, 0, x, y);
					break;
				}
				case 2: {
					blinkrightup(size, 1, x, y);
					Sleep(sleeptime / 2);
					blinkrightup(size, 0, x, y);
					break;
				}
				case 3: {
					blinkleftdown(size, 1, x, y);
					Sleep(sleeptime / 2);
					blinkleftdown(size, 0, x, y);
					break;
				}
				case 4: {
					blinkrightdown(size, 1, x, y);
					Sleep(sleeptime / 2);
					blinkrightdown(size, 0, x, y);
					break;
				}
				}
				if (tip != answers[i]) {
					gotoxy(0, 2);
					printf_s("Wrong number");
					Sleep(sleeptime);
					loose = 1;
					system("cls");
					gotoxy(50, 20);
					printf_s("Your result is %d", score);
					gotoxy(50, 22);
					system("pause");
					break;
				}
			}
			score += 100 * rounds;
			gotoxy(50, 3);
			printf_s("Total score: %d  ", score);
			rounds++;
			if (sleeptime > 250)
				sleeptime -= 150;
			if (sleeptime < 1000) {
				sleeptime += 30;
				move = 1;
			}

		}
	}
	getchar();
	return 0;
}
void gotoxy(int column, int row)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	//#ifdef MY_DEBUG
	//  if (hCons == INVALID_HANDLE_VALUE || hCons == 0) printf("\nERROR!!!\n");
	//#endif  	  
	crd.X = (short)column;
	crd.Y = (short)row;
	//#ifedf MY_DEBUG
	// if (SetConsoleCursorPosition(hCons,crd) == 0) printf("\nERROR2\n");
	//#else 
	SetConsoleCursorPosition(hCons, crd);
	//#endif
}
void prepare(int* size, int mode, int x, int y) {

	if (mode == 1) {
		for (int i = 0; i < *size; i++) {
			gotoxy(x - i, i + y);
			printf_s("/");
			gotoxy(x + 1 + i, i + y);
			printf_s("\\");
			gotoxy(x + 1 + i - *size, i + y + *size);
			printf_s("\\");
			gotoxy(x + *size - i, i + y + *size);
			printf_s("/");
		}
		gotoxy(x + 2 - *size, y - 1 + *size);
		for (int i = 0; i < *size * 2 - 2; i++) {
			printf_s("_");
		}
		for (int i = 0; i < *size * 2 - 3; i++) {
			gotoxy(x, i + y + 1);
			printf_s("||");
		}
	}
	else {
		for (int i = 0; i < *size; i++) {
			gotoxy(x - i, i + y);
			printf_s(" ");
			gotoxy(x + 1 + i, i + y);
			printf_s(" ");
			gotoxy(x + 1 + i - *size, i + y + *size);
			printf_s(" ");
			gotoxy(x + *size - i, i + y + *size);
			printf_s(" ");
		}
		gotoxy(x + 2 - *size, y - 1 + *size);
		for (int i = 0; i < *size * 2 - 2; i++) {
			printf_s(" ");
		}
		for (int i = 0; i < *size * 2 - 3; i++) {
			gotoxy(x, i + y + 1);
			printf_s("  ");
		}
	}
}
void leftup(int size, int mode, int x, int y) {
	if (mode == 1) {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x - i, i + y + 1);
			for (int j = 0; j < i; j++) {
				printf_s("1");
			}
		}
	}
	else {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x - i, i + y + 1);
			for (int j = 0; j < i; j++) {
				printf_s(" ");
			}
		}
	}
}
void rightup(int size, int mode, int x, int y) {
	if (mode == 1) {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x + 2, i + y + 1);
			for (int j = 0; j < i; j++) {
				printf_s("2");
			}
		}
	}
	else {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x + 2, i + y + 1);
			for (int j = 0; j < i; j++) {
				printf_s(" ");
			}
		}
	}
}
void leftdown(int size, int mode, int x, int y) {
	if (mode == 1) {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x + 2 + i - size, i + y + size);
			for (int j = 0; j < size - i - 2; j++) {
				printf_s("3");
			}
		}
	}
	else {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x + 2 + i - size, i + y + size);
			for (int j = 0; j < size - i - 2; j++) {
				printf_s(" ");
			}
		}
	}
}
void rightdown(int size, int mode, int x, int y) {
	if (mode == 1) {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x + 2, i + y + size);
			for (int j = 0; j < size - i - 2; j++) {
				printf_s("4");
			}
		}
	}
	else {
		for (int i = 0; i < size - 2; i++) {
			gotoxy(x + 2, i + y + size);
			for (int j = 0; j < size - i - 2; j++) {
				printf_s(" ");
			}
		}
	}
}
void blinkleftup(int size, int mode, int x, int y) {
	if (mode == 1) {
		gotoxy(x - size - 3, y + size / 2);
		printf_s("****");
		gotoxy(x - size - 4, y + size / 2 + 1);
		printf_s("******");
		gotoxy(x - size - 3, y + size / 2 + 2);
		printf_s("****");
	}
	else {
		gotoxy(x - size - 3, y + size / 2);
		printf_s("    ");
		gotoxy(x - size - 4, y + size / 2 + 1);
		printf_s("      ");
		gotoxy(x - size - 3, y + size / 2 + 2);
		printf_s("    ");
	}
}
void blinkrightup(int size, int mode, int x, int y) {
	if (mode == 1) {
		gotoxy(x + size + 2, y + size / 2);
		printf_s("****");
		gotoxy(x + size + 1, y + size / 2 + 1);
		printf_s("******");
		gotoxy(x + size + 2, y + size / 2 + 2);
		printf_s("****");
	}
	else {
		gotoxy(x + size + 2, y + size / 2);
		printf_s("    ");
		gotoxy(x + size + 1, y + size / 2 + 1);
		printf_s("      ");
		gotoxy(x + size + 2, y + size / 2 + 2);
		printf_s("    ");
	}
}
void blinkleftdown(int size, int mode, int x, int y) {
	if (mode == 1) {
		gotoxy(x - size - 3, y + size + 5);
		printf_s("****");
		gotoxy(x - size - 4, y + size + 6);
		printf_s("******");
		gotoxy(x - size - 3, y + size + 7);
		printf_s("****");
	}
	else {
		gotoxy(x - size - 3, y + size + 5);
		printf_s("    ");
		gotoxy(x - size - 4, y + size + 6);
		printf_s("      ");
		gotoxy(x - size - 3, y + size + 7);
		printf_s("    ");
	}
}
void blinkrightdown(int size, int mode, int x, int y) {
	if (mode == 1) {
		gotoxy(x + size + 2, y + size + 5);
		printf_s("****");
		gotoxy(x + size + 1, y + size + 6);
		printf_s("******");
		gotoxy(x + size + 2, y + size + 7);
		printf_s("****");
	}
	else {
		gotoxy(x + size + 2, y + size + 5);
		printf_s("    ");
		gotoxy(x + size + 1, y + size + 6);
		printf_s("      ");
		gotoxy(x + size + 2, y + size + 7);
		printf_s("    ");
	}
}