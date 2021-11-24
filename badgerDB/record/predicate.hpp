#pragma once
#include <cstdio>
#include <cstring>
using namespace std;

struct predicate {
	int field_idx;
	string op;				// <=, >=, <, >, !=, ==
	int value;

	predicate() {}
	predicate(int field_idx, string op, int value) {
		this->field_idx = field_idx;
		this->op = op;
		this->value = value;
	}

	bool check_operator(string op) {
		if (strcmp(op.c_str(), ">") == 0) {
			return true;
		}

		if (strcmp(op.c_str(), "<") == 0)
		{
			return true;
		}

		if (strcmp(op.c_str(), ">=") == 0)
		{
			return true;
		}

		if (strcmp(op.c_str(), "<=") == 0)
		{
			return true;
		}

		if (strcmp(op.c_str(), "==") == 0)
		{
			return true;
		}

		if (strcmp(op.c_str(), "!=") == 0)
		{
			return true;
		}

		return false;
	}
};