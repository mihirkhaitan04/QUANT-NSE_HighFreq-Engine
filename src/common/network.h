#pragma once
// ===================================================================
//  network.h  —  Simple TCP Socket Wrapper for Windows (Winsock2)
// ===================================================================
//
//  PURPOSE:
//    This file hides ALL the complicated Windows networking code.
//    You only use two simple classes:
//
//      SocketServer  →  Listens on a port, waits for a client to connect.
//      SocketClient  →  Connects to a server at a given IP and port.
//
//    Both classes have simple send() and receive() methods.
//
//  HOW WINDOWS NETWORKING WORKS (in plain English):
//    1. Call WSAStartup()  → Tells Windows: "I want to use the network."
//    2. Create a "socket"  → Think of it as a phone. You need one to talk.
//    3. connect() or bind()+listen()+accept() → Dial or wait for a call.
//    4. send() / recv()    → Talk and listen on the phone.
//    5. closesocket()      → Hang up.
//    6. WSACleanup()       → Tell Windows: "I'm done with networking."
//
// ===================================================================

// --- Windows Networking Headers ---
// These MUST be included in this exact order.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN   // Prevents Windows from including extra junk
#endif
#include <winsock2.h>         // Core Winsock2 functions (socket, send, recv)
#include <ws2tcpip.h>         // IP address conversion functions (inet_pton)

// --- Standard C++ Headers ---
#include <iostream>
#include <string>


// ===================================================================
//  WinsockInit  —  Starts/stops the Windows networking system
// ===================================================================
//  This is called automatically by SocketServer and SocketClient.
//  You never need to touch this directly.
// ===================================================================
class WinsockInit {
public:
    // Constructor: called when the object is created
    WinsockInit() {
        WSADATA wsaData;                           // Holds info about Winsock
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);  // Start Winsock 2.2
        if (result != 0) {
            std::cerr << "[ERROR] WSAStartup failed: " << result << std::endl;
        }
    }

    // Destructor: called automatically when the object goes out of scope
    ~WinsockInit() {
        WSACleanup();   // Tell Windows we are done with the network
    }
};


// ===================================================================
//  SocketServer  —  A TCP server that listens for ONE client
// ===================================================================
//
//  Usage:
//    SocketServer server(9038);          // Listen on port 9038
//    if (server.waitForClient()) {       // Block until a client connects
//        int n = server.receive(buf, 1024);  // Read data from client
//        server.sendData(buf, n);             // Send data back to client
//    }
//
// ===================================================================
class SocketServer {
private:
    WinsockInit   wsa_;            // Automatically starts Winsock
    SOCKET        listenSocket_;   // The "phone" waiting for incoming calls
    SOCKET        clientSocket_;   // The "phone line" to the connected client

public:
    // Constructor: create the server and start listening on the given port
    SocketServer(int port) : listenSocket_(INVALID_SOCKET), clientSocket_(INVALID_SOCKET) {

        // Step 1: Create a socket (a "phone")
        listenSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        //   AF_INET     = We are using IPv4 internet addresses
        //   SOCK_STREAM = We want TCP (reliable, ordered data)
        //   IPPROTO_TCP = Specifically the TCP protocol

        if (listenSocket_ == INVALID_SOCKET) {
            std::cerr << "[ERROR] Could not create server socket." << std::endl;
            return;
        }

        // Step 2: Bind the socket to a port (like assigning a phone number)
        sockaddr_in serverAddr;                        // Holds the address info
        serverAddr.sin_family      = AF_INET;          // IPv4
        serverAddr.sin_addr.s_addr = INADDR_ANY;       // Accept connections from anyone
        serverAddr.sin_port        = htons(port);      // Convert port to network byte order

        if (bind(listenSocket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "[ERROR] Bind failed on port " << port << std::endl;
            closesocket(listenSocket_);
            listenSocket_ = INVALID_SOCKET;
            return;
        }

        // Step 3: Start listening (like turning on the ringer)
        if (listen(listenSocket_, 1) == SOCKET_ERROR) {
            std::cerr << "[ERROR] Listen failed." << std::endl;
            closesocket(listenSocket_);
            listenSocket_ = INVALID_SOCKET;
            return;
        }

        std::cout << "[SERVER] Listening on port " << port << " ..." << std::endl;
    }

    // Destructor: clean up all sockets
    ~SocketServer() {
        if (clientSocket_ != INVALID_SOCKET) closesocket(clientSocket_);
        if (listenSocket_ != INVALID_SOCKET) closesocket(listenSocket_);
    }

    // Block and wait until a client connects. Returns true on success.
    bool waitForClient() {
        std::cout << "[SERVER] Waiting for a client to connect..." << std::endl;
        clientSocket_ = accept(listenSocket_, NULL, NULL);  // Blocks here
        if (clientSocket_ == INVALID_SOCKET) {
            std::cerr << "[ERROR] Accept failed." << std::endl;
            return false;
        }
        std::cout << "[SERVER] Client connected!" << std::endl;
        return true;
    }

    // Receive data from the connected client.
    // Returns the number of bytes received, or -1 on error.
    int receive(char* buffer, int bufferSize) {
        int bytesRead = recv(clientSocket_, buffer, bufferSize, 0);
        if (bytesRead == SOCKET_ERROR) {
            std::cerr << "[ERROR] recv failed." << std::endl;
            return -1;
        }
        return bytesRead;
    }

    // Send data back to the connected client.
    // Returns true on success.
    bool sendData(const char* data, int length) {
        int bytesSent = send(clientSocket_, data, length, 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "[ERROR] send failed." << std::endl;
            return false;
        }
        return true;
    }

    // Check if the server was created successfully
    bool isValid() const { return listenSocket_ != INVALID_SOCKET; }
};


// ===================================================================
//  SocketClient  —  Connects to a TCP server (non-blocking receive)
// ===================================================================
//
//  Usage:
//    SocketClient client("127.0.0.1", 9038);     // Connect to localhost
//    if (client.isConnected()) {
//        client.sendData(buf, length);            // Send binary data
//        int n = client.receive(buf, 1024);       // Non-blocking read
//    }
//
// ===================================================================
class SocketClient {
private:
    WinsockInit   wsa_;          // Automatically starts Winsock
    SOCKET        socket_;       // Our connection to the server
    bool          connected_;    // Are we currently connected?

public:
    // Constructor: connect to the server at the given IP and port
    SocketClient(const std::string& ip, int port) : socket_(INVALID_SOCKET), connected_(false) {

        // Step 1: Create a socket
        socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socket_ == INVALID_SOCKET) {
            std::cerr << "[ERROR] Could not create client socket." << std::endl;
            return;
        }

        // Step 2: Set up the server address we want to connect to
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port   = htons(port);

        // Convert the IP string (e.g. "127.0.0.1") to a binary address
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        if (serverAddr.sin_addr.s_addr == INADDR_NONE) {
            std::cerr << "[ERROR] Invalid IP address: " << ip << std::endl;
            closesocket(socket_);
            socket_ = INVALID_SOCKET;
            return;
        }

        // Step 3: Connect to the server (like dialing a phone number)
        std::cout << "[CLIENT] Connecting to " << ip << ":" << port << " ..." << std::endl;
        if (connect(socket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "[ERROR] Could not connect to server." << std::endl;
            closesocket(socket_);
            socket_ = INVALID_SOCKET;
            return;
        }

        // Step 4: Make the socket NON-BLOCKING for receive
        //   This means recv() will return immediately even if no data arrived yet,
        //   instead of freezing the program while waiting.
        u_long mode = 1;   // 1 = non-blocking, 0 = blocking
        ioctlsocket(socket_, FIONBIO, &mode);

        connected_ = true;
        std::cout << "[CLIENT] Connected successfully!" << std::endl;
    }

    // Destructor: close the socket
    ~SocketClient() {
        if (socket_ != INVALID_SOCKET) closesocket(socket_);
    }

    // Send data to the server. Returns true on success.
    bool sendData(const char* data, int length) {
        int bytesSent = send(socket_, data, length, 0);
        if (bytesSent == SOCKET_ERROR) {
            std::cerr << "[ERROR] send failed." << std::endl;
            return false;
        }
        return true;
    }

    // Receive data from the server (NON-BLOCKING).
    //   Returns number of bytes read.
    //   Returns  0 if no data is available yet (try again later).
    //   Returns -1 on error or disconnection.
    int receive(char* buffer, int bufferSize) {
        int bytesRead = recv(socket_, buffer, bufferSize, 0);

        if (bytesRead == SOCKET_ERROR) {
            int err = WSAGetLastError();
            // WSAEWOULDBLOCK means "no data right now" — this is normal
            if (err == WSAEWOULDBLOCK) {
                return 0;   // Nothing arrived yet, not an error
            }
            std::cerr << "[ERROR] recv failed: " << err << std::endl;
            return -1;
        }

        if (bytesRead == 0) {
            // Server closed the connection
            std::cout << "[CLIENT] Server disconnected." << std::endl;
            connected_ = false;
            return -1;
        }

        return bytesRead;
    }

    // Check if we are still connected
    bool isConnected() const { return connected_; }
};
