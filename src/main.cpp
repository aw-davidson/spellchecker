#include <iostream>
#include <unordered_set>
#include "SpellChecker/SpellChecker.h"
#include <chrono> 
using namespace std::chrono; 
  


int main() {
  try 
  {

    SpellChecker checker("src/utils/word_freq.txt");

    auto start = high_resolution_clock::now(); 
    std::cout << checker.correction("expresion") << std::endl;
    std::cout << checker.correction("thea") << std::endl;
    std::cout << checker.correction("helk") << std::endl;
    std::cout << checker.correction("javaf") << std::endl;
    std::cout << checker.correction("javasipt") << std::endl;
    std::cout << checker.correction("peotry") << std::endl;
    std::cout << checker.correction("auxilaary") << std::endl;
    std::cout << checker.correction("cropg") << std::endl;
    std::cout << checker.correction("velluam") << std::endl;
    std::cout << checker.correction("haiir") << std::endl;
    auto stop = high_resolution_clock::now(); 

    auto duration = duration_cast<microseconds>(stop - start); 
  
    std::cout << "This run took " << duration.count() << " microseconds" << std::endl; 
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