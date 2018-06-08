//
// Created by Andrii Sumko on 06.06.18.
//
#include <iostream>
#include <string>
#include "tv_show.h"
#include "media.h"

#ifndef CPP_SCRAPPER_MOVIE_H
#define CPP_SCRAPPER_MOVIE_H

using namespace std;


class Movie : public Media {
private:
    TV_Show* series;
public:
    explicit Movie(string c_name, string c_genre="");
    string genre;
    void bindToSeries(TV_Show* c_series);
    void displayInfo() const;
};


#endif //CPP_SCRAPPER_MOVIE_H
