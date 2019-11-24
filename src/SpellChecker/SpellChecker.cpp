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

    if (!file.good())
    {
      throw std::runtime_error("The path does not exist: " + path);
    }
    
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

string SpellChecker::correction(string const& word) const {
  if (wordCount.find(word) != wordCount.end()) { return word; }
  const unordered_set<string> candidates = getCorrectionCandidates(word);

  return *std::max_element(begin(candidates), end(candidates),
                            [this](const string& candidateA,  const string& candidateB) {
                              return probability(candidateA) < probability(candidateB);
                            });
}

unordered_set<string> SpellChecker::oneEditDistance(string const& word) const {
  unordered_set<string> permutations;
  // deletes
  for (int i = 0; i < word.size(); i++) {
    permutations.insert(word.substr(0, i) + word.substr(i + 1));
  }
  // inserts
  for (int i = 0; i < word.size() + 1; i++) {
    for (auto& letter : alphabet) {
      permutations.insert(word.substr(0, i) + letter + word.substr(i));
    }
  }
  // replaces
  for (int i = 0; i < word.size(); i++) {
    for (auto& letter : alphabet) {
      permutations.insert(word.substr(0, i) + letter + word.substr(i + 1));
    }
  }
  // transposes
  for (int i = 0; i < word.size() - 1; i++) {
    string transposed = word;
    std::swap(transposed[i], transposed[i + 1]);
    permutations.insert(transposed);
  }

  return permutations;
};

unordered_set<string> SpellChecker::twoEditDistance(string const& word) const {
  unordered_set<string> twoEdits;
  for (auto& w : oneEditDistance(word)) {
    unordered_set<string> oneEdits = oneEditDistance(w);
    twoEdits.insert(oneEdits.begin(), oneEdits.end());
  }
  return twoEdits;
};

unordered_set<string> SpellChecker::filterKnownWords(unordered_set<string> const& words) const {
  unordered_set<string> knowWords;
  std::copy_if(begin(words), end(words), std::inserter(knowWords, knowWords.begin()), 
                            [this](string const& word){ return wordCount.find(word) != wordCount.end(); });
  return knowWords;
};

  unordered_set<string> SpellChecker::getCorrectionCandidates(string const& word) const {
    unordered_set<string> oneEdits = oneEditDistance(word);
    unordered_set<string> twoEdits = twoEditDistance(word);
    unordered_set<string> ones = filterKnownWords(oneEdits);
    unordered_set<string> twos = filterKnownWords(twoEdits);
    ones.insert(twos.begin(), twos.end());
    return ones;
  }

