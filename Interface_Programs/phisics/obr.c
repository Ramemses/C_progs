#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double avg(double* arr, unsigned length)
{
	double total = 0;
	for (unsigned i = 0; i < length; i++)
		total += arr[i];
	return total/length;
}



int main(void)
{
	int res, N;
	double tp;
	double up = 0;
	double down = 0;
	printf("Введите число измерений и коэффициент стьюдента (2 числа через пробел):");
	res = scanf("%d%lf", &N, &tp);
	if (res != 2){
		fprintf(stderr, "Блять, введи 2 числа через пробел\n");
		return 1;
	}

	double *q = calloc(N, sizeof(double));
	double *F = calloc(N, sizeof(double));
	if (q == NULL || F == NULL){
		fprintf(stderr, "Ошибка выделения памяти под измерения\n");
		return 1;
	}

	printf("Введите %d значений силы: ", N);
	for (int i = 0; i < N; i++){
		res = scanf("%lf", F+i); 
		if (res != 1){
			fprintf(stderr, "Неверное введено значение силы. Ещё раз так сделаешь, мать сдохла\n");
			return 2;
		}

	}
	printf("Введите %d значений заряда: ", N);
	for (int i = 0; i < N; i++){
		res = scanf("%lf", q+i); 
		if (res != 1){
			fprintf(stderr, "Неверное введено значение заряда. Ещё раз так сделаешь, мать сдохла\n");
			return 2;
		}

	}

	double F_avg = avg(F, N);
	double Q_avg = avg(q, N);
	
	for (unsigned i = 0; i < N; i++){
		up += (q[i] - Q_avg) * (F[i] - F_avg);
		down += (F[i] - F_avg) * (F[i] - F_avg);
	}
	double d = up/down;


	printf("Среднее значение силы = %.5f\n", F_avg);
	printf("Среднее значение заряда = %.5f\n", Q_avg);
	printf("Среднее значение пьезомодуля d = %.5f\n", d);

	down = 0;
	up = 0;
	for (int i = 0; i < N; i++){
		up += (q[i] - Q_avg)*(q[i] - Q_avg);
		down += (F[i] - F_avg)*(F[i] - F_avg);
	}
	double qf = up/down - d*d;
	
	double delta_d = tp/sqrt(N-2) * sqrt(qf);
	printf("Погрешность пьезомодуля = %.5f\n", delta_d);

	return 0;
}
