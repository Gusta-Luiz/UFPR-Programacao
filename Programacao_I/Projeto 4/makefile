
# Makefile criado usando como base o modelo do site: https://stackoverflow.com/a/42357205

# Origens
SOURCES = main.c HomeUI.c GameUI.c Gamelib.c Global.c

# Nome do Executável
EXE = FruitValley

# Opcoes de compilacao 
CFLAGS = -std=c99 -Wall -Wextra

# Bibliotecas
LIBS = -lallegro -lallegro_font -lallegro_image -lallegro_ttf 

# Compilador
LD = gcc

# Cria uma lista de objetos a partir das origens
OBJECTS = $(SOURCES:%.c=%.o)

# O primeiro target é o default, que sera o all
default: all
all: $(EXE)

# Unindo o executavel a partir dos arquivos de objetos
$(EXE): $(OBJECTS)
	$(LD) $(CFLAGS) $(OBJECTS) $(LIBS) -o $(EXE)

# Target que compila todos os arquivos de origem necessarios transformando em objetos
%.o: %.c
	$(LD) $(CFLAGS) -c $< -o $@

# Target para limpar os arquivos de objetos e executavel
clean:
	-rm -f $(OBJECTS)  # Remove the object files

purge: clean
	-rm -f $(EXE)  # Remove the executable program

# Origens e suas dependencias
main.o: main.c Global.h HomeUI.h GameUI.h Gamelib.h
HomeUI.o: HomeUI.c HomeUI.h Global.h
GameUI.o: GameUI.c GameUI.h Global.h Gamelib.h
Gamelib.o: Gamelib.c Gamelib.h Global.h
Global.o: Global.c Global.h