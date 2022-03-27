
#include <stack>
#include <iostream>
#include <vector>
using namespace std;
struct node {

	int arr[8][8];
	pair <int,int> loc;
	node* parent_node;
	bool explord=false;
};

bool flag_win = false;


void print_arr(int arr[][8]) {
	// print the bord
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			cout << arr[x][y] << " ";
		}
		cout << endl;
	}
}











//mark all the position that the new queen takes
void mark_pos(node &stack) {
	pair<int, int> pos = stack.loc;
	
	cout << stack.loc.first << "  " << stack.loc.second << endl;
	// mark vartical 
	for (int i = pos.first + 1; i < 8; i++) {
		
		stack.arr[i][pos.second]=1;
	}
	for (int i = pos.first-1; i >=0 ; i--) {
		
		stack.arr[i][pos.second] = 1;
	}


	// mark horzintal
	for (int i = pos.second+1; i < 8; i++) {
	
		stack.arr[pos.first][i] = 1;
	}
	for (int i = pos.second-1; i >= 0; i--) {
		
		stack.arr[pos.first][i] = 1;
	}

	int xpos = pos.first;
	// mark dagonal 

	for (int i = pos.second + 1; i < 8 && --xpos >= 0; i++) {

		stack.arr[xpos][i] = 1;
	}

	int xpos1 = pos.first;

	for (int i = pos.second - 1; i >= 0 &&xpos1++ <7; i--) {
		
		stack.arr[xpos1][i] = 1;
	}


	int ypos = pos.second;

	// mark dagonal 
	for (int i = pos.first + 1; i < 8 && ypos<7; i++) {
		
		stack.arr[i][++ypos] = 1;
	}

	int ypos1 = pos.second;

	for (int i = pos.first - 1; i >= 0 && ypos1>0; i--) {
	
		stack.arr[i][--ypos1] = 1;
	}



	print_arr(stack.arr);
}



bool check_win(node& stack) {
	int con = 0;
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (stack.arr[x][y] == 2)
				con++;
		}
	}
	if (con == 8)
		return true;
	else
		return false;
}


void explor_node(stack<node>& stack) {

	//check if the top node is a goal node 
	if (check_win(stack.top())) {
		cout << "ez boy" << endl;
		flag_win = true;
		return;
	}


	pair<int, int > pos = stack.top().loc;
	int layer = pos.first + 1;
	vector<node>subarr;
	for (int i = 0; i < 8; i++) {
		if (stack.top().arr[layer][i] == 0) {

			node* childe = new node;

			//deep copy
			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					childe->arr[x][y] = stack.top().arr[x][y];
				}
			}

			//set value for childes
				childe->loc = make_pair(layer, i);
				childe->parent_node = &stack.top();
				childe->arr[layer][i] = 2;
				mark_pos(*childe);
				subarr.push_back(*childe);
			
		}
	}
	

	stack.pop();

	for (int i = 0; i < subarr.size(); i++) {

		stack.push(subarr.back());
		subarr.pop_back();

	}
	explor_node(stack);
}


	

void queen8sol(int arr[][8] ) {
	//making the parent stats
	node parent[8];
	//making stack
	stack<node> stack;

	for (int i = 0; i < 8; i++) {

		//deep copy
		for (int x = 0; x < 8; x++) {
			for (int y = 0; y < 8; y++) {
				parent[i].arr[x][y] = arr[x][y];
			}
		}

		//set valus for parent stats
		parent[i].arr[0][i] = 2;
		parent[i].loc = make_pair(0, i);


		stack.push(parent[i]);
		mark_pos(stack.top());
	}


	explor_node(stack);
	return;

}


int main()
{
	int arr[8][8]{};

	
	queen8sol(arr);
	
}
