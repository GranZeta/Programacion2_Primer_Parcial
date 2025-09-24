#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nombre[20];
    int legajo;
} REGISTRO;

int main() {
    FILE *fp;
    REGISTRO R;
    int pos;

    fp = fopen("registros.dat", "rb");
    if (fp == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    // Mover 5 registros antes del final
    fseek(fp, -5 * sizeof(REGISTRO), SEEK_END);

    // Leer ese registro
    fread(&R, sizeof(REGISTRO), 1, fp);
    printf("Nombre leido: %s\n", R.nombre);

    // Retroceder 3 registros desde la posición actual
    fseek(fp, -3 * sizeof(REGISTRO), SEEK_CUR);

    // Mostrar la posición actual en número de registro
    pos = ftell(fp) / sizeof(REGISTRO);
    printf("Posicion actual: %d\n", pos);

    fclose(fp);
    return 0;
}

/*
----------------------------------------------------
📌 Respuesta de la primera parte del parcial:

Nombre leido: LAUTARO
Posicion actual: 2
----------------------------------------------------
*/
