#include "img_pro.c"
#define MASK_SIZE 3



unsigned char **medianf(unsigned char **img, int NC, int NR, int count) {
    int i, j, k, l, m, n;
    unsigned char **result = alloc_img(NC, NR);

    while (count > 0) {
        for (i = 1; i < NR - 1; i++) {
            for (j = 1; j < NC - 1; j++) {
                unsigned char values[MASK_SIZE * MASK_SIZE];
                int index = 0;
                for (k = -1; k <= 1; k++) {
                    for (l = -1; l <= 1; l++) {
                        values[index++] = img[i + k][j + l];
                    }
                }
                // Use a simple sorting algorithm to find the median
                for (m = 0; m < MASK_SIZE * MASK_SIZE - 1; m++) {
                    for (n = 0; n < MASK_SIZE * MASK_SIZE - m - 1; n++) {
                        if (values[n] > values[n + 1]) {
                            unsigned char temp = values[n];
                            values[n] = values[n + 1];
                            values[n + 1] = temp;
                        }
                    }
                }
                result[i][j] = values[4]; // Median is at index 4 in the sorted array
            }
        }
        count--;

        // Swap pointers to update for the next iteration
        unsigned char **temp = img;
        img = result;
        result = temp;
    }

    // Free the unused result array
    free_img(result);

    return img;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename.pgm> <count>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int count = atoi(argv[2]);
	printf("%c %c",filename[0],filename[1]);
    int NC, NR;
    unsigned char **original = pgm_file_to_img(filename, &NC, &NR);
    img_to_pgm_file(original, "Im1.pgm", NC, NR);

    unsigned char **medianFiltered = medianf(original, NC, NR, count);
    img_to_pgm_file(medianFiltered, "Im3.pgm", NC, NR);

    show_pgm_file("Im1.pgm");
    show_pgm_file("Im3.pgm");

    free_img(original);
    free_img(medianFiltered);

    return 0;
}

