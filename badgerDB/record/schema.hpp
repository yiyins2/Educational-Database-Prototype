#pragma once

#include <map>
#include <vector>
#include <string>

#include "field_info.hpp"

using namespace std;

class schema {
	private:
		vector<string> field_names;
	
	public:
		schema() {}
		int addField(string);
		vector<string> get_field_names();
		int get_record_size();
};