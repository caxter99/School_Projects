// This is the empmaps.h file for Project 2
// Devin Hopkins
// 4190350

#ifndef EMPMAPS_H_INCLUDED
#define EMPMAPS_H_INCLUDED

#include "Employee.h"
#include <vector>
#include <map>
#include <fstream>
#include <unordered_map>
#include <ctime>

using namespace std;

vector<Employee> employees();
map<int,vector<Employee>> mapEmpDept(vector<Employee> & emp);
map<int,vector<Employee>> mapSalRange(vector<Employee> & emp);
void printSalRange(map<int,vector<Employee>> & salRange);
unordered_map<int,vector<Employee>> umapEmpDept(vector<Employee> & emp);
unordered_map<int,vector<Employee>> umapSalRange(vector<Employee> & emp);
void uprintSalRange(unordered_map<int,vector<Employee>> & salRange);

// MINE
string removeWhitespace(string whitespace);
int getASCIIValue(char character);

#endif // EMPMAPS_H_INCLUDED