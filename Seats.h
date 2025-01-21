#ifndef SEATS_H_INCLUDED
#define SEATS_H_INCLUDED

#include <iostream>
using namespace std;

// Seats class definition
class Seats {
private:
    int rows;                // Number of rows in the seating arrangement
    int columns;             // Number of columns in the seating arrangement
    string seats[10][10];    // 2D array to represent the seating arrangement

public:
    // Default constructor
    Seats() {
        // Default seating arrangement with prices in the last column
        string defaultSeats[10][10] = {
            {" ", "1", "2", "3", "4", "5", "6", "7", "8", "      "},
            {"1", "_", "_", "_", "_", "_", "_", "_", "_", "(100$)"},
            {"2", "_", "_", "_", "_", "_", "_", "_", "_", "(90$) "},
            {"3", "_", "_", "_", "_", "_", "_", "_", "_", "(80$) "},
            {"4", "_", "_", "_", "_", "_", "_", "_", "_", "(70$) "},
            {"5", "_", "_", "_", "_", "_", "_", "_", "_", "(60$) "},
            {"6", "_", "_", "_", "_", "_", "_", "_", "_", "(50$) "},
            {"7", "_", "_", "_", "_", "_", "_", "_", "_", "(50$) "},
            {"8", "_", "_", "_", "_", "_", "_", "_", "_", "(50$) "},
            {"9", "_", "_", "_", "_", "_", "_", "_", "_", "(50$) "}
        };

        // Initialize the seats array with defaultSeats values
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                seats[i][j] = defaultSeats[i][j];
            }
        }
    }

    // Parameterized constructor
    Seats(int row, int column) {
        rows = row;
        this->columns = column;
    }

    // Display available seats
    void showAvailableSeats() const {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                cout << seats[i][j] << ' ';
            }
            cout << endl;
        }
    }

    // Book a seat
    bool bookSeat(int row, int column) {
        if (seats[row][column] == "_") { // Check if the seat is available
            seats[row][column] = "X";    // Mark the seat as booked
            return true;
        } else {
            cout << "Seat not available, please select another seat.\n";
            return false;
        }
    }

    // Free a booked seat
    bool freeSeat(int row, int column) {
        if (seats[row][column] == "X") { // Check if the seat is booked
            seats[row][column] = "_";    // Mark the seat as available
            return true;
        } else {
            cout << "Seat was not booked, no need to free it.\n";
            return false;
        }
    }

    // Count the number of available seats
    int numOfavailableSeats() {
        int availableSeats = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (seats[i][j] == "_") { // Check if the seat is available
                    availableSeats++;
                }
            }
        }
        return availableSeats;
    }
};

#endif // SEATS_H_INCLUDED
