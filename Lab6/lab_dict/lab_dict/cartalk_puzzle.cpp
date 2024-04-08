/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>
#include <algorithm>
#include <cctype>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of "StringTriples" (a typedef'd std::tuple, see top of 
 * cartalk_puzzle.h). Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector< StringTriple > cartalk_puzzle(PronounceDict d,
                                      const string& word_list_fname)
{
    vector< StringTriple > out;
    string word;
    ifstream word_stream(word_list_fname);
    vector<string> words;
    if(word_stream.is_open()) {
        /* Reads a line from words into word until the file ends. */
        while(getline(word_stream, word)) {
            words.push_back(word);
        }
    }

    for (auto & word : words) {
        if (word.length() <= 1) continue;
        string word1 = word.substr(1);
        string word2 = word.front() + word.substr(2);
        
        if (d.homophones(word, word1) && d.homophones(word, word2)) {
            out.push_back({word, word1, word2});
        }
    }

    return out;
}


