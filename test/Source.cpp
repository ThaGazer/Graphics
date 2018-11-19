#include <thread>
#include <iostream>

using namespace std;

void test() {
	this_thread::sleep_for(chrono::seconds(10000000));
}

int main() {
	for (int i = 0; i < 100; i++) {
		cout << i << endl;
		thread(test);
	}


	while (true) {

	}
	return 0;
}