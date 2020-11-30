#include <iostream>

double mean(const double *scores, int numScores) {
  int i = 0;
  double tot = 0;
  while (i < numScores) {
    tot += *(scores + i);
    i++;
  }
  return tot / numScores;
}

const char *findTheChar(const char *str, char chr) {
  while (*str) {
    if (*str == chr) {
      return str;
    }
    str++;
  }

  return nullptr;
}

int main() {
  const char *arr = "Hey there sir!";
  std::cout << findTheChar(arr, 't') - arr << std::endl;
}
