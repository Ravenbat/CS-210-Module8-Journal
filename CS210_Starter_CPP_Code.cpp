#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

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
	char *procname = new char[pName.length() + 1];
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
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char *paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
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
	char *procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject *pName, *pModule, *pDict, *pFunc, *pValue = nullptr, *presult = nullptr;
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
void displayMenu();                                             //Declaration of all functions in advance because C++ requires it.
void itemFrequency();
void printHistogram();
int checkInput(char input);

void main()
{
	CallProcedure("printsomething");                           //CallProcedure is used when calling function which doesn't accept parameters such as TimesEachItemAppear
	cout << callIntFunc("PrintMe","House") << endl;
	cout << callIntFunc("SquareValue", 2);
	displayMenu();

}


void displayMenu() {             //Changed input to char because isdigit only works on characters not integer values.

	for (char i = 0; i != 52;) {
		int number;
		cout << endl << "1: Display how many times each item appears in the list \n2: Find how many times one item has been sold \n3: Output all items frequency to a file and print histogram from it\n4 : Exit" << endl;
		cin >> i;
		if (checkInput(i) == 0) {
			cout << "Invalid input. Please enter 1,2,3 or 4." << endl;
		}
		if (i == 49) {
			CallProcedure("TimesEachItemAppear");            //Calling newly created python functions, this one doesn't take parameter so CallProcedures is used to call it.
		}

		if (i == 50) {
			itemFrequency();
		}

		if (i == 51) {
			cout << endl << "Outputting frequency to frequency.dat..." << endl << endl;
			CallProcedure("OutputFrequency");
			printHistogram();
		}

	}
}

void itemFrequency() {                                   //Function created for option 2 finding frequency of one item
	cout << "Which item's frequency would you like to examine?" << endl;
	string item;
	cin >> item;
	while (cin.fail()) {                                   //cin will fail if user input is anything other than string
		cout << "\n ERROR, enter a word";
		cin.clear();
		cin.ignore(256, '\n');
		cin >> item;
	}                                                             
	cout << item << " was purchased " << callIntFunc("TimesOneItemAppear", item) << " times in a single day." << endl;
}

void printHistogram() {                                     //Function to read from frequency.dat and print histogram
	int count;
	string itemName;
	std::ifstream infile("frequency.dat");                  //using infile from ifstream to read from file the item name and it's count seperately to itemName and count variables.

	while (infile >> itemName >> count)
	{
		cout << itemName << " ";
		for (int i = 0; i < count; ++i) {
			cout << "#";
		}
		cout << endl;

	}

}

int checkInput(char input) {  // Checking if char is number and between 1 to 4
	if (isdigit(input)) {
		if (input > 48 && input < 53) {
			return 1;
		}
	}

	return 0;
}