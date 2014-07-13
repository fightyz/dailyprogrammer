    #include <iostream>
    #include <climits>
    #include <vector>
    
    using namespace std;
    
    typedef struct {
    	int next;
    	int weight;
    } edge;
    
    typedef struct {
    	int distance;
    	char parent;
    } routine;
    
    int main(){
    	int n;
    	cin >> n;
    	vector<vector<edge> > adjacent_matrix(n);
    	routine rout[n];
    	bool mark[n];
    
    	int temp_weight;
    	for(int i = 0; i < n; i++){
    		for(int j = 0; j < n; j++){
    			cin >> temp_weight;
    			if(temp_weight > -1){
    				edge temp_node;
    				temp_node.next = j;
    				temp_node.weight = temp_weight;
    				adjacent_matrix[i].push_back(temp_node);
    			}
    			cin.get();
    		}
    	}
    	for(int i = 0; i < n; i++){
    		rout[i].distance = -1;
    		mark[i] = false;
    	}
    	char start, end;
    	cin >> start >> end;
    	int new_node = start - 'A';
    	rout[new_node].distance = 0;
    	rout[new_node].parent = -1;
    	mark[new_node] = true;
    
    	for(int i = 1; i < n; i++){
    		for(int j = 0; j < adjacent_matrix[new_node].size(); j++){
    			int temp_node = adjacent_matrix[new_node][j].next;
    			int temp_weight = adjacent_matrix[new_node][j].weight;
    			if(mark[temp_node] == true) continue;
    			if(rout[temp_node].distance == -1 ||
    			   rout[temp_node].distance > rout[new_node].distance + temp_weight){
    				rout[temp_node].distance = rout[new_node].distance + temp_weight;
    				rout[temp_node].parent = new_node + 'A';
    			}
    		}
    		int min = INT_MAX;
    		for(int j = 0; j < n; j++){
    			if(mark[j] == true) continue;
    			if(rout[j].distance == -1) continue;
    			if(rout[j].distance < min){
    				min = rout[j].distance;
    				new_node = j;
    			}
    		}
    		mark[new_node] = true;
    	}
    	cout << rout[end - 'A'].distance << endl;
    	
    	vector<char> tmp;
    	for(;end != EOF; end = rout[end - 'A'].parent){
    		tmp.push_back(end);
    	}
    	for(vector<char>::reverse_iterator riter = tmp.rbegin(); riter != tmp.rend(); riter++){
    		cout << *riter;
    	}
    	cout << endl;
    	return 0;
    }