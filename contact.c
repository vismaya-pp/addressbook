#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"


void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    int i,j;
    Contact temp;
    char *strline="----------------------------------------------------------------";
     printf("\n%30s\n", "Contact List");
     printf("\n%s\n%-20s %-15s %-25s\n%s\n", strline, "Name", "Phone", "Email", strline);
     
    for(i=0;i<addressBook->contactCount;i++)
    {
    printf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("%s\n", strline);

       do
       {
          // Sort contacts based on the chosen criteria
        printf("\nSort Criteria:\n");
        printf("1.Sort by Name\n");
        printf("2.Sort by Phone\n");
        printf("3.Sort by Email \n");
        printf("Enter Your Choice : ");
        if(scanf("%d",&sortCriteria)!=1)
        {
         printf("Invalid choice! Please enter a Number.\n");
         fpurge(stdin); // clear input buffer
         sortCriteria=0;
        continue;
        }
        fpurge(stdin);
        
          if (sortCriteria<1 || sortCriteria>3)
            {
            printf("Invalid choice! Try again.\n");
            }
        
       } while(sortCriteria<1 || sortCriteria>3);
        switch(sortCriteria){
        case 1:
            for(i=0;i<addressBook->contactCount-1;i++){
                for(j=0;j<addressBook->contactCount-1-i;j++){
                    if((strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)){
                         temp = addressBook->contacts[j];
                         addressBook->contacts[j] = addressBook->contacts[j+1];
                         addressBook->contacts[j+1] = temp;
                    }
                }
            }
            break;
            case 2:
            for(i=0;i<addressBook->contactCount-1;i++){
                for(j=0;j<addressBook->contactCount-1-i;j++){
                    if((strcmp(addressBook->contacts[j].phone,addressBook->contacts[j+1].phone)>0)){
                         temp = addressBook->contacts[j];
                         addressBook->contacts[j] = addressBook->contacts[j+1];
                         addressBook->contacts[j+1] = temp;
                    }
                }
            }
            break;
            case 3:
            for(i=0;i<addressBook->contactCount-1;i++){
                for(j=0;j<addressBook->contactCount-1-i;j++){
                    if((strcmp(addressBook->contacts[j].email,addressBook->contacts[j+1].email)>0)){
                         temp = addressBook->contacts[j];
                         addressBook->contacts[j] = addressBook->contacts[j+1];
                         addressBook->contacts[j+1] = temp;
                    }
                }
            }
            break;
        }
  printf("After sorting\n");
  printf("\n%30s\n", "Contact List");
  printf("\n%s\n%-20s %-15s %-25s\n%s\n", strline, "Name", "Phone", "Email", strline);
  for(i=0;i<addressBook->contactCount;i++)
  {
    printf("%-20s %-15s %-25s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);  
  }
  printf("%s\n", strline);
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
     char phone[11], email[50];
     int res, ret;
    
    int index = addressBook->contactCount; 
    
    printf("Enter the Name : ");  //read name from user
    scanf(" %[^\n]", addressBook->contacts[index].name);
    
    do
    {
          printf("Enter the Phone Number : "); // read phone number
            //scanf(" %[^\n]",addressBook->contacts[index].phone);
           scanf(" %[^\n]", phone);

       res=validatePhone(addressBook, phone);

          if(res==0)
             {
               printf("Invalid Phone Number! Try again.\n");
        
             }
       
        
    } while(res==0);
            
      strcpy(addressBook->contacts[index].phone, phone);
   do
   {
    printf("Enter the Email : "); //read email id
    //scanf(" %[^\n]",addressBook->contacts[index].email);
    scanf(" %[^\n]", email);

    ret=validateEmail(addressBook, email);

        if(ret==0)
        {
            printf("Invalid Email ID! Try again\n");
            
        
        } 
    }while(ret==0);
        
            strcpy(addressBook->contacts[index].email, email);


    addressBook->contactCount++; //store into database

    printf("Contact Created Successfully.\n");   
}


int searchContact(AddressBook *addressBook) 
{  
    /* Define the logic for search */
    int choice;
    char phone[11];
    char email[50];
    char name[50];
    char *strline= "---------------------------------------------------------------";
   
      do
      { //print the choice
        printf("\n Search Criteria:\n");
        printf("1. Search by Name\n");
        printf("2. Search by Phone Number\n");
        printf("3. Search by Email\n");
        printf("Enter the Choice : ");
        if(scanf("%d",&choice)!=1)
        {
         printf("Invalid choice! Please enter a Number.\n");
        fpurge(stdin); // clear input buffer
        choice=0;
        continue;
        }
        fpurge(stdin);
        
        if (choice<1 || choice>3)
        {
         printf("Invalid choice! Try again.\n");
        }
        
       } while(choice<1 || choice>3);

        switch(choice)
        {
        case 1:
          printf("Enter Name To Search : ");
          scanf(" %[^\n]", name);

          for(int i=0; i<addressBook->contactCount; i++)
          {
            if(strcmp(addressBook->contacts[i].name, name)==0)
            {
                printf("\n%-5s %-20s %-15s %-25s\n%s\n", "Index", "Name", "Phone", "Email", strline);
                printf("%-5d %-20s %-15s %-25s\n%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email, strline);
                return i;
            }
          }
             break;
            
        case 2: 
            printf("Enter Phone Number To Search : ");
            scanf(" %[^\n]", phone);
    
             for(int i=0; i<addressBook->contactCount; i++)
             {
                if(strcmp(addressBook->contacts[i].phone, phone)==0)
                {
                    printf("\n%-5s %-20s %-15s %-25s\n%s\n", "Index", "Name", "Phone", "Email", strline);
                    printf("%-5d %-20s %-15s %-25s\n%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email, strline);
                    return i;
                }
             }
            
             break;
            
        case 3:
            printf("Enter Email to Search : ");
             scanf(" %[^\n]", email);

             for(int i=0; i<addressBook->contactCount; i++)
             {
                if(strcmp(addressBook->contacts[i].email, email)==0)
                {
                    printf("\n%-5s %-20s %-15s %-25s\n%s\n", "Index", "Name", "Phone", "Email", strline);
                    printf("%-5d %-20s %-15s %-25s\n%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email, strline);
                    return i;
                }
             }
            
             break;
        
        }

        printf("Contact not Found!.\n");
        return -1;


}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
int index, choice, res, ret;
char phone[11], email[50];

    index = searchContact(addressBook);//call search function
   if(index==-1)
    {
        printf("No Results.\n");
        return; //back to main menu
    }
    do
    {
    
    printf("Editing contact at index %d\n", index);//index of contact
    //read the choice
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice : ");
    if(scanf("%d",&choice)!=1)
        {
         printf("Invalid choice! Please enter a Number.\n");
         fpurge(stdin); // clear input buffer
        choice=0;
        continue;
        }
     fpurge(stdin); // clear input buffer
        if (choice<1 || choice>3)
        {
            printf("Invalid choice! Try again.\n");
        }
        
       } while(choice<1 || choice>3);
    switch (choice)
    {
        case 1: 
        printf("Enter New Name : "); //read the name
        scanf(" %[^\n]", addressBook->contacts[index].name);

        printf("Edit Name Successfully.\n"); 
        break;

       case 2: 
       do
       {
        printf("Enter New Phone Number : ");
        //scanf(" %[^\n]", addressBook->contacts[index].phone);
         //read the phone number
        scanf(" %[^\n]", phone);
        res=validatePhone(addressBook, phone);
        if(res==0)
        {
            printf("Invalid Phone Number!\n");
        }
       
    }while(res==0);
        
        strcpy(addressBook->contacts[index].phone, phone);
        printf("Phone Number Updated Successfully.\n"); 
    
        break;

       case 3:
       do
       {
        printf("Enter New Email : "); //read email
        //scanf(" %[^\n]", addressBook->contacts[index].email);
          //validation
         scanf(" %[^\n]", email);
         ret=validateEmail(addressBook, email);
        if(ret==0)
        {
            printf("Invalid Email ID!\n");
        } 
    }while(ret==0);
        
      strcpy(addressBook->contacts[index].email, email);
      printf("Email Updated Successfully.\n"); 
        
        break;

      // default:
      // printf("Invalid Choice!\n");
     //  return; 

    }
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index;
    index = searchContact(addressBook);//call search fun
    if(index==-1)
    {
        printf("Unable to Delete. Contact not Found!\n");
        return; //back to main menu
    }
    for(int i=index; i<addressBook->contactCount-1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];

    }
   addressBook->contactCount--; //decrement the contact count

   printf("Contact Deleted Successfully.\n");
}
int validatePhone(AddressBook *addressBook, char *phone)
{
    int i=0, count=0;
    for(int i =0; phone[i]!='\0'; i++)
    {
         if(phone[i]<'0' || phone[i] >'9')
         {
          return 0;   //invalid character
         }
         count++;

    }
   if(count !=10) // check length of digits
     return 0;

    for(i=0; i<addressBook->contactCount; i++) // check duplicate 
    {
        if(strcmp(addressBook->contacts[i].phone, phone)==0)
        {
            return 0;
        }
    }
    return 1;
}  
int validateEmail(AddressBook *addressBook, char *email)
{
char ch1='@', ch2= '.';
int at_count =0, dot_count=0;
int at_pos = -1, dot_pos = -1;

for(int i=0; email[i]!='\0'; i++)
{
    if(email[i]==ch1)
    {
        at_count++;
        at_pos = i;
    }
    if(email[i]==ch2)
    {
        dot_count++;
        dot_pos = i;
    }
}
if(at_count !=1 || dot_count!=1) // '@' and '.' only once
 return 0;

if(at_pos == 0) // '@'should not be first
  return 0;

if(email[dot_pos+1]=='\0') //'.' should not be last'
  return 0;

if(dot_pos<at_pos) // '@' must come before '.'
  return 0; 
if(dot_pos == at_pos+1) //after @__. should be present
  return 0;
  
  for(int i =0; i<addressBook->contactCount; i++)// present or not
  {
    if(strcmp(addressBook->contacts[i].email, email)==0)
    return 0;
  }
       
return 1;
     
}


        
