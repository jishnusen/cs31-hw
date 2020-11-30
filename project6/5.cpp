#include <cstdio>

void removeS(char *s) {
  char *src = s;
  while (*src) {
    *s = *src;
    if (*s != 'S' && *s != 's') {
      s++;
    }
    src++;
  }
  *s = '\0';
}

int main() {
  char msg[50] = "She'll be a massless princess.";
  removeS(msg);
  puts(msg); // prints   he'll be a male prince.
}
