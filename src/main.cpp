#include <iostream>
#include <unordered_set>
#include "SpellChecker/SpellChecker.h"


int main() {
  SpellChecker checker("utils/word_freq.txt");

  std::cout << "Running SpellChecker";
  std::cout << checker.correction("expresion") << std::endl;
  std::cout << checker.correction("thea") << std::endl;
  std::cout << checker.correction("helk") << std::endl;
  std::cout << checker.correction("javaf") << std::endl;
  std::cout << checker.correction("programser") << std::endl;
  
}