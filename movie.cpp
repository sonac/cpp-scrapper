//
// Created by Andrii Sumko on 06.06.18.
//

#include "movie.h"
#include <iostream>
#include <string>

using namespace std;

Movie::Movie(string c_name, string c_genre) :Media(c_name), genre{c_genre}, series{NULL} {
    if (c_name.length() == 0)
        throw std::runtime_error("Error: name cannot be empty");
};

void Movie::bindToSeries(TV_Show* c_series) {
    series = c_series;
    if (studio.length() == 0)
        studio = c_series->studio;
}

void Movie::displayInfo() const {
    cout << "Name is: " << name << endl;
    if (genre.length() > 0)
        cout << "Genre is: " << genre << endl;
    if (studio.length() > 0)
        cout << "Studio is: " << studio << endl;
    if (series != NULL)
        cout << "Binded to " << series->name << " series" << endl;
}