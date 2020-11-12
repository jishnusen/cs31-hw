#include <cassert>
#include <iostream>
#include <string>

using namespace std;

int appendToAll(string a[], int n, string s) {
  if (n < 0) {
    return -1;
  }
  for (int i = 0; i < n; i++) {
    a[i].append(s);
  }
  return n;
}

int lookup(string a[], int n, string s) {
  if (n < 0) {
    return -1;
  }
  for (int i = 0; i < n; i++) {
    if (a[i] == s) {
      return i;
    }
  }
  return -1;
}

int positionOfMax(const string a[], int n) {
  if (n < 0) {
    return -1;
  }
  for (int i = 0; i < n; i++) {
    bool ret = true;
    for (int j = 0; j < n; j++) {
      if (i != j) {
        if (a[i] < a[j]) {
          ret = false;
          break;
        }
      }
    }
    if (ret) {
      return i;
    }
  }
  return -1;
}

int rotateLeft(string a[], int n, int pos) {
  if (n < 1 || pos > n || pos < 0) {
    return -1;
  }
  string del = a[pos];
  for (int i = pos; i < n - 1; i++) {
    a[i] = a[i + 1];
  }
  a[n - 1] = del;
  return pos;
}

int countRuns(const string a[], int n) {
  if (n < 0) {
    return -1;
  }
  int cnt = n != 0;
  for (int i = 1; i < n; i++) {
    if (a[i] != a[i - 1]) {
      cnt++;
    }
  }
  return cnt;
}

int flip(string a[], int n) {
  if (n < 0) {
    return -1;
  }
  for (int i = 0; i < (n / 2); i++) {
    string tmp = a[i];
    a[i] = a[n - i - 1];
    a[n - i - 1] = tmp;
  }

  return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
  int n = max(n1, n2);
  for (int i = 0; i < n; i++) {
    if (i > n1 || i > n2) {
      return i;
    }
    if (a1[i] != a2[i]) {
      return i;
    }
  }
  return n1 < n2 ? n1 : n2;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
  if (n2 > n1 || n1 < 0 || n2 < 0) {
    return -1;
  }
  for (int i = 0; i < (n1 - n2) + 1; i++) {
    bool ret = true;
    for (int j = i; j < i + n2; j++) {
      if (a1[j] != a2[j - i]) {
        ret = false;
        break;
      }
    }
    if (ret) {
      return i;
    }
  }

  if (n1 == 0 && n2 == 0) {
    return 0;
  }

  return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
  if (n1 < 0 || n2 < 0) {
    return -1;
  }
  for (int i = 0; i < n1; i++) {
    for (int j = 0; j < n2; j++) {
      if (a1[i] == a2[j]) {
        return i;
      }
    }
  }
  return -1;
}

int divide(string a[], int n, string divider) {
  if (n < 0) {
    return -1;
  }

  int j = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] < divider) {
      string tmp = a[i];
      a[i] = a[j];
      a[j] = tmp;
      j++;
    }
  }

  for (int i = 0; i < n; i++) {
    if (a[i] >= divider) {
      return i;
    }
  }
  return n;
}

int main() {
  // Array for testing:
  string a[8] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey", "kamala"};

  // Array chosen due to empty string and duplicate

  // LOOKUP Tests:
  assert(lookup(a, 7, "kamala") == 5); // Checks simple lookup with one existing element
  assert(lookup(a, 7, "") == 4); // Checks empty string lookup
  assert(lookup(a, 8, "kamala") == 5); // Checks duplicate element lookup
  assert(lookup(a, 2, "joe") == -1); // Checks nonexistent element lookup
  assert(lookup(a, 0, "joe") == -1); // Checks empty array lookup

  // Make a copy array for appendToAll testing because append modifies the array
  string b[8] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey", "kamala"};

  // APPENDTOALL Tests:
  assert(appendToAll(b, 8, "?") == 8 && b[0] == "martha?" && b[3] == "susan?" && b[4] == "?"); // Checks append with empty and reg strings
  assert(appendToAll(b, 0, "?") == 0 && b[0] == "martha?" && b[3] == "susan?" && b[4] == "?"); // Checks second append leaves array 

  // Make a copy array for rotateLeft testing because append modifies the array
  string c[8] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey", "kamala"};

  // ROTATELEFT TESTS
  assert(rotateLeft(c, 8, 2) == 2 && c[2] == "susan" && c[7] == "joe"); // Simple rotate left
  // Check resultant array == {"martha", "mark", "susan", "", "kamala", "lindsey", "kamala", "joe"}

  assert(rotateLeft(c, 8, 0) == 0 && c[0] == "mark" && c[7] == "martha"); // First element
  // Check resultant array == {"martha", "mark", "susan", "", "kamala", "lindsey", "kamala", "joe"}

  // Make a copy of the testing array because rotateLeft modifies the array
  string d[8] = {"martha", "mark", "joe", "susan", "", "kamala", "kamala", "lindsey"};

  // Another array for runs testing:
  string e[9] = {"susan", "donald", "mike", "mike", "joe", "joe", "joe", "mike", "mike"};

  // COUNTRUNS Tests:
  assert(countRuns(d, 8) == 7); // Array with all unique elements but one
  assert(countRuns(e, 9) == 5); // Array with more than one run
  assert(countRuns(e, 0) == 0); // "empty" array

  // POSITIONOFMAX Tests:
  assert(positionOfMax(d, 8) == 3); // Check regular array
  assert(positionOfMax(e, 9) == 0); // Check array with lots of duplicates
  assert(positionOfMax(d, 0) == -1); // Empty array cannot have intersting elements
  assert(positionOfMax(d, 1) == 0); // Single element should return itself

  string f[2] = {"mike", "mike"};

  assert(positionOfMax(f, 2) == 0); // Only one type of element should return first element

  // Create copy of test array for flip testing
  string g[8] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey", "kamala"};

  // FLIP Tests:
  assert(flip(g, 8) == 8); // Check regular array
  // Check resultant array == {"kamala", "lindsey", "kamala", "", "susan", "joe", "mark", "martha"}

  assert(flip(g, 0) == 0); // Check not flipping any elements
  assert(flip(g, 7) == 7 && g[0] == "mark" && g[1] == "joe" && g[7] == "martha"); // Check regular array
  // Check resultant array == {"mark", "joe", "susan", "", "kamala", "lindsey", "kamala", "martha"}

  // Create copy of test array post-flip
  string h[8] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey", "kamala"};
  string h1[2] = {"martha", "mark"}; // Simple array that matches the start
  string h2[2] = {"susan", ""}; // Array with empty string that matches the middle
  string h3[2] = {"foo", "bar"}; // Array with neither element matching
  string h4[2] = {"susan", "foo"}; // Array with one matching element

  // DIFFER Tests:
  assert(differ(h, 8, h1, 2) == 2); // Check array with no differing elements
  assert(differ(h, 8, h3, 2) == 0); // Check array with no matching elements

  // SUBSEQUENCE Tests:
  assert(subsequence(h, 8, h, 8) == 0); // Check match of identical array 
  assert(subsequence(h, 8, g, 8) == -1); // Check no match of same-length differing array
  assert(subsequence(h, 8, h1, 2) == 0); // Check match at the start
  assert(subsequence(h, 8, h2, 2) == 3); // Check array with empty string that matches the middle
  assert(subsequence(h, 8, h3, 2) == -1); // Check array with neither element matching
  assert(subsequence(h, 8, h4, 2) == -1); // Check array with one matching element
  assert(subsequence(h, 8, h4, 0) == 0); // Check that empty array matches everything
  assert(subsequence(h, 0, h4, 0) == 0); // Check empty array matches empty array

  // LOOKUPANY Tests:
  assert(lookupAny(h, 8, h1, 2) == 0); // Check match at the start with array that has multiple matching values
  assert(lookupAny(h, 8, h2, 2) == 3); // Check match at beginning with array with a stray element
  assert(lookupAny(h, 8, h2, 0) == -1); // Check that empty array has no matching elements

  // DIVIDE Tets:
  assert(positionOfMax(h, 8) == 3);
  assert(divide(h, 8, "susan") == 7); // Check with greatest element, even number array size

  // Copy array after divide
  string k[8] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey", "kamala"};

  assert(divide(k, 7, "mark") == 4); // Check with middle element, odd number array size
  assert(divide(k, 7, "z") == 7); // Check for nothing >= divider 
  cout << "All tests passed" << endl;
}
