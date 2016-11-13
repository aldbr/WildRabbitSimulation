# Exemple de makefile un peu automatique
 
# compilateur 
CC = g++
# options de compilation 
CCFLAGS =-Wall -Wextra -ansi -pedantic -O2
# options de l'edition des liens
LDFLAGS =-lm
# liste des fichiers objets 
OBJ = main.o Modele.o Lapin.o LapinMale.o LapinFemelle.o 
EXE =executable
 
# regle finale pour la creation de l'executable
executable:$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)
 
# compiler tous les .cpp en .o
.cpp.o:
	$(CC) $(CCFLAGS) -c $<
 
# creation automatique des dependances
dep:
	$(CC) -MM *.cpp > makefile.dep
 
clean:
	rm -rf $(OBJ) core *.h.gch
 
include makefile.dep
