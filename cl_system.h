#ifndef __CL_SYSTEM_H__
#define __CL_SYSTEM_H__
#include "cl_base.h"
#include "cl_flat.h"

using namespace std;

class cl_system : public cl_base {
private:
	TYPE_SIGNAL signals[8]; // �������
	TYPE_HANDLER handlers[8];// �����������
	string command;// ��������
	int n, m;// �����, �����������
	cl_base* system;
	cl_base* reading;
	cl_base* remote;
	cl_base* lift;
	cl_base* writing;
	vector<cl_base*>pass;
	vector<cl_base*>flats;
public:
	cl_system(cl_base* p_head_object); // �����������
	void signal_f(string& message); // �������� �������
	void handler_f(string message); // ��������� �������
	void firstObjects(); // ������������� �������������� �������� �������
	void firstConn(); // ��������� �������������� ������
	void secondObjects();
	void secondConn();
	void buildTree(); // ���������� ������
	int exec(); // ������ ����������
};

#endif