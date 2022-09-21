#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "systick.h"



struct flags_t
{
	uint8_t flag_a : 1;
	uint8_t flag_b : 1;
	uint8_t flag_c : 1;
}flags;

void flag_handler_a(void) {
	flags.flag_a = 1;
}
void flag_handler_b(void) {
	flags.flag_b = 1;
}
void flag_handler_c(void) {
	flags.flag_c = 1;
}

void task_A() {
	printf("TASK A!\r\n");
}
void task_B() {
	printf("TASK B!\r\n");
}
void task_C() {
	printf("TASK C!\r\n");
}


int main() {

	add_tasks(flag_handler_a, 10);
	add_tasks(flag_handler_b, 15);
	add_tasks(flag_handler_c, 20);

	while (1) {
		systick_handler();
		if (flags.flag_a) {
			flags.flag_a = 0;
			task_A();
		}
		if (flags.flag_b) {
			flags.flag_b = 0;
			task_B();
		}
		if (flags.flag_c) {
			flags.flag_c = 0;
			task_C();
		}

	}
	return 0;
}
