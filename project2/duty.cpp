#include <iostream>

using namespace std;

int main() {
  cout.setf(ios::fixed);
  cout.precision(2);

  string cheese_type;  // stores type of cheese in raw text
  double cheese_value; // price of the cheese
  string importer;     // name of the cheese importer

  // read in relevant parameters
  cout << "Cheese type: ";
  getline(cin, cheese_type);
  cout << "Value: ";
  cin >> cheese_value;
  cout << "Importer: ";
  cin.ignore(10000, '\n'); // numbers were consumed, so flush cin
  getline(cin, importer);
  cout << "---" << endl;

  if (cheese_type.length() == 0) {
    cout << "You must enter a cheese type" << endl;
    return 0;
  } else if (cheese_value < 0.0) {
    cout << "The value must be positive" << endl;
    return 0;
  } else if (importer.length() == 0) {
    cout << "You must enter an importer" << endl;
    return 0;
  }

  // check first $1000 of value for duty
  double duty = 0.0;
  if (cheese_value <= 1000.0) {
    duty = 0.011 * cheese_value;
  } else {
    duty += 0.011 * 1000.0;

    // cheshire and stilton have a special deal
    double special_percent = 0.02;
    if (cheese_type == "cheshire" || cheese_type == "stilton") {
      special_percent = 0.014;
    }

    // percent for next $13000
    if (cheese_value <= 13000.0) {
      duty += special_percent * (cheese_value - 1000.0);
    } else {
      // remaining price is at 2.9%
      duty += special_percent * 12000.0 + 0.029 * (cheese_value - 13000.0);
    }
  }
  cout << "The import duty for " << importer << " is $" << duty << endl;
  return 0;
}
