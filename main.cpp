#include <iostream>
#include <unordered_set>
#include "SpellChecker.h"


int main() {
  SpellChecker checker("word_freq.txt");

  std::cout << checker.correction("expresion") << std::endl;
  std::cout << checker.correction("thea") << std::endl;
  std::cout << checker.correction("helk") << std::endl;
  std::cout << checker.correction("javaf") << std::endl;
  std::cout << checker.correction("programser") << std::endl;
  
}