#include "cl_reading.h"
#include "cl_base.h"
#include <iostream>
#include <sstream>

cl_reading::cl_reading(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {};

void cl_reading::signal_f(string& message) {
	//cout << "Reading signal\n";
	//cout << "Message -> " << message << endl;
	message = message + ' ' + data + ' ';
}

void cl_reading::handler_f(string message) {
	//cout << "Reading handler\n";
	//cout << "Message -> " << message << endl;
	if (message == "Input_data") { getline(cin, data); }
}