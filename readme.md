# SpellChecker
A project inspired by Peter Norvig's essay [How to Write a Spelling Corrector](http://norvig.com/spell-correct.html)

# Demo
```c++
int main() {
  SpellChecker checker("training.txt");

  std::cout << checker.correction("expresion") << std::endl; // expression
  std::cout << checker.correction("thea") << std::endl; // the
  std::cout << checker.correction("helpo") << std::endl; // hello
}
```

# See It In Action
https://repl.it/@awdavids/spellchecker