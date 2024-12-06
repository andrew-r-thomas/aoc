#include <stdio.h>
#include <stdlib.h>

char* read_file_to_string(const char *path)
{
	FILE *f = fopen(path, "r");

	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	rewind(f);

	char *input = malloc(size + 1);
	fread(input, 8, size, f);
	fclose(f);

	return input;
}
