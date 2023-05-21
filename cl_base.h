#ifndef CL_BASE_H
#define CL_BASE_H
#include <string>
#include <vector>
using namespace std;
//KV4___________
class cl_base;
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f);
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f);
typedef void (cl_base ::* TYPE_SIGNAL)(string&); // ��������� �� ����� ������� �������
typedef void (cl_base ::* TYPE_HANDLER)(string); // ��������� �� ����� ����������� �������
struct o_sh { // ��������� ������� ����� �����
	TYPE_SIGNAL p_signal; // ��������� �� ����� �������
	cl_base* p_cl_base; // ��������� �� ������� ������
	TYPE_HANDLER p_handler; // ��������� �� ����� �����������
};
//_______________
class cl_base {
private:
	string s_object_name; // ��� �������
	cl_base* p_head_object; // ��������� �� ��������
	vector <cl_base*> subordinate_objects; // ������ ���������� �� �����
	//KV2________________
	int condition = 0; // ��������� �������
	//KV4________________
	int cl_add_num; // ����� ������������
	vector <o_sh*> connections; // ������ �� ����������� �� ����������
		//___________________
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_Object"); //�����������
		~cl_base(); //����������
		bool setName(string object_name); //��������� �����
		string getName(); //��������� �����
		cl_base* getParent(); //��������� ��������� �� ��������
		cl_base* getChild(string parent_name); //��������� ��������� �� �������
		void print(); //�����
			//KV2_________________
		cl_base* find_obj_in_tree(string name_p); // ����� ������� � ������ �� �����
		cl_base* find_obj_in_twig(string name_p); // ����� ������� � ����� �� �����
		void print_from_current(int i = 0); // ����� �������� �� ��������
		void print_cond_from_current(int i = 0); // ����� �������� �� �������� � ���������� �������
			void set_cond(int val); // ��������� ���������
		//____________________
		//KV3_________________
		bool newParent(cl_base* object); // ����� ��������
		bool eliminate(string object_name); // ��������
		cl_base* findWay(string way); // ���������� ������� �� ����������
		//____________________
		//KV4_________________
		void set_cl_add_num(int cl_add_num);
		// �������� ������ ������
		int get_cl_add_num();
		// ��������� ������ ������
		int get_cond();
		// ��������� ��������� �������
		void set_cond_ready();
		// ��������� ���������� ���� ��������
		string get_abs();
		// ��������� ���������� ���������� �������
		void set_conn(TYPE_SIGNAL p_signal, cl_base* p_cl_object, TYPE_HANDLER
			p_handler); // ��������� ����������
		void delete_conn(TYPE_SIGNAL p_signal, cl_base* p_cl_object, TYPE_HANDLER
			p_handler); // �������� ����������
		void emit_sign(TYPE_SIGNAL p_signal, string s_command);
		// ������ ������� � ��������� ��������������� ������������
		//____________________
};
#endif