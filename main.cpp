#include "Vector.h"

int main() {
  Vector test1, test2, test3;

  std::ifstream fin("input.txt");
  fin >> test1 >> test2;
  fin.close();

  test3 = test1 + test2;
  customOutput(test3);

  test3 = test1 ^ test2;
  customOutput(test3);

  return 0;
}