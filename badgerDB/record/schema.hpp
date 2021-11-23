#pragma once

#include <map>
#include <vector>
#include <string>

using namespace std;

class schema {
	private:
		vector<string> field_names;
		vector<int> field_types; 
	
	public:
		schema() {}
		bool add_field(string, int);
		vector<string> get_field_names();
		vector<int> get_field_types();
		int get_record_size();
};