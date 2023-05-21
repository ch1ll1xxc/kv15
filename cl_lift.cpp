#include "cl_lift.h"
#include "cl_base.h"
#include <iostream>

cl_lift::cl_lift(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}

void cl_lift::signal_f(string& message) {
	message += " (class: 4)";
	cout << endl << "Signal from lift " << get_abs();
}

void cl_lift::handler_f(string message) {
	cout << endl << "Signal to (lift) " << get_abs() << " Text: " << message;
}