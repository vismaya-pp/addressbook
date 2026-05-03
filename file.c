#include <stdio.h>
#include<stdlib.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
    FILE *fp;
    int i;
     fp=fopen("contacts.csv", "w"); //open file in read 
    if(fp == NULL)
    {
        printf("Error: Unable to open file!\n");
        //return;

    }
     fprintf(fp, "%d\n", addressBook->contactCount);

     for(i=0; i<addressBook->contactCount; i++)
     {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
     }  
        fclose(fp);
        printf("Contact saved Successfully.\n");

    exit(0); 
}

void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fp;
    int i;

    fp=fopen("contacts.csv", "r"); //open file in read 
    if(fp==NULL)
    {
        printf("Error: File not found!\n");
        return;

    }
    fscanf(fp, "%d", &addressBook->contactCount); //read contact count

    fseek(fp, 1, SEEK_CUR); //skip 1 bytes from current position

    for(i=0; i<addressBook->contactCount; i++)
    {
        //read contact details
    fscanf(fp, "%[^,],%[^,],%[^\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
       fseek(fp, 1, SEEK_CUR);// skip newline or skip 1 bytes
    }
    
    fclose(fp); //close file
}
