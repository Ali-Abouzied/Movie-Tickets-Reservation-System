#ifndef RESERVATION_H_INCLUDED
#define RESERVATION_H_INCLUDED

#include "Movie.h"
#include "Customer.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

// Forward declaration of the Price function
int Price(int row);

// Reservation class definition
class Reservation {
private:
    Customer customer;          // Customer who made the reservation
    Movie& movie;               // Reference to the movie for which the reservation is made
    string orderId;             // Unique order ID for the reservation
    int reservedSeats[100][2];  // Array to store reserved seat positions as pairs of row and column
    int reservedSeatsCount;     // Count of reserved seats
    int totalPrice;             // Total price of reserved seats

    // Function to generate a random order ID of a given length
    string generateRandomOrderId(int length) {
        string randomId;
        for (int i = 0; i < length; ++i) {
            randomId += '0' + rand() % 10; // Generate a random digit from 0 to 9
        }
        return randomId;
    }

public:
    // Constructor
    Reservation(int orderId, Customer& c, Movie& m)
        : orderId(generateRandomOrderId(10)), customer(c), movie(m), reservedSeatsCount(0), totalPrice(0) {}

    // Overload the equality operator to compare reservations by order ID
    bool operator==(const Reservation& other) const {
        return orderId == other.orderId;
    }

    // Add a seat to the reservation
    bool addSeat(int row, int column) {
        if (reservedSeatsCount < 100 && movie.getAuditorium().bookSeat(row, column)) {
            reservedSeats[reservedSeatsCount][0] = row;
            reservedSeats[reservedSeatsCount][1] = column;
            reservedSeatsCount++;
            totalPrice += Price(row); // Add the price of the seat to the total price
            return true;
        }
        return false;
    }

    // Remove a seat from the reservation
    bool removeSeat(int row, int column) {
        for (int i = 0; i < reservedSeatsCount; ++i) {
            if (reservedSeats[i][0] == row && reservedSeats[i][1] == column) {
                movie.getAuditorium().freeSeat(row, column);
                // Move the last seat to the current position to maintain the array's integrity
                reservedSeats[i][0] = reservedSeats[reservedSeatsCount - 1][0];
                reservedSeats[i][1] = reservedSeats[reservedSeatsCount - 1][1];
                reservedSeatsCount--;
                totalPrice -= Price(row); // Subtract the price of the seat from the total price
                return true;
            }
        }
        return false;
    }

    // Get the count of reserved seats
    int getReservedSeatsCount() const {
        return reservedSeatsCount;
    }

    // Get the total price of the reservation
    int getTotalPrice() const {
        return totalPrice;
    }

    // Cancel the reservation and free all reserved seats
    void cancelReservation() {
        for (int i = 0; i < reservedSeatsCount; ++i) {
            int row = reservedSeats[i][0];
            int column = reservedSeats[i][1];
            movie.getAuditorium().freeSeat(row, column);
        }
        reservedSeatsCount = 0;
        totalPrice = 0; // Reset the total price
    }

    // Display reservation information
    void showReservationInfo() const {
        cout << "Order ID: " << orderId << endl;
        customer.showCustomerInfo();
        movie.showInfo();
        cout << "Reserved Seats: ";
        for (int i = 0; i < reservedSeatsCount; ++i) {
            cout << "(" << reservedSeats[i][0] << "," << reservedSeats[i][1] << ") ";
        }
        cout << endl;
        cout << "Total Price: $" << totalPrice << endl; // Display the total price
    }

    // Get the order ID
    string GetOrderId() const { return orderId; }
};

#endif // RESERVATION_H_INCLUDED
