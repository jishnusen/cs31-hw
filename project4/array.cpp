#include <iostream>
#include <cassert>
#include <string>
#include <cmath>

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
  if (n < 0 || pos < 0) {
    return -1;
  }
  string del = a[pos];
  for (int i = pos; i < n; i++) {
    a[i] = a[i + 1];
  }
  a[n - 1] = del;
  return pos;
}

int countRuns(const string a[], int n) {
  if (n <= 0) {
    return -1;
  }
  int cnt = 1;
  for (int i = 0; i < n; i++) {
    if (i > 0) {
      if (a[i] != a[i - 1]) {
        cnt++;
      }
    }
  }
  return cnt;
}

int flip(string a[], int n) {
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
    if (i > min(n1, n2)) {
      return i;
    }
    if (a1[i] != a2[i]) {
      return i;
    }
  }
  return min(n1, n2);
}

int main() {
  string h[7] = { "martha", "mark", "joe", "susan", "", "kamala", "lindsey" };
  assert(lookup(h, 7, "kamala") == 5);
  assert(lookup(h, 7, "joe") == 2);
  assert(lookup(h, 2, "joe") == -1);
  assert(positionOfMax(h, 7) == 3);

  string g[4] = { "martha", "mark", "lindsey", "sara" };
  assert(differ(h, 4, g, 4) == 2);
  assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
  assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");


  /* string politician[5] = { "kamala", "jamie", "lindsey", "sara", "mark" }; */
  /* string res[5] = {"kamala", "lindsey", "sara", "mark", "jamie"}; */
  /* assert(rotateLeft(politician, 5, 1) == 1); */

  /* string d[5] = { "mark", "mark", "mark", "susan", "susan" }; */
  /* assert(countRuns(d, 5) == 2); */

  string f[3] = { "lindsey", "joe", "mike" };
  /* assert(lookupAny(h, 7, f, 3) == 2); */
  assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

  string folks[6] = { "donald", "mike", "", "susan", "sara", "jamie" };
  string group[5] = { "donald", "mike", "jamie", "", "susan" };

  assert(differ(folks, 6, group, 5) == 2);
  assert(differ(folks, 2, group, 1) == 1);
  
  cout << "All tests passed" << endl;
}
