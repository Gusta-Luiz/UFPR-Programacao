
# Makefile criado usando como base o modelo do site: https://stackoverflow.com/a/42357205

# Origens
SOURCES = Jewels.c Menulib.c GameLoop.c Gamelib.c

# Nome do Executável
EXE = Jewels

# Opcoes de compilacao
CFLAGS = -std=c99 -Wall -Wextra

# Opcoes de linkagem
LDFLAGS = -r

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
Jewels.o: Jewels.c Gamelib.h Menulib.h GameLoop.h
Menulib.o: Menulib.c Menulib.h Gamelib.h
GameLoop.o: GameLoop.c GameLoop.h Gamelib.h
Gamelib.o: Gamelib.c Gamelib.h