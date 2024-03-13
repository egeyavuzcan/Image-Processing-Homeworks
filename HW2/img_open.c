#include "img_pro.h"
#include "img_pro.c"


#include "img_pro.h"

int main(int argc, char *argv[]) {
    char input_file[256];  // Dosya adý için bir karakter dizisi
    char output_file[256]; // Dosya adý için bir karakter dizisi

    // Kullanýcýdan giriþ dosyasýný al
    printf("Lütfen giriþ dosyasýnýn adýný girin: ");
    scanf("%255s", input_file);

    // Kullanýcýdan çýkýþ dosyasýný al
    printf("Lütfen çýkýþ dosyasýnýn adýný girin: ");
    scanf("%255s", output_file);

    unsigned char **img;
    int NC, NR;

    // pgm_file_to_img fonksiyonu ile img dizisi oluþturulur
    img = pgm_file_to_img(input_file, &NC, &NR);

    // img_to_pgm_file fonksiyonu ile yeni bir pgm dosyasý oluþturulur
    img_to_pgm_file(img, output_file, NC, NR);

    // img dizisinin bellekten serbest býrakýlmasý
    free_img(img);

    // Oluþturulan yeni pgm dosyasýnýn görüntülenmesi
    show_pgm_file(output_file);

    return 0;
}

