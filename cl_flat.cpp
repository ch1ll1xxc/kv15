#include "cl_flat.h"
#include "cl_base.h"
#include <iostream>

cl_flat::cl_flat(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}

void cl_flat::signal_f(string& message) {
	message += " (class: 5)";
	cout << endl << "Signal from flat " << get_abs();
}

void cl_flat::handler_f(string message) {
	cout << endl << "Signal to (flat) " << get_abs() << " Text: " << message;
}

