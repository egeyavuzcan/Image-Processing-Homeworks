#include <stdio.h>
#include <stdlib.h>
#include "img_pro.c"

#define THRESHOLD 128

// Define the connectivity pattern (a, b, c, d)
const int dx[4] = {0, -1, -1, -1};
const int dy[4] = {-1, -1, 0, 1};

// Function to initialize the equivalence table
void initEquivalenceTable(int *eqTable, int size) {
    for (int i = 0; i < size; i++) {
        eqTable[i] = i;
    }
}

// Function to find the root label of a component
int findRoot(int *eqTable, int label) {
    while (label != eqTable[label]) {
        label = eqTable[label];
    }
    return label;
}

// Function to perform label propagation
void propagateLabels(unsigned char **binaryImage, unsigned long **labeledImage, int width, int height, int *eqTable) {
    int currentLabel = 1; // Initial label

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (binaryImage[y][x] >= THRESHOLD) {
                // Check neighbors (a, b, c, d)
                int minLabel = INT_MAX;
                for (int i = 0; i < 4; i++) {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                        if (binaryImage[ny][nx] >= THRESHOLD) {
                            minLabel = min(minLabel, labeledImage[ny][nx]);
                        }
                    }
                }

                if (minLabel == INT_MAX) {
                    // No labeled neighbors, assign a new label
                    labeledImage[y][x] = currentLabel;
                    eqTable[currentLabel] = currentLabel;
                    currentLabel++;
                } else {
                    // Assign the minimum neighbor label
                    labeledImage[y][x] = minLabel;
                    // Update the equivalence table
                    for (int i = 0; i < 4; i++) {
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (nx >= 0 && ny >= 0 && nx < width && ny < height) {
                            if (binaryImage[ny][nx] >= THRESHOLD) {
                                int root1 = findRoot(eqTable, labeledImage[y][x]);
                                int root2 = findRoot(eqTable, labeledImage[ny][nx]);
                                if (root1 != root2) {
                                    eqTable[root1] = root2;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

int main() {
    // Load the binary image from file (e.g., "cells.pgm")
    int width, height;
    unsigned char **binaryImage = pgm_file_to_img("cells.pgm", &width, &height);

    // Create an array to store labeled image
    unsigned long **labeledImage = alloc_img_long(width, height);

    // Initialize the equivalence table
    int eqTable[width * height];
    initEquivalenceTable(eqTable, width * height);

    // Perform label propagation
    propagateLabels(binaryImage, labeledImage, width, height, eqTable);

    // Find and update the equivalent labels
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            labeledImage[y][x] = findRoot(eqTable, labeledImage[y][x]);
        }
    }

    // Count the number of connected components
    int numComponents = 0;
    for (int i = 0; i < width * height; i++) {
        if (eqTable[i] == i) {
            numComponents++;
        }
    }

    printf("Number of connected components: %d\n", numComponents);

    // Assign discriminating gray values to labels
    for (int i = 0; i < numComponents; i++) {
        eqTable[i] = i * (255 / numComponents);
    }

    // Update the labeled image with discriminating gray values
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            labeledImage[y][x] = eqTable[labeledImage[y][x]];
        }
    }
    // Save the result to an output PGM file
    img_to_pgm_file((unsigned char **)labeledImage, "result.pgm", width, height);

    // Clean up memory
    free_img(binaryImage);
    free_img(labeledImage);

    return 0;
}

