#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>	//<for stringstream
#include <iomanip>	//<for setprecision()

using namespace std;

struct Token{
	string label;
	double x1;
	double y1;
	double x2;
	double y2;
	bool intersection_flag;
};

vector<Token> g_token_list;
bool g_first_time_1 = true;
bool g_first_time_2 = true;

double Determinant(double d_11, double d_12, double d_21, double d_22){
	return d_11 * d_22 - d_12 * d_21;
}

void Intersection(vector<Token>::iterator line_1, vector<Token>::iterator line_2){
	double delta = Determinant(
				   line_1->x2 - line_1->x1, -(line_2->x2 - line_2->x1),
				   line_1->y2 - line_1->y1, -(line_2->y2 - line_2->y1)
				   );
	if(delta != 0){
		double lamda = Determinant(line_2->x1 - line_1->x1, -(line_2->x2 - line_2->x1),
								   line_2->y1 - line_1->y1, -(line_2->y2 - line_2->y1))
						/ delta;
		double mu 	 = Determinant(line_1->x2 - line_1->x1, (line_2->x1 - line_1->x1),
								   line_1->y2 - line_1->y1, (line_2->y1 - line_1->y1))
						/ delta;
		if(lamda >= 0 && lamda <= 1 && mu >= 0 && mu <= 1){
			if(g_first_time_1 == true){
				cout << "Intersecting Lines:" << endl;
				g_first_time_1 = false;
			}
			cout << fixed << setprecision(2);
			cout << line_1->label << " " << line_2->label << " "
				 <<	line_1->x1 + lamda * (line_1->x2 - line_1->x1) << "\t"
				 << line_1->y1 + lamda * (line_1->y2 - line_1->y1) << endl;
				 line_1->intersection_flag = true;
				 line_2->intersection_flag = true;
		}
	}

}

int
main(){
	ifstream in_file("input.in");	//<input data file
	string token;
	stringstream ss;
	Token s_token;
	while(getline(in_file, token)){
		ss.clear();
		ss << token;
		ss >> s_token.label;
		ss >> s_token.x1;
		ss >> s_token.y1;
		ss >> s_token.x2;
		ss >> s_token.y2;
		s_token.intersection_flag = false;
		g_token_list.push_back(s_token);
	}
	for(auto line_1 = g_token_list.begin(); line_1 < g_token_list.end(); line_1++){
		for(auto line_2 = line_1 + 1; line_2 < g_token_list.end(); line_2++){
			Intersection(line_1, line_2);
		}
	}
	for(auto iter = g_token_list.begin(); iter < g_token_list.end(); iter++){
		if(iter->intersection_flag == false){
			if(g_first_time_2 == true){
				cout << "No intersections:" << endl;
				g_first_time_2 = false;
			}
			cout << iter->label << endl;
		}
	}
}