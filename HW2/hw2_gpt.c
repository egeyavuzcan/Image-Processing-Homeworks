#include "img_pro.c"

#define MASK_SIZE 3

unsigned char **gaussf(unsigned char **img, int NC, int NR, int count) {
    int i, j, k;
    int mask[MASK_SIZE][MASK_SIZE] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};
    unsigned char **result = alloc_img(NC, NR);

    while (count > 0) {
        for (i = 1; i < NR - 1; i++) {
            for (j = 1; j < NC - 1; j++) {
                int sum = 0;
                for (k = 0; k < MASK_SIZE; k++) {
                    for (int l = 0; l < MASK_SIZE; l++) {
                        sum += mask[k][l] * img[i - 1 + k][j - 1 + l];
                    }
                }
                result[i][j] = sum / 16;
            }
        }
        count--;
        // Swap pointers to update for next iteration
        unsigned char **temp = img;
        img = result;
        result = temp;
    }

    if (count % 2 != 0) {
        // Copy the final result back to original input image if count was odd
        for (i = 0; i < NR; i++) {
            for (j = 0; j < NC; j++) {
                img[i][j] = result[i][j];
            }
        }
        free_img(result);
    } else {
        free_img(img);
        img = result;
    }

    return img;
}

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
                        values[index] = img[i + k][j + l];
                        index++;
                    }
                }
                for (m = 0; m < MASK_SIZE * MASK_SIZE; m++) {
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
        // Swap pointers to update for next iteration
        unsigned char **temp = img;
        img = result;
        result = temp;
    }

    if (count % 2 != 0) {
        // Copy the final result back to original input image if count was odd
        for (i = 0; i < NR; i++) {
            for (j = 0; j < NC; j++) {
                img[i][j] = result[i][j];
            }
        }
        free_img(result);
    } else {
        free_img(img);
        img = result;
    }

    return img;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <filename.pgm> <count>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int count = atoi(argv[2]);

    int NC, NR;

    unsigned char **original = pgm_file_to_img(filename, &NC, &NR);
	printf(" %d ",original[0][5]);
    unsigned char **gaussFiltered = gaussf(original, NC, NR, count);
    unsigned char **medianFiltered = medianf(original, NC, NR, count);

    img_to_pgm_file(original, "Im1_1.pgm", NC, NR);
    img_to_pgm_file(gaussFiltered, "Im2.pgm", NC, NR);
    img_to_pgm_file(medianFiltered, "Im3.pgm", NC, NR);

    show_pgm_file("Im1.pgm");
    show_pgm_file("Im2.pgm");
    show_pgm_file("Im3.pgm");

    free_img(original);
    free_img(gaussFiltered);
    free_img(medianFiltered);

    return 0;
}
