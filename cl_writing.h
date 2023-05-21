#ifndef __CL_WRITING__H__
#define __CL_WRITING__H__
#include "cl_base.h"

using namespace std;

class cl_writing : public cl_base
{
public:
	cl_writing(cl_base* p_head_object, string s_object_name); // �����������
	void signal_f(string& message);							     // ����� �������
	void handler_f(string message);							     // ������ �������
};

#endif
