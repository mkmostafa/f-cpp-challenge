#include <Processor.h>

#include <chrono>
#include <iostream>

int main(int argc, char** argv) {
	Processor p;	
	const auto&  before = std::chrono::high_resolution_clock::now();
	p.process(argc == 2? argv[1]:"data ccchallenge.log");
	p.write();
	const auto&  after = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> total_time = after - before;
	std::cout << "time: " << total_time.count() << "s" << std::endl;

}