#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable :4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define MAX_LEN 100



//콘솔 창의 크기와 제목을 지정하는 함수
void SetConsole() {
	system("title PlayList"); // 콘솔창 이름 설정
	system("mode con:cols=500 lines=500"); // 콘솔창 크기설정

	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);

}
//커서 이동
void gotoxy(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(consoleHandle, Cur);
}
//텍스트 색깔
void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
	/*
	0	검정색	8	회색
	1	파란색	9	연한 파란색
	2	초록색	10	연한 초록색
	3	옥색		11	연한 옥색
	4	빨간색	12	연한 빨간색
	5	자주색	13	연한 자주색
	6	노란색	14	연한 노란색
	7	흰색		15	진한 흰색
	*/
}



//노드 선언
typedef struct node_
{
	int order;
	char title[MAX_LEN];
	char singer[MAX_LEN];
	char album[MAX_LEN];
	char playtime[MAX_LEN];
	struct node_* next;
}Node;
Node* head = NULL;
Node* tail = NULL;

//TOP100 설정
Node top100[100];
void settop100() {
	FILE* fs;
	fs = fopen("top100.txt", "r");

	int n = 0;
	while (feof(fs) == 0) {
		char str[MAX_LEN];
		fgets(str, MAX_LEN, fs);
		strcpy(top100[n].title, str);
		fgets(str, MAX_LEN, fs);
		strcpy(top100[n].singer, str);
		fgets(str, MAX_LEN, fs);
		strcpy(top100[n].album, str);
		fgets(str, MAX_LEN, fs);
		fgets(str, MAX_LEN, fs);
		fgets(str, MAX_LEN, fs);
		fgets(str, MAX_LEN, fs);
		strcpy(top100[n].playtime, str);
		fgets(str, MAX_LEN, fs);
		n++;
	}

	fclose(fs);
}
//TOP100 출력
int page = 0;
void printtop100() {
	int x = 180;
	int y = 0;
	textcolor(11);

	gotoxy(x, y);
	printf("[멜론 TOP100]\n\n");
	for (int i = 0+page; i < 10+page; i++) {
		y++; gotoxy(x, y);
		printf("%d위", i+1);
		y++; gotoxy(x, y);
		printf("제목: %s", top100[i].title);
		y++; gotoxy(x, y);
		printf("가수: %s", top100[i].singer);
		y++; gotoxy(x, y);
		printf("앨범: %s", top100[i].album);
		y++; gotoxy(x, y);
		printf("재생시간: %s", top100[i].playtime);
	}
	y++; y++; gotoxy(x, y);
	printf("\t\t\t\t[<]   [>]");
}
void printNode();
void printplay();
void printtop100();
//노드 삽입
void  insertNode() {
		textcolor(7);
		gotoxy(80, 27);
		int n;
		printf("추가할 노래의 순위를 입력하세요: ");
		scanf("%d", &n);
		if (n > 0 && n < 101) {
			n--;

			Node* newnode = (Node*)malloc(sizeof(Node));
			strcpy(newnode->title, top100[n].title);
			strcpy(newnode->singer, top100[n].singer);
			strcpy(newnode->album, top100[n].album);
			strcpy(newnode->playtime, top100[n].playtime);
			newnode->next = NULL;

			if (head == NULL) head = newnode;
			else tail->next = newnode;

			tail = newnode;
		}		
}
//노드 삭제
int cur_order = 1;
void deleteNode() {
		textcolor(7);
		gotoxy(80, 27);
		int n;
		printf("삭제할 노래의 순서를 입력하세요: ");
		scanf("%d", &n);

		Node* cur_prev = NULL;
		Node* cur = head;
		int search = 0;
		while (cur != NULL)
		{
			if (cur->order == n)
			{
				search = 1;
				break;
			}
			cur_prev = cur;
			cur = cur->next;
		}
		if (search == 1)
		{
			if (cur == head) {
				head = cur->next;
			}
			else if (cur == tail) {
				cur_prev->next = NULL;
				tail = cur_prev;
			}
			else {
				cur_prev->next = cur->next;
			}
			free(cur);
			if (n <= cur_order) {
				cur_order--;
			}
		}
}
//리스트 출력
int last_order=1;
void printNode() {
	system("cls");
	Node* cur = head;
	int n = 1;
	textcolor(7);
	printf("[현재 재생목록]\n\n");
	while (cur != NULL)
	{
		cur->order = n;
		last_order = n;
		n++;
		textcolor(7);
		printf("%d번째\n", cur->order);
		textcolor(10);
		printf("제목: %s", cur->title);
		printf("가수: %s", cur->singer);
		printf("앨범: %s", cur->album);
		printf("재생시간: %s", cur->playtime);
		cur = cur->next;
	}
}
//플레이 인터페이스
void printplay() {
	int x = 80;
	textcolor(13);
	gotoxy(x, 3);
	printf(" ____                                   __     ");
	gotoxy(x, 4);
	printf("/\\  _`\\                                /\\ \\    ");
	gotoxy(x, 5);
	printf("\\ \\,\L\\_\\      ___     ___       __     \\ \\ \\ ");
	gotoxy(x, 6);
	printf(" \\/_\\__ \\    / __`\\ /' _ `\\   /'_ `\\    \\ \\ \\ ");
	gotoxy(x, 7);
	printf("   /\\ \\L\\ \\ /\\ \\L\\ \\/\\ \\/\\ \\ /\\ \\L\\ \\    \\ \\_\\ ");
	gotoxy(x, 8);
	printf("   \\ `\\____\\\\ \\____/\\ \\_\\ \\_\\\\ \\____ \\    \\/\\_\\");
	gotoxy(x, 9);
	printf("    \\/_____/ \\/___/  \\/_/\\/_/ \\/___L\\ \\    \\/_/");
	gotoxy(x, 10);
	printf("                                /\\____/    ");
	gotoxy(x, 11);
	printf("                                \\_/__/   ");
	gotoxy(x, 13);
	textcolor(14);
	Node* cur = head;
	while (cur != NULL)
	{
		if (cur->order == cur_order) {
			printf("\t[현재 재생중]");
			gotoxy(x, 14);
			printf("\t제목: % s", cur->title);
			gotoxy(x, 15);
			printf("\t가수: %s", cur->singer);
			gotoxy(x, 16);
			printf("\t앨범: %s", cur->album);
			gotoxy(x, 20);
			textcolor(9);
			printf("(||)-◎--------------------------------0:00/%s", cur->playtime);

			break;
		}
		else {
			cur = cur->next;
		}
	}
	textcolor(7);
	gotoxy(x, 25);
	printf("[z]입력 [x]삭제 [∧]이전 재생 [∨]다음 재생 [0]종료");
}
//메인 함수
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define ARROW 224
#define Zkey 122
#define Xkey 120
#define ZERO 48
int main(){
	SetConsole();
	settop100();

	printNode();
	printplay();
	printtop100();
	while (1) {
		if (_kbhit()) {
			int nkey = _getch();
			if (nkey == Zkey) {
				insertNode();
			}
			if (nkey == Xkey) {
				deleteNode();
			}
			if (nkey == ZERO) {
				textcolor(7);
				exit(1);
			}
			if (nkey == ARROW) {
				nkey = _getch();
				switch (nkey) {
				case LEFT:
					if (page != 0) { page = page - 10; }
					break;
				case RIGHT:
					if (page != 90) { page = page + 10; }
					break;
				case UP:
					if (cur_order != 1) { cur_order--; }
					break;
				case DOWN:
					if (cur_order != last_order) { cur_order++; }
					break;
				}
			}
			system("cls");
			printNode();
			printplay();
			printtop100();
		}
	}

}