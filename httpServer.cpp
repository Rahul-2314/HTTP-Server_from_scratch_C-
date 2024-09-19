#include <iostream>
#include <winsock2.h>
// #pragma comment(lib, "ws2_32.lib") // Link with Winsock library

#define PORT 8080

void handle_client(SOCKET client_socket){
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Request:\n"
              << buffer << std::endl;

    // HTTP response
    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    send(client_socket, response.c_str(), response.size(), 0);
    closesocket(client_socket);
}

int main(){
    
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa); // Initialize Winsock

    SOCKET server_fd, client_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind socket to IP/Port
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);

    std::cout << "Server is running on port " << PORT << "...\n";

    // Main loop to handle incoming connections
    while ((client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) != INVALID_SOCKET)
    {
        handle_client(client_socket);
    }

    closesocket(server_fd);
    WSACleanup(); // Cleanup Winsock

    return 0;
}
