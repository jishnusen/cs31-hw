#include <cassert>
/* #include <cstdio> */
#include <cctype>
#include <cstring>
#include <iostream>

using namespace std;

const int MAX_WORD_LENGTH = 20;

// Helper function to make string lower case
void makeLower(char s[]) {
  int i = 0;
  while (s[i] != '\0') { // make lower case until we see end of string
    s[i] = tolower(s[i]);
    i++;
  }
}

// Helper function to check if any non letter chars in string
bool nonLetter(char s[]) {
  int i = 0;
  while (s[i] != '\0') { // check for nonletters until end of string
    if (isalpha(s[i]) == 0) {
      return true;
    }
    i++;
  }
  return false;
}

// Helper function to check for duplicate rules
int lookup(char a[][MAX_WORD_LENGTH + 1], char b[][MAX_WORD_LENGTH + 1], int n,
           int pos) {
  if (n < 0) {
    return -1;
  }
  int ret = -1; // if -1 returned, no duplicate rules were found
  for (int i = 0; i < n; i++) {
    // If there is a rule with same word_in and no word_out, then we should keep
    // it. This works even if both the rules have same word_in and no word_out
    // as then it doesn't matter which is deleted
    if (strcmp(a[i], a[pos]) == 0 && strcmp(b[i], "") == 0 && i != pos) {
      return i;
    }
    // If there is a rule with same word_in and word_out, lets store it. We will
    // return this if there is no word_in duplicate rules with no word_out
    // found.
    if (strcmp(a[i], a[pos]) == 0 && strcmp(b[i], b[pos]) == 0 && i < pos) {
      ret = i;
    }
  }
  return ret;
}

// Helper function to set two rules to empty strings. We use this to sanitize
// the array of rules so that the non empty rules are first
void clearRow(char a[], char b[]) {
  strcpy(a, "");
  strcpy(b, "");
}

// Helper function to push the empty rules to the end of the function, so that
// the returned value indicates the number of valid rules.
int pushEmpty(char wordin[][MAX_WORD_LENGTH + 1],
              char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
  int j = 0; // stores last non-empty word
  for (int i = 0; i < nRules; i++) {
    if (strcmp(wordin[i], "") != 0) { // if a word isn't empty, swap it with j
      char tmpin[MAX_WORD_LENGTH + 1];
      strcpy(tmpin, wordin[i]);
      strcpy(wordin[i], wordin[j]);
      strcpy(wordin[j], tmpin);
      char tmpout[MAX_WORD_LENGTH + 1];
      strcpy(tmpout, wordout[i]);
      strcpy(wordout[i], wordout[j]);
      strcpy(wordout[j], tmpout);
      j++; // after the word is swapped, increment j so that it isn't
           // overwritten
    }
  }
  return j; // we can just return j for array size not index, as j was
            // incremented at the end of the loop
}

int cleanUpRules(char wordin[][MAX_WORD_LENGTH + 1],
                 char wordout[][MAX_WORD_LENGTH + 1], int nRules) {
  if (nRules < 0) {
    nRules = 0;
  }
  for (int i = 0; i < nRules; i++) {
    // First we make everything lowercase by convention
    makeLower(wordin[i]);
    makeLower(wordout[i]);

    // Then we remove rules that have same in and out
    if (strcmp(wordin[i], wordout[i]) == 0) {
      clearRow(wordin[i], wordout[i]);
      continue;
    }

    // Then we remove rules with non-letter chars
    if (nonLetter(wordin[i]) || nonLetter(wordout[i])) {
      clearRow(wordin[i], wordout[i]);
      continue;
    }

    // Then we check for any duplicates with this rule
    if (lookup(wordin, wordout, nRules, i) != -1) {
      clearRow(wordin[i], wordout[i]);
      continue;
    }
  }
  return pushEmpty(wordin, wordout, nRules);
}

// Helper function to populate "ret" with a substring of s starting at point p
// and of size l.
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

  char doccpy[251]; // A copy of document to be sanitized
  int n = 0;
  int i = 0;
  while (document[i] != '\0') {
    // Store only alphas and spaces in doccpy
    if (isalpha(document[i]) || document[i] == ' ') {
      doccpy[n] = document[i];
      n++;
    }
    i++;
  }
  // Give doccpy an "end" char for posterity
  doccpy[n] = '\0';

  int ret = 0;   // Var that will store number of fulfilled rules
  char sub[251]; // Var that will hold substrings

  makeLower(doccpy); // Last sanitization step to make doccpy lowercase

  // Our strategy is to check the whole document with each rule
  for (int i = 0; i < nRules; i++) {
    if (strcmp(wordout[i], "") == 0) {  // there is no w_out, just check w_in
      int k = 0;                        // index of start of word
      for (int j = 0; j < n + 1; j++) { // For each char in document
        if (doccpy[j] == ' ' ||
            doccpy[j] == '\0') { // If we find a space or end char,
                                 // we are at the end of a word
          strcpy(sub, "");       // Empty out our substring storage
          substring(sub, doccpy, k,
                    j - k); // Fill it with the substring of the word using out
                            // stored last start of word
          if (strcmp(sub, wordin[i]) == 0) { // Check if it satisfies rule
            ret++; // We only need to satisfy the rule once
            break;
          }
          k = j + 1; // Update word start index
        }
      }
    } else {                    // Now for two word rules
      int k = 0;                // start of word
      bool rule_passed = false; // stores if the rule worked
      for (int j = 0; j < n + 1; j++) {
        if (doccpy[j] == ' ' || doccpy[j] == '\0') {
          strcpy(sub, "");
          substring(sub, doccpy, k, j - k);
          if (strcmp(sub, wordin[i]) ==
              0) { // We don't break this time so we can make sure word_out
                   // isn't in the doc
            rule_passed = true;
          } else if (strcmp(sub, wordout[i]) == 0) {
            rule_passed = false;
            break; // If word_out is found, rule fails no matter what
          }
          k = j + 1;
        }
      }
      ret += rule_passed; // boolean = 1 or 0, so we can increment by it to save
                          // sloc
    }
  }

  return ret;
}

/* void printRules(char wordin[][MAX_WORD_LENGTH + 1], */
/*                  char wordout[][MAX_WORD_LENGTH + 1], int nRules) { */
/*   for (int i = 0; i < nRules; i++) { */
/*     printf("%s\t%s\n", wordin[i], wordout[i]); */
/*   } */
/* } */

int main() {
  const int TEST0_NRULES = 12;
  char test0win[TEST0_NRULES][MAX_WORD_LENGTH + 1] = {
      "confusion", "FAMILY", "charm", "hearty", "house", "worn-out",
      "family",    "charm",  "ties",  "",       "charm", "FaMiLy",
  };

  char test0wout[TEST0_NRULES][MAX_WORD_LENGTH + 1] = {
      "",      "TIES", "confusion", "hearty",     "intrigue", "younger",
      "first", "",     "family",    "frightened", "",         "tIeS",
  };

  assert(cleanUpRules(test0win, test0wout, TEST0_NRULES) == 6);
  /* printRules(test0win, test0wout, TEST0_NRULES); */

  const int TEST2_NRULES = 2;
  char test2win[TEST2_NRULES][MAX_WORD_LENGTH + 1] = {
      "confusion", "",
  };
  char test2wout[TEST2_NRULES][MAX_WORD_LENGTH + 1] = {
      "confusion", "confusion",
  };
  assert(cleanUpRules(test2win, test2wout, TEST2_NRULES) == 0);

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
  assert(determineScore("horse!", test1win, test1wout, TEST1_NRULES) == 1);
  assert(determineScore("ho!r!se!", test1win, test1wout, TEST1_NRULES) == 1);
  assert(determineScore("unhappy", test1win, test1wout, TEST1_NRULES) == 1);
  assert(determineScore("horse:stable ratio is 10:1", test1win, test1wout,
                        TEST1_NRULES) == 0);
  assert(determineScore("**** 2020 ****", test1win, test1wout, TEST1_NRULES) ==
         0);
  assert(determineScore("", test1win, test1wout, TEST1_NRULES) == 0);
  cout << "All tests succeeded" << endl;
}
