#include "img_pro.c"
#include "img_pro.h"

#define THRESHOLD 128

// Data structure to store equivalence table
typedef struct {
    int label;
    int parent;
} EquivTable;

// Function to initialize equivalence table
void initEquivTable(EquivTable *equivTable, int size) {
    for (int i = 0; i < size; i++) {
        equivTable[i].label = i;
        equivTable[i].parent = i;
    }
}

// Function to find the root label for equivalence
int findRoot(EquivTable *equivTable, int label) {
    while (equivTable[label].parent != label) {
        label = equivTable[label].parent;
    }
    return label;
}

// Function to perform union of two labels in the equivalence table
void performUnion(EquivTable *equivTable, int label1, int label2) {
    int root1 = findRoot(equivTable, label1);
    int root2 = findRoot(equivTable, label2);
    if (root1 != root2) {
        equivTable[root1].parent = root2;
    }
}

// Function to apply the second connected component labeling algorithm
void secondConnectedComponentLabeling(unsigned char **binaryImage, int width, int height) {
    // Create a 2D array to store labels
    unsigned char **labelImage = alloc_img_long(width, height);

    // Initialize the equivalence table
    EquivTable *equivTable = (EquivTable *)malloc(width * height * sizeof(EquivTable));
    initEquivTable(equivTable, width * height);

    int currentLabel = 1; // Start labeling from 1

    // Top-down pass for labeling
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (binaryImage[y][x] >= THRESHOLD) {
                int a = labelImage[y - 1][x - 1];
                int b = labelImage[y - 1][x];
                int c = labelImage[y - 1][x + 1];
                int d = labelImage[y][x - 1];

                if (a || b || c || d) {
                    int minLabel = min(a, min(b, min(c, d)));
                    labelImage[y][x] = minLabel;

                    if (a && a != minLabel) performUnion(equivTable, a, minLabel);
                    if (b && b != minLabel) performUnion(equivTable, b, minLabel);
                    if (c && c != minLabel) performUnion(equivTable, c, minLabel);
                    if (d && d != minLabel) performUnion(equivTable, d, minLabel);
                } else {
                    labelImage[y][x] = currentLabel;
                    currentLabel++;
                }
            }
        }
    }

    // Final pass to assign single label for equivalent labels
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (labelImage[y][x] != 0) {
                labelImage[y][x] = findRoot(equivTable, labelImage[y][x]);
            }
        }
    }

    // Count the number of unique components
    int numComponents = 0;
    for (int i = 1; i < currentLabel; i++) {
        if (equivTable[i].label == i) {
            numComponents++;
            equivTable[i].label = numComponents * (255 / numComponents);
        }
    }

    // Assign discriminating gray values for each CC label
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            if (labelImage[y][x] != 0) {
                labelImage[y][x] = equivTable[labelImage[y][x]].label;
            }
        }
    }

    // Display number of components
    printf("Number of components: %d\n", numComponents);

    // Display the result
    img_to_pgm_file(labelImage, "labeled_image2.pgm", width, height);
    show_pgm_file("labeled_image.pgm");

    // Free allocated memory
    free_img((unsigned char **)labelImage);
    free(equivTable);
}

int main() {
    int width, height;
    unsigned char **image = pgm_file_to_img("recs.pgm", &width, &height);
    if (image == NULL) {
        printf("Error: Unable to read the input image file.\n");
        return 1;
    }

    // Convert the image to a binary image
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (image[y][x] >= THRESHOLD) {
                image[y][x] = 255; // Set as foreground
            } else {
                image[y][x] = 0; // Set as background
            }
        }
    }

    // Apply the second connected component labeling algorithm
    secondConnectedComponentLabeling(image, width, height);

    // Free allocated memory for the original image
    free_img(image);

    return 0;
}
