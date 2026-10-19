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
/*MaP*/

While (fgets!=\0)
Fegtc()
C=atoi
While (fgets!=\0)
	Fgetc(ler Segunda parte da string)
L=atoi


/*Position*/

Structure Pos
While (fgets!=\0)
Fegtc(ler string)
[i]=atoi
While (fgets!=\0)
	Fgetc(ler Segunda parte da string)
Cityx[i]=atoi
While (fgets!=\0)
	Fgetc(ler terceira parte da string)
Cityy[i]=atoi
Cityx[i]=(int)malloc
Cityy[i]=(int)malloc
For (j=0, j<C, j++)
	If (i!=j)
Cityx[j]=(int)malloc
Cityy[j]=(int)malloc



/*Structure D*/
For (j=0, j<C, j++)
	If (i!=j)
		D[i]=sqrt(Cityx[j]*Cityx[i] + Cityy[j]*Cityy[i])
	Else

Cluster/Tarefa 1
//k -> clusters

K=0
“int i, p, q, t, N = atoi (argv[1]); 
int *id = (int *) malloc (N * sizeof (int)); 
if (id == NULL) { 
printf(“Unable to allocate id vector! Exiting…\n”); 
exit(2); 
} 
for (i = 0; i < N ; i ++) id[i] = i ; 
while (scanf("%d %d", &p, &q) == 2) { 
if (id[p] == id[q]) continue;
t = id[p]; 
Cluster[k]=malloc
CinC[k] ++
for (i = 0; i < N; i ++) 
if (id[i] == t) id[i] = id[q]; 
printf (“Taks2/n);
For (i=0, i<k, i++);
printf (“Cluster” “%d”, i)
ClusterQ=k+1;
  
    fclose(f_quests);
    fclose(f_map);
    fclose(f_pos);

    return 0;
}
