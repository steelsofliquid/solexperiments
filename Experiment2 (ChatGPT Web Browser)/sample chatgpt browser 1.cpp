#include <iostream>
#include <string>
#include <winsock2.h>
#include <windows.h>
using namespace std;

// Define a function to send an HTTP request and receive the response
string sendHTTPRequest(string host, string path) {
    // Create a TCP socket and connect to the server
    SOCKET sock;
    struct sockaddr_in server;
    char message[1000], response[2000];
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        return "Error initializing Winsock";
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return "Error creating socket";
    }
    server.sin_addr.s_addr = inet_addr(host.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(80);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return "Error connecting to server";
    }

    // Send an HTTP request to the server
    sprintf(message, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", path.c_str(), host.c_str());
    if (send(sock, message, strlen(message), 0) < 0) {
        return "Error sending HTTP request";
    }

    // Receive the response from the server
    int bytesRead;
    string responseStr = "";
    while ((bytesRead = recv(sock, response, 2000, 0)) > 0) {
        responseStr += string(response, bytesRead);
    }

    // Close the socket and return the response
    closesocket(sock);
    return responseStr;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Send an HTTP request and display the response in a message box
    string host = "www.example.com";
    string path = "/";
    string response = sendHTTPRequest(host, path);
    MessageBox(NULL, response.c_str(), "Web Page", MB_OK);

    return 0;
}

