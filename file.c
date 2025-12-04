#include <stdio.h>
#include "file.h"

//1. Open a file named "contacts.txt" for writing.
//2. Write the number of contacts at the beginning of the file.
//3. Loop through each contact and write its details (name, phone, email) to the file.
//4. Close the file after writing all contacts.

void saveContactsToFile(AddressBook *addressBook)    
{            
    FILE * fptr=fopen("contacts.txt", "w"); //read the file in write mode
    if(fptr==NULL)
    {
        printf("Error: File is not accessible");
        return;
    }  
    fprintf(fptr, "#%d\n", addressBook->contactCount); 

    int i;
    for(i=0; i<addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    } 

    fclose(fptr);
}


//Open a file named "contacts.txt" for reading.
//Read the number of contacts from the file.
//Loop through each contact and read its details (name, phone, email) from the file.
//Close the file after reading all contacts.

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE * fptr=fopen("contacts.txt", "r"); //read the file in read mode

    fscanf(fptr, "#%d\n", &addressBook->contactCount);

    int i;
    for(i=0; i<addressBook->contactCount; i++)
    {
        fscanf(fptr, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }

    fclose(fptr);
}
