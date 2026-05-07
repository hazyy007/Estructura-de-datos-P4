#include <stdio.h>
#include <stdlib.h>

#include "bstree.h"
#include "music.h"

int main(int argc, char **argv)
{
  FILE *f;
  BSTree *tree;
  Music **songs;
  Music *m;
  char line[1024];
  int total;
  int i;
  int inserted;
  int min_duration;
  int count;

  if (argc != 3) {
    printf("Error, archivos incompletos");
    return EXIT_FAILURE;
  }

  min_duration = atoi(argv[2]);

  f = fopen(argv[1], "r");
  if (!f) {
    printf("Error abriendo archivo\n");
    return EXIT_FAILURE;
  }

  if (fscanf(f, "%d", &total) != 1) {
    fclose(f);
    return EXIT_FAILURE;
  }

  fgets(line, sizeof(line), f);

  tree = tree_init(music_plain_print, music_cmp);
  if (!tree) {
    fclose(f);
    return EXIT_FAILURE;
  }

  songs = (Music **)malloc(total * sizeof(Music *));
  if (!songs) {
    tree_destroy(tree);
    fclose(f);
    return EXIT_FAILURE;
  }

  inserted = 0;

  for (i = 0; i < total; i++) {
    if (!fgets(line, sizeof(line), f)) {
      break;
    }

    m = music_initFromString(line);
    if (!m) {
      tree_destroy(tree);
      free(songs);
      fclose(f);
      return EXIT_FAILURE;
    }

    if (tree_insert(tree, m) == ERROR) {
      music_free(m);
      tree_destroy(tree);
      free(songs);
      fclose(f);
      return EXIT_FAILURE;
    }

    songs[inserted] = m;
    inserted++;
  }

  fclose(f);

  count = tree_countLongSongs(tree, min_duration);

  printf("Número de canciones con duración mayor a %d segundos: %d\n", min_duration, count);

  tree_destroy(tree);

  for (i = 0; i < inserted; i++) {
    music_free(songs[i]);
  }

  free(songs);

  return EXIT_SUCCESS;
}

/*
P3. No, porque el árbol no está ordenado por duración.

Se construye usando music_cmp, que ordena principalmente por id. Por eso, la
duración de un nodo no permite saber nada sobre la duración de sus hijos.

Así que no se pueden descartar ramas completas y hay que recorrer todo el árbol.
*/