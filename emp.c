/*
Simple checker valid emails
Date: 22/09/2015
Author: Wallas
Versão Beta
Greetz: Bruce_Dickinson
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <regex.h>
 
struct result{
       char *openx;
       char *lista;
       char *rc;
}s;
 
void banner(argc) {
     printf("\nSimple Checker Valid Emails\n");
     printf(" Coder: Wallas !\n\n");
     (argc == 1) ? printf("Use: -h--help\n\n") :
     printf('\0');
}
 
 
int help() {
          char xhelp[] = {
          " Options:\n\n"
          " Usage: ./emp -l [wordlist]\n"
          " Example: ./emp -l emails.txt\n\n"};
          int i;
            for(i=0; i < strlen(xhelp); i++)
                putchar(xhelp[i]);
}
 
void file(struct result s) {
     FILE *fp, *arq;
     if((fp = fopen(s.openx, "rb")) == NULL) {
           perror("Error");
           exit(EXIT_SUCCESS);
      }

     if((arq = fopen("valid_emails.txt", "w")) == NULL) {
           perror("Error");
           exit(EXIT_SUCCESS);
      }

     s.lista = malloc(sizeof(char));
     if(s.lista == NULL)
       abort();
	   
      while(!feof(fp)) {
         if(fgets(s.lista,256, fp) != NULL) {
          s.lista[strcspn(s.lista,"\n")] = 0;
          regex(s,arq);
        }
    }

      printf("\n");
      printf("Complete 100%\n\n");
      fclose(fp);
      free(s.lista);
      free(s.rc);
      s.lista = NULL;
      s.rc = NULL;
}
 
int regex(struct result s, FILE *arq) {
      regex_t reg;
      s.rc = realloc(s.lista,100);
      if(regcomp(&reg, "([a-z]|[0-9])([@])", REG_EXTENDED|REG_NOSUB) != 0) {
           fprintf(stdout,"Regex Failed");
       }
 
      if((regexec(&reg, s.lista, 0, (regmatch_t *)NULL,0)) == 0) { 
         strcat(s.lista,"=>Email valid\n");
         printf("%s", s.lista);
           fprintf(arq, "%s", s.lista);
       } else {
           strcat(s.lista,"=>Invalid email\n");
           printf("%s", s.lista);
       }
}
 
int main(int argc, char *argv[]) {
    banner();
    int opt;
    while((opt = getopt(argc,argv,"hl:")) != -1) {
          switch(opt) {
 
                case 'h':
                   help();
                   break;
 
                case 'l':
                   s.openx = optarg;
                   file(s);
                   break;
 
                default:
                 fprintf(stderr, "Error ?");
          }
    }  
}