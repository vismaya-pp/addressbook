#include <stdio.h>
#include "contact.h"

int main() {
    int choice, sortChoice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book
    char *strline = "------------------------------------------------------";
    do {
        printf("%s\n%20s\n%s\n", strline,"Address Book Menu", strline);
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save and Exit\n");		
        printf("%s\n", strline);
        printf("Enter your choice : ");
       
       if(scanf("%d", &choice)!=1)
        {
            printf("Invalid input! Please enter a number.\n");
            fpurge(stdin); // clear input buffer
            continue;
        }
        fpurge(stdin);
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
               listContacts(&addressBook, sortChoice);
                break;
            case 6:
                printf("Saving and Exiting...\n");
                saveContactsToFile(&addressBook);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);
    
       return 0;
}