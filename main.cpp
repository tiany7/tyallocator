


#include <bits/stdc++.h>
#include "my_allocator.h"
using namespace std;
int main() {
	vector<int, ty_allocator<int>>v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	for (auto i : v){
		cout<<i<<endl;
	}
	return 0;
}
