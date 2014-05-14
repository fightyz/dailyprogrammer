// http://www.reddit.com/r/dailyprogrammer/comments/25clki/5122014_challenge_162_easy_novel_compression_pt_1/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(){
	int n, idx;
	int word_flag, capitalised_flag, upper_case_flag, hyphen_flag, times, newline_flag, symbol_flag;
	vector<string> dict;
	string word, str;

	cin >> n;

	for(int i = 0; i < n; i++){
		cin >> word;
		dict.push_back(word);
	}
	word_flag = 0;
	capitalised_flag = 0;
	upper_case_flag = 0;
	hyphen_flag = 0;
	times = 0;
	newline_flag = 0;
	symbol_flag = 0;

	while(!cin.eof()){
		if(newline_flag){
			newline_flag = 0;
			times = 0;
			cout << endl;
		}
		
		cin >> str;
		idx = 0;
		for(string::size_type i = 0; i < str.size(); i++){
			if(str[i] >= '0' && str[i] <= '9'){//this string is a word
				idx = idx * 10 + str[i] - '0';
				word_flag = 1;
			}else if(str[i] == '^'){
				capitalised_flag = 1;
			}else if(str[i] == '!' && i != 0){
				upper_case_flag = 1;
			}else if(str[i] == '-'){
				hyphen_flag = 2;
				cout << str[i];
			}else if(str[i] == '.' || str[i] == ',' || str[i] == '?' 
				|| str[i] == '!' || str[i] == ';' || str[i] == ':'){
				symbol_flag = 1;
				cout << str[i];
			}else if(str[i] == 'R' || str[i] == 'r'){
				newline_flag = 1;
			}else if(str[i] == 'E' || str[i] == 'e'){
				return 0;
			}
		}

		if(symbol_flag){
			symbol_flag = 0;
			continue;
		}
		if(newline_flag){
			continue;
		}

		if(hyphen_flag <= 0 && times){
			cout << " ";
		}else{
			hyphen_flag--;
		}

		if(word_flag){
			word_flag = 0;
			string tmp = dict[idx];
			if(capitalised_flag){
				capitalised_flag = 0;
				tmp[0] = tmp[0] - 32;
			}else if(upper_case_flag){
				upper_case_flag = 0;
				for(string::size_type k = 0; k < tmp.size(); k++){
					tmp[k] = tmp[k] - 32;
				}
			}
			cout << tmp;
		}
		times++;
	}
}