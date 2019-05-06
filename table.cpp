//Jing Su, 6839039
#include <iostream>
#include <vector>
#include <string>
#include "table.h"
#include "entry.h"

//lab05
Table::Table(const Table& ori){
	max_entries = ori.max_entries;
	v[max_entries];
	for (int i = 0; i < max_entries; i++){
		std::vector<Entry> p;
		v.push_back(p);
		for (int j = 0; j < ori.v[i].size(); j++){
			Entry e;
			e.set_key(ori.v[i][j].get_key());
			e.set_data(ori.v[i][j].get_data());
			this->put(e);
		}
	}
}

Table& Table::operator=(const Table& ori){
	if (&ori == this) return *this;
	v.~vector();
	this->max_entries = ori.max_entries;
	for (int i = 0; i < max_entries; i++){
		std::vector<Entry> p;
		v.push_back(p);
		for(int j = 0; j < ori.v[i].size(); j++){
			Entry e;
			e.set_key(ori.v[i][j].get_key());
			e.set_data(ori.v[i][j].get_data());
			this->put(e);
		}
	}
	return *this;
}

Table::~Table(){
	v.~vector();
}









//lab04
Table::Table(unsigned int max_entries):max_entries(max_entries){
	v[max_entries];
	for (int i = 0; i < max_entries; i++){
		std::vector<Entry> p;
		v.push_back(p);
	}
}

Table::Table(unsigned int entries, std::istream& input){
	max_entries = entries;
	v[entries];
	for (int i = 0; i < entries; i++){
		std::vector<Entry> p;
		v.push_back(p);
	}
	std::string line;
	getline(input, line);
	for (int i = 0; i < entries; i++){
		int index = stoi(line);
		Entry e;
		e.set_key(index);
		int pos = line.find("	");
		e.set_data(line.substr(pos + 1, line.length() - 1));
		index = index % max_entries;
		v[index].push_back(e);
		getline(input, line);
	}
}

void Table::put(unsigned int key, std::string data){
	Entry e;
	e.set_key(key);
	e.set_data(data);
	int index = key % (max_entries);
	for (int i = 0; i < v[index].size(); i++){
		if (v[index][i].get_key() == key){
			v[index][i].set_data(data);
			return;
		}
	}
	v[index].push_back(e);
}

void Table::put(Entry e){
	unsigned int value = e.get_key();
	value = value % (max_entries);
	for (int i = 0; i < v[value].size(); i++){
		if (v[value][i].get_key() == e.get_key()){
			v[value][i].set_data(e.get_data());
			return;
		}
	}
	v[value].push_back(e);
}

std::string Table::get(unsigned int key) const {
	int index = key % (max_entries);
	int okey;
	std::string str;
	for(int i = 0; i < v[index].size(); i++){
		okey = v[index][i].get_key();
		str = v[index][i].get_data();
		if (key == okey) break;
		if (i == v[index].size() - 1) str = "";
	}
	return str;
}

bool Table::remove(unsigned int key){
	int index = key % (max_entries);
	for (int i = 0; i < v[index].size(); i++){
		if (v[index][i].get_key() == key){
			v[index].erase(v[index].begin() + i);
			return true;
		}
	}
	return false;
}

void merge(Entry v[], size_t leftArraySize, size_t rightArraySize){
	Entry* temp;
	size_t copied = 0;
	size_t leftCopied = 0;
	size_t rightCopied = 0;

	temp = new Entry[leftArraySize + rightArraySize];

	while((leftCopied < leftArraySize) && (rightCopied < rightArraySize)){
		if(v[leftCopied].get_key() < (v + leftArraySize)[rightCopied].get_key()){
			temp[copied++] = v[leftCopied++];
		}else{
			temp[copied++] = (v + leftArraySize)[rightCopied++];
		}
	}
	while(leftCopied < leftArraySize){
		temp[copied++] = v[leftCopied++];
	}
	while(rightCopied < rightArraySize){
		temp[copied++] = (v + leftCopied)[rightCopied++];
	}
	for (size_t i = 0; i < leftArraySize + rightArraySize; i ++){
		v[i] = temp[i];
	}
	delete[] temp;
}

void mergesort(Entry s[], size_t size){
	size_t leftArraySize;
	size_t rightArraySize;

	if (size > 1){
		leftArraySize = size/2;
		rightArraySize = size - leftArraySize;
	mergesort(s, leftArraySize);
	mergesort((s + leftArraySize), rightArraySize);
	merge(s, leftArraySize, rightArraySize);
	}
}

std::ostream& operator<< (std::ostream& out, const Table& t){
	Entry s[t.max_entries];
	int num = 0;
	for (int i = 0; i < t.v.size(); i++){
		for (int j = 0; j < t.v[i].size(); j++){
			s[num] = (t.v[i][j]);
			num += 1;
		}
	}
	mergesort(s, num);
	for (int i = 0; i < num; i++){
		out << s[i] << std::endl;
	}
	return out;
}
