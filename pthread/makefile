CC=gcc
CFLAGS=-W
LIBRARY=-lpthread -lrt
SOURCE_MULT=mult-matrix-pthread.c
SOURCE_SUM=sum-matrix-pthread.c
BIN_MULT=mult-matrix-pthread
BIN_SUM=sum-matrix-pthread

all:
	$(CC) $(CFLAGS) -o $(BIN_MULT) $(SOURCE_MULT) $(LIBRARY)
	$(CC) $(CFLAGS) -o $(BIN_SUM) $(SOURCE_SUM) $(LIBRARY)

mult-matrix-pthread:
	$(CC) $(CFLAGS) -o $(BIN_MULT) $(SOURCE_MULT) $(LIBRARY)

sum-matrix-pthread:
	$(CC) $(CFLAGS) -o $(BIN_SUM) $(SOURCE_SUM) $(LIBRARY)

clean:
	@rm -rf mult-matrix-pthread sum-matrix-pthread
