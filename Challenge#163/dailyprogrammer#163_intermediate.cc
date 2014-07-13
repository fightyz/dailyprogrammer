// http://www.reddit.com/r/dailyprogrammer/comments/263dp1/5212014_challenge_163_intermediate_fallouts/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <array>

using namespace std;

vector<string> read_dictionary(const string filename, const size_t letters){
	ifstream file(filename);
	vector<string> dict;
	string word;
	for(; getline(file, word);){
		if(word.size() - 1 == letters){ //<because there is a \r in word's trailing
			dict.push_back(word);
		}
	}
	random_shuffle(dict.begin(), dict.end(), [] (int i){return rand() % i;});	//<[] represents that the followings are lamda function
	return dict;
}

vector<string> get_words(const size_t letters, const int num, const vector<string> &dict){
	vector<string> wordlist;
	for(int i = 0; i < num; i++){
		auto word = dict[i];
		wordlist.push_back(word);
		transform(word.begin(), word.end(), word.begin(), (int(&)(int))std::toupper);
		cout << word << endl;
	}
	return wordlist;
}

string get_secret(vector<string> &wordlist, const size_t letters){
	auto res = wordlist[rand() % letters];
	res.pop_back();
	return res;
}

int guess_word(const string word, const string guess){
	if(word.size() != guess.size()){
		cout << "Bad Guess";
		return 0;
	}
	int number_correct = 0;
	for(size_t i = 0; i < word.size(); i++){
		if(tolower(word[i]) == tolower(guess[i]))
			number_correct++;
	}
	return number_correct;
}

int main(){
	srand((unsigned)time(NULL));
	const array< array<int,2> ,5> settings = {{{4,10},{7,10},{10,10},{13,10},{15,10}}};
	cout << "Difficulty (1-5)? ";
	int difficulty;
	cin >> difficulty;

	auto length = settings[difficulty - 1][0], amount = settings[difficulty - 1][1];

	auto dict = read_dictionary("enable1.txt", length);
	auto wordlist = get_words(length, amount, dict);
	auto word = get_secret(wordlist, amount);

	size_t number_correct = 0, guesses = 0;
	do{
		cout << "Guess: (" << 4 - guesses << " left)? ";
		string guess;
		cin >> guess;
		number_correct = guess_word(word, guess);
		guesses++;
		cout << number_correct << "/" << word.size() << " Correct" << endl;
		if(number_correct == word.size())
			cout << "You Win!" << endl;
	}while(number_correct != word.size() && guesses < 4);
}