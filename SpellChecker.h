#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

class SpellChecker {
  private:
    std::string alphabet = "abcdefghijklmnopqrstuv";
    std::unordered_map<std::string, int> wordCount;
    int wordTotal = 0;
    

  public:
    SpellChecker(std::string path);
    double probability(std::string word);
    std::string correction(std::string word);
    std::unordered_set<std::string> oneEditDistance(std::string word) const;
    std::unordered_set<std::string> twoEditDistance(std::string word) const;
    std::unordered_set<std::string> filterKnownWords(std::unordered_set<std::string> words);
    
    std::unordered_set<std::string> getCorrectionCandidates (std::string word);
};