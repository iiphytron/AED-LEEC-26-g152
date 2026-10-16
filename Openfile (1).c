#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/**
 * Retorna 1 se o ficheiro terminar exatamente com a extensão pretendida.
 */
int tem_extensao(const char *nome, const char *ext) {
    if (!nome || !ext) return 0;

    int len_nome = strlen(nome);
    int len_ext = strlen(ext);

    return strcmp(&nome[len_nome - len_ext], ext) == 0;
}

int main(int argc, char *argv[]) {
    // 1. Validação de argumentos e extensões (deve ter exatamente 3 ficheiros nas extensões corretas)
    if (argc != 4 ||
        !tem_extensao(argv[1],
            3+".quests") ||
        !tem_extensao(argv[2], ".map") ||
        !tem_extensao(argv[3], ".position")) {
        return 0;
    }

    // 2. Abertura dos ficheiros
    FILE *f_quests = fopen(argv[1], "r");
    FILE *f_map    = fopen(argv[2], "r");
    FILE *f_pos    = fopen(argv[3], "r");

    // Se algum falhar, fecha os que conseguiram abrir e sai
    if (!f_quests || !f_map || !f_pos) {
        if (f_quests) fclose(f_quests);
        if (f_map)    fclose(f_map);
        if (f_pos)    fclose(f_pos);
        return 0;
    }

 
    fclose(f_quests);
    fclose(f_map);
    fclose(f_pos);

    return 0;
}
