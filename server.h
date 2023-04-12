#ifndef SERVER_H
#define SERVER_H

#include "library.h"

void handleSig1(int);
void closeAll(LibraryType *);
void serveOneClient(int, LibraryType *);

#endif