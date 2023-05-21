#ifndef __CL_READING_H__
#define __CL_READING_H__
#include "cl_base.h"

using namespace std;

class cl_reading : public cl_base {
private:
	string data;
public:
	cl_reading(cl_base* p_head_object, string s_object_name); // �����������
	void signal_f(string& message);							   // ����� �������
	void handler_f(string message);							   // ������ �������
};

#endif