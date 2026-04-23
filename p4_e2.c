#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"
#include "radio.h"

int main(int argc, char const *argv[]) {
    FILE *f_in = NULL;
    BSTree *t = NULL;
    Radio *r = NULL;
    Music *m = NULL;
    long music_id;
    int i, n;

    /* Pedimos el fichero txt y la ID de la canción que queremos borrar */
    if (argc != 3) {
        printf("Uso: %s <fichero_in> <music_id_a_borrar>\n", argv[0]);
        return EXIT_FAILURE;
    }

    f_in = fopen(argv[1], "r");
    if (!f_in) {
        printf("Error: No se pudo abrir el archivo %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    r = radio_init();
    if (!r || radio_readFromFile(f_in, r) == ERROR) {
        if (r) radio_free(r);
        fclose(f_in);
        return EXIT_FAILURE;
    }

    t = tree_init(music_plain_print, music_cmp);
    if (!t) {
        radio_free(r);
        fclose(f_in);
        return EXIT_FAILURE;
    }

    /* 1. Llenamos el árbol con las canciones del fichero */
    n = radio_getNumberOfMusic(r);
    for (i = 0; i < n; i++) {
        tree_insert(t, radio_getMusicIndex(r, i));
    }

    printf("Árbol construido correctamente.\n");
    printf("-> Tamaño original: %ld | Profundidad: %d\n\n", tree_size(t), tree_depth(t));

    /* 2. Buscamos la canción en la base de datos de la radio para borrarla del árbol */
    music_id = atol(argv[2]);
    for (i = 0; i < n; i++) {
        if (music_getId(radio_getMusicIndex(r, i)) == music_id) {
            m = radio_getMusicIndex(r, i);
            break;
        }
    }

    if (!m) {
        printf("Error: La canción con ID %ld no existe en la base de datos.\n", music_id);
    } else {
        /* 3. EJERCICIO 2 - PROBAR EL BORRADO */
        printf("Intentando borrar la canción: ");
        music_plain_print(stdout, m);
        printf("\n");

        if (tree_remove(t, m) == OK) {
            printf("[ÉXITO] Canción borrada del árbol.\n");
        } else {
            printf("[ERROR] Fallo al borrar la canción.\n");
        }

        printf("-> Tamaño final tras borrado: %ld | Profundidad: %d\n", tree_size(t), tree_depth(t));
    }

    /* Limpieza */
    tree_destroy(t);
    radio_free(r);
    fclose(f_in);

    return EXIT_SUCCESS;
}