//
//  main.cpp
//  SOCKET
//
//  Created by cuddor on 13-3-27.
//  Copyright (c) 2013�� cuddor. All rights reserved.
//
#include "StdAfx.h"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
#ifdef WIN32
#include<winsock.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<unistd.h>
#define SOCKET int
#endif

string GetURLContents(char *url)
{
	intsockfd;
	struct sockaddr_inaddr;
	struct hostent*pURL;
	charmyurl[BUFSIZ]="";
	char*pHost = 0;
	charhost[BUFSIZ]="", GET[BUFSIZ]="";
	charheader[BUFSIZ] = "";
	chartext[BUFSIZ];
	/*
	*windows��ʹ��socket������WSAStartup��ʼ���������ܵ���
	*/
#ifdef WIN32
	WSADATA WSAData={0};
	if(WSAStartup(MAKEWORD(2,2), &WSAData))
	{
		printf("WSA failed\n");
		return "";
	}
#endif
	/*
	*����url�е�������ַ�����·��
	*/
	strcpy(myurl, url);
	for (pHost = myurl; *pHost != '/' && *pHost != '\0'; ++pHost);
	if ( (int)(pHost - myurl) == strlen(myurl) )
		strcpy(GET, "/");
	else
		strcpy(GET, pHost);
	*pHost = '\0';
	strcpy(host, myurl);
	printf("%s\n%s\n", host, GET);
	/*
	*�趨socket����,��δ������ʼ��
	*/
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	pURL = gethostbyname(host);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
	addr.sin_port = htons(80);
	/*
	*��֯���͵�web����������Ϣ
	*Ϊ��Ҫ�����������Ϣ��ο�HTTPЭ���Լ��
	*/
	strcat(header, "GET ");
	strcat(header, GET);
	strcat(header, " HTTP/1.1\r\n");
	strcat(header, "HOST: ");
	strcat(header, host);
	strcat(header, "\r\nConnection: Close\r\n\r\n");
	/*
	*���ӵ�����������������header�������ܷ���������ҳԴ���룩
	*/
	connect(sockfd,(struct sockaddr *)&addr,sizeof(addr));
	send(sockfd, header, strlen(header), 0);
	string strData="";
	while ( recv(sockfd, text, BUFSIZ, 0) > 0)
	{
        //printf("%s", text);
		strData.append(text);
		memset(text, 0, BUFSIZ);
	}
    
#ifdef WIN32
	closesocket(sockfd);
	WSACleanup();
#else
    close(sockfd);
#endif
    return strData;
}

int main()
{
	charurl[256];
	printf("http://");
	scanf("%s", url);
	printf(GetURLContents(url).c_str());
	return 0;
} 
