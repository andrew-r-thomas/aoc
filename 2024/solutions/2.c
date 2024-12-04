/*
 just put the lines in an array and do stuff that way,
 need to do some more complete checking for the removal stuff
*/

#include <stdio.h>
#include <stdlib.h>

enum DIRECTION
{
	increasing,
	decreasing,
	initial,
};

int check_safe(int prev, int current, enum DIRECTION *dir)
{
	if (!(prev == 0))
	{
		// check diff
		int diff = abs(current - prev);
		if (diff < 1 || diff > 3)
		{
			return 0;
		}

		// check asc/dec
		switch (*dir)
		{
			case initial:
				if (current < prev) *dir = decreasing;
				else if (current > prev) *dir = increasing;
				else
				{
					return 0;
				}
				break;
			case increasing:
				if (!(current > prev))
				{
					return 0;
				}
				break;
			case decreasing:
				if (!(current < prev))
				{
					return 0;
				}
				break;
		}
	}

	return 1;
}

int line_is_safe(char line[])
{
	int safe = 1;
	int first = 1;

	enum DIRECTION dir = initial;
	int prev = 0;
	int current = 0;
	int i = 0;
	int looping = 1;
	while (looping)
	{
		int s;
		char c = line[i];
		int digit;
		switch (c) {
		case ' ':
			s = check_safe(prev, current, &dir);
			if (first == 1 && s == 0)
			{
				first = 0;
			}
			else
			{
				looping = s;
				safe = s;
			}
			prev = current;
			current = 0;
			break;
		case '\n':
			// maybe need to add first check here
			s = check_safe(prev, current, &dir);
			safe = s;
			looping = 0;
			break;
		default:
			digit = c - '0';
			current *= 10;
			current += digit;
			break;
		}

		i++;
	}

	return safe;
}

#define LINES 6

int main(void)
{
	FILE *f = fopen("../data/2.txt", "r");

	int answer = 0;
	for (int i = 0; i < LINES; i++)
	{
		char line_buff[25] = {0};

		char current = 0;
		int j = 0;
		while (current != '\n')
		{
			fread(&current, 1, 1, f);
			line_buff[j] = current;
			j++;
		}

		answer += line_is_safe(line_buff);
	}

	printf("answer is: %d\n", answer);
}
