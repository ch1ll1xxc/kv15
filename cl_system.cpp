#include "cl_system.h"
#include "cl_reading.h"
#include "cl_remote.h"
#include "cl_lift.h"
#include "cl_flat.h"
#include "cl_writing.h"
//#include "cl_passenger.h"
//#include "cl_pass_lift.h"
//#include "cl_pass_flat.h"

#include <sstream>
#include <iostream>
#include <string>

using namespace std;

void cl_system::signal_f(string& message) {
}

void cl_system::handler_f(string message) {
	//cout << "System handler\n";
	//cout << "Message -> " << message << endl;

	stringstream ss;
	string comm;
	ss << message;
	ss >> comm;
	if (comm == "System") {
		ss << message;
		ss >> comm;
		if (comm == "n_m") {
			ss << message << message;
			ss >> n >> m;
		}
		else if (comm == "End") {}
	}
}

cl_system::cl_system(cl_base* p_head_object) : cl_base(p_head_object) {
	signals[0] = SIGNAL_D(cl_system::signal_f);
	signals[1] = SIGNAL_D(cl_reading::signal_f);
	signals[2] = SIGNAL_D(cl_remote::signal_f);
	signals[3] = SIGNAL_D(cl_lift::signal_f);
	signals[4] = SIGNAL_D(cl_flat::signal_f);
	signals[5] = SIGNAL_D(cl_writing::signal_f);
	//signals[6] = SIGNAL_D(cl_passenger::signal_f);
	/*
	signals = {SIGNAL_D(cl_system::signal_f),
				SIGNAL_D(cl_reading::signal_f),
				SIGNAL_D(cl_remote::signal_f),
				SIGNAL_D(cl_lift::signal_f),
				SIGNAL_D(cl_flat::signal_f),
				SIGNAL_D(cl_writing::signal_f),
				SIGNAL_D(cl_passenger::signal_f)};
	*/
	handlers[0] = HANDLER_D(cl_system::handler_f);
	handlers[1] = HANDLER_D(cl_reading::handler_f);
	handlers[2] = HANDLER_D(cl_remote::handler_f);
	handlers[3] = HANDLER_D(cl_lift::handler_f);
	handlers[4] = HANDLER_D(cl_flat::handler_f);
	handlers[5] = HANDLER_D(cl_writing::handler_f);
	//handlers[6] = HANDLER_D(cl_passenger::handler_f);
	/*
	handlers = {HANDLER_D(cl_system::handler_f),
				HANDLER_D(cl_reading::handler_f),
				HANDLER_D(cl_remote::handler_f),
				HANDLER_D(cl_lift::handler_f),
				HANDLER_D(cl_flat::handler_f),
				HANDLER_D(cl_writing::handler_f),
				HANDLER_D(cl_passenger::handler_f)};
	*/
	set_cl_add_num(1);
	command = "";
};

void cl_system::firstObjects() {
	this->setName("System");
	system = this;
	reading = new cl_reading(system, "Reading");
	reading->set_cl_add_num(2);
	remote = new cl_remote(system, "Remote");
	reading->set_cl_add_num(3);
	lift = new cl_lift(remote, "Lift");
	reading->set_cl_add_num(4);
	//cl_base *test = new cl_remote(system, "test");
}

void cl_system::firstConn() {
	system->set_conn(signals[0], remote, handlers[2]);
	remote->set_conn(signals[2], system, handlers[0]);

	reading->set_conn(signals[1], remote, handlers[2]);
	remote->set_conn(signals[2], reading, handlers[1]);
	
}

void cl_system::secondObjects() {
	int i = 0;
	while (i < n) {
		cl_base* flat = new cl_flat(system, "Flat" + to_string(i+1));
		flat->set_cl_add_num(5);
		flats.push_back(flat);
		i++;

	}
	writing = new cl_writing(system, "Writing");
	writing->set_cl_add_num(10);
	cl_base* test = new cl_remote(system, "test");
}



void cl_system::buildTree() {

	// First
	firstObjects();

	// Second
	firstConn();
	set_cond_ready(); // Я это исправил

	// Third
	while (true) {
		command = "Input_data";
		remote->emit_sign(signals[2], command);
		//cout << "___" << endl;
		//system -> emit_sign(signals[0], command);
		//cout << "___" << endl;
		command = "Remote_data";
		reading->emit_sign(signals[1], command);
		//cout << "___" << endl;
		command = "System n_m";
		remote->emit_sign(signals[2], command);
		//cout << "___" << endl;
		break;
	}

	cout << n << ' ' << m;
	// Fourth

	//secondObjects();
	secondObjects();
	set_cond_ready();

	//Fivth
	print_cond_from_current();
	cout << endl;

}

int cl_system::exec() {


	return 0;
}