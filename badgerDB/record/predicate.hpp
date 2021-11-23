#pragma once
#include <cstdio>
#include <cstring>
using namespace std;

struct predicate {
	string field;
	string op;				// <=, >=, <, >, !=, ==
	int value;

	predicate() {}
	predicate(string field, string op, int value) {
		this->field = field;
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