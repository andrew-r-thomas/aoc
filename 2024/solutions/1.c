#include <stdio.h>
#include <stdlib.h>

void print_array(int *arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int partition(int arr[], int low, int high)
{
	int p = arr[low];
	int i = low;
	int j = high;

	while (i < j)
	{
		while (arr[i] <= p && i <= high - 1) i++;
		while (arr[j] > p && j >= low + 1) j--;
		if (i < j) swap(&arr[i], &arr[j]);
	}

	swap(&arr[low], &arr[j]);

	return j;
}

void sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        sort(arr, low, pi - 1);
        sort(arr, pi + 1, high);
    }
}

// assumes arr is sorted in ascending order
int count_occurences(int arr[], int target)
{
	int count = 0;

	int i = 0;
	while (1)
	{
		if (arr[i] < target) i++;
		else if (arr[i] > target) break;
		else
		{
			count++;
			i++;
		}
	}

	return count;
}

#define LINES 1000
#define LINE_LEN 14

int main(void)
{
	FILE *f = fopen("data/1.txt", "r");

	int l[LINES] = {0};
	int r[LINES] = {0};

	// chuck everything into arrays
	for (int i = 0; i < LINES; i++)
	{
		char buff[LINE_LEN + 1] = {0};
		fread(&buff, 1, LINE_LEN, f);

		char l_str[6] = {0};
		char r_str[6] = {0};
		for (int i = 0; i < 6; i++)
		{
			l_str[i] = buff[i];
			r_str[i] = buff[i + 8];
		}
		int l_num = atoi(l_str);
		int r_num = atoi(r_str);

		l[i] = l_num;
		r[i] = r_num;
	}

	sort(l, 0, LINES - 1);
	sort(r, 0, LINES - 1);

	int answer = 0;

	for (int i = 0; i < LINES; i++)
	{
		// part 1 answer
		// answer += abs(l[i] - r[i]);

		// part 2 answer
		int check = l[i];
		answer += check * count_occurences(r, check);
	}

	printf("answer: %d\n", answer);
}
