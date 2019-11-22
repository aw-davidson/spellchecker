#include <iostream>
#include <unordered_set>
#include "SpellChecker/SpellChecker.h"


int main() {
  try 
  {
    SpellChecker checker("src/utils/word_freq.txt");

    std::cout << checker.correction("expresion") << std::endl;
    std::cout << checker.correction("thea") << std::endl;
    std::cout << checker.correction("helk") << std::endl;
    std::cout << checker.correction("javaf") << std::endl;
    std::cout << checker.correction("programser") << std::endl;
  }
  catch(const std::runtime_error& re)
  {
      std::cerr << "Runtime error: " << re.what() << std::endl;
  }
  catch(const std::exception& ex)
  {
      std::cerr << "Error occurred: " << ex.what() << std::endl;
  }
  catch(...)
  {
      std::cerr << "Unknown failure occurred." << std::endl;
  }
  
}