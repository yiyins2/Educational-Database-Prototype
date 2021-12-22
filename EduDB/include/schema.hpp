#pragma once

#include <map>
#include <vector>
#include <string>
#include <algorithm>

#include "field_info.hpp"
#include "constant.hpp"

using namespace std;

class schema {
	private:
		vector<string> field_names;
	
	public:
		schema() {}
		int addField(string);
		int get_field_idx(string);
		vector<string> get_field_names();
		int get_record_size();
		bool has_field(string);
};