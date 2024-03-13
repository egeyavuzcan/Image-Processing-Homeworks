// gcc hw4.c -o hw4 img_pro.c -lm
// ./hw4 filtest1.pgm 100 20

#include "img_pro.h"

#define M 512 //Image width
#define N 512 //Image height

// Structure to store complex numbers
typedef struct {
    double real;
    double imag;
} complex_t;

// Function to perform 2D DFT
void dft2d(double *x, complex_t *X, int m, int n) {
	printf("DTF2 GIRDIM XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX");
    double *cos_values = malloc(m * n * sizeof(double));
    double *sin_values = malloc(m * n * sizeof(double));

    // Precompute cosine and sine values
    for (int n1 = 0; n1 < m; n1++) {
    	printf("n1 %d",n1);
        for (int n2 = 0; n2 < n; n2++) {
        	
            double angle = -2 * M_PI * ((n1 / (double)m) + (n2 / (double)n));
            cos_values[n1 * n + n2] = cos(angle);
            sin_values[n1 * n + n2] = sin(angle);
        }
    }
	printf("2.FOR GIRDIM AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
    // DFT computation using precomputed values
    for (int k1 = 0; k1 < 3; k1++) {
    	printf("k1 %d",k1);
        for (int k2 = 0; k2 < n; k2++) {
        	
            double sum_real = 0;
            double sum_imag = 0;
            for (int n1 = 0; n1 < m; n1++) {
                for (int n2 = 0; n2 < n; n2++) {
                	//printf("fordaym %d",&n1);
                	
                	//printf("n2 %d",n2);
                    int index = n1 * n + n2;
                    sum_real += X[index].real * cos_values[index] - X[index].imag * sin_values[index];
                    sum_imag += X[index].imag * cos_values[index] + X[index].real * sin_values[index];
                }
            }
            X[k1 * n + k2].real = sum_real;
            X[k1 * n + k2].imag = sum_imag;
        }
    }

    free(cos_values);
    free(sin_values);
    printf("ciktim");
}

// 2D inverse DFT function
void idft2d(const complex_t *X, double *x, int m, int n) 
{
	printf("girdim %d");
    for (int n1 = 0; n1 < 1; n1++) 
    {	
    	printf("girdim %d",n1);
        for (int n2 = 0; n2 < n; n2++) 
        {
            double sum_real = 0;
            double sum_imag = 0;
            for (int k1 = 0; k1 < m; k1++) 
            {
                for (int k2 = 0; k2 < n; k2++) 
                {
                    double twiddle1 = 2 * M_PI * n1 * k1 / m;
                    double twiddle2 = 2 * M_PI * n2 * k2 / n;
                    sum_real += X[k1 * N + k2].real * cos(twiddle1 + twiddle2) - X[k1 * N + k2].imag * sin(twiddle1 + twiddle2);
                    sum_imag += X[k1 * N + k2].real * sin(twiddle1 + twiddle2) + X[k1 * N + k2].imag * cos(twiddle1 + twiddle2);
                }
            }
           x[n1 * n + n2] = sqrt(sum_real * sum_real + sum_imag * sum_imag) / (m * n);
           
        }
        ;
    }
    printf("2D IDFT Process is finished.");
}

int main(int argc , char **argv)
{
unsigned char **img;
char *pgm_file;
int i , j , k , r , bw , NC , NR;

if(argc!=4) 
{
  printf("\nUsage: hw4 [Image file (*.ppm)] [center frequency] [bandwith]\n");
  printf("\nE.g.   hw4 filtest1.ppm 100 20\n");
  exit(-1); 
}

pgm_file = argv[1]; // 2nd input for which image should be corrected
r = atoi(argv[2]);
bw = atoi(argv[3]);

img = pgm_file_to_img(pgm_file , &NC , &NR); // to save uncorrected pixel values
//show_pgm_file(pgm_file); // shows uncorrected image

for (int i = 0; i < NR; i++)
{
    for (int j = 0; j < NC; j++)
    {
        
    }
    
}

// Check that r and bw are valid
if (r < 0 || r > 256 || bw < 0 || bw >= r)
{
    printf("Error: Invalid r or bw\n");
    return 1;
}

// Allocate memory for DFT arrays
complex_t *X = (complex_t *) malloc(M * N * sizeof(complex_t));
double *x = (double *) malloc(M * N * sizeof(double));

// Convert image data to double precision and copy to x
for (int i = 0; i < M; i++)
{
    for (int j = 0; j < N; j++)
    {
        x[i * N + j] = (double) img[i][j];
    }
}

// Perform 2D DFT
dft2d(x, X, M, N);

// Apply ideal band-pass filter
int r2 = r * r;
int bw2 = bw * bw;
for (i = 0; i < M; i++)
{
    for (j = 0; j < N; j++)
    {
        int d = (i - M / 2) * (i - M / 2) + (j - N / 2) * (j - N / 2);
        if (d < r2 - bw2 || d > r2 + bw2)
        {
            X[i * N + j].real = 0;
            X[i * N + j].imag = 0;
        }
    }
}

// Perform 2D inverse DFT
idft2d(X, x, M, N);

// Normalize output image data and convert to 8-bit integer
for (int i = 0; i < M; i++)
{
	for (int j = 0; j < N; j++)
	{
		img[i][j] = (unsigned char) (x[i * N + j] / (M * N) * 255);
	}
}

// Write output image to file
img_to_pgm_file(img, "filtered.pgm", M, N);

// Display output image
//show_pgm_file("filtered.pgm");

// Free memory
free(x);
free(X);
free_img(img);

return 0;
}
