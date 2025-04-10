#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

// Contact class with encapsulation
class Contact {
private:
    string name;
    string phone;
    string email;

public:
    Contact() {}
    Contact(string n, string p, string e) : name(n), phone(p), email(e) {}

    // Getters
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }

    // Display Contact
    void display() const {
        cout << "Name : " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "----------------------" << endl;
    }

    // Serialize and Deserialize
    void writeToFile(ofstream &out) const {
        out << name << '\n' << phone << '\n' << email << '\n';
    }

    void readFromFile(ifstream &in) {
        getline(in, name);
        getline(in, phone);
        getline(in, email);
    }
};

// Address Book class
class AddressBook {
private:
    vector<Contact> contacts;

    void loadFromFile() {
        contacts.clear();
        ifstream infile("contacts.txt");
        if (infile.is_open()) {
            while (!infile.eof()) {
                Contact c;
                c.readFromFile(infile);
                if (!c.getName().empty()) {
                    contacts.push_back(c);
                }
            }
            infile.close();
        }
    }

    void saveToFile() const {
        ofstream outfile("contacts.txt");
        for (const auto &c : contacts) {
            c.writeToFile(outfile);
        }
        outfile.close();
    }

public:
    AddressBook() {
        loadFromFile();
    }

    ~AddressBook() {
        saveToFile();
    }

    void addContact() {
        string name, phone, email;
        cout << "Enter Name : ";
        getline(cin, name);
        cout << "Enter Phone: ";
        getline(cin, phone);
        cout << "Enter Email: ";
        getline(cin, email);
        contacts.emplace_back(name, phone, email);
        cout << "Contact added successfully.\n";
    }

    void displayContacts() const {
        if (contacts.empty()) {
            cout << "No contacts available.\n";
            return;
        }
        for (const auto &c : contacts) {
            c.display();
        }
    }

    void searchContact() const {
        string name;
        cout << "Enter name to search: ";
        getline(cin, name);
        bool found = false;
        for (const auto &c : contacts) {
            if (c.getName() == name) {
                c.display();
                found = true;
            }
        }
        if (!found)
            cout << "Contact not found.\n";
    }

    void deleteContact() {
        string name;
        cout << "Enter name to delete: ";
        getline(cin, name);
        auto it = remove_if(contacts.begin(), contacts.end(), [&name](Contact &c) {
            return c.getName() == name;
        });
        if (it != contacts.end()) {
            contacts.erase(it, contacts.end());
            cout << "Contact deleted.\n";
        } else {
            cout << "Contact not found.\n";
        }
    }
};

// Main function with menu
int main() {
    AddressBook book;
    int choice;

    do {
        cout << "\n-------- Address Book --------\n";
        cout << "1. Add Contact\n";
        cout << "2. Display Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit";
        cout << "\n------------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        switch (choice) {
            case 1: book.addContact(); break;
            case 2: book.displayContacts(); break;
            case 3: book.searchContact(); break;
            case 4: book.deleteContact(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
