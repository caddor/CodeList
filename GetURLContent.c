//
//  main.cpp
//  SOCKET
//
//  Created by cuddor on 13-3-27.
//  Copyright (c) 2013年 cuddor. All rights reserved.
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
	*windows下使用socket必须用WSAStartup初始化，否则不能调用
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
	*分离url中的主机地址和相对路径
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
	*设定socket参数,并未真正初始化
	*/
	sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	pURL = gethostbyname(host);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = *((unsigned long*)pURL->h_addr);
	addr.sin_port = htons(80);
	/*
	*组织发送到web服务器的信息
	*为何要发送下面的信息请参考HTTP协议的约定
	*/
	strcat(header, "GET ");
	strcat(header, GET);
	strcat(header, " HTTP/1.1\r\n");
	strcat(header, "HOST: ");
	strcat(header, host);
	strcat(header, "\r\nConnection: Close\r\n\r\n");
	/*
	*连接到服务器，发送请求header，并接受反馈（即网页源代码）
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
