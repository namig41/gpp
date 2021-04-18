#include <stdio.h>
#include "gpp.h"

int main(int argc, char** argv)
{
	if (argc != 2) {
		printf("gpp: fatal error: no input files\n"
		       "compilation terminated.");
		return 1;
	}
	gpp_compiler(argv[1]);
	return 0;
}
