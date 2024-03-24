#define PY_SSIZE_T_CLEAN
#include <python.h>
#include <iostream>
#include "shape/shape.h"
#include "swigpyrun.h"

int main()
{
	std::cout << "Hello from C++!\n";
	Py_Initialize();
	Circle* circlePtr = new Circle(10);
	circlePtr->x = 5;
	std::cout << "C++ circle has area: " << circlePtr->area() << std::endl;
	PyRun_SimpleString("print('Hello World from Embedded Python!!!')");
	PyRun_SimpleString("from shape import Circle");
	PyRun_SimpleString("circle = None");
	PyRun_SimpleString(
		"def receive(circle_from_cxx):\n"
		"    print ('receive called with %s', circle_from_cxx)\n"
		"    print('Python transferred circle has area', circle_from_cxx.area())\n"
		"    global circle\n"
		"    circle = circle_from_cxx\n");
	
	swig_type_info* pTypeInfo = nullptr;
	PyObject* main = PyImport_AddModule("__main__");
	pTypeInfo = SWIG_TypeQuery("_p_Circle");
	int owned = 0;
	PyObject* pInstance = SWIG_NewPointerObj(reinterpret_cast<void*>(circlePtr), pTypeInfo, owned);
	if (pInstance == NULL)
	{
		std::cout << "Something went wrong creating the Python instance of the circle\n";
	}
	PyObject* receive = PyObject_GetAttrString(main, "receive");
	PyObject* result = PyObject_CallFunctionObjArgs(receive, pInstance, NULL);
	if (result == NULL)
	{
		std::cout << "Something went wrong setting the circle in Python\n";
	}
	PyGILState_Ensure();
	PyObject* globals = PyModule_GetDict(main);
	// get circle from Python context
	PyObject* pyCircle = PyDict_GetItemString(globals, "circle");
	if (pyCircle == NULL)
	{
		std::cout << "Could not get image from Python" << std::endl;
	}
	
	// Manipulating pointer to check if it's changed in Python too
	circlePtr->x = 15; 

	Circle* circlePtrReceived;
	int res = 0;
	void* voidPtr;
	// get cicle from Python context as C++ void pointer
	res = SWIG_ConvertPtr(pyCircle, &voidPtr, pTypeInfo, 0);
	if (!SWIG_IsOK(res))
	{
		std::cout << "Could not cast circle to C++ type";
	}
	circlePtrReceived = reinterpret_cast<Circle*>(voidPtr);
	std::cout << "C++ received circle has area: " << circlePtrReceived->area() << std::endl;;
	std::cout << "C++ received circle has X: " << circlePtrReceived->x << std::endl;
	Py_Finalize();
	return 0;
}
