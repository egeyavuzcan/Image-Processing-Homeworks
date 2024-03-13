#include "img_pro.h"
int create_same_img(unsigned char **binaryImage, int NC, int NR){
	unsigned char **labelImage = alloc_img_long(NC, NR);
	for(int i=0;i<NR;i++){
		for(int j=0;j<NC;j++){
				labelImage[i][j]=binaryImage[i][j];
				//printf("%d",image[i][j]);

		}
	}
	return labelImage;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_image.pgm>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int NC, NR;
    unsigned char **image = pgm_file_to_img("text.pgm", &NC, &NR);
    unsigned char **image2;
    
    image2 = create_same_img(image,NC,NR);
    
	/* unsigned char **zort = alloc_img(NC,NR);
	for(int i=0;i<NR;i++){
		for(int j=0;j<NC;j++){
				zort[i][j]=image[i][j];
				//printf("%d",image[i][j]);

		}
	} */
	
    img_to_pgm_file(image, "Im1.pgm", NR, NC);

    printf("Successfully created a new PGM file: Im1.pgm\n");
    printf("%d %d",NC,NR);

    free_img(image);

    return 0;
}
