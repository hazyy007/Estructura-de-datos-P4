#include <stdio.h>
#include <stdlib.h>
#include "bstree.h"
#include "radio.h"

int main(int argc, char const *argv[]) {
    FILE *f_in = NULL;
    BSTree *t = NULL;
    Radio *r = NULL;
    Music *m_min = NULL, *m_max = NULL;
    List *l = NULL;
    long id_min, id_max;
    int i, n;

    if (argc != 4) {
        printf("Uso: %s <fichero_in> <id_min> <id_max>\n", argv[0]);
        return EXIT_FAILURE;
    }

    f_in = fopen(argv[1], "r");
    if (!f_in) {
        printf("Error al abrir el fichero.\n");
        return EXIT_FAILURE;
    }

    r = radio_init();
    if (!r || radio_readFromFile(f_in, r) == ERROR) {
        if (r) radio_free(r);
        fclose(f_in);
        return EXIT_FAILURE;
    }

    t = tree_init(music_plain_print, music_cmp);
    n = radio_getNumberOfMusic(r);
    for (i = 0; i < n; i++) {
        tree_insert(t, radio_getMusicIndex(r, i));
    }

    id_min = atol(argv[2]);
    id_max = atol(argv[3]);

    m_min = music_init();
    music_setId(m_min, id_min);
    m_max = music_init();
    music_setId(m_max, id_max);

    music_setTitle(m_max, "zzzzzzzzzz");
    music_setArtist(m_max, "zzzzzzzzzz");

        
    printf("Lista de canciones desde id %ld hasta id %ld\n", id_min, id_max);
    
    l = tree_rangeSearch(t, m_min, m_max);
    
    if (l) {
        while (!list_isEmpty(l)) {
            Music *m = (Music *)list_popFront(l);
            music_plain_print(stdout, m);
            printf("\n");
        }
        list_free(l);
    }

    music_free(m_min);
    music_free(m_max);
    tree_destroy(t);
    radio_free(r);
    fclose(f_in);

    return EXIT_SUCCESS;
}

/* 
 * RESPUESTA P2: ¿qué características observas en la lista resultante?, ¿a qué se debe?
 * 
 * Se observa que la lista resultante está estrictamente ordenada de menor a mayor 
 * según el identificador (ID) de las canciones. 
 * Esto se debe a que la exploración del Árbol Binario de Búsqueda (BST) se ha 
 * implementado siguiendo un recorrido "In-Order" (Inorden). En un BST, recorrer 
 * primero la rama izquierda (menores), luego la raíz (medio), y finalmente la 
 * rama derecha (mayores), garantiza que los elementos se visiten y se inserten 
 * en la lista en su orden natural ascendente.
 */