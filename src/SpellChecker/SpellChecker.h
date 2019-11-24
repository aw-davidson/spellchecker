#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>

class SpellChecker {
  private:
    std::string alphabet = "abcdefghijklmnopqrstuv";
    std::unordered_map<std::string, long> wordCount;

    long probability(std::string const& word) const {
      return wordCount.find(word)->second;
    };
    std::unordered_set<std::string> oneEditDistance(std::string const& word) const;
    std::unordered_set<std::string> twoEditDistance(std::string const& word) const;
    std::unordered_set<std::string> getCorrectionCandidates (std::string const& word) const;
    std::unordered_set<std::string> filterKnownWords(std::unordered_set<std::string> const& words) const;

  public:
    SpellChecker(std::string path);
    std::string correction(std::string const& word) const;
};