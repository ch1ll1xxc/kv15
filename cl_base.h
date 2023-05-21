#ifndef CL_BASE_H
#define CL_BASE_H
#include <string>
#include <vector>
using namespace std;
//KV4___________
class cl_base;
#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f);
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f);
typedef void (cl_base ::* TYPE_SIGNAL)(string&); // указатель на метод сигнала объекта
typedef void (cl_base ::* TYPE_HANDLER)(string); // указатель на метод обработчика объекта
struct o_sh { // Структура задания одной связи
	TYPE_SIGNAL p_signal; // Указатель на метод сигнала
	cl_base* p_cl_base; // Указатель на целевой объект
	TYPE_HANDLER p_handler; // Указатель на метод обработчика
};
//_______________
class cl_base {
private:
	string s_object_name; // имя объекта
	cl_base* p_head_object; // указатель на родителя
	vector <cl_base*> subordinate_objects; // вектор указателей на детей
	//KV2________________
	int condition = 0; // состояние объекта
	//KV4________________
	int cl_add_num; // класс наследования
	vector <o_sh*> connections; // вектор из указателями на соединения
		//___________________
public:
	cl_base(cl_base* p_head_object, string s_object_name = "Base_Object"); //конструктор
		~cl_base(); //деструктор
		bool setName(string object_name); //установка имени
		string getName(); //получение имени
		cl_base* getParent(); //получение указателя на родителя
		cl_base* getChild(string parent_name); //получение указателя на ребенка
		void print(); //вывод
			//KV2_________________
		cl_base* find_obj_in_tree(string name_p); // поиск объекта в дереве по имени
		cl_base* find_obj_in_twig(string name_p); // поиск объекта в ветке по имени
		void print_from_current(int i = 0); // вывод объектов от текущего
		void print_cond_from_current(int i = 0); // вывод объектов от текущего с состоянием объекта
			void set_cond(int val); // установка состояния
		//____________________
		//KV3_________________
		bool newParent(cl_base* object); // смена родителя
		bool eliminate(string object_name); // удаление
		cl_base* findWay(string way); // нахождение объекта по координате
		//____________________
		//KV4_________________
		void set_cl_add_num(int cl_add_num);
		// устновка номера класса
		int get_cl_add_num();
		// получение номера класса
		int get_cond();
		// получение состояния объекта
		void set_cond_ready();
		// установка готовности всех объектов
		string get_abs();
		// получение абсолютной координаты объекта
		void set_conn(TYPE_SIGNAL p_signal, cl_base* p_cl_object, TYPE_HANDLER
			p_handler); // установка соединения
		void delete_conn(TYPE_SIGNAL p_signal, cl_base* p_cl_object, TYPE_HANDLER
			p_handler); // удаление соединения
		void emit_sign(TYPE_SIGNAL p_signal, string s_command);
		// выдачи сигнала и отработки соответствующих обработчиков
		//____________________
};
#endif