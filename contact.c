#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"


void listContacts(AddressBook *addressBook, int sortCriteria) //function to list or display all the contacts
{
    // Sort contacts based on the chosen criteria
    int i;
    for(i=0; i<addressBook->contactCount; i++) //loop runs for contact count times
    {
        printf("%s\t %s\t %s\t\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); //print all the contacts stored
    } 
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) { //save all the changes done by the user
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validname(char *str1); //function prototypes for the three functions for validation 
int validphone(AddressBook *addressBook, char *str2);
int validmail(char *str3);

void createContact(AddressBook *addressBook) //function to create a new contact be the user
{
	/* Define the logic to create a Contacts */
    char str1[50], str2[10], str3[50]; //three variables for name, phone and mail
    int res;

    do{
        printf("\nEnter the name: "); //creating new name
        scanf(" %[^\n]", str1);        
        res=validname(str1);
        if(res==0)
        {
            printf("Invalid input!");
        }
    }while(res==0);
    strcpy(addressBook->contacts[addressBook->contactCount].name, str1); //copy the created name into addressbook

    do{
        printf("Enter the ph num: "); //creating new phone number
        scanf(" %[^\n]", str2);
        res=validphone(addressBook, str2);
    }while(res==0);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, str2);

    do{
        printf("Enter the email: "); //creating new mail id
        scanf(" %[^\n]", str3);
        res=validmail(str3);
        if(res==0)
        {
            printf("Enter a valid email address that contains only one @, only lowercases and dots!");
        }
    }while(res==0);
    strcpy(addressBook->contacts[addressBook->contactCount].email, str3);
    
    addressBook->contactCount++; //increase the contactcount number as new contact is created

    printf("%d", addressBook->contactCount);
}

int searchContact(AddressBook *addressBook, int *index)  //to perform search operation by the user
{
    /* Define the logic for search */
    char str[50];
    int s;
    printf("Search by \n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &s);
    getchar();
    int flag=0, i;
    if(s>=1 && s<=3)
    {
        printf("Enter the string: ");
        scanf(" %[^\n]", str);
        for(i=0; i<addressBook->contactCount; i++) //loop runs for contact count times
        {
            if((s==1 && strcmp(str, addressBook->contacts[i].name)==0) || (s==2 && strcmp(str, addressBook->contacts[i].phone)==0) || (s==3 && strcmp(str, addressBook->contacts[i].email)==0))
            {
                *index=i; //storing in the index value using pointer
                printf("%s %s %s %d \n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email, i);
                flag++; //increase the flag value
            }
        }
        if(flag!=0)
        {
            printf("Contact found!");
        }
        else
        {
            printf("Contact not found!");
        }
    }
    return flag;
}

void editContact(AddressBook *addressBook) //to perform edit operation
{
	/* Define the logic for Editcontact */
    int index;
    int res=searchContact(addressBook, &index);

    if(res==0)
    {
        printf("No matching contact found.\n");
        return;
    }

    if(res>1)
    {
        printf("Enter the index value: "); //ask the index value from the user is similar contacts appear
        scanf("%d", &index);
    }
    int option;
    printf("\nEnter the option to edit:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &option);

    int valid=0;

    switch(option)
    {
        case 1: //Edit name
        do {
                printf("Enter new name: ");
                scanf(" %[^\n]", addressBook->contacts[index].name);
                valid = validname(addressBook->contacts[index].name);
                if (valid == 0)
                    printf("Invalid name! Only alphabets and spaces allowed.\n");
            } while (valid == 0);
            printf("Name updated successfully.\n");
            break;

        case 2: // Edit phone
        char temp[20];
            do {
                printf("Enter new phone number (10 digits): ");
                scanf(" %[^\n]", temp);
                valid = validphone(addressBook, temp);
                if (valid == 0)
                    printf("Invalid or duplicate phone number! Try again.\n");
            } while (valid == 0);

            strcpy(addressBook->contacts[index].phone, temp);
            printf("Phone number updated successfully.\n");
            break;

        case 3: // Edit email
        char temp1[20];
            do {
                printf("Enter new email: ");
                scanf(" %[^\n]", temp1);
                valid = validmail(temp1);
                if (valid == 0)
                    printf("Invalid email! Use lowercase letters, digits, dots, and exactly one '@'.\n");
            } while (valid == 0);

            strcpy(addressBook->contacts[index].email, temp1);
            printf("Email updated successfully.\n");
            break;

        default:
            printf("Invalid option!\n");
            return;
    }

    printf("\nContact after update:\n"); //print the updated contact
    printf("Name: %s\nPhone: %s\nEmail: %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);
}

void deleteContact(AddressBook *addressBook) //to perform delete operation
{
	/* Define the logic for deletecontact */
    int index=0;
    int res=searchContact(addressBook, &index); //caaling the search function

    if(res==0)
    {
        printf("Invalid input");
    }

    if(res>1)
    {
        printf("Enter the index value: "); //read the index value
        scanf("%d", &index);
    }

    int i;
    for(i=index; i<addressBook->contactCount; i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1]; //store the contact with next index value
    }

    addressBook->contactCount--;
    printf("\nContact Deleted Successfully!\n");
}

int validname(char * str1) //valid the name that contains only alphabets
{
    int size=strlen(str1);
    int i;
    for(i=0; i<size; i++)
    {
        if (!((str1[i] >= 'A' && str1[i] <= 'Z') || (str1[i] >= 'a' && str1[i] <= 'z') || (str1[i] == ' ')))
        {
            return 0;
        }
    }
    return 1;
}

int validphone(AddressBook *addressBook, char * str2) //valid phone number that are unique and only have numbers
{
    int size=strlen(str2);
    int i;

    if(size!=10)
    {
        return 0;
    }
        
    for(i=0; i<size; i++)
    {
        if(str2[i]<'0' || str2[i]>'9')
        {
            return 0;
        }
    }
    //uniqueness
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(str2, addressBook->contacts[i].phone) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int validmail(char * str3) //valid email id that have 1 @ symbol and only lowercases
{
    int size=strlen(str3);
    int i, count=0;
    for(i=0; i<size; i++)
    {
        char ch=str3[i];

        if(ch=='@')
        {
            count++;
        }
        else if((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == '.')
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    if(count!=1)
    {
        return 0;
    }

    return 1;
}
