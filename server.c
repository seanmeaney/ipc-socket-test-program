#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "server.h"

#include <unistd.h>

int listenSocket;

int main() {
    LibraryType *lib;
    int clientSocket = 0;
    initLibrary(&lib, "Test");
    setupServerSocket(&listenSocket);
    serveOneClient(clientSocket, lib);
    return 0;
}

/**
 * @brief Closes listening socket and exits server process
 * 
 * @param i exit code
 */
void handleSig1(int i) {
    printf("Shutting down...\n");
    close(listenSocket);
    printf("... done\n");
    exit(i);
}

/**
 * @brief Closes listening socket and deallocates library memory
 * 
 * @param lib   library to free
 */
void closeAll(LibraryType *lib) {
    close(listenSocket);
    cleanupLibrary(lib);
}

/**
 * @brief Serves all requests from client (recieving request's and returning result)
 * 
 * @param clientSocket  clientsocket
 * @param lib           library with books
 */
void serveOneClient(int clientSocket, LibraryType *lib) {
    char requestStr[MAX_STR];
    char resultStr[MAX_BUFF];
    int request;
    int bookID;

    signal(SIGUSR1, handleSig1);
    printf("\nWaiting for connection request...\n");
    acceptConnection(listenSocket, &clientSocket);
    printf("... connected\n");
    while (1) {
        resultStr[0] = 0;
        printf("\nWaiting for message...\n");
        rcvData(clientSocket, requestStr);
        printf("... recieved\n");
        sscanf(requestStr, "%d", &request);
        switch (request) {
            case REQ_RET_BOOKS:
                formatBooks(&lib->books, resultStr);
                sendData(clientSocket, resultStr);
                break;
            case REQ_CHECK_OUT:
                sscanf(&requestStr[2], "%d", &bookID);  //scan starts at third character (request and space before)
                sprintf(resultStr, "%d", checkOutBook(lib, bookID));
                sendData(clientSocket, resultStr);
                break;
            case REQ_CHECK_IN:
                sscanf(&requestStr[2], "%d", &bookID);
                sprintf(resultStr, "%d", checkInBook(lib, bookID));
                sendData(clientSocket, resultStr);
                break;
            case REQ_CLOSE:
                printf("\nShutting down...\n");
                close(clientSocket);
                closeAll(lib);
                printf("... done\n");
                exit(0);
        }
    }
}
