#include "img_pro.h"
#include "img_pro.c"


#include "img_pro.h"

int main(int argc, char *argv[]) {
    char input_file[256];  // Dosya ad� i�in bir karakter dizisi
    char output_file[256]; // Dosya ad� i�in bir karakter dizisi

    // Kullan�c�dan giri� dosyas�n� al
    printf("L�tfen giri� dosyas�n�n ad�n� girin: ");
    scanf("%255s", input_file);

    // Kullan�c�dan ��k�� dosyas�n� al
    printf("L�tfen ��k�� dosyas�n�n ad�n� girin: ");
    scanf("%255s", output_file);

    unsigned char **img;
    int NC, NR;

    // pgm_file_to_img fonksiyonu ile img dizisi olu�turulur
    img = pgm_file_to_img(input_file, &NC, &NR);

    // img_to_pgm_file fonksiyonu ile yeni bir pgm dosyas� olu�turulur
    img_to_pgm_file(img, output_file, NC, NR);

    // img dizisinin bellekten serbest b�rak�lmas�
    free_img(img);

    // Olu�turulan yeni pgm dosyas�n�n g�r�nt�lenmesi
    show_pgm_file(output_file);

    return 0;
}

