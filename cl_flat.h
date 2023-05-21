#ifndef __CL_FLAT__H__
#define __CL_FLAT__H__
#include "cl_base.h"

using namespace std;

class cl_flat : public cl_base
{
private:
	int number;
public:
	cl_flat(cl_base* p_head_object, string s_object_name); 		 // �����������
	void signal_f(string& message);							     // ����� �������
	void handler_f(string message);							     // ������ �������
	void setNum(int num);
	int getNum();
};

#endif
