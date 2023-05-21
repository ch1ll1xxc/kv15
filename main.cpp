#include <iostream>
#include "cl_system.h"
int main()
{
	cl_system ob_cl_application(nullptr);
	ob_cl_application.buildTree();
	return ob_cl_application.exec();
}