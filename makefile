CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
EXE2 = p4_e2


# Opciones de Valgrind
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

# Regla principal para compilar todos los ejecutables
all: $(EXE1) $(EXE2) $(EXE3) $(EXE1S) $(EXE2S)

# -----------------------------------------------------------
# COMPILACIÓN DE EJECUTABLES
# -----------------------------------------------------------

# --- Ejercicio 2 ---
$(EXE2): p4_e2.o queue.o radio.o music.o libstack.a list.o
	$(CC) $(CFLAGS) -o $@ $^

p4_e2.o: p4_e2.c radio.h stack.h list.h types.h
	$(CC) $(CFLAGS) -c p4_e2.c
# -----------------------------------------------------------
# COMPILACIONES COMUNES (LIBRERÍAS)
# -----------------------------------------------------------

queue.o: queue.c queue.h types.h
	$(CC) $(CFLAGS) -c queue.c

radio.o: radio.c radio.h music.h queue.h
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

run1: $(EXE1)
	./$(EXE1) radio.txt

run2: $(EXE2)
	./$(EXE2) radio_bfs.txt 1 2

run3: $(EXE3)
	./$(EXE3) radio_bfs.txt

# Ejecutar todos seguidos
run: run1 run2 run3
runs: $(EXE1S) $(EXE2S)
	./$(EXE1S) radio.txt
	./$(EXE2S) radio_bfs.txt 1 2


# -----------------------------------------------------------
# REGLAS DE EJECUCIÓN CON VALGRIND
# -----------------------------------------------------------

runv1: $(EXE1)
	$(VALGRIND) ./$(EXE1) radio.txt

runv2: $(EXE2)
	$(VALGRIND) ./$(EXE2) radio_bfs.txt 1 10

runv3: $(EXE3)
	$(VALGRIND) ./$(EXE3) radio_bfs.txt

# Ejecutar todos seguidos con Valgrind
runv: runv1 runv2 runv3


# -----------------------------------------------------------
# LIMPIEZA
# -----------------------------------------------------------

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3) $(EXE1S) $(EXE2S)
