#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Customer.h"
#include "Movie.h"
#include "Reservation.h"
#include "Seats.h"

using namespace std;

const int MAX_RESERVATIONS = 100;  // Maximum number of reservations
const int MOVIE_COUNT = 7;  // Number of movies available

// Prices for each row, indexed from 0 (i.e., row 1 is at index 0)
const int ROW_PRICES[9] = { 100, 90, 80, 70, 60, 50, 50, 50, 50 };

// Global variable to store the number of seats
int n_seats;

// Function to display the menu options to the user
void showMenu() {
    cout << "\n--- Movie Ticket Reservation System ---\n";
    cout << "1. Browse Movies\n";
    cout << "2. Book Tickets\n";
    cout << "3. Cancel Reservation\n";
    cout << "4. Browse Reservations\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

// Function to get a valid integer input from the user
int getValidId() {
    int num;
    while (true) {
        cin >> num;
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            while (cin.get() != '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number: ";
        } else {
            return num;
        }
    }
}

// Function to display information about all available movies
void browseMovies(Movie movies[], int movieCount) {
    cout << "\n--- Available Movies ---\n";
    for (int i = 0; i < movieCount; ++i) {
        cout << "Movie ID: " << i + 1 << endl;  // Display movie ID
        movies[i].showInfo();  // Show movie information
        cout << endl;
    }
}

// Function to get the price of a seat in a specific row
int Price(int row) {
    if (row >= 1 && row <= 9) {
        return ROW_PRICES[row - 1];
    } else {
        cout << "Invalid row number!" << endl;
        return -1;  // Indicate an error with an invalid row number
    }
}

// Function to cancel a reservation
void cancelReservation(Reservation* reservations[], int& reservationCount) {
    cout << "Enter Order ID to cancel: ";
    string orderId;
    cin >> orderId;

    bool found = false;
    for (int i = 0; i < reservationCount; ++i) {
        if (reservations[i] && reservations[i]->GetOrderId() == orderId) {
            found = true;
            cout << "Reservation found. What would you like to do?\n";
            cout << "1. Cancel entire reservation\n";
            cout << "2. Cancel specific tickets\n";
            int choice;
            choice = getValidId();

            if (choice == 1) {
                cout << "Are you sure you want to cancel the entire reservation? (y/n): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'y' || confirm == 'Y') {
                    reservations[i]->cancelReservation();  // Cancel the entire reservation
                    delete reservations[i];
                    reservations[i] = nullptr;
                    cout << "Reservation cancelled successfully!" << endl;
                } else if (confirm == 'n' || confirm == 'N') {
                    cout << "Reservation was not cancelled" << endl;
                } else {
                    cout << "Error, reservation was not cancelled" << endl;
                }
            } else if (choice == 2) {
                int n_cancelled;
                cout << "Enter number of seats you want to cancel: ";
                n_cancelled = getValidId();
                cout << endl;

                while (n_cancelled > n_seats || n_cancelled < 1) {
                    cout << "Error, you only booked " << n_seats << " seats." << endl;
                    cout << "Enter number of seats you want to cancel: ";
                    n_cancelled = getValidId();
                    cout << endl;
                }

                for (int j = 0; j < n_cancelled; j++) {
                    cout << "Enter seat row and column to cancel: ";
                    int row, column;
                    row = getValidId();
                    column = getValidId();

                    if (reservations[i]->removeSeat(row, column)) {  // Remove a specific seat from the reservation
                        cout << "Seat cancellation successful!" << endl;
                    } else {
                        cout << "Failed to cancel seat. Seat not found or already free!" << endl;
                        j--;
                    }
                }

                if (reservations[i]->getReservedSeatsCount() == 0) {
                    delete reservations[i];
                    reservations[i] = nullptr;
                    cout << "All seats cancelled. Reservation removed!" << endl;
                }
            } else {
                cout << "Invalid choice!" << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Invalid Order ID!" << endl;
    }
}

// Function to book tickets for a movie
void bookTickets(Movie movies[], int movieCount, Reservation* reservations[], int& reservationCount) {
    int movieId;
    while (true) {
        cout << "Enter Movie ID to book: ";
        movieId = getValidId();
        if (movieId >= 1 && movieId <= movieCount) {
            break;
        }
        cout << "Invalid Movie ID! Please enter a valid Movie ID." << endl;
    }
    cin.ignore();  // Ignore the newline character after the movie ID input
    cout << "Enter your name: ";
    string name;
    getline(cin, name);

    while (name == "") {
        cout << "Enter your name: ";
        getline(cin, name);
    }

    cout << "Enter your email: ";
    string email;
    getline(cin, email);

    while (email == "") {
        cout << "Enter your email: ";
        getline(cin, email);
    }

    Customer customer(name, email);  // Create a Customer object
    Reservation* res = new Reservation(reservationCount + 1, customer, movies[movieId - 1]);  // Create a new Reservation object

    int row, column;

    cout << "Enter number of seats: ";
    n_seats = getValidId();
    while (n_seats < 1) {
        cout << "Invalid input, Enter number of seats: ";
        n_seats = getValidId();
    }
    while (n_seats > movies[movieId - 1].getAuditorium().numOfavailableSeats()) {
        cout << "Error, only " << movies[movieId - 1].getAuditorium().numOfavailableSeats() << " seats available. Enter number of seats: ";
        n_seats = getValidId();
        cout << endl;
    }

    for (int i = 0; i < n_seats; i++) {
        cout << "Enter seat row and column to book: ";
        row = getValidId();
        column = getValidId();

        while (column > 9 || column <= 0 || row > 9 || row <= 0) {
            cout << "Invalid input! Enter seat row and column to book: ";
            row = getValidId();
            column = getValidId();
        }

        if (res->addSeat(row, column)) {  // Add seat to reservation
            cout << "Seat booked successfully!" << endl;
        } else {
            cout << "Failed to book seat. Try again!" << endl;
            i--;  // Try again if booking fails
        }
    }

    reservations[reservationCount++] = res;  // Add the reservation to the reservations array
    cout << "The total price is: $" << res->getTotalPrice() << endl ;
char confirmation;
do {
    cout << "Please confirm (y/n): ";
    cin >> confirmation;
    if (confirmation == 'n' || confirmation == 'N') {
        res->cancelReservation();// Cancel the reservation
        cout << "Reservation cancelled"<< endl;
    } else if (confirmation == 'y' || confirmation == 'Y') {
        cout << "Reservation successful! Your Order ID is: " << res->GetOrderId() << endl;
    } else {
        cout << "Invalid input. Please enter 'y' or 'n'." << endl;
    }

    } while (confirmation != 'n' && confirmation != 'N' && confirmation != 'y' && confirmation != 'Y');
}

// Function to display all reservations
void browseReservations(Reservation* reservations[], int reservationCount) {
    cout << "\n--- Reservations ---\n";
    for (int i = 0; i < reservationCount; ++i) {
        if (reservations[i] != nullptr) {
            reservations[i]->showReservationInfo();  // Show reservation information
            cout << "---------------------------------------" << endl;
        }
    }
}

// Function to clean up and delete all reservation objects
void cleanUpReservations(Reservation* reservations[], int reservationCount) {
    for (int i = 0; i < reservationCount; ++i) {
        if (reservations[i]) {
            delete reservations[i];
        }
    }
}

// Function to get a valid menu choice from the user
int getValidChoice() {
    int choice;
    while (true) {
        cin >> choice;
        if (cin.fail()) {
            cin.clear(); // Clear the error state
            while (cin.get() != '\n'); // Discard invalid input
            cout << "Invalid choice! Please enter a number: ";
        } else {
            cin.get(); // Consume the newline character left in the input buffer
            return choice;
        }
    }
}

// Function to convert a genre string to a Genre enum
Genre stringToGenre(const string& genreStr) {
    if (genreStr == "ACTION") return ACTION;
    else if (genreStr == "COMEDY") return COMEDY;
    else if (genreStr == "DRAMA") return DRAMA;
    else if (genreStr == "HORROR") return HORROR;
    else if (genreStr == "ROMANCE") return ROMANCE;
    else if (genreStr == "SCIFI") return SCIFI;
    else if (genreStr == "DOCUMENTARY") return DOCUMENTARY;
    else return ACTION;  // Default case, or throw an exception
}

int main() {
    ifstream file("movie_data.txt"); //opens the file
    if (!file.is_open()) { //checks if the file opens correctly
        cout << "Failed to open file movie_data.txt" << endl;
        return 1; // Handle error appropriately
    }

    const int MAX_MOVIES = 7; // Maximum number of movies to read
    Movie movies[MAX_MOVIES]; // Array to store movie objects
    string line; // variable for every line
    int movieCount = 0;

    // loop reads lines from the file using getline
    //continues looping until either the end of the file is reached or MAX_MOVIES movies have been read
    //getline(file, line) reads a line from the file into the string variable line

    while (getline(file, line) && movieCount < MAX_MOVIES) {
        stringstream ss(line); // A stringstream named ss is created to parse the line read from the file.
        string title, genreStr, releaseYearStr, durationStr, startTime;
        Genre genre;
        int releaseYear;
        float duration;

        //this line of code reads from a string as if it were a text file and extracts characters
        //until it encounters a specific delimiter(comma), then stores the extracted characters into a variable

        getline(ss, title, ',');
        getline(ss, genreStr, ',');
        getline(ss, releaseYearStr, ',');
        getline(ss, durationStr, ',');
        getline(ss, startTime);

        genre = stringToGenre(genreStr);
        releaseYear = stoi(releaseYearStr); //function convert the string representations of releaseyear into integer
        duration = stof(durationStr); //function convert the string representations of duration into floats

        // Create and store the Movie object in the array
        movies[movieCount] = Movie(title, genre, releaseYear, duration, startTime);
        movieCount++;
    }

    // Array to store reservations
    Reservation* reservations[MAX_RESERVATIONS] = { nullptr };
    int reservationCount = 0;

    // Main menu loop
    while (true) {
        showMenu();  // Display menu options
        int choice = getValidChoice();

        switch (choice) {
            case 1:
                browseMovies(movies, MOVIE_COUNT);  // Browse movies
                break;
            case 2:
                bookTickets(movies, MOVIE_COUNT, reservations, reservationCount);  // Book tickets
                break;
            case 3:
                cancelReservation(reservations, reservationCount);  // Cancel a reservation
                break;
            case 4:
                browseReservations(reservations, reservationCount);  // Browse all reservations
                break;
            case 5:
                cleanUpReservations(reservations, reservationCount); // Clean up
                cout << "Thank you for using the Movie Ticket Reservation System. Goodbye!" << endl;
                return 0;  // Exit the program
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    }

    return 0;
}
