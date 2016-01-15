#pragma once

#include <map>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <vector>

using std::string;
using std::cin;
using std::map;
using std::cout;
using std::endl;
using std::vector;

//先声明，三个class，后面再实现，就不用考虑嵌套问题，注意先后问题,C++中就这样
class Object;
class Array;
class Value;
class Object {
	map<string, Value> obj_map;

public:
	Object() {};
	Object(string );
	Value &operator[](const string &key) {
		return obj_map[key];
	}
	
	//find的参数是key
	map<string, Value> :: iterator find(const string key) {
		obj_map.find(key);
	}
	map<string, Value> ::iterator begin() {
		obj_map.begin();
	}
	map<string, Value> ::iterator end() {
		obj_map.end();
	}
	bool empty() {
		obj_map.empty();
	}
	void erase(map<string, Value> ::iterator pos) {
		obj_map.erase( pos);
	}
	int size() {
		obj_map.size();
	}
	void clear() {
		obj_map.clear();
	}

	
	
	string to_json();
	Object read_object(const string &, int &);
	Value read_value(const string &, int &);
	Array read_array(const string &, int &);
	string read_string(const string &, int &);
	bool read_bool(const string &, int &);
	Value read_number(const string &, int &);
	void read_char(const string &, int &, char);
	



};
class Array {
	vector<Value> v_vec;
public:
	Value &operator[](int index) {
		return v_vec[index];
	}

	void push_back(const Value &val) {
		v_vec.push_back(val);
	}
	bool empty() {
		return v_vec.empty();
	}
	int size() {
		return v_vec.size();
	}
	void clear() {
		v_vec.clear();
	}
	vector<Value>::iterator  begin() {
		return v_vec.begin();
	}
	vector<Value>::iterator end() {
		return v_vec.end();
	}
	string to_json();
	


};
//枚举类型
enum ValueType {
	INT,
	FLOAT,
	BOOL,
	STRING,
	OBJECT,
	ARRAY,
	//空
	NIL
};
class Value {
	string v_string;
	double v_float;
	int v_int;
	bool v_bool;
	Object v_object;
	Array v_array;
	ValueType type;
public:
	Value() {};
	Value(string v) :v_string(v), type(STRING) {}
	Value(float v) :v_float(v), type(FLOAT) {}
	Value(int v) :v_int(v), type(INT) {}
	Value(bool v) :v_bool(v), type(BOOL) {}
	Value(Object v) :v_object(v), type(OBJECT) {}
	Value(Array v) :v_array(v), type(ARRAY) {}
	Value(char *v) :v_string(v), type(STRING) {}
	Value(double v) : v_float(v), type(FLOAT) {};
	Value(long double v) : v_float(v), type(FLOAT) {};

	Value &operator[](int index) {
		return v_array[index];
	}

	Value &operator[](const string &key) {
		return v_object[key];
	}
	void push_back(const Value &val) {
		v_array.push_back(val);
	}

	bool empty() {
		return v_array.empty();
	}
	int size() {
		return v_array.size();
	}
	void clear() {
		v_array.clear();
	}
	vector<Value>::iterator  begin() {
		return v_array.begin();
	}
	vector<Value>::iterator end() {
		return v_array.end();
	}
	//operator=里面需要给type赋值
	Value &operator=(const string &v) { v_string = v; type = STRING; return *this; }
	Value &operator=(const Array &v) { v_array = v; type = ARRAY;  return *this;}
	Value &operator=(const int &v) { v_int = v; type = INT;  return *this;}
	Value &operator=(const bool &v) { v_bool = v; type = BOOL; return *this;}
	Value &operator=(const Object &v) { v_object = v; type = OBJECT; return *this;}
	Value &operator=(const double &v) { v_float = v; type = FLOAT; return *this;}
	Value & operator=(const char * val) { v_string = string(val); type = STRING; return *this; }
	

	string to_string() {
		return v_string;
	}
	bool to_bool() {
		return v_bool;
	}
	double &to_float(){
		return v_float;
	}
	int &to_int() {
		return v_int;
	}
	Object to_object(){
		return v_object;
	}
	Array to_array(){
		return v_array;
	}

	ValueType Value::get_type();
	string to_json();


};




