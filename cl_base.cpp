#include "cl_base.h"
#include <iostream>
#include <algorithm>
#include <sstream>
using namespace std;
cl_base::cl_base(cl_base* p_head_object, string s_object_name) {
	this->p_head_object = p_head_object;
	this->s_object_name = s_object_name;
	if (p_head_object != nullptr) {
		p_head_object->subordinate_objects.push_back(this);
	}
};
bool cl_base::setName(string object_name) {
	if (getChild(object_name) == nullptr) {
		this->s_object_name = object_name;
		return true;
	}
	else {
		return false;
	}
}
string cl_base::getName() {
	return s_object_name;
}
cl_base* cl_base::getParent() {
	return p_head_object;
}
void cl_base::print() {
	vector <cl_base*> ::iterator it;
	if (p_head_object == nullptr) cout << getName();
	if (subordinate_objects.size() > 0) {
		cout << endl << s_object_name;
		it = subordinate_objects.begin();
		while (it != subordinate_objects.end()) {
			cout << " " << (*it)->getName();
			it++;
		}
		it--;
		(*it)->print();
	}
}
cl_base* cl_base::getChild(string parent_name) {
	for (int i = 0; i < subordinate_objects.size(); i++) {
		if (this->subordinate_objects[i]->getName() == parent_name) {
			return subordinate_objects[i];
		}
	}
	return nullptr;
}

cl_base :: ~cl_base() {
	/*
	vector<cl_base*>remove_objects{ findWay("/") };
	while (remove_objects.size() != 0) {
		cl_base* current = remove_objects.back();
		remove_objects.pop_back();
		for (int i = 0; i < current->connections.size(); i++) {
			if (current->connections[i]->p_cl_base == this) {
				current->delete_conn(current->connections[i] ->
					p_signal, this, current->connections[i]->p_handler);
				i--;
			}
		}
		for (int i = 0; i < current->subordinate_objects.size(); i++)
		{
			remove_objects.push_back(current->subordinate_objects[i]);
		}
	}
	for (int i = 0; i < subordinate_objects.size(); i++) {
		delete
			subordinate_objects[i];
	}
	for (int i = 0; i < connections.size(); i++) { delete connections[i]; }
	subordinate_objects.clear();
	connections.clear();
	*/
	cl_base* head = findWay("/");
	vector<cl_base*>r;
	r.push_back(head);
	while (!r.empty()) {
		cl_base* c = r.back();
		r.pop_back();
		//cout << c->connections.size() << endl;
		//cout << "p_signal -> " << c->connections[i]->p_signal << endl;
		//cout << "p_cl_object -> " << c->getName() << endl;
		//cout << "p_handler -> " << c->connections[i]->p_handler << endl << endl;
		if (c) {
			//cout << "p_signal -> " << c->connections[i]->p_signal << endl;
			cout << "p_cl_object -> " << c->getName() << endl;
			//cout << "p_handler -> " << c->connections[i]->p_handler << endl << endl;
			for (int i = 0; i < c->connections.size(); i++) {
				
				//c->delete_conn(c->connections[i]->p_signal,this,c->connections[i]->p_handler);
				
				if (c->connections[i]->p_cl_base->getName() == this->getName()) {
					c->delete_conn(c->connections[i]->p_signal,
						this,
						c->connections[i]->p_handler);
					i--;
				}
				
			}
			for (auto it : c->subordinate_objects) r.push_back(it);
		}
	}
	for (int i = 0; i < connections.size(); i++) { delete connections[i]; }
	connections.clear();
	for (int i = 0; i < subordinate_objects.size(); i++) {
		delete subordinate_objects[i];
	}
	subordinate_objects.clear();
}
//KV2____________
cl_base* cl_base::find_obj_in_tree(string name_p) {
	cl_base* p_head = this;
	while (p_head->p_head_object != nullptr) {
		p_head = p_head->p_head_object;
	}
	return p_head->find_obj_in_twig(name_p);
}
cl_base* cl_base::find_obj_in_twig(string name_p) {
	int ch = 0;
	vector <cl_base*> arr(1, this);
	cl_base* ptr = nullptr;
	while (arr.size()) {
		cl_base* arr_2 = arr.back();
		arr.pop_back();
		if (arr_2->s_object_name == name_p) {
			ptr = arr_2;
			ch++;
		}
		for (auto i : arr_2->subordinate_objects) { arr.push_back(i); }
	}
	if (ch < 2) { return ptr; }
	else { return nullptr; }
}
void cl_base::print_from_current(int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
	cout << s_object_name;
	for (auto p_sub_obj : subordinate_objects) {
		p_sub_obj ->
			print_from_current(n + 1);
	}
}
void cl_base::print_cond_from_current(int n) {
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << " ";
	}
	cout << s_object_name;
	if (condition != 0) { cout << " is ready"; }
	else { cout << " is not ready"; }
	for (auto p_sub_obj : subordinate_objects) {
		p_sub_obj ->
			print_cond_from_current(n + 1);
	}
}
void cl_base::set_cond(int val) {
	if (p_head_object == nullptr || p_head_object->condition != 0) {
		if (condition != 0 && val == 0) {
			for (auto p_sub_obj : subordinate_objects) {
				p_sub_obj ->
					set_cond(val);
			}
		}
		condition = val;
	}
}
//KV3____________
cl_base* cl_base::findWay(string way) {
	cl_base* current = this;
	string object;
	while (way[0] == '/' && current->p_head_object) {
		current = current ->
			p_head_object;
	}
	way += '/';
	stringstream path(way);
	if (way[0] != '/' && way[0] != '.') {
		getline(path, object, '/');
		current = current->find_obj_in_tree(object);
		while (getline(path, object, '/') && current) {
			current = current ->
				getChild(object);
		}
	}
	else {
		if (way[0] == '/' && way[1] == '/' && way.size() > 3) {
			for (int i = 0; i < 3; i++) { getline(path, object, '/'); }
			current = current->find_obj_in_tree(object);
		}
		else {
			if (way[0] == '.' && way.size() > 2) {
				getline(path, object, '/');
				object.erase(object.begin());
				current = current->find_obj_in_twig(object);
			}
			else {
				if (way.size() > 2) {
					getline(path, object, '/');
					while (getline(path, object, '/') && current)
					{
						current = current->getChild(object);
					}
				}
			}
		}
	}
	return current;
}
bool cl_base::newParent(cl_base* object) {
	bool flag = true;
	cl_base* tmp = object;
	while (tmp->p_head_object && flag) {
		if (tmp->s_object_name == this->s_object_name) { flag = false; }
		tmp = tmp->p_head_object;
	}
	if (!this->p_head_object) { flag = false; }
	else if (flag) {
		int val = 0;
		for (int i = 0; i < this->p_head_object ->
			subordinate_objects.size(); i++) {
			if (this->p_head_object->subordinate_objects[i] ->
				s_object_name == this->s_object_name) {
				val = i;
			}
		}
		this->p_head_object->subordinate_objects.erase(this ->
			p_head_object->subordinate_objects.begin() + val);
		this->p_head_object = object;
		object->subordinate_objects.push_back(this);
	}
	return flag;
}
bool cl_base::eliminate(string name) {
	if (getChild(name) != nullptr) {
		subordinate_objects.erase(remove(subordinate_objects.begin(),
			subordinate_objects.end(), getChild(name)), subordinate_objects.end());
		delete getChild(name);
		return true;
	}
	return false;
}
//KV4________________
void cl_base::set_cl_add_num(int cl_add_num) { this->cl_add_num = cl_add_num; }
int cl_base::get_cl_add_num() { return cl_add_num; }
int cl_base::get_cond() { return condition; }
void cl_base::set_cond_ready() {
	if (this->condition == 0) { this->condition = 1; }
	for (int i = 0; i < subordinate_objects.size(); i++) {
		subordinate_objects[i]
			->set_cond_ready();
	}
}
string cl_base::get_abs() {
	cl_base* current = this;
	string abs = "";
	while (current->p_head_object) {
		abs = '/' + current->s_object_name + abs;
		current = current->p_head_object;
	}
	if (abs == "") { return "/"; }
	else { return abs; }
}
void cl_base::set_conn(TYPE_SIGNAL p_signal, cl_base* p_cl_base, TYPE_HANDLER
	p_handler) {
	o_sh* p_tmp;
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i]->p_signal == p_signal && connections[i] ->
			p_cl_base == p_cl_base &&
			connections[i]->p_handler == p_handler) {
			return;
		}
	}
	p_tmp = new o_sh;
	p_tmp->p_signal = p_signal;
	p_tmp->p_cl_base = p_cl_base;
	p_tmp->p_handler = p_handler;
	this->connections.push_back(p_tmp);
}
void cl_base::delete_conn(TYPE_SIGNAL p_signal, cl_base* p_cl_base, TYPE_HANDLER
	p_handler) {
	for (int i = 0; i < connections.size(); i++) {
		if (connections[i]->p_signal == p_signal && connections[i] ->
			p_cl_base == p_cl_base &&
			connections[i]->p_handler == p_handler) {
			delete connections[i];
			connections.erase(connections.begin() + i);
			return;
		}
	}
}
void cl_base::emit_sign(TYPE_SIGNAL p_signal, string s_command) {
	if (condition != 0) {
		cl_base* current;
		TYPE_HANDLER p_handler;
		(this->*p_signal)(s_command);
		for (int i = 0; i < connections.size(); i++) {
			if (connections[i]->p_signal == p_signal && connections[i] ->
				p_cl_base->condition != 0) {
				current = connections[i]->p_cl_base;
				p_handler = connections[i]->p_handler;
				(current->*p_handler)(s_command);
			}
		}
	}
}