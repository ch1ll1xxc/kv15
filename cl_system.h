#ifndef __CL_SYSTEM_H__
#define __CL_SYSTEM_H__
#include "cl_base.h"
#include "cl_flat.h"

using namespace std;

class cl_system : public cl_base {
private:
	TYPE_SIGNAL signals[8]; // Сигналы
	TYPE_HANDLER handlers[8];// Обработчики
	string command;// Комманды
	int n, m;// Этажи, вместимость
	cl_base* system;
	cl_base* reading;
	cl_base* remote;
	cl_base* lift;
	cl_base* writing;
	vector<cl_base*>pass;
	vector<cl_base*>flats;
public:
	cl_system(cl_base* p_head_object); // Конструктор
	void signal_f(string& message); // Отправка системы
	void handler_f(string message); // Обработка сигнала
	void firstObjects(); // Инициализация первоначальных объектов системы
	void firstConn(); // Настройка первоначальных связей
	void secondObjects();
	void secondConn();
	void buildTree(); // Построение дерева
	int exec(); // Запуск приложения
};

#endif