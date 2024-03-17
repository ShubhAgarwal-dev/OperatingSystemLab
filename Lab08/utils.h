#ifndef __IITDH_CS312_LAB08_UTILS__
#define __IITDH_CS312_LAB08_UTILS__

#include <bits/stdc++.h>
#define DEBUG_MODE 0

typedef struct PTE {
	// PTE inspiration taken from Page 8 of Lecture 23-24, OS
	int PFN; // Physical Frame Number
	bool valid;
	bool protection;
	bool present;
	bool dirty;
	bool accessed;
	PTE() {
		valid = false;
		protection = false;
		present = false;
		dirty = false;
		accessed = false;
	}
} PTE;

// std::vector<page_table>;

std::vector<int> file_reader(const std::string &file_name);

class MemoryBaseClass
{
// private:
public:
	MemoryBaseClass(int psize, int ssize);
	int get_page_fault();
	int pmem_size;
	int swap_size;
	std::set<int> swap;
	int page_fault;
	int page_hit;
};

#endif // __IITDH_CS312_LAB08_UTILS__
