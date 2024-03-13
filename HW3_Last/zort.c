// gcc hw3.c -o hw3 img_pro.c -lm
// ./hw3 lenna.ppm 1
/* If auto-detection doesn't work, choose your operating system. Comment out the rest. */
 //#define _WIN32 
/* #define _WIN32 */
/* #define __linux */
/* #define __unix */
/* #define __APPLE__ */

#include "img_pro.h"



color **cgaussf(color **img, int flag, int NC, int NR, int count)
{
	color **temp_1;
	color **temp_2;
	int i , j , k , padding;
	temp_1 = (color **)alloc_color_img(NC , NR); // to allocate space for corrected pixel values (same size with img)
	temp_2 = (color **)alloc_color_img(NC , NR); // to allocate space for corrected pixel values (same size with img)
	padding = count / 2; // define a padding which prevents segmentation faults
	if(flag == 0)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].r=img[i][j].r; // to process the gaussian filter for red pixels, and not destroy the original img, temp_1 used as a temporary variable
						temp_1[i][j].g=img[i][j].g; // to process the gaussian filter for green pixels, and not destroy the original img, temp_1 used as a temporary variable
						temp_1[i][j].b=img[i][j].b; // to process the gaussian filter for blue pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].r = (temp_1[i][j-1].r + 2 * temp_1[i][j].r + temp_1[i][j+1].r) / 4; // horizontal mask was done to red pixels and stored in temp_2 variable
							temp_2[i][j].g = (temp_1[i][j-1].g + 2 * temp_1[i][j].g + temp_1[i][j+1].g) / 4; // horizontal mask was done to green pixels and stored in temp_2 variable
							temp_2[i][j].b = (temp_1[i][j-1].b + 2 * temp_1[i][j].b + temp_1[i][j+1].b) / 4; // horizontal mask was done to blue pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].r = (temp_2[i-1][j].r + 2 * temp_2[i][j].r + temp_2[i+1][j].r) / 4; // vertical mask was done to red pixels and stored in temp_1 varible
							temp_1[i][j].g = (temp_2[i-1][j].g + 2 * temp_2[i][j].g + temp_2[i+1][j].g) / 4; // vertical mask was done to green pixels and stored in temp_1 varible
							temp_1[i][j].b = (temp_2[i-1][j].b + 2 * temp_2[i][j].b + temp_2[i+1][j].b) / 4; // vertical mask was done to blue pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	else if(flag == 1)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].r=img[i][j].r; // to process the gaussian filter for red pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].r = (temp_1[i][j-1].r + 2 * temp_1[i][j].r + temp_1[i][j+1].r) / 4; // horizontal mask was done to red pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].r = (temp_2[i-1][j].r + 2 * temp_2[i][j].r + temp_2[i+1][j].r) / 4; // vertical mask was done to red pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	else if(flag == 2)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].g=img[i][j].g; // to process the gaussian filter for green pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].g = (temp_1[i][j-1].g + 2 * temp_1[i][j].g + temp_1[i][j+1].g) / 4; // horizontal mask was done to green pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].g = (temp_2[i-1][j].g + 2 * temp_2[i][j].g + temp_2[i+1][j].g) / 4; // vertical mask was done to green pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	else if(flag == 3)
	{
		for(i = padding; i < NR - padding; i++)
		{
			for(j = padding; j < NC - padding; j++)
			{
				for(i = 0 ; i < NR ; i++) 
				{
					for(j = 0 ; j < NC ; j++)
					{
						temp_1[i][j].b=img[i][j].b; // to process the gaussian filter for blue pixels, and not destroy the original img, temp_1 used as a temporary variable
					}
				}

				for(k = 0 ; k < count ; k++)
				{
					for(i = 0 ; i < NR ; i++)
					{
						for(j = 1 ; j < NC - 1 ; j++)
						{
							temp_2[i][j].b = (temp_1[i][j-1].b + 2 * temp_1[i][j].b + temp_1[i][j+1].b) / 4; // horizontal mask was done to blue pixels and stored in temp_2 variable
						}
					}
					for(i = 1 ; i < NR - 1 ; i++)
					{
						for(j = 0 ; j < NC ; j++)
						{
							temp_1[i][j].b = (temp_2[i-1][j].b + 2 * temp_2[i][j].b + temp_2[i+1][j].b) / 4; // vertical mask was done to blue pixels and stored in temp_1 varible
						}
					}
				}
			}
		}
	}
	free_color_img(temp_2); // since temp_2 is not gonna used, it was freed
	return temp_1; // in the main part, temp_1 variable will be assigned for displaying the processed image, so it was returned
}

int main(int argc , char **argv)
{
int i,j,NR,NC,NR2,NC2,count;
char *ppm_file;
color **img;
color **img_temp;
color **first;
color **second;
color **third;
color **fourth;


if(argc!=3) 
{
  printf("\nUsage: hw3 [Image file (*.pgm)] [count]\n");
  printf("\nE.g.   hw3 lenna.ppm 1\n");
  exit(-1); 
}

ppm_file = argv[1]; // 2nd input for which image should be corrected
count = atoi(argv[2]); // 3rd count variable got from user as string, we convert it into integer value to use it. It will be used as a flag to choose if we want to perform Gauss operation

img = (color **)ppm_file_to_img(ppm_file , &NC , &NR); // to save uncorrected pixel values

img_temp = (color **)alloc_color_img(NC*4 ,NR);	// to allocate space for corrected pixel values (same size with img)
first = (color **)alloc_color_img(NC , NR); 		// to allocate space for corrected pixel values (same size with img)
second = (color **)alloc_color_img(NC , NR);		// to allocate space for corrected pixel values (same size with img)
third = (color **)alloc_color_img(NC , NR); 	// to allocate space for corrected pixel values (same size with img)
fourth = (color **)alloc_color_img(NC , NR); 	// to allocate space for corrected pixel values (same size with img)

// ----------------------- GAUSSIAN FILTERING MAIN (CALLING THE FUNCTION) PART ----------------------
first = cgaussf(img , 0 , NC , NR , count); 		// Filtering part: for top-left, count times gaussian filter was processed, flag 0 situation occured; which includes RGB pixels.
second = cgaussf(img , 1 , NC , NR , count);		// Filtering part: for top-right, count times gaussian filter was processed, flag 1 situation occured; which includes R pixels.
third = cgaussf(img , 2 , NC , NR , count);		// Filtering part: for bottom-left, count times gaussian filter was processed, flag 2 situation occured; which includes G pixels.
fourth = cgaussf(img , 3 , NC , NR , count);		// Filtering part: for bottom-right, count times gaussian filter was processed, flag 3 situation occured; which includes B pixels.

for(int i=0;i<NR;i++){
	for(int j=0;j<NC;j++){
		second[i][j].g=0;
		second[i][j].b=0;
	}
}
for(int i=0;i<NR;i++){
	for(int j=0;j<NC;j++){
		third[i][j].r=0;
		third[i][j].b=0;
	}
}
for(int i=0;i<NR;i++){
	for(int j=0;j<NC;j++){
		fourth[i][j].g=0;
		fourth[i][j].r=0;
	}
}
// reconstruct the image by adding up the sliced and filtered pieces according to conditions mentioned below
for(i = 0 ; i < NR ; i++)
{
	for(j = 0 ; j < NC*4 ; j++)
	{
		if(i < NR && j < NC)
		{
			img_temp[i][j] = first[i][j];		// Q1 allocation from top-left array to the img_temp array
		}
		else if(i < NR && j <2*NC && j>NC )
		{
			img_temp[i][j] = second[i][j-NC]; 		// Q2 allocation from second array to the img_temp array
		}
		else if(i < NR && j <3*NC && j>2*NC )
		{
			img_temp[i][j] = third[i][j-2*NC];	// Q3 allocation from third array to the img_temp array
		}
		else if(i < NR && j <4*NC && j>3*NC)
		{
			img_temp[i][j] = fourth[i][j-3*NC];	// Q4 allocation from fourth array to the img_temp array
		}
	}
}
// img_temp used to reconstruct the image because, we wanted a non-destructive approach, with this, we saved the original img

// img to pgm conversion and showing part
img_to_ppm_file(img_temp, "gauss.ppm" , NC*4, NR); 	// Converting image(matrix) to actual image



return(1);
}
