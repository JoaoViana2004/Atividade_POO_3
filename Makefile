# Compilar arquivos fonte  (livro.cpp, usuario.cpp, emprestimo.cpp, main.cpp
# Gerar o executavel biblioteca
#
# CC - variavel que armazena o nome do compilador
# CFLAGS - opcoes de compilacao 
# TARGET - variavel que define o nome do arquivo executavel
# SRCDIR - variavel que contem o diretorio dos arquivos fonte
# OBJDIR - variavel que contem o diretorio dos arquivos objetos
# SOURCES - variavel que lista os arquivos fontes
# OBJECTS - variavel que lista os arquivos objetos
# $(TARGET) - alvo para criar o executavel (depende dos objetos)
# $(OBJDIR) - alvo para criar o diretorio de objetos 
#
#
CC = g++
CFLAGS = -Wall -std=c++11
TARGET = Executavel_Biblioteca
SRCDIR = Biblioteca
OBJDIR = obj
 
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $SRCDIR/%.cpp,$(OBJDIR)/%.o,$(SOURCES))
 
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
 
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@
 
$(OBJDIR):
	mkdir -p $@
 
clean:
	rm -rf $(OBJDIR) $(TARGET)
 
.PHONY: clean