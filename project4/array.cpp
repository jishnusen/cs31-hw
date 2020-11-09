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
  if (n < 1) {
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
    if (i > min(n1, n2)) {
      return i;
    }
    if (a1[i] != a2[i]) {
      return i;
    }
  }
  return min(n1, n2);
}

int subsequence(const string a1[], int n1, const string a2[], int n2) {
  if (n2 > n1 || n1 < 0 || n2 < 0) {
    return -1;
  }
  for (int i = 0; i < n1 - n2; i++) {
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
  for (int i = 0; i < n; i++) {
    if (a[i] < divider) {
      rotateLeft(a, n, i);
    }
  }

  flip(a, n);

  for (int i = 0; i < n; i++) {
    if (!(a[i] < divider)) {
      return i;
    }
  }
  return n;
}

int main() {
  string h[7] = {"martha", "mark", "joe", "susan", "", "kamala", "lindsey"};
  assert(lookup(h, 7, "kamala") == 5);
  assert(lookup(h, 7, "joe") == 2);
  assert(lookup(h, 2, "joe") == -1);
  assert(positionOfMax(h, 7) == 3);

  string g[4] = {"martha", "mark", "lindsey", "sara"};
  assert(differ(h, 4, g, 4) == 2);
  assert(appendToAll(g, 4, "?") == 4 && g[0] == "martha?" && g[3] == "sara?");
  assert(rotateLeft(g, 4, 1) == 1 && g[1] == "lindsey?" && g[3] == "mark?");

  string politician[5] = {"kamala", "jamie", "lindsey", "sara", "mark"};
  string res[5] = {"kamala", "lindsey", "sara", "mark", "jamie"};
  assert(rotateLeft(politician, 5, 1) == 1);

  string d[5] = {"mark", "mark", "mark", "susan", "susan"};
  assert(countRuns(d, 5) == 2);

  string f[3] = {"lindsey", "joe", "mike"};
  /* assert(lookupAny(h, 7, f, 3) == 2); */
  assert(flip(f, 3) == 3 && f[0] == "mike" && f[2] == "lindsey");

  string folks[6] = {"donald", "mike", "", "susan", "sara", "jamie"};
  string group[5] = {"donald", "mike", "jamie", "", "susan"};

  assert(differ(folks, 6, group, 5) == 2);
  assert(differ(folks, 2, group, 1) == 1);

  string names[10] = {"kamala", "mark", "sara", "martha", "donald", "lindsey"};
  string names1[10] = {"mark", "sara", "martha"};
  int t = subsequence(names, 6, names1, 3); // returns 1
  string names2[10] = {"kamala", "martha"};
  int u = subsequence(names, 5, names2, 2); // returns -1

  assert(t == 1);
  assert(u == -1);

  string names3[10] = {"kamala", "mark", "sara", "martha", "donald", "lindsey"};
  string set1[10] = {"jamie", "donald", "martha", "mark"};
  int v = lookupAny(names3, 6, set1, 4); // returns 1 (a1 has "mark" there)
  string set2[10] = {"susan", "joe"};
  int w = lookupAny(names3, 6, set2, 2); // returns -1 (a1 has none)

  assert(v == 1);
  assert(w == -1);

  string candidate[6] = {"jamie", "lindsey", "mark", "susan", "joe", "donald"};
  int x = divide(candidate, 6, "kamala"); //  returns 3
  string candidate2[4] = { "mark", "sara", "lindsey", "mike" };
  int y = divide(candidate2, 4, "mike");  //  returns 2

  assert(x == 3);
  assert(y == 2);

  cout << "All tests passed" << endl;
}
