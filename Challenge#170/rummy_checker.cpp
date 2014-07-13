#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <map>

using namespace std;

map<string, int> card_nums;
map<string, int> card_types;

string card_nums_to_word[14] = {
	"", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven", 
	"Eight", "Nine", "Ten", "Jack", "Queen", "King"
};
string card_types_to_word[4] = {
	"Spades", "Hearts", "Clubs", "Diamonds"
};

void cards_info_init(){
	card_nums.insert(make_pair("Ace", 	1));
	card_nums.insert(make_pair("Two", 	2));
	card_nums.insert(make_pair("Three", 3));
	card_nums.insert(make_pair("Four", 	4));
	card_nums.insert(make_pair("Five", 	5));
	card_nums.insert(make_pair("Six", 	6));
	card_nums.insert(make_pair("Seven", 7));
	card_nums.insert(make_pair("Eight", 8));
	card_nums.insert(make_pair("Nine", 	9));
	card_nums.insert(make_pair("Ten", 	10));
	card_nums.insert(make_pair("Jack", 	11));
	card_nums.insert(make_pair("Queen", 12));
	card_nums.insert(make_pair("King", 	13));

	card_types.insert(make_pair("Spades", 	0));
	card_types.insert(make_pair("Hearts", 	1));
	card_types.insert(make_pair("Clubs", 	2));
	card_types.insert(make_pair("Diamonds", 3));
}

pair<int, int> split(string &token){
	size_t pos = token.find_first_of(" ");
	size_t length = token.length();
	string card_num = token.substr(0, pos);
	string card_type = token.substr(pos + 4, length - pos - 4);
	return make_pair(card_types[card_type], card_nums[card_num]);
}

class hand_cards_info {
private:
	int cards_set[4][14];
	int check_mask[4][14];
	int sets[14];

public:
	void construct_cards(string &hand_info);
	hand_cards_info();
	void print(int cards[][14]);
	pair<int, int> analysis(int idx, pair<int, int> &card);
	void swap(int idx, int &type, int &num, pair<int, int> &card);
	bool check_set(int column);
	void clear_check_mask();
	int * get_cards_set();
	int * get_check_mask();

};

int * hand_cards_info::get_cards_set(){
	return &cards_set[0][0];
}

int * hand_cards_info::get_check_mask(){
	return &check_mask[0][0];
}

void hand_cards_info::clear_check_mask(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 14; j++){
			check_mask[i][j] = 0;
		}
	}
}

void hand_cards_info::swap(int idx, int &type, int &num, pair<int, int> &card){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 14; j++){
			if(cards_set[i][j]){
				if(idx == 0){
					cards_set[i][j] = 0;
					type = i;
					num = j;
					cards_set[card.first][card.second] = 1;
					return;
				}else{
					idx--;
				}
			}
		}
	}
}

pair<int, int> hand_cards_info::analysis(int idx, pair<int, int> &card){
	int type, num;
	int run_num = 0;
	swap(idx, type, num, card);

	// check run
	//print(cards_set);
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 14; j++){
			if(cards_set[i][j]){
				run_num++;
			}else if(run_num == 3 || run_num == 4){
				for(int k = 0; k < run_num; k ++){
					check_mask[i][j - 1 - k] = 1;
				}
				run_num = 0;
			}else if(run_num == 5){
				bool flag_1 = check_set(j);
				bool flag_2 = check_set(j - 4);
				if(flag_1 || flag_2){
					cards_set[card.first][card.second] = 0;
					cards_set[type][num] = 1;
					return make_pair(type, num);
				}else{
					cards_set[card.first][card.second] = 0;
					cards_set[type][num] = 1;
					return make_pair(0, 0);
				}
			}else if(run_num == 6){
				cards_set[card.first][card.second] = 0;
				cards_set[type][num] = 1;
				return make_pair(0, 0);
			}else if(run_num == 7){
				cards_set[card.first][card.second] = 0;
				cards_set[type][num] = 1;
				return make_pair(type, num);
			}else{
				run_num = 0;
			}
		}
		run_num = 0;
	}

	for(int i = 0; i < 14; i++){
		check_set(i);
	}

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 14; j++){
			if(cards_set[i][j] != check_mask[i][j]){
				cards_set[card.first][card.second] = 0;
				cards_set[type][num] = 1;
				return make_pair(0, 0);
			}
		}
	}

	cards_set[card.first][card.second] = 0;
	cards_set[type][num] = 1;

	//print(check_mask);

	return make_pair(type, num);
}

bool hand_cards_info::check_set(int column){
	int count = 0;
	for(int i = 0; i < 4; i++){
		if(cards_set[i][column]){
			count++;
		}
	}
	if(count == 3 || count == 4){
		for(int i = 0; i < 4; i++){
		if(cards_set[i][column]){
			check_mask[i][column] = 1;
		}
	}
		return true;
	}else{
		return false;
	}
}


void hand_cards_info::print(int cards[][14]){
	cout << "cards set: " << endl;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 14; j++){
			cout << cards[i][j] << " ";
		}
		cout << endl;
	}
}

hand_cards_info::hand_cards_info(){
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 14; j++){
			cards_set[i][j] = 0;
		}
	}

	for(int i = 0; i < 14; i++){
		sets[i] = 0;
	}
}

void hand_cards_info::construct_cards(string &hand_info){
	size_t last_searched_pos = -2;
	size_t current_searched_pos;
	while(current_searched_pos = hand_info.find(",", last_searched_pos + 2), current_searched_pos != string::npos){
		string token = hand_info.substr(last_searched_pos + 2, current_searched_pos - last_searched_pos - 2);
		pair<int, int> card = split(token);
		cards_set[card.first][card.second] = 1;
		last_searched_pos = current_searched_pos;
	}
	string token = hand_info.substr(last_searched_pos + 2, hand_info.length() - last_searched_pos - 2);
	pair<int, int> card = split(token);
	cards_set[card.first][card.second] = 1;

}

int main(){
	string hand_info, pickup_info;
	pair<int, int> ans;
	ifstream in;
	in.open("hand.txt");
	cards_info_init();
	while(getline(in, hand_info) && getline(in, pickup_info)){
		hand_cards_info c_hand_cards;
		c_hand_cards.construct_cards(hand_info);
		pair<int, int> pickup_card = split(pickup_info);
		for(int i = 0; i < 7; i++){
			ans = c_hand_cards.analysis(i, pickup_card);
			c_hand_cards.clear_check_mask();
			if(ans.second) break;
		}

		if(ans.second){
			cout << "Swap the new card for the " << card_nums_to_word[ans.second] << " of " << card_types_to_word[ans.first] << " to win!" << endl;
		}else{
			cout << "No possible winning hand." << endl;
		}
	}

	return 0;
}