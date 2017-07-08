
#include "IndexedQueue.h"

#include <iostream>
#include <gflags/gflags.h>

int main(int argc, char* argv[]) {
	
	gflags::ParseCommandLineFlags(&argc, &argv, false);

	IndexedQueue iq_;

	for (int i = 1; i < 50; i++) {
		iq_.insert(i % 5, i);
	}
	std::cout << iq_.print() << std::endl;
	std::cout << "-------------" << std::endl;
	iq_.deleteTill(25);
	std::cout << iq_.print() << std::endl;
	std::cout << "-------------" << std::endl;
	iq_.deleteTill(50);
	std::cout << iq_.print() << std::endl;
	std::cout << "-------------" << std::endl;
};
