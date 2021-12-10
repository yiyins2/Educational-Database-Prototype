#pragma once

#include <map>
#include <vector>
#include <string>

#include "field_info.hpp"
#include "messages.hpp"

using namespace std;

class schema {
	private:
		vector<string> field_names;
		vector<int> field_types; 
	public:
		schema() {}
		bool add_field(string, int);
		int get_field_idx(string);
		vector<string> get_field_names();
		vector<int> get_field_types();
		int get_num_fields();
		bool has_field(string);
};