#include <stdio.h>
#include <unistd.h>
#include <string.h>
//#define VALOR 1

int main(void){
  //int desc_arch[2];
  int i,j,k, num=1;
  long int mtx_a[10][10],mtx_b[10][10],mtx_multi[10][10],mtx_suma[10][10];
  //Llenamos las matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++) {
      mtx_a[i][k]=num;
      mtx_b[i][k]=num++;
    }
  }

  //Imprimimos matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%ld ", mtx_a[i][k]);
    printf("\n");
  }
  printf("\n");
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%ld ", mtx_b[i][k]);
    printf("\n");
  }

  //MULTIPLICACIÓN

  for (i=0;i<10;i++){
   for (j=0;j<10;j++){
     mtx_multi[i][j]=0;
     for (k=1;k<=10;k++)
       mtx_multi[i][j]=mtx_multi[i][j]+mtx_a[i][k]*mtx_b[k][j];
    }
  }

  printf("\n\tRESULTADO MULTIPLICACIÓN\n\n");
  //Imprimimos matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%ld ", mtx_multi[i][k]);
    printf("\n");
  }

  //SUMA
  for(i=0;i<10;i++){
    for(j=0;j<10;j++)
      mtx_suma[i][j]=mtx_a[i][j]+mtx_b[i][j];
    /*Se guarda el resultado de la suma en la matriz A*/
  }

  printf("\n\tRESULTADO Suma\n\n");
  //Imprimimos matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%ld ", mtx_suma[i][k]);
    printf("\n");
  }


  //INVERSA
  for(i=0;i<15;i++){//Sacando la identidad
    	for(j=0;j<15;j++) {
        	if(i==j) {
            	mtx_Ia[i][j] = 1;
            	mtx_Ib[i][j] = 1;
        	} else {
            	mtx_Ia[i][j] = 0;
            	mtx_Ib[i][j] = 0;
        	}
    	}
	}


  return 0;
}
