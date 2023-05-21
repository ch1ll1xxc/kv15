#ifndef __CL_LIFT__H__
#define __CL_LIFT__H__
#include "cl_base.h"

using namespace std;

class cl_lift : public cl_base
{
public:
	cl_lift(cl_base* p_head_object, string s_object_name); // конструктор
	void signal_f(string& message);							     // прием сигнала
	void handler_f(string message);							     // выдача сигнала
};

#endif
