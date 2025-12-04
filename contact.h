#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100 //maximum number of contacts can be stored

typedef struct {
    char name[50]; //name, phone number and email are included in the contact struct to store
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount; //variable to track the number of contacts
} AddressBook;

//addressBook is a pointer to the AddressBook struct

void createContact(AddressBook *addressBook); //to create a new contact
int searchContact(AddressBook *addressBook, int *index); //to search a contact 
void editContact(AddressBook *addressBook); //to edit a contact
void deleteContact(AddressBook *addressBook); //to delete a contact
void listContacts(AddressBook *addressBook, int sortCriteria); //to list or display the contacts
void initialize(AddressBook *addressBook); //to initialize the contacts
void saveContactsToFile(AddressBook *AddressBook); //to save and exit the file

#endif
