#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "bstree.h"
#include "radio.h"
#include "types.h"

fprintf(f_out, "Removing element in tree: ");
    time = clock();
    fprintf(f_out, "%s", tree_remove(t, m) == OK ? "OK" : "ERR");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
    fprintf(f_out, "Tree size: %ld\nTree depth: %d\n", tree_size(t), tree_depth(t));

  } else {
    fprintf(f_out, "Element NOT found");
    time = clock() - time;
    fprintf(f_out, " - %ld ticks (%f seconds)\n", (long)time, ((float) time) / CLOCKS_PER_SEC);
  }
  
  tree_destroy(t);
  mainCleanUp (EXIT_SUCCESS, r, f_in);
}