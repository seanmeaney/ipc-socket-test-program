#ifndef BOOKS_H
#define BOOKS_H

#include <stdio.h>
#include <string.h>

#include "defs.h"


typedef struct {
    int id;
    char title[MAX_STR];
    char author[MAX_STR];
    int year;
    BookStatusType status;
} BookType;

typedef struct Node {
    BookType *data;
    struct Node *next;
} NodeType;

typedef struct {
    NodeType *head;
    NodeType *tail;
} BookListType;

void initList(BookListType *);
void cleanupList(BookListType *);
void initBook(int, char *, char *, int, BookStatusType, BookType **);
void addBook(BookListType *, BookType *);
int findBook(BookListType *, int, BookType **);
void formatBook(BookType *, char *);
void formatBooks(BookListType *, char *);

char *convertBookStatus(BookStatusType *);

#endif