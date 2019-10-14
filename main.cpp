#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <bitset>
#include <bits/stdc++.h> 
#include <map>

#define SIZE 20000

using namespace std;

/**
 *  HELPERS
 */

void populate_list(int (&list)[SIZE], int v) {
  string binaries;
  ifstream file;

  if (v == 1) {
    file.open("chave.txt");
  } else if (v == 2) {
    file.open("chave2.txt");
  } else if (v == 3) {
    file.open("chave3.txt");
  } else if (v == 4) {
    file.open("chave4.txt");
  } else if (v == 5) {
    file.open("chave5.txt");
  } else if (v == 6) {
    file.open("chave6.txt");
  } else if (v == 7) {
    file.open("chave7.txt");
  } else if (v == 8) {
    file.open("chave8.txt");
  } else if (v == 9) {
    file.open("chave9.txt");
  } else if (v == 10) {
    file.open("chave10.txt");
  }

  if (file.is_open()) {
    int HEAD = 0;

    while(getline(file, binaries)) {
      int len = binaries.length();
      char char_array[len + 1];

      strcpy(char_array, binaries.c_str());

      for (int i = 0; i < len; i++) {
        stringstream str;
        str << char_array[i];
        int bit;
        str >> bit;

        list[HEAD + i] = bit;
      }

      HEAD = len;
    }
  }

  file.close();
}

int get_one_count(int (&list)[SIZE]) {
  int count = 0;

  for (int i = 0; i < SIZE; i++) {
    if (list[i] == 1) count++;
  }

  return count;
}

/**
 *  TESTES
 */

bool monobit_test(int (&list)[SIZE]) {
  int one_count = get_one_count(list);

  cout << "X: " << one_count << endl;

  return one_count > 9654 && one_count < 10346;
}

bool poker_test(int (&list)[SIZE]) {
  double X;
  map<string, int> dictionary;

  for (int i = 0; i < SIZE; i += 4) {
    ostringstream oss;
    oss << list[i] << list[i + 1] << list[i + 2] << list[i + 3];


    string key = oss.str();
    if (dictionary.find(key) != dictionary.end()) {
      dictionary[key] += 1;
    } else {
      dictionary[key] = 1;
    }
  }

  int sum = 0;
  for (auto& x : dictionary) {
    sum += x.second * x.second;
  }

  X = (16.0 / 5000.0) * sum - 5000.0;

  cout << "X: " << X << endl;

  return X > 1.03 && X < 57.4;
}

bool run_test(int (&list)[SIZE]) {
  map<int, int> dictionary;
  int last_item = 2;
  int run_length = 0;

  for (int i = 0; i < SIZE; i ++) {
    int cur_item = list[i];
    if (last_item == cur_item) {
      if (run_length < 6) {
        run_length++;
      }
    } else {
      if (dictionary.find(run_length) != dictionary.end()) {
          dictionary[run_length] += 1;
      } else {
          dictionary[run_length] = 1;
      }

      run_length = 1;
      last_item = cur_item;
    }
  }

  int one_length = dictionary[1];
  int two_length = dictionary[2];
  int three_length = dictionary[3];
  int four_length = dictionary[4];
  int five_length = dictionary[5];
  int six_length = dictionary[6];

  cout << "1: " << one_length << ", 2: " << two_length << ", 3: " << three_length << ", 4: " << four_length << ", 5: "<< five_length << ", 6+:"<< six_length << endl;

  return one_length >= 2267 && one_length <= 2733 && two_length >= 1079 && two_length <= 1421 && three_length >= 502 && three_length <= 748 && four_length >= 223 && four_length <= 402 && five_length >= 90 && five_length <= 223 && six_length >= 90 && six_length <= 223;
}

bool long_run_test(int (&list)[SIZE]) {
  map<int, int> dictionary;
  int last_item = 2;
  int run_length = 0;

  for (int i = 0; i < SIZE; i ++) {
    int cur_item = list[i];
    if (last_item == cur_item) {
      if (run_length < 34) {
        run_length++;
      }
    } else {
      if (dictionary.find(run_length) != dictionary.end()) {
          dictionary[run_length] += 1;
      } else {
          dictionary[run_length] = 1;
      }

      run_length = 1;
      last_item = cur_item;
    }
  }

  return dictionary.find(34) == dictionary.end();
}

void execute(int v) {
  cout << endl << "-------------" << endl << "Chave " << v << endl << "-------------" << endl;

  // Populate list
  int binaries[SIZE];
  populate_list(binaries, v);

  bool monobit_pass = monobit_test(binaries);
  if (monobit_pass) {
    cout << "Monobit Test: Passed!" << endl << endl;
  } else {
    cout << "Monobit Test: Fail!" << endl << endl;
  }

  bool poker_pass = poker_test(binaries);
  if (poker_pass) {
    cout << "Poker Test: Passed!" << endl << endl;
  } else {
    cout << "Poker Test: Fail!" << endl << endl;
  }

  bool run_pass = run_test(binaries);
  if (run_pass) {
    cout << "Run Test: Passed!" << endl << endl;
  } else {
    cout << "Run Test: Fail!" << endl << endl;
  }

  bool long_run_pass = long_run_test(binaries);
  if (long_run_pass) {
    cout << "Long Run Test: Passed!" << endl << endl;
  } else {
    cout << "Long Run Test: Fail!" << endl << endl;
  }
}

int main() {
  for (int i = 1; i <= 10; i++)
    execute(i);

  return 0;
}