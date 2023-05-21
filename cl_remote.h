#ifndef __CL_REMOTE__H__
#define __CL_REMOTE__H__
#include "cl_base.h"

using namespace std;

class cl_remote : public cl_base
{
private:
	string data;
public:
	cl_remote(cl_base* p_head_object, string s_object_name); // �����������
	void signal_f(string& message);							     // ����� �������
	void handler_f(string message);							     // ������ �������
};

#endif