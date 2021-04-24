#include "io.h"

char* io_read_file(const char* file_name)
{
	FILE* fp;
	char* line = NULL;
	size_t len = 0;
	size_t read;

	fp = fopen(file_name, "rb");
	if (fp == NULL) {
		printf("Could not read file `%s`\n", file_name);
		exit(1);
	}

	char* buffer = (char *)calloc(1, sizeof(char));
	buffer[0] = '\0';

	while ((read = getline(&line, &len, fp)) != -1) {
		buffer = (char *)realloc(buffer, (strlen(buffer) + strlen(line) + 1) * sizeof(char));
		strcat(buffer, line);
	}
	fclose(fp);
	if (line) {
		free(line);
	}
	return buffer;
}

