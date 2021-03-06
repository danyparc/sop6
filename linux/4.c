#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double determinant(double[10][10],double);
void cofactor(double[10][10],double);
void transpose(double[10][10],double[10][10],double);

int i,j,k, num=1;
double mtx_a[10][10],mtx_b[10][10],mtx_multi[10][10],mtx_suma[10][10];
int desc_a[2], desc_b[2], desc_Rsuma[2], desc_Rmulti[2], desc_nieto_a[2],desc_nieto_b[2];
int buffer[15][15], buffer2[15][15], buffer3[15][15],buffer4[15][15];

int main(void){
  //int desc[2];

  if(pipe(desc_a) != 0)
    exit(1);

  if(pipe(desc_b) != 0)
    exit(1);

  if (fork()==0) {//Proceso hijo
    if (fork()==0) {//Proceso Nieto
      if(pipe(desc_Rsuma) != 0)
        exit(1);
      printf ("Proceso nieto pid: %d\n", getpid());
      //Leemos matrices
      read (desc_nieto_a[0], mtx_a, 100*sizeof(double));
      read (desc_nieto_b[0], mtx_b, 100*sizeof(double));
      //SUMA
      for(i=0;i<10;i++){
        for(j=0;j<10;j++)
        mtx_suma[i][j]=mtx_a[i][j]+mtx_b[i][j];
      }
      //Pasamos resultado de la suma
      write(desc_Rsuma[1],mtx_suma,100*sizeof(double));
      return EXIT_SUCCESS;
    }
    if(pipe(desc_Rmulti) != 0)
      exit(1);

    if(pipe(desc_nieto_a) != 0)
      exit(1);

    if(pipe(desc_nieto_b) != 0)
      exit(1);

    if(pipe(desc_Rsuma) != 0)
      exit(1);

    printf ("Proceso hijo pid: %d\n", getpid());
    //leemos matrices
    close(desc_a[1]);
    close(desc_b[1]);
    read (desc_a[0], mtx_a, 100*sizeof(double));
    read (desc_a[0], mtx_b, 100*sizeof(double));
    //Imprimimos matrices
    for ( i = 0; i < 10; i++) {
      for ( k = 0; k < 10; k++)
        printf("%.1lf h", mtx_a[i][k]);
      printf("\n");
    }
    //printf("\nhey");
    //MULTIPLICACIÓN
    for (i=0;i<10;i++){
     for (j=0;j<10;j++){
       mtx_multi[i][j]=0;
       for (k=1;k<=10;k++)
         mtx_multi[i][j]=mtx_multi[i][j]+mtx_a[i][k]*mtx_b[k][j];
      }
    }
    for ( i = 0; i < 10; i++) {
      for ( k = 0; k < 10; k++)
        printf("%.1lf ", mtx_multi[i][k]);
    }

    //Pasamos mismas matrices al nieto
    close(desc_nieto_a[0]);
    close(desc_nieto_b[0]);
    write(desc_nieto_a[1], mtx_a, 100*sizeof(double));
    write(desc_nieto_b[1], mtx_b, 100*sizeof(double));
    //Pasamos resultado de la multiplicacion
    write(desc_Rmulti[1],mtx_multi,100*sizeof(double));
    return EXIT_SUCCESS;
  }


  //Llenamos las matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++) {
      mtx_a[i][k]=num;
      mtx_b[i][k]=num++;
    }
  }

  //Pasamos las matrices al hijo
  close(desc_a[0]);
  write(desc_a[1], mtx_a, 100*sizeof(double));
  close(desc_b[0]);
  write(desc_b[1], mtx_b, 100*sizeof(double));

  //Imprimimos matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%.1lf ", mtx_a[i][k]);
    printf("\n");
  }
  printf("\n");
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%.1lf ", mtx_b[i][k]);
    printf("\n");
  }

  close(desc_Rmulti[1]);
  read(desc_Rmulti[0],mtx_multi,100*sizeof(double));
  printf("\n\tRESULTADO MULTIPLICACIÓN\n\n");
  //Imprimimos matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%.1lf ", mtx_multi[i][k]);
    printf("\n");
  }

  close(desc_Rsuma[1]);
  read(desc_Rsuma[0],mtx_suma,100*sizeof(double));
  printf("\n\tRESULTADO Suma\n\n");
  //Imprimimos matrices
  for ( i = 0; i < 10; i++) {
    for ( k = 0; k < 10; k++)
      printf("%.1lf ", mtx_suma[i][k]);
    printf("\n");
  }





  //INVERSA
  double d;
  d=determinant(mtx_multi, 10);
  if (d==0) {
    printf("Determinante multi: %f\n", d);
    printf("No existe la inversa para esta matriz\n");
  }else{
    cofactor(mtx_multi,10);
  }

  d=determinant(mtx_suma, 10);
  if (d==0) {
    printf("Determinante suma: %f\n", d);
    printf("No existe la inversa para esta matriz\n");
  }else{
    cofactor(mtx_suma,10);
  }




  return 0;
}

/*For calculating Determinant of the Matrix . this function is recursive*/
double determinant(double matrix[10][10],double size){
  double s=1,det=0,m_minor[10][10];
  int i,j,m,n,c;
  if (size==1){
    return (matrix[0][0]);
  }
  else{
    det=0;
    for (c=0;c<size;c++){
      m=0;
      n=0;
      for (i=0;i<size;i++){
        for (j=0;j<size;j++){
          m_minor[i][j]=0;
          if (i != 0 && j != c){
            m_minor[m][n]=matrix[i][j];
            if (n<(size-2))
            n++;
            else{
              n=0;
              m++;
            }
          }
        }
      }
      det=det + s * (matrix[0][c] * determinant(m_minor,size-1));
      s=-1 * s;
    }
  }
  return (det);
}


/*calculate cofactor of matrix*/
void cofactor(double matrix[10][10],double size){
  double m_cofactor[10][10],matrix_cofactor[10][10];
  int p,q,m,n,i,j;
  for (q=0;q<size;q++){
    for (p=0;p<size;p++){
      m=0;
      n=0;
      for (i=0;i<size;i++){
        for (j=0;j<size;j++){
          if (i != q && j != p){
            m_cofactor[m][n]=matrix[i][j];
            if (n<(size-2))
            n++;
            else{
              n=0;
              m++;
            }
          }
        }
      }
      matrix_cofactor[q][p]=pow(-1,q + p) * determinant(m_cofactor,size-1);
    }
  }
  transpose(matrix,matrix_cofactor,size);
}

/*Finding transpose of cofactor of matrix*/
void transpose(double matrix[10][10],double matrix_cofactor[10][10],double size){
  int i,j;
  double m_transpose[10][10],m_inverse[10][10],d;
  for (i=0;i<size;i++){
    for (j=0;j<size;j++){
      m_transpose[i][j]=matrix_cofactor[j][i];
    }
  }
  d=determinant(matrix,size);
  for (i=0;i<size;i++){
    for (j=0;j<size;j++){
      m_inverse[i][j]=m_transpose[i][j] / d;
    }
  }
  printf("\n\n\t* * * * * * * * * * * * * * * * * * * * * * * \n\n\tLa Matriz Inversa es : \n\n");
  for (i=0;i<size;i++){
    for (j=0;j<size;j++){
      printf("%.2lf",m_inverse[i][j]);
    }
    printf("\n\n");
  }
  printf("\n\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
  printf("\n* * * * * * * * * * * * * * * * * THE END * * * * * * * * * * * * * * * * * * *");
  printf("\n* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
}
