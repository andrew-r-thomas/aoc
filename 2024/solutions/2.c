/*
 just put the lines in an array and do stuff that way,
 need to do some more complete checking for the removal stuff

 NOTE:
 friendly reminder, probably want to keep code from part 1 when you
 implement part 2
*/

#include <stdio.h>
#include <stdlib.h>

enum DIRECTION
{
	increasing,
	decreasing,
	initial,
};

int line_is_safe(int line[], int len)
{
	enum DIRECTION dir = initial;
	int current = 0;
	int previous = 0;
	for (int i = 0; i < len; i++)
	{
		previous = current;
		current = line[i];

		if (!(previous == 0))
		{
			// check prev for violations
			int diff = abs(current - previous);
			if (diff < 1 || diff > 3) return 0;
			else {
				switch (dir) {
				case initial:
					if (current > previous) dir = increasing;
					else if (current < previous) dir = decreasing;
					else return 0;
					break;
				case increasing:
					if (!(current > previous)) return 0;
					break;
				case decreasing:
					if (!(current < previous)) return 0;
					break;
				}
			}
		}
	}

	return 1;
}

int parse_line(char line[], int len, int buff[])
{
	int current = 0;
	int buff_i = 0;
	for (int i = 0; i < len; i++)
	{
		char c = line[i];
		int digit;
		switch (c) {
		case ' ':
			buff[buff_i] = current;
			buff_i++;
			current = 0;
			break;

		case '\n':
			buff[buff_i] = current;
			buff_i++;
			break;

		default:
			digit = c - '0';
			current *= 10;
			current += digit;
			break;
		}
	}

	return buff_i;
}

#define LINES 1000

int main(void)
{
	FILE *f = fopen("data/2.txt", "r");

	int answer = 0;
	for (int line_i = 0; line_i < LINES; line_i++)
	{
		char line_buff[25] = {0};

		char current = 0;
		int line_buff_i = 0;
		while (current != '\n')
		{
			fread(&current, 1, 1, f);
			line_buff[line_buff_i] = current;
			line_buff_i++;
		}

		int num_buff[25] = {0};
		int len = parse_line(line_buff, line_buff_i, num_buff);

		int safe = line_is_safe(num_buff, len);
		if (!safe)
		{
			for (int rebuff_i = 0; rebuff_i < len; rebuff_i++)
			{
				// make a buff without this entry
				int buff[25] = {0};
				int b_i = 0;
				for (int buff_i = 0; buff_i < len; buff_i++)
				{
					if (buff_i != rebuff_i)
					{
						buff[b_i] = num_buff[buff_i];
						b_i++;
					}
				}

				if (line_is_safe(buff, len - 1))
				{
					answer += 1;
					break;
				}
			}
		}
		else answer += 1;
	}

	printf("answer is: %d\n", answer);
}
