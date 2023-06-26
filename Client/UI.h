#pragma once
#include "Resources.h"
#include "DataIO.h"
#include "Account.h"
#include "Group.h"
#include "File.h"



void firstFrame() {
	system("cls");
	cout << "\n**********************************************************";
	cout << "\n*              Programmed by Duong Xuan Hoan             *";
	cout << "\n*                            Le Viet Hoang               *";
	cout << "\n*                                                        *";
	cout << "\n*------------------------[ WELCOME ]---------------------*";
	cout << "\n*                                                        *";
	cout << "\n*    1. Login                                            *";
	cout << "\n*    2. Register                                         *";
	cout << "\n*    3. Exit                                             *";
	cout << "\n*    4. Clear screen                                     *";
	cout << "\n*                                                        *";
	cout << "\n*--------------------------------------------------------*\n";
}

int optionFirstFrame(SOCKET sock, Account& acc) {

	int choice;
	char id[BUFF_SIZE];
	char pass[BUFF_SIZE];
	char* input = (char*)malloc(sizeof(char) * BUFF_SIZE);
	char* message = (char*)malloc(BUFF_SIZE * sizeof(char));

	firstFrame();
	do {
		cout << "Please enter your selection : ";
		cin.getline(input, BUFF_SIZE);
		choice = atoi(input);
		switch (choice) {
			case 1:
				cout << "Username : ";
				cin.getline(id, BUFF_SIZE);
				cout << "Password : ";
				cin.getline(pass, BUFF_SIZE);

				if (login(sock, acc, id, pass) == SECOND_FRAME) {
					free(input);
					free(message);
					return SECOND_FRAME;
				}
				break;
			case 2:
				cout << "Username : ";
				cin.getline(id, BUFF_SIZE);
				cout << "Password : ";
				cin.getline(pass, BUFF_SIZE);

				registerAcc(sock, id, pass);
				break;
			case 3:
				free(input);
				free(message);
				return EXIT;
			case 4:
				firstFrame();
				break;
		}
		cout << "----------------------------------------------------------\n";
	} while (choice != EXIT);
	return 0;
}


void secondMenu(Account acc) {
	system("cls");
	cout << "\n**********************************************************";
	cout << "\n*              Programmed by Duong Xuan Hoan             *";
	cout << "\n*                            Le Viet Hoang               *";
	cout << "\n*                                                        *";
	cout << "\n*------------------------[ WELCOME ]---------------------*";
	cout << "\n* " << "Hello " << acc.user << "                                           *";
	cout << "\n*                                                        *";
	cout << "\n*    1.  Show my group             5.  Join group        *";
	cout << "\n*    2.  Show other group          6.  Leave group       *";
	cout << "\n*    3.  Create group              7.  Logout            *";
	cout << "\n*    4.  Enter group               8.  Clear screen      *";
	cout << "\n*                                                        *";
	cout << "\n*--------------------------------------------------------*\n";
}

int optionSecondFrame(SOCKET sock, Account& acc, Group& gr) {
	int choice;
	char* input = (char*)malloc(sizeof(char) * BUFF_SIZE);
	char* nameGroup = (char*)malloc(BUFF_SIZE * sizeof(char));

	secondMenu(acc);
	while (true) {
		cout << "Please enter your selection : ";
		cin.getline(input, BUFF_SIZE);
		choice = atoi(input);
		switch (choice) {
			case 1:
				cout << "All of group you are member :" << endl;
				showGroup(sock, acc.id, SHOW_MY_GROUP);
				break;
			case 2:
				cout << "All of group you are not member :" << endl;
				showGroup(sock, acc.id, SHOW_OTHER_GROUP);
				break;
			case 3:
				cout << "Enter name of new group : ";
				cin.getline(input, BUFF_SIZE);
				createGroup(sock, acc.id, input);
				break;
			case 4:
				cout << "Name of group : ";
				cin.getline(input, BUFF_SIZE);
				if (enterGroup(sock, acc, gr, input) == THIRD_FRAME) {
					free(input);
					free(nameGroup);
					return THIRD_FRAME;
				}
				break;
			case 5:
				cout << "Name of group : ";
				cin.getline(input, BUFF_SIZE);
				joinGroup(sock, acc.id, input);
				break;
			case 6:
				cout << "Name of group : ";
				cin.getline(nameGroup, BUFF_SIZE);
				cout << "Are you sure : ";
				cin.getline(input, 255);

				if (strcmp(input, "Y") == 0 || strcmp(input, "y") == 0) {
					leaveGroup(sock, acc.id, nameGroup);
				}
				break;
			case 7:
				logout(sock, acc.id);
				free(input);
				free(nameGroup);
				return FIRST_FRAME;
			case 8:
				secondMenu(acc);
				break;

		}
		cout << "----------------------------------------------------------\n";
	}
	return 0;
}

void thirdMenu(Account acc, Group gr) {
	if (acc.role == 1) {
		system("cls");
		cout << "\n**********************************************************";
		cout << "\n*              Programmed by Duong Xuan Hoan             *";
		cout << "\n*                            Le Viet Hoang               *";
		cout << "\n*                                                        *";
		cout << "\n*------------------------[ WELCOME ]---------------------*";
		cout << "\n* " << "Hello " << acc.user << "                                           *";
		cout << "\n* " << "Group : " << gr.nameGroup << "                                         *";
		cout << "\n*                                                        *";
		cout << "\n*    1.  Upload                7.  Delete file           *";
		cout << "\n*    2.  Download              8.  Change directory      *";
		cout << "\n*    3.  List of file          9.  Show request          *";
		cout << "\n*    4.  List member          10.  Show log              *";
		cout << "\n*    5.  Create folder        11.  Clear screen          *";
		cout << "\n*    6.  Delete folder        12.  Back                  *";
		cout << "\n*                                                        *";
		cout << "\n*--------------------------------------------------------*\n";
	} else {
		system("cls");
		cout << "\n**********************************************************";
		cout << "\n*              Programmed by Duong Xuan Hoan             *";
		cout << "\n*                            Le Viet Hoang               *";
		cout << "\n*                                                        *";
		cout << "\n*------------------------[ WELCOME ]---------------------*";
		cout << "\n* " << "Hello " << acc.user << "                                           *";
		cout << "\n* " << "Group : " << gr.nameGroup << "                                         *";
		cout << "\n*                                                        *";
		cout << "\n*    1.  Upload                6.  Change directory      *";
		cout << "\n*    2.  Download              7.  Show log              *";
		cout << "\n*    3.  List of file          8.  Clear screen          *";
		cout << "\n*    4.  List member           9.  Back                  *";
		cout << "\n*    5.  Create folder                                   *";
		cout << "\n*                                                        *";
		cout << "\n*--------------------------------------------------------*\n";
	}
}

int optionThirdFrame(SOCKET sock, Account acc, Group gr) {
	int choice;
	char* input = (char*)malloc(sizeof(char) * BUFF_SIZE);
	char* curDir = (char*)malloc(sizeof(char) * BUFF_SIZE);
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);

	sprintf(curDir, "%s", gr.nameGroup);

	if (acc.role == 1) {
		thirdMenu(acc, gr);
		while (true) {
			cout << curDir << " > ";
			cin.getline(input, BUFF_SIZE);
			choice = atoi(input);
			switch (choice) {
				case 1:
					cout << curDir << " > ";
					cin.getline(buff, BUFF_SIZE);
					upload(sock, gr.nameGroup, buff);
					break;
				case 2:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					download(sock, gr.nameGroup, buff);
					break;
				case 3:
					showListFile(sock, curDir);
					break;
				case 4:
					showListMember(sock, gr.nameGroup);
					break;
				case 5:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					createFolder(sock, curDir, buff);
					break;
				case 6:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					deleteFolder(sock, curDir, buff);
					break;
				case 7:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					deleteFile(sock, curDir, buff);
					break;
				case 8:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					changeDirectory(sock, curDir, buff);
					break;
				case 9:
					showRequest(sock, gr.nameGroup);
					break;
				case 10:
					showLog(sock, gr.nameGroup);
					break;
				case 11:
					thirdMenu(acc, gr);
					break;
				case 12:
					free(input);
					free(curDir);
					free(buff);
					return SECOND_FRAME;

			}
			cout << "\n----------------------------------------------------------" << endl;
		}
	} else {
		thirdMenu(acc, gr);
		while (true) {
			cout << curDir << " > ";
			cin.getline(input, BUFF_SIZE);
			choice = atoi(input);
			switch (choice) {
				case 1:
					cout << curDir << " > ";
					cin.getline(buff, BUFF_SIZE);
					upload(sock, gr.nameGroup, buff);
					break;
				case 2:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					download(sock, gr.nameGroup, buff);
					break;
				case 3:
					showListFile(sock, curDir);
					break;
				case 4:
					showListMember(sock, gr.nameGroup);
					break;
				case 5:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					createFolder(sock, curDir, buff);
					break;
				case 6:
					cout << curDir << " < ";
					cin.getline(buff, BUFF_SIZE);
					changeDirectory(sock, curDir, buff);
					break;
				case 7:
					showLog(sock, gr.nameGroup);
					break;
				case 8:
					thirdMenu(acc, gr);
					break;
				case 9:
					free(input);
					free(curDir);
					free(buff);
					return SECOND_FRAME;
			}
			cout << "\n----------------------------------------------------------" << endl;
		}
	}
}
