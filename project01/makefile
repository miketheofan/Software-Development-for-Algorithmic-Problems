SOURCE_FILES = ./src/
HEADER_FILES = ./headers/
DATA_FILES = ./data/
TESTS_FILES = ./tests/
LSH_FILES = ./LSH/
STRUCTURES_FILES = ./structures/
BRUTE_FILES = ./brute/
CUBE_FILES = ./CUBE/
CLUSTER_FILES = ./CLUSTER/

LSH_OBJS = $(LSH_FILES)/mainLSH.o $(SOURCE_FILES)/utilLSH.o $(DATA_FILES)/items.o $(STRUCTURES_FILES)/Hash.o $(STRUCTURES_FILES)/HashTable.o $(BRUTE_FILES)/bruteFunctionsLSH.o $(STRUCTURES_FILES)/G.o $(STRUCTURES_FILES)/H.o
CUBE_OBJS = $(CUBE_FILES)/mainCUBE.o $(SOURCE_FILES)/utilCUBE.o $(STRUCTURES_FILES)/HyperCube.o $(DATA_FILES)/items.o $(STRUCTURES_FILES)/HashTable.o $(BRUTE_FILES)/bruteFunctionsCUBE.o $(STRUCTURES_FILES)/H.o
CLUSTER_OBJS = $(CLUSTER_FILES)/mainCLUSTER.o $(SOURCE_FILES)/utilCLUSTER.o $(STRUCTURES_FILES)/Cluster.o $(DATA_FILES)/items.o $(STRUCTURES_FILES)/HyperCube.o  $(STRUCTURES_FILES)/HashTable.o $(STRUCTURES_FILES)/Hash.o $(STRUCTURES_FILES)/G.o $(STRUCTURES_FILES)/H.o
SOURCE = $(LSH_FILES)mainLSH.cpp $(SOURCE_FILES)/utilLSH.cpp $(DATA_FILES)/items.cpp $(STRUCTURES_FILES)/Hash.cpp $(STRUCTURES_FILES)/HashTable.cpp $(BRUTE_FILES)/bruteFunctionsLSH.cpp $(CUBE_FILES)/mainCUBE.cpp $(STRUCTURES_FILES)/HyperCube.cpp $(SOURCE_FILES)/utilCUBE.cpp $(BRUTE_FILES)/bruteFunctionsCUBE.cpp $(CLUSTER_FILES)/mainCLUSTER.cpp $(SOURCE_FILES)/utilCLUSTER.cpp $(STRUCTURES_FILES)/Cluster.cpp
HEADER = $(LSH_FILES)mainLSH.h $(HEADER_FILES)/utilLSH.h $(HEADER_FILES)/items.h $(HEADER_FILES)/HashTable.o $(HEADER_FILES)/bruteFunctionsLSH.h $(CUBE_FILES)/mainCUBE.h $(HEADER_FILES)/HyperCube.h $(HEADER_FILES)/utilCUBE.h $(HEADER_FILES)/bruteFunctionsCUBE.h $(CLUSTER_FILES)/mainCLUSTER.h $(HEADER_FILES)/utilCLUSTER.h $(HEADER_FILES)/Cluster.h
OUT1 = outLSH
OUT2 = outCUBE 
OUT3 = outCLUSTER
ARGS1 = -i $(TESTS_FILES)dataset.txt -q $(TESTS_FILES)query.txt -k 4 -L 5 -o output.txt -N 3 -r 500
ARGS2 = -i $(TESTS_FILES)dataset.txt -q $(TESTS_FILES)query.txt -k 14 -M 10 -probes 2 -o output.txt -N 3 -r 500
ARGS3 = -i $(TESTS_FILES)dataset.txt -c $(TESTS_FILES)cluster.conf -o output.txt -complete -m Classic
CC = g++ -O2 -std=c++11
FLAGS = -g -c -Ο3

all: $(LSH_OBJS) $(CUBE_OBJS) $(CLUSTER_OBJS)
	$(CC) -g $(LSH_OBJS) -o $(OUT1)
	$(CC) -g $(CUBE_OBJS) -o $(OUT2)
	$(CC) -g $(CLUSTER_OBJS) -o $(OUT3)

mainLSH.o: mainLSH.cpp
	$(CC) $(FLAGS) $(LSH_FILES)mainLSH.cpp

utilLSH.o: utilLSH.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)utilLSH.cpp

items.o: items.cpp
	$(CC) $(FLAGS) $(DATA_FILES)items.cpp

Hash.o: Hash.cpp
	$(CC) $(FLAGS) $(LSH_FILES)Hash.cpp

HashTable.o: HashTable.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)HashTable.cpp	

bruteFunctionsLSH.o: bruteFunctionsLSH.cpp
	$(CC) $(FLAGS) $(BRUTE_FILES)bruteFunctions.cpp

mainCUBE.o: mainCUBE.cpp
	$(CC) $(FLAGS) $(CUBE_FILES)mainCUBE.cpp	

HyperCube.o: HyperCube.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)HyperCube.cpp	

utilCUBE.o: utilCUBE.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)utilCUBE.cpp	

bruteFunctionsCUBE.o: bruteFunctionsCUBE.cpp
	$(CC) $(FLAGS) $(BRUTE_FILES)bruteFunctionsCUBE.cpp	

mainCLUSTER.o: mainCLUSTER.cpp
	$(CC) $(FLAGS) $(CLUSTER_FILES)mainCLUSTER.cpp	

utilCLUSTER.o: utilCLUSTER.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)utilCLUSTER.cpp	

Cluster.o: Cluster.cpp
	$(CC) $(FLAGS) $(SOURCE_FILES)Cluster.cpp

G.o: G.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)G.cpp	

H.o: H.cpp
	$(CC) $(FLAGS) $(STRUCTURES_FILES)H.cpp		

out1:
	@./$(OUT1) $(ARGS1)

out2:
	@./$(OUT2) $(ARGS2)

out3:
	@./$(OUT3) $(ARGS3)

debug:
	@valgrind  --leak-check=full ./$(OUT3) $(ARGS3)

clean:
	@rm $(OUT1)
	@rm $(OUT2)
	@rm $(OUT3)
	@rm $(SOURCE_FILES)*.o
	@rm $(DATA_FILES)*.o
	@rm $(LSH_FILES)*.o
	@rm $(STRUCTURES_FILES)*.o
	@rm $(CUBE_FILES)*.o
	@rm $(CLUSTER_FILES)*.o
	@rm $(BRUTE_FILES)*.o
