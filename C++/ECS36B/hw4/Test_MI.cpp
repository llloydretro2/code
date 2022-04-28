#include <iostream>
#include "MultipleInheritance.h"
using namespace std;


int main() {

Work_Study Obj_WS;
Work_Study * Obj_WS_ptr = & Obj_WS;


cout << "A1(Employee): " << &((Employee*) Obj_WS_ptr) -> A1 << endl;
cout << "A1(Student): " << &((Student*) Obj_WS_ptr) -> A1 << endl;
cout << "E1: " << &Obj_WS_ptr -> E1 << endl;
cout << "S1: " << &Obj_WS_ptr -> S1 << endl;
cout << "W1: " << &Obj_WS_ptr -> W1 << endl;

cout << "Employee: " << (Employee *) Obj_WS_ptr << endl;
cout << "Student: " << (Student *) Obj_WS_ptr << endl;
cout << "Account(Employee): " << (Account*)((Employee*) Obj_WS_ptr) << endl;
cout << "Account(Student): " << (Account*)((Student*) Obj_WS_ptr) << endl;
return 0;

}
