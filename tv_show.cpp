//
// Created by Andrii Sumko on 06.06.18.
//
#include "tv_show.h"
#include <iostream>

using namespace std;

TV_Show::TV_Show(string c_name, string c_genre, string c_studio)  :name{c_name}, genre{c_genre}, studio{c_studio} {
    if (c_name.length() == 0)
        throw std::runtime_error("Error: name cannot be empty");
};

bool TV_Show::init(const string& i_name, string i_genre, string i_studio) {

    if (i_name.length() == 0)
        return false;

    name = i_name;
    genre = i_genre;
    studio = i_studio;
    return true;

}

void TV_Show::addEpisodes(int a) {
    length += a;
}

void TV_Show::displayInfo() {
    cout << "TV Show name is: " << name << endl << "Genre: " << genre << endl << "Studio: " << studio << endl;
    cout << "Length is " << length << " episodes" << endl;
}

TV_Show TV_Show::operator++() {
    ++length;
    return *this;
}