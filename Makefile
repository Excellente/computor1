CC		= clang++
EXE		= computor
INC 	= ./include/
SRC 	= main.cpp computor.cpp
SRCDIR 	= ./src/
SRCS 	= $(addprefix $(SRCDIR), $(SRC))

all:
	$(CC) $(SRCS) -I $(INC) -o $(EXE)

clean:
	rm -f $(EXE)

re: clean all