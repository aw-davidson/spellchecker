#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#include "SpellChecker.h"

using std::string;
using std::unordered_set;
using std::vector;
using std::ifstream;


SpellChecker::SpellChecker(string path) {
    ifstream file(path);
    string line;
    
    while (std::getline(file, line))
    {
        remove_if(line.begin(), line.end(), isspace);
        string word;
        string freq;
        for (char c : line) {
          if (std::isdigit(c)) {
            freq.push_back(c);
          } else {
            word.push_back(c);
          }
        }
        wordCount[word] = std::stol(freq);
    }
}

string SpellChecker::correction(string word) {
  string mostLikelyWord;
  double prob = 0.0;
  for (string w : getCorrectionCandidates(word)) {
    double p = probability(w);
    if (p > prob) {
      prob = p;
      mostLikelyWord = w;
    }
  }
  return mostLikelyWord;
}

unordered_set<string> SpellChecker::oneEditDistance(string word) const {
  vector<string> perms;
  // deletes
  for (char c : word) {
    int i = word.find(c);
    perms.push_back(word.substr(0, i) + word.substr(i + 1));
  }
  // inserts
  for (int i = 0; i < word.size() + 1; i++) {
    for (char letter : alphabet) {
      perms.push_back(word.substr(0, i) + letter + word.substr(i));
    }
  }
  // replaces
  for (int i = 0; i < word.size(); i++) {
    for (char letter : alphabet) {
      perms.push_back(word.substr(0, i) + letter + word.substr(i + 1));
    }
  }
  // transposes
  for (int i = 0; i < word.size() - 1; i++) {
    string transposed = word;
    std::swap(transposed[i], transposed[i + 1]);
    perms.push_back(transposed);
  }

  unordered_set<string> permsSet(perms.begin(), perms.end());
  return permsSet;
};

unordered_set<string> SpellChecker::twoEditDistance(string word) const {
  unordered_set<string> twoEdits;
  for (string w : oneEditDistance(word)) {
    unordered_set<string> oneEdits = oneEditDistance(w);
    twoEdits.insert(oneEdits.begin(), oneEdits.end());
  }
  return twoEdits;
};

double SpellChecker::probability(string word) {
  return  wordCount[word];
};

unordered_set<string> SpellChecker::filterKnownWords(unordered_set<string> words) {
   for(auto it = words.begin(); it != words.end(); ) {
        if(!wordCount[*it])
            it = words.erase(it);
        else
            ++it;
    }
    return words;
};

  unordered_set<string> SpellChecker::getCorrectionCandidates(string word) {
    unordered_set<string> ones = filterKnownWords(oneEditDistance(word));
    unordered_set<string> twos = filterKnownWords(twoEditDistance(word));
    ones.insert(twos.begin(), twos.end());
    return ones;
  }

