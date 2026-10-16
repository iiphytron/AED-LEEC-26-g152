# Makefile de exemplo para o projeto Manhattan
# Ajusta a lista SOURCES aos ficheiros .c que realmente existem no projeto.

CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -Wpedantic -g
LDLIBS   = -lm
TARGET   = projeto

SOURCES  = OpenFile.c Tasks.c Map.c Task3Task4Oficial.c ExitFile.c
OBJECTS  = $(SOURCES:.c=.o)

# Nomes por omissão dos ficheiros de entrada para o alvo "run".
QUESTS   ?= exemplo.quests
MAP      ?= exemplo.map
POSITION ?= exemplo.position

.PHONY: all clean run rebuild

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) "$(QUESTS)" "$(MAP)" "$(POSITION)"

rebuild: clean all

clean:
	rm -f $(OBJECTS) $(TARGET)
