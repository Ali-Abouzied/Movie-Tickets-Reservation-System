#ifndef MOVIE_H_INCLUDED
#define MOVIE_H_INCLUDED

#include <iostream>
#include <string>
#include "Seats.h"
using namespace std;

// Enumeration for different movie genres
enum Genre {
    ACTION,
    COMEDY,
    DRAMA,
    HORROR,
    ROMANCE,
    SCIFI,
    DOCUMENTARY
};

// Movie class definition
class Movie {
private:
    // Private member variables
    string title;          // Title of the movie
    Genre genre;           // Genre of the movie
    int releaseYear;       // Release year of the movie
    float durationHours;   // Duration of the movie in decimal hours
    string startTime;      // Starting time of the movie
    Seats auditorium;      // Auditorium seats for the movie

public:
    // Default constructor
    Movie() : title(""), genre(ACTION), releaseYear(0), durationHours(0.0), startTime("") {}

    // Parameterized constructor
    Movie(string t, Genre g, int y, float d, string s)
        : title(t), genre(g), releaseYear(y), durationHours(d), startTime(s) {}

    // Convert decimal hours to hours and minutes
    void convertDecimalHoursToHoursMinutes(int &hours, int &minutes) {
        hours = (int)durationHours;  // Extract the whole number of hours
        double fractionalPart = durationHours - hours;  // Get the fractional part
        minutes = (int)(fractionalPart * 60);  // Calculate the minutes
    }

    // Display movie information
    void showInfo() {
        int hrs = 0, min = 0;
        convertDecimalHoursToHoursMinutes(hrs, min);

        cout << "Title: " << title << endl;
        cout << "Genre: " << getGenreString() << endl;
        cout << "Release Year: " << releaseYear << endl;
        cout << "Duration: " << hrs << " hours and " << min << " minutes" << endl;
        cout << "Starting Time: " << startTime << endl;
        auditorium.showAvailableSeats();  // Display available seats in the auditorium
    }

    // Get genre as a string
    string getGenreString() const {
        switch (genre) {
            case ACTION: return "Action";
            case COMEDY: return "Comedy";
            case DRAMA: return "Drama";
            case HORROR: return "Horror";
            case ROMANCE: return "Romance";
            case SCIFI: return "Sci-Fi";
            case DOCUMENTARY: return "Documentary";
            default: return "Unknown";
        }
    }

    // Get the auditorium seats
    Seats& getAuditorium() {
        return auditorium;
    }
};

#endif // MOVIE_H_INCLUDED
