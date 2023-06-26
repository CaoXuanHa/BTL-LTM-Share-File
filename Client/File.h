#pragma once
#include "Resources.h"
#include "DataIO.h"



void handleFileResponse(int msgOpcode) {
	switch (msgOpcode) {
		case ACCEPT_UPLOAD:
			cout << " => SYSTEM : File is allow to upload" << endl;
			break;
		case UPLOAD_SUCCESS:
			cout << " => SYSTEM : Upload file successfully" << endl;
			break;
		case ACCEPT_DOWNLOAD:
			cout << " => SYSTEM : File is allow to download" << endl;
			break;
		case DOWNLOAD_SUCCESS:
			cout << " => SYSTEM : Download file successfully" << endl;
			break;
		case CREATE_FOLDER_SUCCESS:
			cout << " => SYSTEM : Create group successfully" << endl;
			break;
		case DELETE_FOLDER_SUCCESS:
			cout << " => SYSTEM : Delete group successfully" << endl;
			break;
		case FOLDER_NOT_FOUND:
			cout << " => SYSTEM : Folder is not found" << endl;
			break;
		case FOLDER_ALREADY_EXIST:
			cout << " => SYSTEM : Folder is already exist" << endl;
			break;
		case DELETE_FILE_SUCCESS:
			cout << " => SYSTEM : Delete file successfully" << endl;
			break;
		case FILE_NOT_FOUND:
			cout << " => SYSTEM : File is not found" << endl;
			break;
	}
}

void upload(SOCKET sock, char* nameGroup, char* nameFile) {
	int ret;
	Message msg;
	char* message = (char*)malloc(sizeof(char) * BUFF_SIZE);
	if (checkFile(nameFile) == 0) {
		sprintf(message, "%s/%s", nameGroup, nameFile);
		ret = sendMessage(sock, message, UPLOAD);
		if (ret != SOCKET_ERROR) {
			recvMessage(sock, msg);
			handleFileResponse(msg.opcode);
			if (msg.opcode == ACCEPT_UPLOAD) {
				ret = sendFile(sock, nameFile);
				if (ret != SOCKET_ERROR) {
					recvMessage(sock, msg);
					handleFileResponse(msg.opcode);
				} else {
					cout << "Something wrong" << endl;
					return;
				}
			} else {
				cout << " => Server : Upload file is not accepted" << endl;
			}
		} else {
			cout << "Something wrong" << endl;
			return;
		}
	} else {
		cout << "File is not exist" << endl;
	}
	free(message);
}

void download(SOCKET sock, char* nameGroup, char* nameFile) {
	Message msg;
	char* message = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sprintf(message, "%s/%s", nameGroup, nameFile);
	sendMessage(sock, message, DOWNLOAD);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	if (msg.opcode == ACCEPT_DOWNLOAD) {
		recvFile(sock, nameFile);
		cout << " => SYSTEM : Download file is completed" << endl;
	}
	free(message);
}


void showListFile(SOCKET sock, char* curDir) {
	Message msg;
	char* file = (char*)malloc(sizeof(char) * 256);
	char* message = (char*)malloc(sizeof(char) * BUFF_SIZE);
	
	sendMessage(sock, curDir, LIST_FILE);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	sprintf(file, "");
	file = strtok_s(msg.payload, DELIMETER, &message);
	while (file != NULL) {
		for (int i = 0; i < 3; i++) {
			if (file == NULL) {
				break;
			}
			cout << file << "\t";
			file = strtok_s(message, DELIMETER, &message);
		}
		cout << endl;
	}
}

void showListMember(SOCKET sock, char* nameGroup) {
	Message msg;
	char* member = (char*)malloc(sizeof(char) * 256);
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	
	sendMessage(sock, nameGroup, LIST_MEMBER);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	sprintf(member, "");
	member = strtok_s(msg.payload, DELIMETER, &buff);
	while (member != NULL) {
		for (int i = 0; i < 3; i++) {
			if (member == NULL) {
				break;
			}
			cout << member << "\t";
			member = strtok_s(buff, DELIMETER, &buff);
		}
		cout << endl;
	}
}

void createFolder(SOCKET sock, char* curDir, char* nameFolder) {
	Message msg;
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sprintf(buff, "%s/%s/%s", SERVER_FOLDER, curDir, nameFolder);
	sendMessage(sock, buff, CREATE_FOLDER);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	free(buff);
}

void deleteFolder(SOCKET sock, char* curDir, char* nameFolder) {
	Message msg;
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sprintf(buff, "%s/%s/%s", SERVER_FOLDER, curDir, nameFolder);
	sendMessage(sock, buff, DELETE_FOLDER);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	free(buff);
}

void deleteFile(SOCKET sock, char* curDir, char* nameFile) {
	Message msg;
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sprintf(buff, "%s/%s/%s", SERVER_FOLDER, curDir, nameFile);
	sendMessage(sock, buff, DELETE_FILE);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	free(buff);
}

void changeDirectory(SOCKET sock, char* curDir, char* nameFolder) {
	Message msg;
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sprintf(buff, "%s/%s %s", SERVER_FOLDER, curDir, nameFolder);
	sendMessage(sock, buff, CHANGE_DIRECTORY);
	recvMessage(sock, msg);
	handleFileResponse(msg.opcode);
	if (msg.opcode != FOLDER_NOT_FOUND) {
		sprintf(curDir, msg.payload);
	}
	free(buff);
}

void showRequest(SOCKET sock, char* nameGroup) {
	Message msg;
	char* request = (char*)malloc(sizeof(char) * 255);
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	char* message = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sendMessage(sock, nameGroup, SHOW_REQUEST);
	recvMessage(sock, msg);
	sprintf(request, "");
	request = strtok_s(msg.payload, DELIMETER, &buff);
	while (request != NULL) {
		for (int i = 0; i < 3; i++) {
			if (request == NULL) {
				break;
			}
			cout << request << "\t";
			request = strtok_s(buff, DELIMETER, &buff);
		}
		cout << endl;
	}
	cout << "Enter name to accept ? ";
	cin.getline(buff, 255);
	if (strlen(buff) != 0) {
		sprintf(message, "%s %s", nameGroup, buff);
		sendMessage(sock, message, ACCEPT_REQUEST);
		recvMessage(sock, msg);
	}
}

void showLog(SOCKET sock, char* nameGroup) {
	Message msg;
	char* buff = (char*)malloc(sizeof(char) * BUFF_SIZE);
	sendMessage(sock, nameGroup, SHOW_LOG);
	recvMessage(sock, msg);
	cout << msg.payload;
	free(buff);
}
