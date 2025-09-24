#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 20

typedef struct {
    char ONG[MAX];
    int MONTO;
    char FILANTROPO[MAX];
} DONACION;

int main() {
    FILE *fp;
    DONACION d, aux;
    int maxMonto = 0;
    char ONGmax[MAX];

    fp = fopen("donaciones.dat", "rb");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Recorremos todas las donaciones
    while (fread(&d, sizeof(DONACION), 1, fp)) {
        int suma = 0;
        long pos = ftell(fp);

        // Sumamos todas las donaciones de esa ONG
        rewind(fp);
        while (fread(&aux, sizeof(DONACION), 1, fp)) {
            if (strcmp(aux.ONG, d.ONG) == 0) {
                suma += aux.MONTO;
            }
        }

        if (suma > maxMonto) {
            maxMonto = suma;
            strcpy(ONGmax, d.ONG);
        }

        fseek(fp, pos, SEEK_SET);
    }

    fclose(fp);

    // Mostramos la ONG con más donaciones
    printf("La ONG que recibio mas donaciones es: %s con un total de %d USD\n", ONGmax, maxMonto);

    // Listamos a sus benefactores
    fp = fopen("donaciones.dat", "rb");
    if (fp == NULL) return 1;

    printf("Sus benefactores fueron:\n");
    while (fread(&d, sizeof(DONACION), 1, fp)) {
        if (strcmp(d.ONG, ONGmax) == 0) {
            printf("- %s dono %d USD\n", d.FILANTROPO, d.MONTO);
        }
    }

    fclose(fp);
    return 0;
}
