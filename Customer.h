#ifndef CUSTOMER_H_INCLUDED
#define CUSTOMER_H_INCLUDED

#include <iostream>
#include <string>
using namespace std;

// Customer class definition
class Customer {
private:
    // Private member variables
    string name;   // Name of the customer
    string email;  // Email of the customer

public:
    // Constructor with default parameters
    Customer(string name = "", string email = "")
        : name(name), email(email) {}

    // Getter for the name
    string Getname() { return name; }

    // Getter for the email
    string Getemail() { return email; }

    // Display customer information
    void showCustomerInfo() const {
        cout << "Name: " << name << "\nEmail: " << email << endl;
    }
};

#endif // CUSTOMER_H_INCLUDED
