CC = gcc
CFLAGS = -Wall -ansi -pedantic -g
EXE1 = p3_e1
EXE2 = p3_e2
EXE3 = p3_e3
EXE1S = p3_e1s
EXE2S = p3_e2s

# Opciones de Valgrind
VALGRIND = valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all

# Regla principal para compilar todos los ejecutables
all: $(EXE1) $(EXE2) $(EXE3) $(EXE1S) $(EXE2S)

# -----------------------------------------------------------
# COMPILACIÓN DE EJECUTABLES
# -----------------------------------------------------------

# --- Ejercicio 1 ---
$(EXE1): p3_e1.o queue.o radio.o music.o libstack.a
	$(CC) $(CFLAGS) -o $@ $^

p3_e1.o: p3_e1.c queue.h radio.h music.h types.h stack.h
	$(CC) $(CFLAGS) -c p3_e1.c

# --- Ejercicio 2 ---
$(EXE2): p3_e2.o queue.o radio.o music.o libstack.a
	$(CC) $(CFLAGS) -o $@ $^

p3_e2.o: p3_e2.c radio.h stack.h
	$(CC) $(CFLAGS) -c p3_e2.c

# --- Ejercicio 3 ---
$(EXE3): p3_e3.o list.o radio.o music.o libstack.a queue.o
	$(CC) $(CFLAGS) -o $@ $^

p3_e3.o: p3_e3.c list.h radio.h music.h stack.h
	$(CC) $(CFLAGS) -c p3_e3.c

# Ejecutable 1 Variante List
$(EXE1S): p3_e1.o queueList.o radio.o music.o libstack.a list.o
	$(CC) $(CFLAGS) -o $@ $^

# Ejecutable 2 Variante List
$(EXE2S): p3_e2.o queueList.o radio.o music.o libstack.a list.o
	$(CC) $(CFLAGS) -o $@ $^


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
