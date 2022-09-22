#pragma once
#include <malloc.h>
#include <stdio.h>
#include <string.h>



struct Systick_t
{
	int tick_counter;
	struct task_t {
		int interval;
		void(*task)(void); //reserve for future needs
		int exe_time;
	}task_obj;
}systick_obj;

	//Systick_t* task_vec;
struct Systick_t task_vec[10];
uint8_t* task_exe_flag;


void add_tasks(char* task_name, int interval) {
	static int task_count = 0;
	struct Systick_t new_systick;
	new_systick.task_obj.interval = interval;
	//new_systick.task_obj.task = task; //change the add_tasks signatuer if you need to pass function
	new_systick.task_obj.exe_time = new_systick.task_obj.interval + systick_obj.tick_counter;
	
	//task_vec = malloc(sizeof(struct Systick_t));
	task_vec[task_count] = new_systick;
	task_exe_flag = malloc(0);

	task_count++;
}

void systick_init(void) {
	for (int i = 0; i < sizeof(task_exe_flag) / sizeof(task_exe_flag[0]); i++) { // i < task_exe_flag size
		task_exe_flag[i] = 0;
	}
}

void systick_isr() {
	int task_vec_size = sizeof(task_vec) / sizeof(task_vec[0]);
	systick_obj.tick_counter++;
	printf("tick_counter :%d\r\n", systick_obj.tick_counter);
	for (int i = 0; i < task_vec_size; i++) {
		if (task_vec[i].task_obj.interval > 0) { //if the task is valid
			if (task_vec[i].task_obj.exe_time == systick_obj.tick_counter) {
				//task_vec[i].task_obj.task();
				task_vec[i].task_obj.exe_time = systick_obj.tick_counter + task_vec[i].task_obj.interval;
				task_exe_flag[i] = 1;
			}
		}
	}
}
void systick_handler() {
	static int timer = 0;
	if (++timer >= 50000000) {
		timer = 0;
		systick_isr();
	}
}
