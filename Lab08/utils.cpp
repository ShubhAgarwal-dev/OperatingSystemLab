#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

vector<int> file_reader(const string &file_name) {
	vector<int> page_numbers;
	ifstream my_file(file_name);

	if (!my_file) {
		cout << "Can not open the file" << endl;
		exit(1);
	}

	istream_iterator<string> fileIterator(my_file);
	istream_iterator<string> endIterator;

	while(fileIterator != endIterator) {
		string word = *fileIterator;
		int num = stoi(word);
		DEBUG_MODE && cout << num << " got into the array" << endl;
		page_numbers.push_back(num);
		++fileIterator;
	}

	my_file.close();
	return page_numbers;
}

MemoryBaseClass::MemoryBaseClass (int psize, int ssize) {
	this->pmem_size = psize;
	this->swap_size = ssize;
	this->page_fault = 0;
}

int MemoryBaseClass::get_page_fault() {
	return this->page_fault;
}
