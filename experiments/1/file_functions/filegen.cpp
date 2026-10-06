#include <iostream>
#include <fstream>
#include <random>
#include <string>

using namespace std;

const int seed = 53;

std::string textgen(size_t len)
{
    std::string text;
    text.reserve(len);
    for(size_t i = 0; i < len; ++i){
        int c = 33 + (rand() % (126 - 33 +1));
        text += static_cast<char>(c);
    }
    return text;
}

int main ()
{
    srand(seed);
    for(int i = 0; i < 9; ++i){
        std::string filename = "long"+std::to_string(i)+".txt";
        ofstream f(filename, std::ios::binary);
        std::string bytes = textgen(1200);
        f << bytes;
        f.close();
    }
}