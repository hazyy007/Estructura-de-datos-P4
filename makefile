CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
EXE1 = p4_e1
EXE2 = p4_e2

# Opciones de Valgrind
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

# Regla principal para compilar todos los ejecutables
all: $(EXE1) $(EXE2)

# -----------------------------------------------------------
# COMPILACIÓN DE EJECUTABLES
# -----------------------------------------------------------

# --- Ejercicio 1 ---
$(EXE1): p4_e1.o bstree.o radio.o music.o queue.o list.o libstack.a
	$(CC) $(CFLAGS) -o $@ $^

p4_e1.o: p4_e1.c bstree.h radio.h types.h
	$(CC) $(CFLAGS) -c p4_e1.c

# --- Ejercicio 2 ---
$(EXE2): p4_e2.o bstree.o radio.o music.o queue.o list.o libstack.a
	$(CC) $(CFLAGS) -o $@ $^

p4_e2.o: p4_e2.c bstree.h radio.h types.h
	$(CC) $(CFLAGS) -c p4_e2.c
# -----------------------------------------------------------
# COMPILACIONES COMUNES (LIBRERÍAS Y TADs)
# -----------------------------------------------------------

bstree.o: bstree.c bstree.h list.h types.h
	$(CC) $(CFLAGS) -c bstree.c

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

radio.o: radio.c radio.h music.h queue.h stack.h
	$(CC) $(CFLAGS) -c radio.c

music.o: music.c music.h types.h
	$(CC) $(CFLAGS) -c music.c

list.o: list.c list.h types.h
	$(CC) $(CFLAGS) -c list.c

queueList.o: queueList.c queue.h list.h types.h
	$(CC) $(CFLAGS) -c queueList.c

# -----------------------------------------------------------
# REGLAS DE EJECUCIÓN NORMAL
# -----------------------------------------------------------
run1n: $(EXE1)
	./$(EXE1) data_music_10.txt 8 normal
run1s: $(EXE1)
	./$(EXE1) data_music_10.txt 8 sorted
run2: $(EXE2)
	./$(EXE2) data_music_10.txt 3 7
run: run1n run1s run2

# -----------------------------------------------------------
# REGLAS DE EJECUCIÓN CON VALGRIND
# -----------------------------------------------------------
runv1n: $(EXE1)
	$(VALGRIND) ./$(EXE1) data_music_10.txt 8 normal
runv1s: $(EXE1)
	$(VALGRIND) ./$(EXE1) data_music_10.txt 8 sorted
runv2: $(EXE2)
	$(VALGRIND) ./$(EXE2) data_music_10.txt 3 7
runv: runv1n runv1s runv2
# -----------------------------------------------------------
# LIMPIEZA
# -----------------------------------------------------------
clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3)