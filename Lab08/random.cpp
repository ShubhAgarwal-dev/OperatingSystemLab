#include <bits/stdc++.h>
#include "utils.h"

using namespace std;

class Memory: public MemoryBaseClass
{
private:
	vector<int> in_memory_pages;
public:
	Memory(int psize, int ssize)
		: MemoryBaseClass(psize, ssize) {
		return;
	}

	void access_memory(int page_number, PTE *page_table) {
		PTE pte = page_table[page_number];
		if (pte.present) {
			DEBUG_MODE && cout << "PAGE HIT OCCOUR" << endl;
			page_hit += 1;
		} else {
			DEBUG_MODE && cout << "PAGE FAULT OCCOUR" << endl;
			page_fault += 1;
			handle_page_fault(page_number, page_table);
		}
	}

	void handle_page_fault(int page_number, PTE *page_table) {
		if (in_memory_pages.size() < pmem_size) {
			page_table[page_number].PFN = rand();
		} else {
			int random_index = rand() % in_memory_pages.size();
			int victim = in_memory_pages.at(random_index);
			// in_memory_pages[random_index] = page_number;
			in_memory_pages.erase(in_memory_pages.begin() + random_index);
			if (swap.size() < swap_size) {
				swap.insert(victim);
			} else {
				cerr << "SWAP SPACE IS INSUFFICIENT" << endl;
				exit(2);
			}
			if (swap.find(page_number) != swap.end()) {
				swap.erase(page_number);
			}
			page_table[victim].present = false;
			page_table[page_number].PFN = page_table[victim].PFN;
		}
		in_memory_pages.push_back(page_number);
		page_table[page_number].present = true;
	}
};

int main(int argc, char *argv[]) {
	if (argc != 5 && !DEBUG_MODE) {
		cout << "./random <Addressable Pages> <Pages in Main Memory> <Swap Space> <Page Access Sequnce File>" << endl;
		exit(1);
	}

	string file_name;
	int total_pages, phy_mem, swp_space;

	if (DEBUG_MODE) {
		total_pages = 60;
		phy_mem = 20;
		swp_space = 60;
		file_name = "access/req1.dat";
	} else {
		total_pages = atoi(argv[1]);
		phy_mem = atoi(argv[2]);
		swp_space = atoi(argv[3]);
		file_name = argv[4];
	}

	vector<int> page_accesses = file_reader(file_name);
	PTE *page_table = new PTE[total_pages];

	Memory mem(phy_mem, swp_space);
	for (auto i : page_accesses) {
		mem.access_memory(i, page_table);
	}

	cout << "Number of page faults: " << mem.get_page_fault() << endl;
	cout << "Total number of accesses: " << page_accesses.size() << endl;
	cout << "Page fault ratio: " << (double)mem.get_page_fault() / page_accesses.size() << endl;

	delete[] page_table;
}