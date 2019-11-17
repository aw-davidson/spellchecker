#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>

#include "SpellChecker.h"
#include "Utils.h"


SpellChecker::SpellChecker(std::string path) {
  std::ifstream infile(path);
  std::string text;
  while (infile >> text)
  {
      removePunct(text);
      std::transform(text.begin(), text.end(), text.begin(), ::tolower);
      ++wordCount[text];
      ++wordTotal;
  }
}

std::string SpellChecker::correction(std::string word) {
  std::string mostLikelyWord;
  double prob = 0.0;
  for (std::string w : getCorrectionCandidates(word)) {
    double p = probability(w);
    if (p > prob) {
      prob = p;
      mostLikelyWord = w;
    }
  }
  return mostLikelyWord;
}

std::unordered_set<std::string> SpellChecker::oneEditDistance(std::string word) const {
  std::vector<std::string> perms;
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
    std::string transposed = word;
    std::swap(transposed[i], transposed[i + 1]);
    perms.push_back(transposed);
  }

  std::unordered_set<std::string> permsSet(perms.begin(), perms.end());
  return permsSet;
};

std::unordered_set<std::string> SpellChecker::twoEditDistance(std::string word) const {
  std::unordered_set<std::string> twoEdits;
  for (std::string w : oneEditDistance(word)) {
    std::unordered_set<std::string> oneEdits = oneEditDistance(w);
    twoEdits.insert(oneEdits.begin(), oneEdits.end());
  }
  return twoEdits;
};

// std::unordered_set<std::string> SpellChecker::filterKnownWords() {

// };

double SpellChecker::probability(std::string word) {
  return  wordCount[word] / (double)wordTotal;
};

std::unordered_set<std::string> SpellChecker::filterKnownWords(std::unordered_set<std::string> words) {
   for(auto it = words.begin(); it != words.end(); ) {
        if(!wordCount[*it])
            it = words.erase(it);
        else
            ++it;
    }
    return words;
};

  std::unordered_set<std::string> SpellChecker::getCorrectionCandidates(std::string word) {
    std::unordered_set<std::string> ones = filterKnownWords(oneEditDistance(word));
    std::unordered_set<std::string> twos = filterKnownWords(twoEditDistance(word));
    ones.insert(twos.begin(), twos.end());
    return ones;
  }

