#include <iostream>
#include <string>
#include<iomanip>

using namespace std;

// Contact class to represent contact information
class Contact {
private:
    string name;
    string email;
    string phoneNumber;

public:
    Contact(const string& _name, const string& _email, const string& _phoneNumber)
        : name(_name), email(_email), phoneNumber(_phoneNumber) {}

    // Getters for contact information
    string getName() const {
        return name;
    }

    string getEmail() const {
        return email;
    }

    string getPhoneNumber() const {
        return phoneNumber;
    }
};

// ContactBook class to manage a collection of contacts
class ContactBook {
private:
    Contact** contacts;
    int numContacts;
    int capacity;

public:
    ContactBook() : contacts(nullptr), numContacts(0), capacity(0) {}

    ~ContactBook() {
        for (int i = 0; i < numContacts; ++i) {
            delete contacts[i];
        }
        delete[] contacts;
    }

    // Add a new contact
    void addContact(const Contact& contact) {
        if (numContacts == capacity) {
            // Increase capacity by doubling the size
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            Contact** newContacts = new Contact*[newCapacity];

            // Copy existing contacts to the new array
            for (int i = 0; i < numContacts; ++i) {
                newContacts[i] = contacts[i];
            }

            // Delete the old array
            delete[] contacts;

            // Update the member variables
            contacts = newContacts;
            capacity = newCapacity;
        }

        contacts[numContacts] = new Contact(contact);
        numContacts++;
        cout << "Contact added successfully." << endl;
    }

    // Delete a contact by name
    void deleteContact(const string& name) {
        for (int i = 0; i < numContacts; ++i) {
            if (contacts[i]->getName() == name) {
                // Delete the contact
                delete contacts[i];

                // Shift the remaining contacts to fill the gap
                for (int j = i; j < numContacts - 1; ++j) {
                    contacts[j] = contacts[j + 1];
                }
                numContacts--;
                cout << "Contact deleted successfully." << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    // Search for a contact by name
    void searchContact(const string& name) const {
        for (int i = 0; i < numContacts; ++i) {
            if (contacts[i]->getName() == name) {
                cout << "Contact Found:" << endl;
                cout << "Name: " << contacts[i]->getName() << endl;
                cout << "Email: " << contacts[i]->getEmail() << endl;
                cout << "Phone Number: " << contacts[i]->getPhoneNumber() << endl;
                return;
            }
        }
        cout << "Contact not found." << endl;
    }

    // Display all contacts in a table-like format
    // Display all contacts in a table-like format
    void displayContacts() const {
        if (numContacts == 0) {
            cout << "Contact book is empty." << endl;
            return;
        }

        cout << "Contact List:" << endl;

        // Print table header
        cout << left << setw(20) << "Name";
        cout << left << setw(15) << "Email";
        cout << left << setw(15) << "Phone Number" << endl;

        // Print contact information
        for (int i = 0; i < numContacts; ++i) {
            cout << left << setw(20) << contacts[i]->getName();
            cout << left << setw(15) << contacts[i]->getEmail();
            cout << left << setw(15) << contacts[i]->getPhoneNumber() << endl;
        }
    }


};

int main() {
    ContactBook contactBook;

    int choice;
    string name, email, phoneNumber;

    while (true) {
        // Display menu options
        cout << "Contact Management System" << endl;
        cout << "1. Add Contact" << endl;
        cout << "2. Delete Contact" << endl;
        cout << "3. Search Contact" << endl;
        cout << "4. Display Contacts" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter email: ";
                cin >> email;
                cout << "Enter phone number: ";
                cin >> phoneNumber;
                contactBook.addContact(Contact(name, email, phoneNumber));
                break;

            case 2:
                cout << "Enter name to delete: ";
                cin.ignore();
                getline(cin, name);
                contactBook.deleteContact(name);
                break;

            case 3:
                cout << "Enter name to search: ";
                cin.ignore();
                getline(cin, name);
                contactBook.searchContact(name);
                break;

            case 4:
                contactBook.displayContacts();
                break;

            case 5:
                cout << "Exiting program..." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
