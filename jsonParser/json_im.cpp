
#include "stdafx.h"
#include "json_source.h"
#include <sstream> 

using std::istringstream;

string Object::to_json() {
	string tojson = "";
	for (auto i = obj_map.begin(); i != obj_map.end(); ++i) {
		if (tojson == "") {			
			tojson += "{" + (string) "\"" + i->first + "\"" + ":" + i->second.to_json();
		}
		else {
			tojson += "," + (string) "\"" + i->first + "\"" + ":" + i->second.to_json();
		}
	}
	tojson += "}";
	return tojson;
}

string Array::to_json() {	
	string arr = "";
	for (auto i = 0; i<v_vec.size(); i++) {
		if (arr == "") {
			arr +=  "["+ v_vec[i].to_json();
		}
		else {
			arr += ","+ v_vec[i].to_json();
		}	
	}
	//在for循环的外面,细心！
	arr += "]";
	return arr;
}

ValueType Value:: get_type() {
	//this ->
	return this->type;
}
string Value::to_json(){
	//创建一个流
	std::ostringstream ostr;
	switch (get_type()) {
	case STRING:
		//把值传入流中
		return  "\""+v_string+"\"";
	case FLOAT:
		ostr << v_float;
		return ostr.str();
	case INT:
		ostr << v_int;
		return ostr.str();
	case BOOL:
		ostr << v_bool;
		return ostr.str();
	case OBJECT:
		return v_object.to_json();
	case ARRAY:
		return v_array.to_json();
	default:return "";
	}


}


Object::Object(string  json_string) {
	int p = 0;
	*this = read_object(json_string, p);
}

Object Object:: read_object(const string &str,int &p) {
	Object obj;
	read_char(str, p, '{');
	while (1) {
		string key = read_string(str,p);
		read_char(str,p,':');
		Value val = read_value(str,p);
		obj[key] = val;
		if (str[p]=='}') {
			read_char(str,p,'}');
			break;
		}
		else {
			read_char(str,p,',');
		}
	}
	return obj;

}

Value Object:: read_value(const string &str, int  &p) {
	//Value val;
	Value val="";
	if (str[p]=='{') {
		val = read_object(str,p);	
	}
	else if (str[p]=='\"') {
		val = read_string(str,p);	
	}
	else if (str[p]=='[') {
		val = read_array(str,p);	
	}
	else if (str[p]=='t'||str[p]=='f') {
		val = read_bool(str,p);	
	}
	//负数，检查参数是否为阿拉伯数字0到9
	else if (str[p]=='-'||isdigit(str[p])) {
		val = read_number(str,p);
	}
	return val;
}

string Object::read_string(const string &str, int &p) {
	p = p + 1;
	string tmp_s = "";
	//外用单引号
	while (str[p] != '\"') {
		tmp_s += str[p];
		p++;
	}
	p = p + 1;
	return tmp_s;
}
//void 类型
void Object::read_char(const string &str, int &p, char c) {
	while (p<str.size() && str[p] != c) p++;
	p = p + 1;

}
bool Object::read_bool(const string &str, int &p) {
	bool tmp_bool;
	if (str[p]=='t') {
		tmp_bool = true;
		p = p + 4;
	
	}
	else {
		tmp_bool = false;
		p = p + 5;
	
	}
	return tmp_bool;
}
Value Object::read_number(const string &str, int &p) {
	string tmp_string = "";
	tmp_string += str[p];
	p = p + 1;

	while (isdigit(str[p])) {
		tmp_string += str[p];
		p++;
	}
	if (str[p] == '.') { // it's a float number
		tmp_string += str[p];
		p = p + 1;
		while (isdigit(str[p])) {
			tmp_string += str[p];
			p++;
		}
		double v_num;
		istringstream istream;
		istream.str(tmp_string);
		istream >> v_num;
		return Value(v_num);
	}
	else {
		int v_num;
		istringstream istream;
		istream.str(tmp_string);
		istream >> v_num;
		return Value(v_num);
	}

}
Array Object::read_array(const string &str, int &p) {
	p = p + 1;
	Array tmp_arr;
	while (str[p]!=']') {
		if (str[p] == ',') p = p + 1;
		tmp_arr.push_back(read_value(str,p));
	}
	p = p + 1;
	return tmp_arr;

}

void json_write() {
	Object obj;
	obj["title"] = "Think in Java";
	obj["author"] = "Bruce";
	obj["price"] = 116.0;
	obj["pages"] = 927;
	obj["authors"] = Array();
	obj["authors"].push_back("Bruce Eckel");
	obj["authors"].push_back("Chuck Allison");

	obj["pub_info"] = Object();
	obj["pub_info"]["name"] = "China Machine Press";
	cout << obj.to_json();


}

void json_read() {
	string json_string = "{\"ISBN\":\"978-7-111-35021-7\",\"title\":\"Thinking in C++\",\"price\":116.0,\"authors\":[\"Bruce Eckel\",\"Chuck Allison\"],\"pages\":927,\"pub_info\":{\"name\":\"China Machine Press\",\"phone\":\"010-88378891\",\"email\":\"hzjsj@hzbook.com\"}}";
	Object obj(json_string);
	cout << obj.to_json() << endl;
	cout << obj["price"].to_float() << endl;
	cout << obj["authors"][0].to_string() << endl;
	cout << obj["pub_info"]["email"].to_string() << endl;



}
int _tmain(int argc, _TCHAR* argv[])

{
	//json_write();
	json_read();
	getchar();

}

