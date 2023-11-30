#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int ecrire(int fd, char *buffer, int TAILLE) {
  int err;
      
  // La partie qui vous interesse se trouve ici
  err = write(fd,buffer,TAILLE); // ecrire TAILLE octets sur le fichier
  if (err<0) {
    perror("Erreur d'ecriture");
    exit(1);
  }
  return 0;
}

int main() {
  int i = 0;
  int fd, err;
  int TAILLE = 1024*1024*1024;
  int sys_call_counter = 10; // une variable permettant de définir le nombre d'appels système à effectuer
  char *buffer = malloc(TAILLE/sys_call_counter); // une variable de 1 GB 

  // Ouvrir le fichier /dev/null
  fd = open("/dev/null", O_WRONLY);
  if (fd<0) {
    perror("Erreur d'ouverture");
    exit(1);
  }

  // Appeler la fonction "ecrire" autant de fois qu'il y'a d'appels système à effectuer
  for (i = 0; i < sys_call_counter; i++) {
    ecrire(fd,buffer,TAILLE);
  }

  // Fermer le ficheir /dev/null
  close(fd);
  return 0;
}
