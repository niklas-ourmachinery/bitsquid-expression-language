#include <stdio.h>

#include "expression_language.h"

using namespace skinny::expression_language;

void test(const char *source)
{
	const char *variable_names[1] = {"x"};
	float variable_values[1] = {3};
	const char *constant_names[1] = {"pi"};
	float constant_values[1] = {3.14159265f};
	
	unsigned byte_code[128];
	float stack_data[32];
	
	Stack stack(stack_data, 32);
	
	printf("Compiling: %s\n", source);
	unsigned size = compile(source, 1, variable_names, 1, constant_names, constant_values, byte_code, 128);
	printf("Program size: %u\n", size);
	if (is_constant(byte_code))
		printf("Constant value: %f\n", constant_value(byte_code));
	else {
		bool result = run(byte_code, variable_values, stack);
		if (!result)
			printf("Run failed!");
		else {
			printf("Result:\n");
			for (unsigned i=0; i<stack.size; ++i)
				printf("    %i: %f\n", i, stack_data[i]);
		}
	}
	printf("\n");
}

int main (int argc, char * const argv[]) 
{
	if (argc == 1) {
		test("3+(2*sin(pi))-1");
		test("3+(2*sin(x))-1");
	} else {
		for (int i=1; i<argc; ++i)
			test(argv[i]);
	}
}