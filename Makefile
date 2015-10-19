DEBUG=yes
CC=gcc
ifeq ($(DEBUG),yes)
	CDFLAGS=-W -Wall -Wextra -Werror --std=c99 -g
	LDFLAGS=
else
	CDFLAGS=-W -Wall
	LDFLAGS=
endif

EXEC=ISS_ASM

SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)

all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif

$(EXEC): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

document:
	@echo "Génération de la documentation du projet..."
	@echo "Commande à définir."

clean:
	@echo "Suppression des fichiers générés..."
	@rm -vrf *.o
	@echo "Fichiers générés supprimés."

mrproper:	clean
	@rm -vrf $(EXEC)
