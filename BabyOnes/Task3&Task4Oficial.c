#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <Tasks.c>
#include <Map.c>

int **Cluster = NULL;
int *ClusterSize = NULL;
int numeroClusters = 0;
int C = 0;
int *Task3C = NULL;
int *Task4C = NULL;

int Task3(int i, int C, int Temp,
          int **Cluster, int CinC[],
          int **Cityx, int **Cityy,
          int *clusterCC)
{
    int k, j, n; //k->clusters totais, j->incrementador, n->ve a cidade
    int KRef = -1;
    int CC = -1;
    int Temp2 = i;
    int CurrentK;
    int TempK;
    
    double ShortestD = DBL_MAX;
    double D;
    double dx, dy;

    if (k<=1) {     //verificar se existe mais do que um cluster
        return -2;
    }

    for (CurrentK=0; CurrentK<=k; CurrentK++) {  //encontar cluster da cidae de referencia
        for (n=0; n<CinC; n++){
            for (j=0; j<=ClusterSize; j++){
                if (Cluster[n]==Task3C){
                KRef=CurrentK;
                }
            }
        }

    }

    for (TempK=0; TempK<=k; TempK++){   //percorrer clusters dif de ref
        if (TempK!=KRef){}
            for (n=0; n<ClusterSize[TempK]; n++){   //calcular distancias
            dx = (double) Cityx[TempK][n] - Cityx[KRef][i];
            dy = (double) Cityy[TempK][n] - Cityy[KRef][i];
            
            D = sqrt(dx * dx + dy * dy);

            if (ShortestD>D){   //guardo a distancia mais curta e a cidade
            ShortestD=D;
            CC=n;
            }
        }
        printf ("A distância mais pequena da cidade %d, do cluster %d, no cluster %d é a cidade %d",
            Task3C, KRef, TempK, Cluster[TempK][n]);
        printf ("A sua distância é de %d", ShortestD);
    }
    
}

int Task4 (int i, int C, int Temp,
          int **Cluster, int CinC[],
          int **Cityx, int **Cityy,
          int *clusterCC) {

    int k, j, n; //k->clusters totais, j->incrementador, n->ve a cidade
    int KRef = -1;
    int CC, CCR;
    int Temp2 = 0;
    int CurrentK;
    int TempK;
    int Rep1, Rep2;
    
    double ShortestD = DBL_MAX;
    double D;
    double dx, dy;
    
    if (k<=1) {     //verificar se existe mais do que um cluster
        return -2;
    }

    for (CurrentK=0; CurrentK<=k; CurrentK++) {
        for (n=0; n<CinC; n++){
            for (j=0; j<=ClusterSize; j++){
                if (Cluster[n]==Task4C){
                KRef=CurrentK;
                }
            }
        }
    }
    for (TempK=0; TempK<=k; TempK++){
        if (TempK!=KRef){}
        CC=-1;
        CCR=-2;
        while (Temp2 == 0) {     //loop infinito
        
        
            for (n=0; n<ClusterSize[TempK]; n++){
                dx = (double) Cityx[TempK][n] - Cityx[KRef][i];
                dy = (double) Cityy[TempK][n] - Cityy[KRef][i];
            
                D = sqrt(dx * dx + dy * dy);

                if (ShortestD>D){
                    ShortestD=D;
                    CC=n;
                }
            }
            for (j=0; n<ClusterSize[KRef]; j++){    //calcular distancia entre CC e as outras cidades do cluster de referencia
                dx = (double) Cityx[KRef][j] - Cityx[TempK][CC];
                dy = (double) Cityy[KRef][j] - Cityy[TempK][CC];
            
                D = sqrt(dx * dx + dy * dy);

                    if (ShortestD>D){
                        ShortestD=D;
                        i = j;
                        CCR=j;
                }
            }
            if (Rep1==CC){break;}  //break se o valor não mudou
            Rep1 = CC;   //guardar cidade para depois ver se repete
            if (Rep2==CCR){break;} //break se o valor não mudou
            Rep2 = CCR;   //guardar cidade para depois ver se repete
        }
}