#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> dict;
string char_set = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ,.?!:;";

int convert_to_lowercase_word(string &token, int &capitalised_flag, int &uppercase_flag){
	string::size_type count = 0;
	string::size_type len = token.size();
	int first_flag = 0;
	for(string::size_type i = 0; i < len; i++){
		if(token[i] >= 'A' && token[i] <= 'Z'){
			if(!first_flag){
				first_flag = i + 1;
			}
			count++;
			token[i] += 0x20;
		}else if(token[i] >= 'a' && token[i] <= 'z'){

		}else{
			return -1;
		}
	}
	if(first_flag != 1 && first_flag != 0){
		return -1;
	}
	if(count == 1){
		capitalised_flag = 1;
	}else if(count > 1){
		uppercase_flag = 1;
	}
	return 0;
}

int find_in_dict(string word){
	vector<string>::iterator iter = find(dict.begin(), dict.end(), word);
	if(iter == dict.end()){//this word is not in dict, add it
		dict.push_back(word);
	}
	iter = find(dict.begin(), dict.end(), word);
	return distance(dict.begin(), iter);
}

void print_dict(){
	cout << endl;
	vector<string>::size_type num = dict.size();
	cout << num << endl;
	vector<string>::iterator iter;
	for(iter = dict.begin(); iter != dict.end(); iter++){
		cout << *iter <<endl;
	}
}

int main(){
	int idx, capitalised_flag, uppercase_flag;
	string token, symbol, word;

	capitalised_flag = 0;
	uppercase_flag = 0;
	symbol = "";
	word = "";
	dict.clear();

	while(cin >> token){
		
		int len = token.size();
		int found_tmp;

		string::size_type found = token.find_first_of(".,!?;:-");
		string::size_type found_wrong_char = token.find_first_not_of(char_set);
		if(found_wrong_char != string::npos){
			return 0;
		}

		if(found == string::npos){// this token is a single word
			int tmp = convert_to_lowercase_word(token, capitalised_flag, uppercase_flag);
			if(tmp == -1){
				return 0;
			}
			idx = find_in_dict(token);
		}else if(found_tmp = (found + 1) % len,
				token[found_tmp] == '.' ||
				token[found_tmp] == ',' ||
				token[found_tmp] == '!' ||
				token[found_tmp] == '?' ||
				token[found_tmp] == ';' ||
				token[found_tmp] == ':'){
			return 0;
		}else{
			symbol = token.substr(found);
			word = token.substr(0, found);
			int tmp = convert_to_lowercase_word(word, capitalised_flag, uppercase_flag);
			if(tmp == -1){
				return 0 ;
			}
			idx = find_in_dict(word);
		}

		if(idx != -1){
	        if(capitalised_flag){
	        	capitalised_flag = 0;
	        	cout << idx << "^";
	        }else if(uppercase_flag){
	        	uppercase_flag = 0;
	        	cout << idx << "!";
	        }else{
	        	cout << idx;
	        }
		}
		idx = -1;

		if(!symbol.empty()){
			cout << " " << symbol;
			symbol.clear();
		}
		cout << " ";

		if(cin.get() == '\n'){
			cout << "R ";
		}

	}
	cout << 'E';

	print_dict();

	return 0;
}