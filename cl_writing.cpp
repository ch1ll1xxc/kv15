#include "cl_writing.h"
#include "cl_base.h"
#include <iostream>

cl_writing::cl_writing(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}

void cl_writing::signal_f(string& message) {

}

void cl_writing::handler_f(string message) {
	cout << "i get a message!";
}