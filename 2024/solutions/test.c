#include <stdint.h>
#include <stdio.h>
#include "pico/stdlib.h"

int main() {
	stdio_init_all();

	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	char start;
	bool started = false;
	while (1)
	{
		if (!started)
		{
			start = getchar();
			switch (start)
			{
				case '1':
					started = true;
					printf("started\n");
					break;
				default:
					printf("invalid input\n");
			}
		} else {
			gpio_put(PICO_DEFAULT_LED_PIN, true);
			sleep_ms(500);

			gpio_put(PICO_DEFAULT_LED_PIN, false);
			sleep_ms(1000);
		}
	}
}
