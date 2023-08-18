Mock library database server and client programs with inter-process communication accomplished by UNIX sockets

Server maintains a list of books in memory and listens for client connections/ requests on local socket

Client is able to query server for list of books and their status, and check-out/ check-in books using terminal

Build and execution:
Make, start server and then start client

Make
./server
./client

