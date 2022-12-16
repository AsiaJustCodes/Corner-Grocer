#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void main()
{
	int userChoice; // variable for user input
	string searchTerm;
	bool valid = true;
	string line; // varialble stores files words
	int num = 0; // vraiable stores files integers

	// user menu
	cout << "----------------- Menu ----------------------\n";
	cout << "1: Produce a list of all items purchased with quantities\n";
	cout << "2: Display how many times a specific item was sold\n";
	cout << "3: Produce a histogram of sales data\n";
	cout << "4: Exit\n";
	cout << "---------------------------------------------\n\n";

	// user input for menu selection
	cin >> userChoice;

	while (valid != false) {
		if (userChoice == 3)
		{
			// First write the appropriate counts from the input file to the output file
			cout << "\n\nWriting items and quantities sold today to a file: \n\n";
			CallProcedure("histogram");
			cout << "\n\n";
			// Open the output file and read the data
			ifstream frequencyFile("frequency.dat");
			string item;
			string fileLine;
			int count;
			// Parse through the file line by line and print the histogram
			while (getline(frequencyFile, fileLine))
			{
				istringstream iss(fileLine);
				if (!(iss >> item >> count)) { break; } // error
				// Print the item name and "count" number of asterisks
				cout << item << " " << string(count, '*') << endl;
			}
			cout << "\n\n";
			return;

		}
		switch (userChoice) {// input validation
		case 1: {
			valid = false;
			cout << "Items purchased: \n";
			CallProcedure("itemCount");
			break;
		}
		case 2: {
			valid = false;
			cout << "Enter item name: \n";
			cin >> searchTerm;
			cout << callIntFunc("specificItem", searchTerm);
			break;
		}
		case 3: {
			valid = false;
			break;
		}
		case 4: { // exits program
			valid = false;
			cout << "Goodbye\n";
			break;
		}
		default:
			valid = false;
			cout << "Choose options 1 - 4 \n";

		}
	}
} 

