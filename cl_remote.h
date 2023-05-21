#ifndef __CL_REMOTE__H__
#define __CL_REMOTE__H__
#include "cl_base.h"

using namespace std;

class cl_remote : public cl_base
{
private:
	string data;
public:
	cl_remote(cl_base* p_head_object, string s_object_name); // конструктор
	void signal_f(string& message);							     // прием сигнала
	void handler_f(string message);							     // выдача сигнала
};

#endif