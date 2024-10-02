#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define FILE_NAME "library.txt"

// Structure to store book information
typedef struct {
    int id;
    char title[100];
    char author[100];
    int available;
} Book;

Book library[MAX_BOOKS];
int bookCount = 0;

// Load books from file
void loadBooks() {
    FILE *file = fopen(FILE_NAME, "r");
    if (file) {
        while (fscanf(file, "%d %99[^\n] %99[^\n] %d", &library[bookCount].id, library[bookCount].title, library[bookCount].author, &library[bookCount].available) == 4) {
            bookCount++;
        }
        fclose(file);
    }
}

// Save books to file
void saveBooks() {
    FILE *file = fopen(FILE_NAME, "w");
    if (file) {
        for (int i = 0; i < bookCount; i++) {
            fprintf(file, "%d %s %s %d\n", library[i].id, library[i].title, library[i].author, library[i].available);
        }
        fclose(file);
    }
}

// Add a new book
void addBook() {
    if (bookCount < MAX_BOOKS) {
        Book newBook;
        newBook.id = bookCount + 1;

        // Get book title and author
        printf("Enter title: ");
        getchar();
        fgets(newBook.title, sizeof(newBook.title), stdin);
        newBook.title[strcspn(newBook.title, "\n")] = '\0';

        printf("Enter author: ");
        fgets(newBook.author, sizeof(newBook.author), stdin);
        newBook.author[strcspn(newBook.author, "\n")] = '\0';

        newBook.available = 1;
        library[bookCount] = newBook;
        bookCount++;
        saveBooks();
        printf("Book added successfully!\n");
    } else {
        printf("Library is full!\n");
    }
}

// Display all books
void displayBooks() {
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d, Title: %s, Author: %s, Available: %d\n", library[i].id, library[i].title, library[i].author, library[i].available);
    }
}

// Delete a book by ID
void deleteBook() {
    int id;
    printf("Enter book ID to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            saveBooks();
            printf("Book deleted successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

int main() {
    loadBooks();
    int choice;
    while (1) {
        printf("--------------------------Library system managment-----------------------------\n");
        printf("1. Add Book\n2. Display Books\n3. Delete Book\n4. Exit\nEnter your choice: \n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
