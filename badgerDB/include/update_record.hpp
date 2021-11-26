#pragma once

struct update_record {
	int field_pos_idx;		// Field position in the record
	int new_value;

	update_record(int idx, int new_value) {
		this->field_pos_idx = idx;
		this->new_value = new_value;
	}
};