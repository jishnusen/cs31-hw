#include <iostream>

int main() {
  double *cat;
  double mouse[5];
  cat = mouse + 4;
  *cat = 25;
  *(mouse + 3) = 54;
  cat -= 3;
  cat[1] = 42;
  for (int i = 0; i < 5; i++) {
    std::cout << mouse[i] << std::endl;
  }
}
