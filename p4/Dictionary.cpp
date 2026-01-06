#include "Dictionary.h"
#include <string>
#include <list>
#include <cctype>
#include <utility>  // for swap
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional> // for hash
using namespace std;

void removeNonLetters(string& s);

  // This class does the real work of the implementation.

class DictionaryImpl
{
  public:
    DictionaryImpl(int maxBuckets);
    ~DictionaryImpl();
    void insert(string word);
    void lookup(string letters, void callback(string)) const;
  private:
    vector<list<string>*> dict; // hash table
    int max_bucks;
    string letterSort(string letters) const;
    unsigned int h(string s) const; // returns hash
};


DictionaryImpl::DictionaryImpl(int maxBuckets) : max_bucks(maxBuckets/2) {
    if (maxBuckets < 1)
        max_bucks = 1;
    for (int i = 0; i < max_bucks; ++i) // creates hash table of empty buckets
        dict.push_back(new list<string>);
}

DictionaryImpl::~DictionaryImpl() {
    for (int i = 0; i < dict.size(); ++i)
        delete dict[i];
    dict.clear();
}

void DictionaryImpl::insert(string word)
{
    removeNonLetters(word);
    unsigned int ind = h(letterSort(word)); // puts word in bucket of its sorted string
    if ( ! word.empty())
        dict[ind]->push_back(word);
}

unsigned int DictionaryImpl::h(string s) const {
    return std::hash<string>()(s) % max_bucks;
}

string DictionaryImpl::letterSort(string letters) const {
    sort(letters.begin(), letters.end());
    return letters;
}

void DictionaryImpl::lookup(string letters, void callback(string)) const
{
    if (callback == nullptr)
        return;

    removeNonLetters(letters);
    if (letters.empty())
        return;

    string sortedWord = letterSort(letters);
    string anagram;
    
    unsigned int bucket = h(letterSort(letters));
    for (list<string>::iterator p = dict[bucket]->begin(); p != dict[bucket]->end(); ++p) {
        anagram = letterSort(*p);
        if (anagram.length() == sortedWord.length() && anagram == sortedWord)
            callback(*p);
    }
}

void removeNonLetters(string& s)
{
    string::iterator to = s.begin();
    for (string::const_iterator from = s.begin(); from != s.end(); from++)
    {
        if (isalpha(*from))
        {
            *to = tolower(*from);
            to++;
        }
    }
    s.erase(to, s.end());  // chop everything off from "to" to end.
}

//******************** Dictionary functions ******************************

// These functions simply delegate to DictionaryImpl's functions
// You probably don't want to change any of this code

Dictionary::Dictionary(int maxBuckets)
{
    m_impl = new DictionaryImpl(maxBuckets);
}

Dictionary::~Dictionary()
{
    delete m_impl;
}

void Dictionary::insert(string word)
{
    m_impl->insert(word);
}

void Dictionary::lookup(string letters, void callback(string)) const
{
    m_impl->lookup(letters,callback);
}
