#include <iostream>
#include <limits>
#include <cmath>
#include <map>
#include <set>
#include <vector>

using namespace std;

const int INFESTED = 0x80;
const int PASSABLE = 0x08;

struct pos {
	int x, y;
	double dist(const pos &other) const {
		double dx = (x - other.x), dy = (y - other.y);
		return sqrt(dx * dx + dy * dy);
	}

	bool operator<(const pos &other) const {
		return x < other.x || (x == other.x && y < other.y);
	}

	bool operator==(const pos &other) const {
		return x == other.x && y == other.y;
	}

	bool operator!=(const pos &other) const {
		return x != other.x || y != other.y;
	}

	pos u() { return pos{x + 0, y + 1}; }
	pos d() { return pos{x + 0, y - 1}; }
	pos l() { return pos{x - 1, y + 0}; }
	pos r() { return pos{x + 1, y + 0}; }
};

struct Map {
	int w, h;
	pos source, dest;
	vector<vector<char> > grid;
	char empty = '\0'; //<for get()

	/* Safely get the tile at (X, Y). */
	char &get(const pos &p) {
		return (p.x >= 0 && p.x < w && p.y >= 0 && p.y < h)
			? grid[p.x][p.y] : empty;
	}

	/* A* shortest path: return shortest path between START and GOAL. */
	vector<pos> astar(pos start, pos goal){
		set<pos> closed, open;
		map<pos, double> g_score, f_score;
		map<pos, pos> came_from;
		open.insert(start);
		g_score[start] = 0.0;
		f_score[start] = start.dist(goal);
		while(!open.empty()){
			double best = numeric_limits<double>::infinity();
			pos current;
			for(auto &p : open) {
				double score = f_score[p];
				if(score < best) {
					best = score;
					current = p;
				}
			}
			open.erase(current);
			closed.insert(current);
			if(current == goal) { //<reach the goal(that is 'o')
				vector<pos> path;
				while(current != start){
					path.push_back(current);
					current = came_from[current];
				}
				return path;
			} else {
				pos neighbors[] = {
					current.u(), current.d(), current.l(), current.r()
				};
				for(auto &p : neighbors) {
					if(closed.count(p) > 0 || !(get(p) & PASSABLE)){
						continue; //<neighbors node is already in closed set, or is '#', '@'
					} else {
						double tentative = g_score[current] + 1;
						if(open.count(p) == 0 || tentative < g_score[p]) {
							came_from[p] = current;
							g_score[p] = tentative;
							f_score[p] = tentative + p.dist(goal);
							open.insert(p);
						}
					}
				}
			}
		}
		return vector<pos>{};
	}

	/* Return true if the bunkers are currently safe. */
	bool safe() {
		return astar(source, dest).empty();
	}

	/* Attempt to solve the map for COUNT walls. */
	bool solve(int count){
		if(count == 0) return safe();
		auto path = astar(source, dest);
		for(auto &p : path) {
			if(get(p) == '-') {
				get(p) = '@';
				if(solve(count - 1)) {
					return true;
				} else {
					get(p) = '-';
				}
			}
		}
		return false;
	}

	/* Remove all infestation markers. */
	void clear(){
		for(int y = 0; y < h; y++){
			for(int x = 0; x < w; x++){
				grid[x][y] &= ~INFESTED;
			}
		}
	}
};

istream & operator>>(istream &in, Map &map) {
	in >> map.h >> map.w;
	map.grid.resize(map.w, vector<char>(map.h));
	for(int y = 0; y < map.h; ++y) {
		for(int x = 0; x < map.w; ++x) {
			in >> map.grid[x][y];
			if(map.grid[x][y] == '*') map.source = {x, y};
			if(map.grid[x][y] == 'o') map.dest = {x, y};
		}
	}
	return in;
}

ostream & operator<<(ostream &out, Map map) {
	for(int y = 0; y < map.h; ++y){
		for(int x = 0; x < map.w; ++x){
			out << map.grid[x][y];
		}
		out << endl;
	}
	return out;
}

int main(){
	Map map;
	cin >> map;
	int wallcount = 0;
	while(!map.solve(wallcount)) ++wallcount;
	cout << wallcount << endl << map;
	return 0;
}