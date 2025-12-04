#ifndef FILE_H
#define FILE_H

#include "contact.h"

//these functions are used to save and load contacts from a file
//saveContactsToFile= saves the contacts in the address book to a file named "contacts.txt"
//loadContactsFromFile= loads the contacts from the file "contacts.txt" into the address book

void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

#endif
