#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/**
 * @brief Initializes the book list to null values
 * 
 * @param list in-out: BookList to initialize
 */
void initList(BookListType *list) {
    list->head = NULL;
    list->tail = NULL;
}

/**
 * @brief Creates a new node, allocates memory and handles pointers for list continuity
 * 
 * @param prev in: previous node in list
 * @param next in: next node in list
 * @param data in: book data to be assigned to new node
 * @return out: NodeType* newly created node
 */
NodeType *initNode(NodeType *prev, NodeType *next, BookType *data) {
    NodeType *n;
    n = malloc(sizeof(NodeType));
    n->data = data;
    n->next = next;
    if (prev != NULL) {
        prev->next = n;
    }
    return n;
}

/**
 * @brief Convert value of BookStatusType enum to string representation
 * 
 * @param s in: BookStatusType
 * @return out: string representation
 */
char *convertBookStatus(BookStatusType *s) {
    switch (*s) {
        case CHECKED_IN:
            return "Checked in";
        case CHECKED_OUT:
            return "Checked out";
        case UNDER_REPAIR:
            return "Under repair";
        case LOST:
            return "Lost";
        default:
            return "Unknown";
    }
}

/**
 * @brief Free dynamically allocated memory allocated for list and node data
 * 
 * @param list in: list with allocated memory
 */
void cleanupList(BookListType *list) {
    NodeType *current = list->head;
    NodeType *next;
    while (current != NULL) {
        next = current->next;
        free(current->data);
        free(current);
        current = next;
    }
}

/**
 * @brief Adds book in its correct position in list (ascending order by title)
 * 
 * @param list in-out: current list
 * @param b in: new book
 */
void addBook(BookListType *list, BookType *b) {
    NodeType *current = list->head;
    if (current == NULL) {
        list->head = initNode(NULL, NULL, b);
        list->tail = list->head;
    } else if (strcmp(current->data->title, b->title) > 0) {
        list->head = initNode(NULL, current, b);
    } else if (strcmp(list->tail->data->title, b->title) <= 0) {
        list->tail = initNode(list->tail, NULL, b);
    } else {
        while (current != NULL) {
            if (strcmp(current->next->data->title, b->title) > 0) {
                initNode(current, current->next, b);
                break;
            }
            current = current->next;
        }
    }
}

/**
 * @brief finds book with given id in list
 * 
 * @param list in: list to search
 * @param id in: id for book to find
 * @param b in-out: book if found
 * @return out: int C_OK if book found and C_BOOK_NOT_FOUND if not
 */
int findBook(BookListType *list, int id, BookType **b) {
    NodeType *current = list->head;
    while (current != NULL) {
        if (current->data->id == id) {
            *b = current->data;
            return C_OK;
        }
        current = current->next;
    }
    *b = NULL;
    return C_BOOK_NOT_FOUND;
}

/**
 * @brief formats all book data into a string
 * 
 * @param b in: book to be formated
 * @param outStr in-out: formatted book data
 */
void formatBook(BookType *b, char *outStr) {
    sprintf(outStr, "%04d : %-37s : %-18s : %04d : %s\n", b->id, b->title, b->author, b->year, convertBookStatus(&b->status));
}

/**
 * @brief formats the data of all books into a single string
 * 
 * @param list in: list of books
 * @param outStr in-out: formatted data for all books in list
 */
void formatBooks(BookListType *list, char *outStr) {
    NodeType *current = list->head;
    char bookStr[MAX_BUFF];
    while (current != NULL) {
        formatBook(current->data, bookStr);
        strcat(outStr, bookStr);
        current = current->next;
    }
    formatBook(list->head->data, bookStr);
    strcat(outStr, "-- Head: ");
    strcat(outStr, bookStr);
    formatBook(list->tail->data, bookStr);
    strcat(outStr, "-- Tail: ");
    strcat(outStr, bookStr);
}

/**
 * @brief initialize a new book data type to passed values and allocate memory
 * 
 * @param i in: book id
 * @param t in: book title
 * @param a in: book author
 * @param y in: book published year
 * @param st in: book status
 * @param book in-out: book
 */
void initBook(int i, char *t, char *a, int y, BookStatusType st, BookType **book) {
    (*book) = malloc(sizeof(BookType));
    (*book)->id = i;
    strcpy((*book)->title, t);
    strcpy((*book)->author, a);
    (*book)->year = y;
    (*book)->status = st;
}