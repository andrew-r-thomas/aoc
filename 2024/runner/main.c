#include <stdio.h>
#include <stdlib.h>

int main(int _num_args, char* args[])
{
	printf("running day %s\n", args[1]);

	char* path = malloc(9 + sizeof(args[1]));
	sprintf(path, "data/%s.txt", args[1]);

	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		printf("error opening %s\n", path);
		return 1;
	}
}
