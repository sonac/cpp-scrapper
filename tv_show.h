//
// Created by Andrii Sumko on 06.06.18.
//

#include <iostream>
#include <string>
#include <stdexcept>


#ifndef CPP_SCRAPPER_TV_SHOW_H
#define CPP_SCRAPPER_TV_SHOW_H


using namespace std;

class TV_Show {

    private:
        int length;
        string studio;

    public:
        TV_Show(string c_name, string c_genre="", string c_studio="");
        string name, genre;
        bool init(const string& i_name, string i_genre="", string i_studio="");
        void addEpisodes(int a);
        void displayInfo();
        TV_Show operator++();
        friend class Movie;

};

#endif //CPP_SCRAPPER_TV_SHOW_H