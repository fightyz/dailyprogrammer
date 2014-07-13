#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

class Dice{
public:
	void init();
	int roll() const;	//<roll dice once, return the number
	void countSideOccurence(int side);	//<cont occurence of each side
	int getSideOccurence(int side);
private:
	int m_side_occurence[7];	//<m_side_occurence[0] is not used
};

void Dice::init(){
	for(int i = 0; i < 7; i++){
		m_side_occurence[i] = 0;
	}
}

int Dice::roll() const{
	return rand() % 6 + 1;
}

void Dice::countSideOccurence(int side){
	m_side_occurence[side]++;
}

int Dice::getSideOccurence(int side ){
	return m_side_occurence[side];
}

int main(){
	Dice c_dice;
	int side_num;
	srand((unsigned)time(NULL));	//<generate the seed of rand()
	cout << "# of Rolls" << "\t" << "1s" << "\t" << "2s" << "\t" 
		 << "3s" << "\t" << "4s" <<"\t" << "5s" << "\t" << "6s" << endl;
	cout << "==============================================================" << endl;
	for(int rolls_num = 10; rolls_num < 1000001; rolls_num *= 10){
		c_dice.init();
		for(int i = 0; i < rolls_num; i++){
			side_num = c_dice.roll();
			c_dice.countSideOccurence(side_num);
		}
		cout.setf(ios::fixed);
		cout << rolls_num <<
		"\t\t" << setprecision(2) << c_dice.getSideOccurence(1) / (float)rolls_num * 100 << "%" <<
		"\t" << c_dice.getSideOccurence(2) / (float)rolls_num * 100 << "%" <<
		"\t" << c_dice.getSideOccurence(3) / (float)rolls_num * 100 << "%" <<
		"\t" << c_dice.getSideOccurence(4) / (float)rolls_num * 100 << "%" <<
		"\t" << c_dice.getSideOccurence(5) / (float)rolls_num * 100 << "%" <<
		"\t" << c_dice.getSideOccurence(6) / (float)rolls_num * 100 << "%" <<
		endl;

	}
}