#include <iostream>
#include <unordered_set>
#include "SpellChecker.h"


int main() {
  SpellChecker checker("training.txt");

  std::cout << checker.correction("expresion") << std::endl;
  std::cout << checker.correction("pyton") << std::endl;
  std::cout << checker.correction("thea") << std::endl;
  std::cout << checker.correction("asdasd") << std::endl;
  
}