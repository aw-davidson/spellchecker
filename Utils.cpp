#include <string>
#include "Utils.h"

using std::ispunct;

void removePunct(std::string& text) {
  for (int i = 0, len = text.size(); i < len; i++) {
      if (ispunct(text[i])) {
          text.erase(i, 1);
          len = text.size();
          i--;
      }
  }
}