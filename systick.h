#pragma once
#include <malloc.h>
#include <stdio.h>



struct Systick_t
{
	int tick_counter;
	struct task_t {
		int interval;
		void(*task)(void);
		int exe_time;
	}task_obj;
}systick_obj;

	//Systick_t* task_vec;
struct Systick_t task_vec[10];


void add_tasks(void(*task)(void), int interval) {
	static int task_count = 0;
	struct Systick_t new_systick;
	new_systick.task_obj.interval = interval;
	new_systick.task_obj.task = task;
	new_systick.task_obj.exe_time = new_systick.task_obj.interval + systick_obj.tick_counter;
	
	//task_vec = malloc(sizeof(struct Systick_t));
	task_vec[task_count] = new_systick;
	task_count++;
}

void systick_isr() {
	//int task_vec_size = sizeof(task_vec) / sizeof(task_vec[0]);
	systick_obj.tick_counter++;
	printf("tick_counter :%d\r\n", systick_obj.tick_counter);
	for (int i = 0; i < 3; i++) {
		if (task_vec[i].task_obj.exe_time == systick_obj.tick_counter) {
			task_vec[i].task_obj.task();
			task_vec[i].task_obj.exe_time = systick_obj.tick_counter + task_vec[i].task_obj.interval;
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
