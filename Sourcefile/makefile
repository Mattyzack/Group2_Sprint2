INC = ../inc
SRC = ../src
BIN = ../bin
OBJ = ../obj

CFLAGS = -c -g -Wall
LFLAGS = -o
GCC = gcc -fprofile-arcs -ftest-coverage
IFLAGS = -I $(INC)

all : $(BIN)/client $(BIN)/server

$(OBJ)/client.o : $(SRS)/client.cpp
        $(GCC) $(CFLAGS) $(SRC)/client.cpp $(IFLAGS)
        mv *.o ../obj

$(OBJ)/server.o : $(SRS)/server.cpp
        $(GCC) $(CFLAGS) $(SRC)/server.cpp $(IFLAGS)
        mv *.o ../obj

$(OBJ)/server.o : $(SRS)/voters_list.cpp
          $(GCC) $(CFLAGS) $(SRC)/voters_list.cpp $(IFLAGS)
          mv *.o ../obj

$(OBJ)/server.o : $(SRS)/candidate_list.cpp
         $(GCC) $(CFLAGS) $(SRC)/candidate_list.cpp $(IFLAGS)
         mv *.o ../obj

$(OBJ)/server.o : $(SRS)/Casted_voter_list.cpp
         $(GCC) $(CFLAGS) $(SRC)/casted_voted_list.cpp $(IFLAGS)
         mv *.o ../obj

$(BIN)/server : $(OBJ)/server.o $(OBJ)/voters_list.o
        $(GCC) $(OBJ)/server.o $(OBJ)/voters_list.o $(LFLAGS) $(BIN)/voters_list

$(BIN)/client : $(OBJ)/client.o $(OBJ)/candidate_list.o
        $(GCC) $(OBJ)/client.o $(OBJ)/candidate_list.o $(LFLAGS) $(BIN)/candidate_list

$(BIN)/client : $(OBJ)/client.o $(OBJ)/casted_voted_list.o
        $(GCC) $(OBJ)/client.o $(OBJ)/casted_voted_list.o $(LFLAGS) $(BIN)/casted_voted_list

clean:
        rm -f $(OBJ)/*.o $(BIN)/client $(BIN)/server
