#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

int main() {
	ifstream in("input.in");
	streambuf *cinbuf = cin.rdbuf();
	cin.rdbuf(in.rdbuf());

	ofstream out("output.out");
	streambuf *coutbuf = cout.rdbuf();
	cout.rdbuf(out.rdbuf());
  /* Load dictionary. */
  vector<string> dictionary;
  unsigned count;
  cin >> count;
  while (count-- > 0) {
    string word;
    cin >> word;
    dictionary.push_back(word);
  }

  /* Decompress input */
  bool needSpace = false;
  string token;
  while (!cin.eof()) {
    cin >> token;
    if (token == "E") {
      break;
    } else if (token == "R") {
      cout << endl;
      needSpace = false;
    } else if (token == "-") {
      cout << "-";
      needSpace = false;
    } else if (token.find_first_of(".,?!;:") == 0) {
      cout << token;
      needSpace = true;
    } else {
      if (needSpace) cout << " ";
      string word = dictionary[stoi(token)];
      char modifier = token[token.size() - 1];
      switch (modifier) {
        case '^':
          word[0] = toupper(word[0]);
          break;
        case '!':
          for (auto &c : word) {
            c = toupper(c);
          }
          break;
      }
      cout << word;
      needSpace = true;
    }
  }
  cin.rdbuf(cinbuf);
  cout.rdbuf(coutbuf);

  return 0;
}