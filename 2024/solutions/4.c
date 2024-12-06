#include "../utils.c"
#include <stdio.h>

#define LINES 140
#define LINE_LEN 140

// assumes in[0] == 'X' or 'A' for part 2
void check_x(char *in, int x, int y, int *answer)
{
	// part 1
	// int west = 0;
	// int east = 0;
	// int south = 0;
	// int north = 0;
	
	// // first check which directions we can go
	// if (y >= 3) north = 1;
	// if (y + 3 < LINES) south = 1;
	// if (x >= 3) west = 1;
	// if (x + 3 < LINE_LEN) east = 1;
	//
	// // N
	// if (
	// 	north &&
	// 	in[((LINE_LEN + 1) * (y-1)) + x] == 'M' &&
	// 	in[((LINE_LEN + 1) * (y-2)) + x] == 'A' &&
	// 	in[((LINE_LEN + 1) * (y-3)) + x] == 'S'
	// ) (*answer)++;
	//
	// // NW
	// if (
	// 	north &&
	// 	west &&
	// 	in[((LINE_LEN + 1) * (y-1)) + (x-1)] == 'M' &&
	// 	in[((LINE_LEN + 1) * (y-2)) + (x-2)] == 'A' &&
	// 	in[((LINE_LEN + 1) * (y-3)) + (x-3)] == 'S'
	// ) (*answer)++;
	//
	// // NE
	// if (
	// 	north &&
	// 	east &&
	// 	in[((LINE_LEN + 1) * (y-1)) + (x+1)] == 'M' &&
	// 	in[((LINE_LEN + 1) * (y-2)) + (x+2)] == 'A' &&
	// 	in[((LINE_LEN + 1) * (y-3)) + (x+3)] == 'S'
	// ) (*answer)++;
	//
	// // W
	// if (
	// 	west &&
	// 	in[((LINE_LEN + 1) * y) + (x-1)] == 'M' &&
	// 	in[((LINE_LEN + 1) * y) + (x-2)] == 'A' &&
	// 	in[((LINE_LEN + 1) * y) + (x-3)] == 'S'
	// ) (*answer)++;
	//
	// // E
	// if (
	// 	east &&
	// 	in[((LINE_LEN + 1) * y) + (x+1)] == 'M' &&
	// 	in[((LINE_LEN + 1) * y) + (x+2)] == 'A' &&
	// 	in[((LINE_LEN + 1) * y) + (x+3)] == 'S'
	// ) (*answer)++;
	//
	// // S
	// if (
	// 	south &&
	// 	in[((LINE_LEN + 1) * (y+1)) + x] == 'M' &&
	// 	in[((LINE_LEN + 1) * (y+2)) + x] == 'A' &&
	// 	in[((LINE_LEN + 1) * (y+3)) + x] == 'S'
	// ) (*answer)++;
	//
	// // SW
	// if (
	// 	south &&
	// 	west &&
	// 	in[((LINE_LEN + 1) * (y+1)) + (x-1)] == 'M' &&
	// 	in[((LINE_LEN + 1) * (y+2)) + (x-2)] == 'A' &&
	// 	in[((LINE_LEN + 1) * (y+3)) + (x-3)] == 'S'
	// ) (*answer)++;
	//
	// // SE
	// if (
	// 	south &&
	// 	east &&
	// 	in[((LINE_LEN + 1) * (y+1)) + (x+1)] == 'M' &&
	// 	in[((LINE_LEN + 1) * (y+2)) + (x+2)] == 'A' &&
	// 	in[((LINE_LEN + 1) * (y+3)) + (x+3)] == 'S'
	// ) (*answer)++;
	
	// part 2
	if (
		// we can go 1 in every direction
		y >= 1 && y + 1 < LINES && x >= 1 && x + 1 < LINE_LEN
	) {
		int first_mas = 0;
		int second_mas = 0;

		char tl = in[((LINE_LEN + 1) * (y-1)) + (x-1)];
		char tr = in[((LINE_LEN + 1) * (y-1)) + (x+1)];
		char bl = in[((LINE_LEN + 1) * (y+1)) + (x-1)];
		char br = in[((LINE_LEN + 1) * (y+1)) + (x+1)];

		switch (tl) {
		case 'M':
			if (br == 'S') first_mas = 1;
			break;
		case 'S':
			if (br == 'M') first_mas = 1;
			break;
		default:
			break;
		}
		switch (tr) {
		case 'M':
			if (bl == 'S') second_mas = 1;
			break;
		case 'S':
			if (bl == 'M') second_mas = 1;
			break;
		default:
			break;
		}

		if (first_mas && second_mas) (*answer)++;
	}

	return;
}

int main()
{
	char *input = read_file_to_string("data/4.txt");
	int answer = 0;

	int y = 0;
	int x = 0;

	int i = 0;
	while (1)
	{
		char current = input[i];
		i++;
		switch (current) {
		case 'A':
			check_x(input, x, y, &answer);
			x++;
			break;
		case '\n':
			y++;
			x = 0;
			break;
		case 0:
			printf("answer is: %d\n", answer);
			return 0;
		default:
			x++;
			break;
		}
	}
}
