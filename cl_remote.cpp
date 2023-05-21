#include "cl_remote.h"
#include "cl_base.h"
#include <iostream>
#include <string>
#include <sstream>

cl_remote::cl_remote(cl_base* p_head_object, string s_object_name) : cl_base(p_head_object, s_object_name) {}

void cl_remote::signal_f(string& message) {
	//cout << "Remote signal\n";
	//cout << "Message -> " << message << endl;
	//cout << "REMOTE DATA -> " << data << endl;;
	stringstream ss;
	string comm;
	ss << message;
	ss >> comm;
	if (comm == "System") { message += ' ' + data + '\n'; }
}

void cl_remote::handler_f(string message) {
	//cout << "Remote handler\n";
	//cout << "Message -> " << message << endl; 
	stringstream ss;
	string comm;
	ss << message;
	ss >> comm;
	if (comm == "Remote_data") {
		data = message.substr(message.find(' ') + 1, message.size());
	}
}