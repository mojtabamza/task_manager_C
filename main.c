#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "systick.h"


void task_A() {
	printf("TASK A!\r\n");
}
void task_B() {
	printf("TASK B!\r\n");
}
void task_C() {
	printf("TASK C!\r\n");
}
void task_D() {
	printf("TASK D!\r\n");
}


int main() {

	add_tasks("TASK_0", 10); //set flag[0] for being true every 10 tick
	add_tasks("TASK_1", 15);
	add_tasks("TASK_2", 20);
	add_tasks("TASK_3", 4);

	systick_init();

	while (1) {
		systick_handler();
		if (task_exe_flag[0]) { //0 the flag of task_0 ==> task_A will execute every 10 tick
			task_exe_flag[0] = 0;
			task_A();
		}
		if (task_exe_flag[1]) {
			task_exe_flag[1] = 0;
			task_B();
		}
		if (task_exe_flag[2]) {
			task_exe_flag[2] = 0;
			task_C();
		}
		if (task_exe_flag[3]) {
			task_exe_flag[3] = 0;
			task_D();
		}

	}
	return 0;
}
