#include <cassert>
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_WORD_LENGTH = 20;

// Helper function to make string lower case
void makeLower(char s[]) {
  int i = 0;
  while (s[i] != '\0') {
    s[i] = tolower(s[i]);
    i++;
  }
}

bool nonLetter(char s[]) {
  int i = 0;
  while (s[i] != '\0') {
    if (isalpha(s[i]) == 0) {
      return true;
    }
    i++;
  }
  return false;
}

int lookup(char a[][MAX_WORD_LENGTH + 1], char b[][MAX_WORD_LENGTH + 1], int n,
           int pos) {
  if (n < 0) {
    return -1;
  }
  int ret = -1;
  for (int i = 0; i < n; i++) {
    if (strcmp(a[i], a[pos]) == 0 && strcmp(b[i], "") == 0 && i != pos) {
      return i;
    }
    if (strcmp(a[i], a[pos]) == 0 && strcmp(b[i], b[pos]) == 0 && i < pos) {
      ret = i;
    }
  }
  return ret;
}

void clearRow(char a[], char b[]) {
  strcpy(a, "");
  strcpy(b, "");
}

int pushEmpty(char wordin[][MAX_WORD_LENGTH + 1],
              char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
  int j = 0;
  for (int i = 0; i < nRules; i++) {
    if (strcmp(wordin[i], "") != 0) {
      char tmpin[MAX_WORD_LENGTH + 1];
      strcpy(tmpin, wordin[i]);
      strcpy(wordin[i], wordin[j]);
      strcpy(wordin[j], tmpin);
      char tmpout[MAX_WORD_LENGTH + 1];
      strcpy(tmpout, wordout[i]);
      strcpy(wordout[i], wordout[j]);
      strcpy(wordout[j], tmpout);
      j++;
    }
  }
  return j;
}

int cleanUpRules(char wordin[][MAX_WORD_LENGTH + 1],
                 char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
  if (nRules < 0) {
    nRules = 0;
  }
  for (int i = 0; i < nRules; i++) {
    makeLower(wordin[i]);
    makeLower(wordout[i]);

    if (strcmp(wordin[i], wordout[i]) == 0) {
      clearRow(wordin[i], wordout[i]);
    }

    if (nonLetter(wordin[i]) || nonLetter(wordout[i])) {
      clearRow(wordin[i], wordout[i]);
    }

    if (lookup(wordin, wordout, nRules, i) != -1) {
      clearRow(wordin[i], wordout[i]);
    }
  }
  return pushEmpty(wordin, wordout, nRules);
}

void substring(char ret[], const char s[], int p, int l) {
  strncpy(ret, s + p, l);
  ret[l] = '\0';
}

int determineScore(const char document[],
                   const char wordin[][MAX_WORD_LENGTH + 1],
                   const char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
  if (nRules < 0) {
    nRules = 0;
  }

  char doccpy[251];
  int n = 0;
  int i = 0;
  while (document[i] != '\0') {
    if (isalpha(document[i]) || document[i] == ' ') {
      doccpy[n] = document[i];
      n++;
    }
    i++;
  }
  doccpy[n] = '\0';

  int ret = 0;
  char sub[251];

  makeLower(doccpy);

  for (int i = 0; i < nRules; i++) {
    if (strcmp(wordout[i], "") == 0) { // there is no w_out, just check w_in
      int k = 0;                       // start of word
      for (int j = 0; j < n; j++) {
        if (doccpy[j] == ' ') {
          strcpy(sub, "");
          substring(sub, doccpy, k, j - k);
          if (strcmp(sub, wordin[i]) == 0) {
            ret++;
            break;
          }
          k = j + 1;
        }
      }
    } else {
      int k = 0; // start of word
      bool rule_passed = false;
      for (int j = 0; j < n; j++) {
        if (doccpy[j] == ' ') {
          strcpy(sub, "");
          substring(sub, doccpy, k, j - k);
          if (strcmp(sub, wordin[i]) == 0) {
            rule_passed = true;
          } else if (strcmp(sub, wordout[i]) == 0) {
            rule_passed = false;
            break;
          }
          k = j + 1;
        }
      }
      ret += rule_passed;
    }
  }

  return ret;
}

int main() {
  const int TEST1_NRULES = 3;
  char test1win[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
      "family",
      "unhappy",
      "horse",
  };
  char test1wout[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
      "",
      "horse",
      "",
  };
  assert(determineScore("Happy families are all alike; every unhappy family is "
                        "unhappy in its own way.",
                        test1win, test1wout, TEST1_NRULES) == 2);
  assert(determineScore("Happy horses are all alike; every unhappy horse is "
                        "unhappy in its own way.",
                        test1win, test1wout, TEST1_NRULES - 1) == 0);
  assert(determineScore("Happy horses are all alike; every unhappy horse is "
                        "unhappy in its own way.",
                        test1win, test1wout, TEST1_NRULES) == 1);
  assert(determineScore("A horse!  A horse!  My kingdom for a horse!", test1win,
                        test1wout, TEST1_NRULES) == 1);
  assert(determineScore("horse:stable ratio is 10:1", test1win, test1wout,
                        TEST1_NRULES) == 0);
  assert(determineScore("**** 2020 ****", test1win, test1wout, TEST1_NRULES) ==
         0);
  cout << "All tests succeeded" << endl;
}
