//#include "stdafx.h"
#include "Resources.h"
#include "UI.h"

int main(int argc, char* argv[]) {

	//Step 1: Inittiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData))
		cout << "Version is not supported" << endl;

	//Step 2: Construct socket	
	SOCKET client;
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	//(optional) Set time-out for receiving
	int tv = 10000; //Time-out interval: 10000ms
	setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, (const char*)(&tv), sizeof(int));

	//Step 3: Specify server address
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons((unsigned short)atoi((char*)argv[2]));
	serverAddr.sin_addr.s_addr = inet_addr(argv[1]);

	//Step 4: Request to connect server
	if (connect(client, (sockaddr*)&serverAddr, sizeof(serverAddr))) {
		cout << "Error! Cannot connect server. " << WSAGetLastError() << endl;
		return 0;
	}
	/*-------------------------------------------------------------------*/

	//Step 5: Communicate with server
	//MENU

	createFolderLocal(CLIENT_FOLDER);

	int scene = 1;
	Account acc;
	Group gr;
	do {
		if (scene == 1) {
			scene = optionFirstFrame(client, acc);
			system("pause");
		}
		if (scene == 2) {
			scene = optionSecondFrame(client, acc, gr);
			system("pause");
		}
		if (scene == 3) {
			scene = optionThirdFrame(client, acc, gr);
			system("pause");
		}
	} while (scene != 4);
	/*-------------------------------------------------------------*/
	printf("Closed connection.\n");
	//Step 6: Close socket
	closesocket(client);
	//Step 7: Terminate Winsock
	WSACleanup();
	return 0;
}
