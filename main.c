#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50

// Arrays to store book details
int bookIDs[MAX_BOOKS] = {0};
char bookTitles[MAX_BOOKS][50];
int bookAvailable[MAX_BOOKS] = {0}; // 1 = available, 0 = borrowed
int totalBooks = 0;

// Arrays to store member details
int memberIDs[MAX_MEMBERS] = {0};
char memberNames[MAX_MEMBERS][50];
int totalMembers = 0;

// Prototype functions
void addBook();
void viewBooks();
void searchBook();
void borrowBook();
void returnBook();
void registerMember();
void viewMembers();

int idExists();


void menu()
{
    int choice;
    do
    {
        printf("\nLibrary Management System\n");
        printf("1. Add a New Book\n");
        printf("2. View All Books\n");
        printf("3. Search for a Book\n");
        printf("4. Borrow a Book\n");
        printf("5. Return a Book\n");
        printf("6. Register a New Member\n");
        printf("7. View Member Details\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch(choice)
        {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: borrowBook(); break;
            case 5: returnBook(); break;
            case 6: registerMember(); break;
            case 7: viewMembers(); break;
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid Choice! Try again.\n");
        }
    }
    while(choice != 8);
}


void addBook()
{
    if(totalBooks >= MAX_BOOKS)
    {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    int id;
    char title[50];

    printf("Enter book ID (positive number): ");
    scanf("%d", &id);
    getchar(); // Consume newline

    if(id <= 0 || idExists(bookIDs, totalBooks, id) != -1)
    {
        printf("Invalid or duplicate Book ID!\n");
        return;
    }

    printf("Enter book title: ");
    fgets(title, 50, stdin);
    title[strcspn(title, "\n")] = 0; // Remove newline

    bookIDs[totalBooks] = id;
    strcpy(bookTitles[totalBooks], title);
    bookAvailable[totalBooks] = 1;
    totalBooks++;

    printf("Book added successfully!\n");
}

int idExists(int arr[], int size, int id)
{
    for(int i = 0; i < size; i++)
    {
        if(arr[i] == id)
        {
            return i;
        }
    }
    return -1;
}

void viewBooks()
{
    if(totalBooks == 0)
    {
        printf("No books available.\n");
        return;
    }

    printf("\nLibrary Books:\n");
    printf("ID\tTitle\t\t\tStatus\n");
    for(int i = 0; i < totalBooks; i++)
    {
        printf("%d\t%-20s\t%s\n", bookIDs[i], bookTitles[i], bookAvailable[i] ? "Available" : "Borrowed");
    }
}

void searchBook()
{
    int choice, id, index = -1;
    char title[50];

    printf("Search by (1) ID or (2) Title: ");
    scanf("%d", &choice);
    getchar();

    if(choice == 1)
    {
        printf("Enter book ID: ");
        scanf("%d", &id);
        index = idExists(bookIDs, totalBooks, id);
    }
    else if(choice == 2)
    {
        printf("Enter book title: ");
        fgets(title, 50, stdin);
        title[strcspn(title, "\n")] = 0;

        for(int i = 0; i < totalBooks; i++)
        {
            if(strcmp(bookTitles[i], title) == 0)
            {
                index = i;
                break;
            }
        }
    }

    if(index != -1)
    {
        printf("Book Found - ID: %d, Title: %s, Status: %s\n", bookIDs[index], bookTitles[index], bookAvailable[index] ? "Available" : "Borrowed");
    }
    else
    {
        printf("Book not found.\n");
    }
}

void borrowBook()
{
    int bookID, memberID, bookIndex, memberIndex;

    printf("Enter Member ID: ");
    scanf("%d", &memberID);
    memberIndex = idExists(memberIDs, totalMembers, memberID);

    if(memberIndex == -1)
    {
        printf("Member not found. Register first!\n");
        return;
    }

    printf("Enter Book ID to borrow: ");
    scanf("%d", &bookID);
    bookIndex = idExists(bookIDs, totalBooks, bookID);

    if(bookIndex == -1)
    {
        printf("Book does not exist.\n");
    }
    else if(!bookAvailable[bookIndex])
    {
        printf("Book is already borrowed.\n");
    }
    else
    {
        bookAvailable[bookIndex] = 0;
        printf("Book borrowed successfully!\n");
    }
}

void returnBook()
{
    int bookID, bookIndex;

    printf("Enter Book ID to return: ");
    scanf("%d", &bookID);
    bookIndex = idExists(bookIDs, totalBooks, bookID);

    if(bookIndex == -1)
    {
        printf("Invalid book ID.\n");
    }
    else if(bookAvailable[bookIndex])
    {
        printf("Book is not borrowed.\n");
    }
    else
    {
        bookAvailable[bookIndex] = 1;
        printf("Book returned successfully!\n");
    }
}

void registerMember()
{
    if(totalMembers >= MAX_MEMBERS)
    {
        printf("Member registration full!\n");
        return;
    }

    int id;
    char name[50];

    printf("Enter Member ID (positive number): ");
    scanf("%d", &id);
    getchar();

    if(id <= 0 || idExists(memberIDs, totalMembers, id) != -1)
    {
        printf("Invalid or duplicate Member ID!\n");
        return;
    }

    printf("Enter Member Name: ");
    fgets(name, 50, stdin);
    name[strcspn(name, "\n")] = 0;

    memberIDs[totalMembers] = id;
    strcpy(memberNames[totalMembers], name);
    totalMembers++;

    printf("Member registered successfully!\n");
}

void viewMembers()
{
    if(totalMembers == 0)
    {
        printf("No members registered.\n");
        return;
    }

    printf("\nRegistered Members:\n");
    printf("ID\tName\n");
    for(int i = 0; i < totalMembers; i++)
    {
        printf("%d\t%s\n", memberIDs[i], memberNames[i]);
    }
}

// Main function
int main()
{
    menu();
    return 0;
}