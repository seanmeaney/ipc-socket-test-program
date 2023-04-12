#ifndef LIBRARY_H
#define LIBRARY_H

#include "defs.h"
#include "books.h"

typedef struct {
    char name[MAX_STR];
    BookListType books;
} LibraryType;

void loadBooks(BookListType *);
void initLibrary(LibraryType **, char *);
int checkOutBook(LibraryType *, int);
int checkInBook(LibraryType *, int);
void cleanupLibrary(LibraryType *);

#endif
