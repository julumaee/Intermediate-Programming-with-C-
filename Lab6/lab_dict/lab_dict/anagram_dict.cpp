/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/** 
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */ 
AnagramDict::AnagramDict(const string& filename)
{
    ifstream word_stream(filename);
    string word;
    vector<string> words;
    if(word_stream.is_open()) {
        /* Reads a line from words into word until the file ends. */
        while(getline(word_stream, word)) {
            words.push_back(word);
        }
    }
    *this = AnagramDict(words);
}

/** 
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */ 
AnagramDict::AnagramDict(const vector< string >& words)
{
    for (auto & word: words) {
        string sorted = word;
        sort(sorted.begin(), sorted.end());
        if (std::find(dict[sorted].begin(), dict[sorted].end(), word) == dict[sorted].end())
            dict[sorted].push_back(word);
    }

    for (auto it = dict.begin(); it != dict.end(); ) {
        if (it->second.size() == 1) {
            it = dict.erase(it);
        } else {
            ++it;
        }
    }
}

/**
 * @param word The word to find anagrams of. 
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the 
 * word list.
 */
vector< string > AnagramDict::get_anagrams(const string& word) const
{
    vector<string> anagrams;
    string sorted = word;
    sort(sorted.begin(), sorted.end());
    auto it = dict.find(sorted);
    if (it != dict.end()){
        anagrams = it->second;
    }
    return anagrams;
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector< vector< string > > AnagramDict::get_all_anagrams() const
{
    vector< vector < string > > all_anagrams;
    for (auto & pair : dict) {
        all_anagrams.push_back(pair.second);
    }
    return all_anagrams;
}


