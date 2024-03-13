
/*
To compile type:
gcc -o example-color example-color.c img_pro.c -lm
Note that img_pro.c and img_pro.h are updated to handle color images
*/


#include "img_pro.h"


int main()

{
int i,j,NR,NC,NR2,NC2;
color **img;
color **img2;


/*---------->>> Start image manipulation example */
img=(color **)ppm_file_to_img("mandrill.ppm",&NC,&NR);/* read img and its size from file, also allocates memory for img */
img2=(color **)alloc_color_img(NC,NR); /* allocate memory for img2 */

for(i=0;i<NR;i++) 
  for(j=0;j<NC;j++) 
   if(i<10 || i>NR-10 || j<10 || j>NC-10) 
     PPM_ASSIGN(img2[i][j],180,45,80); /* one way to assign R,G,B values to a color pixel */
   else {                              /* another way to assign R,G,B values to a color pixel */
     img2[i][j].r=img[i][j].r;
     img2[i][j].g=img[i][j].g;
     img2[i][j].b=img[i][j].b;
         }
img_to_ppm_file(img2,"test2.ppm",NC,NR);/*  write to file */
free_color_img(img); /* free array */
free_color_img(img2);
show_pgm_file("test2.ppm");/*  show image using an external viewer */
/*----------<<< End image manipulation example */

}
