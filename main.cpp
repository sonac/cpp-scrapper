#include <iostream>
#include <string>
#include <fstream>
#include "tv_show.h"
#include "movie.h"

using namespace std;

int main() {
    TV_Show arrow("Arrow", "action", "CW");
    arrow.addEpisodes(15);
    ++arrow;
    arrow.displayInfo();
    Movie wonder_woman("Wonder Woman", "action");
    wonder_woman.bindToSeries(&arrow);
    string actors[] = {"Chris Pain", "Gal Gadot"};
    wonder_woman.add_actors(actors);
    wonder_woman.displayInfo();
    wonder_woman.show_actors();
    int64_t fib[90];
    fib[0] = 0;
    fib[1] = 1;
    for (int i = 2; i < 90; ++i) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    ofstream fib_file("fib.txt");
    for (int i = 0; i < 90; ++i) {
        fib_file << fib[i] << endl;
    }
    fib_file.close();
    return 0;
}