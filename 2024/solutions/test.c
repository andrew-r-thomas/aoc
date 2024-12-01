#include <stdio.h>
#include "pico/stdlib.h"

int main() {
	stdio_init_all();

	gpio_init(PICO_DEFAULT_LED_PIN);
	gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

	while (1)
	{
		gpio_put(PICO_DEFAULT_LED_PIN, true);
		printf("led on\n");
		sleep_ms(500);

		gpio_put(PICO_DEFAULT_LED_PIN, false);
		printf("led off\n");
		sleep_ms(1000);
	}
}
