#include <runtime.hpp>

#include <iostream>
#include <logs.hpp>

int main() {
	auto runtime = std::make_unique<Runtime>();

	runtime->run();
}