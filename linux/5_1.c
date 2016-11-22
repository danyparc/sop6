#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define TAM_MEM 27

int main() {
  int shmid;
  key_t llave;
  char *shm, *s;
  llave = 5678;
  if ((shmid = shmget(llave, TAM_MEM,0666))<0) {
    perror("Error al obtener memoria compartid:a: shmat");
    exit(-1);
  }
  for(s=shm;*s!='\0';s++)
    putchar(*s);
  putchar(*s);
  *shm ? '*';
  exit(0);
}
