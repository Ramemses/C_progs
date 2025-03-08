#include <stdio.h>
#include <stdlib.h>


double avg_R(double* I, double* U, double E, size_t length)
{
	double total = 0;
	for (size_t i = 0; i < length; i++)
		total += (E-U[i])/I[i] * 1000;
	return total/length;
}


int main(void)
{
	double E1 = 7.6, E2 = 6.1;

	double I1[] = {13.75, 15, 12.5, 11.25, 10, 8.75, 7.5, 6.25, 5, 3.75};
	double I2[] = {14.75, 13.75, 12.5, 11.25, 10.25, 9.25, 8.5, 6.25, 5.25, 4, 7.25};

	double U1[] = {1.2, 0.6, 1.8, 2.4, 3, 3.6, 4.2, 4.8, 5.4, 6};
	double U2[] = {0.8, 1.2, 1.6, 2, 2.4, 2.8, 3.2, 4, 4.4, 4.8, 3.6};

	size_t length_1, length_2;
	length_1 = sizeof(I1)/sizeof(*I1);
	length_2 = sizeof(I2)/sizeof(*I2);
	

	double R1, R2;
	R1 = avg_R(I1, U1, E1, length_1);
	R2 = avg_R(I2, U2, E2, length_2);


	double Pe1, Pe2;
	double Pk1, Pk2;
	Pe1 = E1*E1/(4*R1);
	Pe2 = E2*E2/(4*R2);


	Pk1 = E1*E1/(R1);
	Pk2 = E2*E2/(R2);
	
	printf("R1 = %.5f\n", R1);
	printf("R2 = %.5f\n", R2);
	printf("Pe1 = %.5f\n", Pe1);
	printf("Pe2 = %.5f\n", Pe2);
	printf("Pkz1 = %.5f\n", Pk1);
	printf("Pkz2 = %.5f\n", Pk2);


	return 0;
}
