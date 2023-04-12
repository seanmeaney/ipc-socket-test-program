#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

void handleCheck(int, RequestType, char *, char *);
void clientMenu(int *);

int main() {
    int socket;
    setupClientSocket(&socket);
    int choice = -1;

    char request[MAX_STR];
    char response[MAX_BUFF];

    while (1) {
        clientMenu(&choice);

        switch (choice) {
            case 1:  // Print books
                sprintf(request, "%d", REQ_RET_BOOKS);
                sendData(socket, request);
                rcvData(socket, response);
                printf("RECEIVED BOOKS:\n%s", response);
                continue;
            case 2:  // Check out a book
                handleCheck(socket, REQ_CHECK_OUT, request, response);
                continue;
            case 3:  // Check in a book
                handleCheck(socket, REQ_CHECK_IN, request, response);
                continue;
            case 0:  // Close everything
                sprintf(request, "%d", REQ_CLOSE);
                sendData(socket, request);
                break;
            default:
                printf("ERROR:  invalid option\n");
        }
        break;
    }
    close(socket);
    return 0;
}
/**
 * @brief handles check in and check out process by sending request, recieving response and displaying confirmation / error message
 * 
 * @param socket in: client socket
 * @param r in: what request to send (ie check in, check out)
 * @param request in: request string (empty or book name)
 * @param response in-out: string to return with server response
 */
void handleCheck(int socket, RequestType r, char *request, char *response) {
    char inputStr[MAX_STR];
    int responseInt;
    int bookID;

    printf("Enter Book id: ");
    fgets(inputStr, sizeof(inputStr), stdin);
    inputStr[strcspn(inputStr, "\n")] = 0;
    sprintf(request, "%d %s", r, inputStr);
    sscanf(inputStr, "%d", &bookID);
    sendData(socket, request);
    rcvData(socket, response);
    sscanf(response, "%d", &responseInt);
    switch (responseInt) {
        case C_OK:
            printf("Book id %d was successfully %s\n", bookID, (r == REQ_CHECK_IN) ? "checked in" : "checked out");
            break;
        case C_BAD_STATUS:
            printf("ERROR:  Book id %d is not %s\n", bookID, (r == REQ_CHECK_IN) ? "checked out" : "checked in");
            break;
        case C_BOOK_NOT_FOUND:
            printf("ERROR:  Book id %d was not found\n", bookID);
            break;
    }
}

void clientMenu(int *choice) {
    int c = -1;
    int numOptions = 3;
    char str[MAX_STR];

    printf("\nMAIN MENU\n");
    printf("  (1) Print books\n");
    printf("  (2) Check out a book\n");
    printf("  (3) Check in a book\n");
    printf("  (0) Exit\n\n");

    printf("Please enter your selection: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = 0;
    sscanf(str, "%d", &c);

    if (c == 0) {
        *choice = c;
        return;
    }

    while (c < 0 || c > numOptions) {
        printf("Please enter your selection: ");
        fgets(str, sizeof(str), stdin);
        sscanf(str, "%d", &c);
    }

    *choice = c;
}
