#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>


typedef std::size_t HASH_INDEX_T;

struct MyStringHash {

    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }

    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        HASH_INDEX_T holder[5] = { 0 };
        std::size_t len = k.size();
        std::size_t index = 0;
        std::size_t extra = 0;

        for (std::size_t i = 0; i < len; ++i) {
            holder[4 - index] += letterDigitToNumber(k[len - 1 - i]) * pow(36, i - extra);

            if ((i + 1) % 6 == 0) {
                ++index;
                extra += 6;
            }
        }

        HASH_INDEX_T result = 0;
        for (std::size_t i = 0; i < 5; ++i) {
            result += holder[i] * rValues[i];
        }

        return result;
    }
   // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {

        char lower = tolower(letter);


        if (lower >= 97 && lower <= 122)
        {
            return lower - 'a';
        }

        return lower - '0' + 26;
    }
    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }

};


#endif