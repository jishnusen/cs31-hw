
#include <iostream>
using namespace std;

// This function returns the greater of the two integers pointed to
int *maxwell(int *a, int *b) {
  if (*a > *b)
    return a;
  else
    return b;
}

// This function switches the variable that the pointers point to
void swap1(int *a, int *b) {
  int *temp = a;
  a = b;
  b = temp;
}

// This function switches the values of the variables that the pointers
// point to
void swap2(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main() {
  // Declare the array
  int array[6] = {5, 3, 4, 17, 22, 19};

  // Set ptr to point to element 0 as it is bigger than element 2
  int *ptr = maxwell(array, &array[2]);
  // Modify element 0 to be -1, now
  // array = { -1, 3, 4, 17, 22, 19 };
  *ptr = -1;
  // Move ptr to element 2
  ptr += 2;
  // Modify element 3 to be 9, now
  // array = { -1, 3, 4, 9, 22, 19 };
  ptr[1] = 9;
  // Modify element 1 to be 79, now
  // array = { -1, 79, 4, 9, 22, 19 };
  *(array + 1) = 79;

  // Print the index difference between 5 and ptr
  // ptr is at element 2, so this prints 3
  cout << &array[5] - ptr << endl;

  // Make array[0] point to array[1] and vice versa
  // array = { -1, 79, 4, 9, 22, 19 };
  swap1(&array[0], &array[1]);
  // This swaps the value of array[1] and array[3]
  // array = { 4, 79, -1, 9, 22, 19 };
  swap2(array, &array[2]);

  for (int i = 0; i < 6; i++)
    // print each element of:
    // array = { 4, 79, -1, 9, 22, 19 };
    cout << array[i] << endl;
}
