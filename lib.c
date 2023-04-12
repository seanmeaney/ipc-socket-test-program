#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"

/**
 * @brief Reads book data from booksData.txt and generates unique id for each book, initializes books and assigns values
 * 
 * @param books    list of books
 */
void loadBooks(BookListType *books) {
    FILE *infile;
    char title[MAX_STR];
    char author[MAX_STR];
    int baseID = 1001;
    int year;
    int status;
    infile = fopen("booksData.txt", "r");

    if (!infile) {
        printf("Error: could not open file\n");
        exit(1);
    }
    while (1) {
        BookType *new;
        fgets(title, sizeof(title), infile);
        if (feof(infile)) {  //because empty line at end, idk if the test data will always have empty line
            break;
        }
        title[strcspn(title, "\n")] = 0;
        fgets(author, sizeof(author), infile);
        author[strcspn(author, "\n")] = 0;
        fscanf(infile, "%d%d%*c", &year, &status);
        initBook(baseID, title, author, year, status, &new);
        addBook(books, new);
        if (feof(infile)) {
            break;
        }
        baseID++;
    }
    fclose(infile);
}

/**
 * @brief Initialize library, allocates memory, loads book data and prints the data of all books
 * 
 * @param library   uninitialized library variable
 * @param n         name for library
 */
void initLibrary(LibraryType **library, char *n) {
    (*library) = malloc(sizeof(LibraryType));
    strcpy(&(*library)->name[0], n);
    initList(&(*library)->books);
    loadBooks(&(*library)->books);
    char bookStr[MAX_BUFF] = "";
    formatBooks(&(*library)->books, bookStr);
    printf("BOOKS:\n%s", bookStr);
}

/**
 * @brief Searches for for book in library, and marks it checked out if found and valid (currently checked in)
 * 
 * @param lib       library struct containing list of books
 * @param bookId    bookid to search for
 * @return          int success flag C_OK if found and valid, C_BAD_STATUS if invalid and C_BOOK_NOT_FOUND if not found
 */
int checkOutBook(LibraryType *lib, int bookId) {
    BookType *b;
    findBook(&lib->books, bookId, &b);
    if (b != NULL) {
        if (b->status == CHECKED_IN) {
            b->status = CHECKED_OUT;
            return C_OK;
        } else {
            return C_BAD_STATUS;
        }
    } else {
        return C_BOOK_NOT_FOUND;
    }
}

/**
 * @brief Searches for for book in library, and marks it checked in if found and valid (currently checked out)
 * 
 * @param lib       library struct containing list of books
 * @param bookId    bookid to search for
 * @return          int success flag C_OK if found and valid, C_BAD_STATUS if invalid and C_BOOK_NOT_FOUND if not found
 */
int checkInBook(LibraryType *lib, int bookId) {
    BookType *b;
    findBook(&lib->books, bookId, &b);
    if (b != NULL) {
        if (b->status == CHECKED_OUT) {
            b->status = CHECKED_IN;
            return C_OK;
        } else {
            return C_BAD_STATUS;
        }
    } else {
        return C_BOOK_NOT_FOUND;
    }
}

/**
 * @brief Deallocates all memory for books and library
 * 
 * @param lib library struct to free
 */
void cleanupLibrary(LibraryType *lib) {
    cleanupList(&lib->books);
    free(lib);
}