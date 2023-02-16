// Race conditions example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "account.h"

// Import things we need from the standard library
using std::cout;
using std::endl;

Account bill;

void callAdd() {

	for (int i = 0; i < 100; i++) {
		bill.add(17, 29);
	}
}

int main(int argc, char *argv[])
{

	cout << "Initial: " << bill.total() << "\n";

	std::vector<std::thread> threadVector;

	
	for (int i = 0; i < 10; i++) {
		threadVector.push_back(std::thread (callAdd));
	}

	/*for each (std::thread &thread in threadVector) {
		thread.join();
	}*/

	for (std::thread& thread : threadVector) {
		thread.join();
	}

	cout << "Total: " << bill.total() << "\n";

	return 0;
}