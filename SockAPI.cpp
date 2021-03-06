/* SockAPI.cpp
 * ----------------------------------------------------------------------------
 * Copyright (C) 2015 George Mitchell
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/


#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>
#include <cstdio>

#include <algorithm>
#include "SockAPI.hpp"

//#define DEBUG 1
#if DEBUG
#define DPRINTF(...) printf(__VA_ARGS__);
#else
#define DPRINTF(...)
#endif

const std::vector<std::string> API::API_CALLS = 
{"ReadTemp", "AddSchedule", "RemoveSchedule", "ShouldRunHeat", "ShouldRunAC", 
    "ShouldRunFan","TargetTemp", "EnableFan", "DisableFan", "PrintSchedule"};

API::API(bool isServer) : isServer_(isServer)
{
    sock_ = socket(AF_UNIX, SOCK_STREAM, 0);
    // set timeout options for our fancy-schmancy socket
    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    int yes = 1;

    if (setsockopt (sock_, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
        perror("setsockopt failed");

    if (setsockopt (sock_, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
        perror("setsockopt failed\n");
    if (setsockopt (sock_, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout)) < 0)
        perror("setsockopt failed\n");

    struct sockaddr_un addr;
    strcpy(addr.sun_path, "/tmp/api");
    addr.sun_family = AF_UNIX;

    if (isServer)
    {
        // just in case we have a lingering socket
        unlink (addr.sun_path);
        if (bind(sock_, (struct sockaddr*)&addr, strlen(addr.sun_path) + sizeof(addr.sun_family))
                < 0) 
        {
            perror("Bind failed");
            throw "Bind failed";
        }
        if (listen(sock_, 5) < 0) 
        {
            perror("Listen failed");
            throw "Listen failed";
        }
    }
    else
    {
        if (connect(sock_, (struct sockaddr*)&addr, strlen(addr.sun_path) + sizeof(addr.sun_family))
                < 0)
        {
            perror("Connect failed");
            throw "Could not connect to server";
        }
    }
}

bool API::CallFunction(API_CALL call, void* adtlData, size_t dataLen, void* buffer, size_t len)
{
    std::string message = API_CALLS[call];

    if (dataLen > 0) 
    {
        message.append(" ");
        message.append((const char*)adtlData, dataLen);
        DPRINTF("Message capacity: %d, Datalen: %d\n", message.capacity(), dataLen);
    }
    size_t bytesToSend = message.length();
    size_t bytesSent = 0;
   
    DPRINTF("Sending bytes for message: %s\n", API_CALLS[call].c_str());

    ssize_t s = 0;
    while ((bytesSent += s) < bytesToSend)
    {
        s = send(sock_, message.c_str(), bytesToSend, 0);
        if (s < 0) 
        {
            perror("Client send");
            break;
        } 
    } 
    DPRINTF("We sent %d/%d bytes\n", bytesSent, bytesToSend);
    
//    sleep(1);
    if (len > 0) 
    {
        DPRINTF("Pointer: %p\n", buffer);
        ssize_t btRecvd = recv(sock_, buffer, len, 0);
        if (btRecvd < 0) 
        {
            perror("Recv failed");
            return false;
        }
        DPRINTF("Received: %d/%d bytes\n", btRecvd, len);
    }
    close(sock_);
    return true;
}

bool API::CallFunction(API_CALL call)
{
    return this->CallFunction(call, NULL, 0, NULL, 0);
}

void API::Callback(API_CALL call, const void *rcvData, const size_t rcvDataLen, void *&sendData, int *sendDataLen)
{
    // do custom stuff here
    DPRINTF("Call: %s", API_CALLS[call].c_str());
}

void API::CallbackWrapper()
{
    char inBuf[512];

    int nRecv;

    struct sockaddr_un clientAddr;
    unsigned int clientAddrLen = sizeof(clientAddr);

    int clientfd;
    if ((clientfd = accept(sock_, (struct sockaddr*)&clientAddr, &clientAddrLen)) < 0) 
    {
        perror("Connection refused");
        return;
    }

    if ((nRecv = recv(clientfd, inBuf, 512, 0)) > 0)
    {
        DPRINTF("Received %d bytes.\n", nRecv);
        std::string funcName;
        std::string inStr = std::string(inBuf);
        size_t pos = inStr.find_first_of(' ');
        if (pos != std::string::npos)
            funcName = inStr.substr(0, pos);
        else
            funcName = inStr;

        auto itr = std::find (API_CALLS.begin(), API_CALLS.end(), funcName);
        API_CALL call = (API_CALL) (itr - API_CALLS.begin());
        if (itr == API_CALLS.end())
        {
            printf("Could not find call: %s\n", funcName.c_str());
            return;
        }

        std::string recvData;
        if (pos != std::string::npos)
        {
            recvData = inStr.substr(inStr.find_first_of(' ') + 1, inStr.length());
//            printf("RecvData: ");
//            for (size_t i = 0; i < recvData.length(); ++i)
//            {
//                printf("%02X ", recvData[i]);
//            }
//            printf("\n");
        }

        void* sendData;
        int sendDataLen;
        DPRINTF("Calling callback with call: %s\n", API_CALLS[call].c_str());
        this->Callback(call, recvData.c_str(), recvData.length(), sendData, &sendDataLen);

        ssize_t bytesSent = 0;
        DPRINTF("About to reply to client with: %d bytes\n", sendDataLen);
        if (sendDataLen > 0)
        {
            ssize_t s = 0;
            while ((bytesSent += s) < sendDataLen)
            {
                DPRINTF("Before send\n");
                s = send(clientfd, sendData, sendDataLen, 0);
                if (s < 0) perror("Server send failed");
            }
        }
        DPRINTF("Bytes sent: %d/%d\n", bytesSent, sendDataLen);        
    }
    else perror("Odd.");

    close (clientfd);
    shutdown (clientfd, SHUT_RDWR);
}

API::~API()
{
    DPRINTF("Closing socket\n");
    close(sock_);
    shutdown (sock_, SHUT_RDWR);
}

