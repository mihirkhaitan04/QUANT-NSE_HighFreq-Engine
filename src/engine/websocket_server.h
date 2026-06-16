#pragma once
// ===================================================================
//  websocket_server.h  —  Native Windows WebSocket Server
// ===================================================================
//
//  PURPOSE:
//    Provides a minimal, zero-dependency WebSocket server that 
//    broadcasts raw binary bytes to all connected Web Browsers.
//    
//    This allows the React UI to receive ultra-low latency updates
//    without using slow JSON serialization.
//
// ===================================================================

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <wincrypt.h>
#include <iostream>
#include <string>
#include <vector>

// ===================================================================
// Helper functions for WebSocket Handshake (SHA1 and Base64)
// ===================================================================
class WSHelper {
public:
    static std::string base64Encode(const std::vector<BYTE>& data) {
        static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string out;
        out.reserve(((data.size() + 2) / 3) * 4);
        int val = 0, valb = -6;
        for (BYTE c : data) {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0) {
                out.push_back(b64[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6) out.push_back(b64[((val << 8) >> (valb + 8)) & 0x3F]);
        while (out.size() % 4) out.push_back('=');
        return out;
    }

    static std::vector<BYTE> sha1Hash(const std::string& input) {
        HCRYPTPROV hProv = 0;
        HCRYPTHASH hHash = 0;
        std::vector<BYTE> hash(20);

        if (CryptAcquireContext(&hProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
            if (CryptCreateHash(hProv, CALG_SHA1, 0, 0, &hHash)) {
                CryptHashData(hHash, (BYTE*)input.c_str(), (DWORD)input.length(), 0);
                DWORD hashLen = 20;
                CryptGetHashParam(hHash, HP_HASHVAL, hash.data(), &hashLen, 0);
                CryptDestroyHash(hHash);
            }
            CryptReleaseContext(hProv, 0);
        }
        return hash;
    }

    static std::string generateAcceptKey(const std::string& clientKey) {
        const std::string magic = "258EAFA5-E914-47DA-95CA-C5AB0DC85B11";
        return base64Encode(sha1Hash(clientKey + magic));
    }
};

// ===================================================================
//  WebSocketServer Class
// ===================================================================
class WebSocketServer {
private:
    WinsockInit wsa_; // Automatically starts Winsock for the WebSocket server
    SOCKET listenSocket_;
    std::vector<SOCKET> clients_;

    // Handle an incoming HTTP WebSocket handshake
    void processHandshake(SOCKET clientSocket) {
        char buffer[4096];
        int bytes = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytes <= 0) return;

        buffer[bytes] = '\0';
        std::string request(buffer);

        // Find the Sec-WebSocket-Key
        std::string keyHeader = "Sec-WebSocket-Key: ";
        size_t start = request.find(keyHeader);
        if (start != std::string::npos) {
            start += keyHeader.length();
            size_t end = request.find("\r\n", start);
            std::string clientKey = request.substr(start, end - start);

            // Generate Accept Key
            std::string acceptKey = WSHelper::generateAcceptKey(clientKey);

            // Build HTTP 101 Response
            std::string response = 
                "HTTP/1.1 101 Switching Protocols\r\n"
                "Upgrade: websocket\r\n"
                "Connection: Upgrade\r\n"
                "Sec-WebSocket-Accept: " + acceptKey + "\r\n\r\n";

            send(clientSocket, response.c_str(), (int)response.length(), 0);
            
            // Set client socket to non-blocking
            u_long mode = 1;
            ioctlsocket(clientSocket, FIONBIO, &mode);
            
            clients_.push_back(clientSocket);
            std::cout << "[WS] Web client connected! Total clients: " << clients_.size() << std::endl;
        } else {
            closesocket(clientSocket);
        }
    }

public:
    WebSocketServer(int port) : listenSocket_(INVALID_SOCKET) {
        listenSocket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (listenSocket_ == INVALID_SOCKET) {
            std::cerr << "[WS ERROR] Could not create WebSocket server socket." << std::endl;
            return;
        }

        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(port);

        if (bind(listenSocket_, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
            std::cerr << "[WS ERROR] Bind failed on port " << port << std::endl;
            closesocket(listenSocket_);
            listenSocket_ = INVALID_SOCKET;
            return;
        }

        if (listen(listenSocket_, 5) == SOCKET_ERROR) {
            std::cerr << "[WS ERROR] Listen failed." << std::endl;
            closesocket(listenSocket_);
            listenSocket_ = INVALID_SOCKET;
            return;
        }

        // Make listening socket non-blocking
        u_long mode = 1;
        ioctlsocket(listenSocket_, FIONBIO, &mode);

        std::cout << "[WS] WebSocket Server listening on port " << port << "..." << std::endl;
    }

    ~WebSocketServer() {
        for (SOCKET s : clients_) closesocket(s);
        if (listenSocket_ != INVALID_SOCKET) closesocket(listenSocket_);
    }

    // Call this repeatedly in the main loop to accept new clients
    void poll() {
        SOCKET client = accept(listenSocket_, NULL, NULL);
        if (client != INVALID_SOCKET) {
            processHandshake(client);
        }

        // Clean up disconnected clients (simple check by doing a non-blocking recv)
        for (auto it = clients_.begin(); it != clients_.end(); ) {
            char dump[1];
            int res = recv(*it, dump, 1, MSG_PEEK);
            if (res == 0 || (res == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)) {
                closesocket(*it);
                it = clients_.erase(it);
                std::cout << "[WS] Web client disconnected. Total clients: " << clients_.size() << std::endl;
            } else {
                ++it;
            }
        }
    }

    // Broadcasts raw binary data to all connected web browsers
    void broadcastBinary(const char* data, size_t length) {
        if (clients_.empty()) return;

        std::vector<char> frame;
        frame.push_back((char)0x82); // FIN (0x80) | Binary Opcode (0x02)

        if (length < 126) {
            frame.push_back((char)length);
        } else if (length <= 65535) {
            frame.push_back((char)126);
            frame.push_back((char)((length >> 8) & 0xFF));
            frame.push_back((char)(length & 0xFF));
        } else {
            // Not supporting >64KB frames in this prototype to keep it simple
            return;
        }

        frame.insert(frame.end(), data, data + length);

        for (SOCKET s : clients_) {
            send(s, frame.data(), (int)frame.size(), 0);
        }
    }
};
