
/* If auto-detection doesn't work, choose your operating system. Comment out the rest. */
 //#define _WIN32 
/* #define _WIN32 */
/* #define __linux */
/* #define __unix */
/* #define __APPLE__ */


/* Include standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <io.h>

/* Some useful macros */
/* #define PI     3.1415927 */ /*   should be already defined  */
#define twoPI  6.2831853
#define halfPI 1.5707963
#define max(a,b) (((a)>=(b))?a:b)
#define min(a,b) (((a)<=(b))?a:b)
#define sq(a) ((a)*(a))
#define cube(a) ((a)*(a)*(a))          
#define diagonal(a,b) (sqrt((a)*(a)+(b)*(b)))


struct a {
    unsigned char r, g, b;
};

typedef struct a color;


#define PPM_GETR(p) ((p).r)
#define PPM_GETG(p) ((p).g)
#define PPM_GETB(p) ((p).b)
#define PPM_ASSIGN(p,red,grn,blu) do { (p).r = (red); (p).g = (grn); (p).b = (blu); } while ( 0 )
#define PPM_EQUAL(p,q) ( (p).r == (q).r && (p).g == (q).g && (p).b == (q).b )
 
    
/* Function definitions */
unsigned char **alloc_img(int ncol,int nrow);
color **alloc_color_img(int ncol,int nrow);
void free_img(unsigned char** img);
void free_color_img(color** img);
void img_to_pgm_file(unsigned char **img, char *file_name,int NC, int NR);
unsigned char **pgm_file_to_img(char *file_name,int *pNC,int *pNR);
void img_to_ppm_file(color **img, char *file_name,int NC, int NR);
color **ppm_file_to_img(char *file_name,int *pNC,int *pNR);
