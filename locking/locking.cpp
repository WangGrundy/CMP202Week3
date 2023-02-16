// Race conditions example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <chrono>	
#include <mutex>
#include "account.h"

// 22 none (wrong answer)
// 76 mutex
// 73 unique lock
// 3392 class mutex (very slow)

typedef std::chrono::steady_clock the_clock;

// Import things we need from the standard library
using std::cout;
using std::endl;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

Account bill;
std::mutex bill_mutex;

void callAdd(int threadNum) {

	//bill_mutex.lock();

	//std::unique_lock<std::mutex> lockName(bill_mutex);

	cout << "thread " << threadNum << " started\n";

	for (int i = 0; i < 10000000; i++) { //this number needs to be large enough for other threads to overwrite this
		bill.add(17, 29);
	}

	cout << "thread " << threadNum << " finished\n";

	//bill_mutex.unlock();
}

int main(int argc, char *argv[])
{

	std::vector<std::thread> threadVector;

	cout << "Initial: " << bill.total() << "\n";

	the_clock::time_point start = the_clock::now();

	for (int i = 0; i < 10; i++) {
		threadVector.push_back(std::thread (callAdd, i));
	}

	for (std::thread& thread : threadVector) {
		thread.join();
	}

	cout << "Total: " << bill.total() << "\n";

	the_clock::time_point end = the_clock::now();

	// Compute the difference between the two times in milliseconds
	auto time_taken = duration_cast<milliseconds>(end - start).count();
	cout << "time taken: " << time_taken << " miliseconds \n";

	return 0;
}