#include <stdio.h>
#include <stdlib.h>


typedef struct task_t{
	int start;
	int finish;
} task;

double e = 0.00001;	


int create_task_table(task* tasks, int n)
{
	int* table = calloc(n, sizeof(int));
	if (table == NULL) return -1;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < i; j++){
			if (tasks[j].finish <= tasks[i].start)
				if (table[i] < table[j] + 1)
					table[i] = table[j] +1;
		}
	int max = table[0];
	for (int i = 1; i < n; i++)
		if (table[i] > max)
			max = table[i];
	
	return max+1;						
}


int max_rec(task* tasks, int n, int i)
{
	printf("a%d ", i+1);

	int m = i+1;
	while (tasks[m].start < tasks[i].finish && m < n)
		m++;
	if (m < n){
		max_rec(tasks, n, m);
	}

	return 0;
}




void sort(task* task_arr, int n)
{
	for (int i = 0 ;i < n; i++){
		int pos = i;
		for (int j = i+1; j < n; j++)
			if (task_arr[pos].finish > task_arr[j].finish)
				pos = j;	
		if (pos != i){
			task tmp = task_arr[pos];
			task_arr[pos] = task_arr[i];
			task_arr[i] = tmp;
		}
	}
}

int main(void)
{
	
	int n;
	printf("Enter the number of tasks: ");	
	int result = scanf("%d", &n);
	if (result != 1){
		fprintf(stderr, "Хуйня");
		return 2;
	}


	task* task_arr = calloc(n, sizeof(task));
	if (task_arr == NULL){
		fprintf(stderr, "Ошибка выделения памяти");
		return 1;
	}
	for (int i = 0; i < n; i++){
		result = scanf("%d%d", &task_arr[i].start, &task_arr[i].finish);
		if (result != 2){
			fprintf(stderr, "Error input!\n");
			return 2;
		}
		if (task_arr[i].start - task_arr[i].finish > e){
			fprintf(stderr, "Error format! Task finish must be bigger then task start");
			return 2;
		}
	}

	int res = create_task_table(task_arr, n);
	printf("%d \n", res);
	
	max_rec(task_arr, n, 0);
	printf("\n");	
	
	return 0 ;
}
