#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void parse_mul(char **in, int *answer)
{
	// check that we have valid "mul("
	if ((*in)[0] != 'm' || (*in)[1] != 'u' || (*in)[2] != 'l' || (*in)[3] != '(')
	{
		(*in)++;
		return;
	}
	else
	{
		(*in) += 4;
		int num = 0;
		int mul = 0;
		while (1)
		{
			char current = (*in)[0];
			if (isdigit(current))
			{
				num *= 10;
				int digit = current - '0';
				num += digit;
				(*in)++;
			}
			else
			{
				switch (current)
				{
				case ',':
					if (num == 0) return;
					else
					{
						mul = num;
						num = 0;
						(*in)++;
					}
					break;
				case ')':
					if (mul == 0) return;
					else
					{
						mul *= num;
						(*answer) += mul;
						(*in)++;
						return;
					}
				default:
					return;
				}
			}
		}
	}
}

void parse_cond(char **in, int *d)
{
	if ((*in)[0] != 'd' || (*in)[1] != 'o')
	{
		(*in)++;
		return;
	}

	if ((*in)[2] == '(' && (*in)[3] == ')')
	{
		(*d) = 1;
		(*in) += 4;
		return;
	}
	else if ((*in)[2] == 'n' && (*in)[3] == '\'' && (*in)[4] == 't' && (*in)[5] == '(' && (*in)[6] == ')')
	{
		(*d) = 0;
		(*in) += 7;
		return;
	}
	else
	{
		(*in)++;
		return;
	}
}

int main()
{
	FILE *f = fopen("data/3.txt", "r");

	// first lets read the whole thing to a string
	fseek(f, 0, SEEK_END);
	long filesize = ftell(f);
	rewind(f);

	char *input = malloc(filesize+1);
	fread(input, 8, filesize, f);

	int answer = 0;
	int d = 1;

	while (1)
	{
		char current = input[0];

		switch (current) {
		case 'm':
			if (d) parse_mul(&input, &answer);
			else input++;
			break;
		case 'd':
			parse_cond(&input, &d);
			break;
		case 0:
			printf("answer is %d\n", answer);
			return 0;
		default:
			input++;
			break;
		}
	}
}

