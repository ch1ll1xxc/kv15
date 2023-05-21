#ifndef __CL_FLAT__H__
#define __CL_FLAT__H__
#include "cl_base.h"

using namespace std;

class cl_flat : public cl_base
{
private:
	int number;
public:
	cl_flat(cl_base* p_head_object, string s_object_name); 		 // конструктор
	void signal_f(string& message);							     // прием сигнала
	void handler_f(string message);							     // выдача сигнала
	void setNum(int num);
	int getNum();
};

#endif
