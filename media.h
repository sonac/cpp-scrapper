//
// Created by Andrii Sumko on 07.06.18.
//

#include <string>
#include <vector>

#ifndef CPP_SCRAPPER_MEDIA_H
#define CPP_SCRAPPER_MEDIA_H

using namespace std;

class Media {
protected:
    string studio;
    vector<string> actors;
public:
    Media(const string& c_name) :name{c_name} {};
    string name;
    virtual void displayInfo() const = 0;
    void add_actors(string actor_list[]) {
        for (int i=0; i < sizeof(*actor_list)/sizeof(actor_list); ++i)
            actors.push_back(actor_list[i]);
    };
    void show_actors() {
        for (int i=0; i < actors.size() - 1; ++i)
            cout << actors[i] << endl;
    };
};

#endif //CPP_SCRAPPER_MEDIA_H
