#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define Q 5           /*Nombre de question de base*/
#define P 5           /*Nombre de personnage de base*/

void init(int persoTextPoint[][Q+1], char persoText[][90], char quest[][70]);
/* rempli les tableaux a partir des fichiers textes, il y a les questions, les personnages,
et des points correspond à chaque personnages pour chaque question*/
int bestQuestion(int tabPP[][Q+1], int qPos[]);       /* Chercher la meilleur question à poser en fonction des points des personnages*/
int pointQuestion(char quest[][70], int persoPoint[][Q+1], int questPoint[], int qPos[]);
int verif(char quest[][70], int cmp);     /* Verifier le resultat mis par l'utilisateur*/


int nbrQuest(void);


int main(void) {
  /* int nbrA = 0;*/
  /* nbrA = nbrQuest();*/
  /* printf("%d",nbrA);*/
  char static quest[0][70];              /* Va falloir changer ça*/
  char static personnage[0][90];         /* Faut faire des mallocs en fait*/
  int static questPoint[0];              /* Et les deux variables Q et P sont provisoire faut trouver un truc sans*/

  int qPos[Q];
  int persoPoint[P][Q+1];
  int perso;  
  init(persoPoint, personnage, quest);
  int i;

  /* int GP,GQ;                               
   P: nombre de personnage, Q: nombre de question
   GP = initPerso(persoPoint, personnage);
   GQ = initQuest(quest);*/

  for(i = 0; i<Q;i++){
    printf("%s",quest[i]);
  }


  printf("\nNuméros entre 1 et 5 : \n 0 : non connaissance de la question\n 1 : Oui\n 2 : probablement oui\n 3 : ne sais pas \n 4 : probablement non \n 5 : non\n\n");

  perso = pointQuestion(quest, persoPoint, questPoint, qPos);

  printf("Vous pensez à %s ?\n", personnage[perso]);
  return 0;
}

int nbrQuest(void){
  FILE* question = NULL;
  question = fopen("quest.txt", "r+");
  int i=0;

  if(!question) {
    printf("Can't open the file");
  }

   while(feof(question) == 0){
     i++;

     }
  fclose(question);
  printf("%d",i);
  return i-i;
}


/*==========================/ Init \=============================
Fill the array in parameters
- persoTextPoint[][] is the array that must contain the point for each celeb and each question
- persoText[][] is the array that must contain the name of each celeb
- quest[][] is the array that must contain each question
================================================================*/
void init(int persoTextPoint[][Q+1], char persoText[][90], char quest[][70]){
  /*Ouverture des fichiers textes*/
  FILE* celeb = NULL;
  FILE* question = NULL;
  question = fopen("quest.txt", "r+");
  celeb = fopen("people.txt", "r+");

  int i=0, a=0, j=0, rdChar=1;
  char videChar;

  /*Si les fichiers sont vides, message d'erreur.*/
  if(!question || !celeb) {
    printf("Can't open the file");
  }
  
  /*Lecture du fichier question*/
  while(feof(question) == 0){
    /*quest[i] = malloc(1);*/
    fgets(quest[i], 70, question);                                  /*Rempli le tableau 2D des questions
    printf("%s", quest[i]);                                         //Affiche le tableau*/
    i++;
  }
  fclose(question);                                                 /*Fermeture fichier question*/

  int op = 0;
  fgets(persoText[op],90, celeb);                                   /*Initialise la première ligne du tableau de la première célébrité*/
  rdChar = 0;
  
  /*rdChar -> 1: lecture du nom de la célébrité | 0: lecture des points de la célébrité*/
  while(feof(celeb) == 0){                                          /*Parcours le fichier celeb*/
    if(rdChar){
      op++;
      fgets(persoText[op],90, celeb);                               /*Remplit les lignes suivantes du tableau */
      rdChar = 0;                                                   /*Fin de ligne = passage en lecture de points*/
    }
    else{
      fscanf(celeb, "%d", &persoTextPoint[j][a%i]);                 /*Remplit le tableau de point à l'adresse a%i */
      if(persoTextPoint[j][a%(i)] == -1){                           /*Si la ligne de chiffres lu est finie :*/
        j++;
        fgets(&videChar,90, celeb);                                 /*Remplit videChar de \n */
        rdChar = 1;                                                 /*Début de ligne = passage en lecture de celeb    */                      
      }
      a++;
    }
  }
  fclose(celeb);


/*===========/ Affichage provisoire \=============
printf("\n%d/%d/%d/%d",i,op,j,a);
int M = 0;
int R = 0;
for(R = 0; R <Q; R++){
  printf("\n%d:%s:", R, persoText[R]);
  for( M = 0; M <= Q; M++){
    printf("{%d:%d:%d}",R, M,persoTextPoint[R][M]);
  }
}
=================================================*/
  return;
}

/*==========================/ verif \=============================
This function is used in order to check if the answer from the user is valid.
It's called each time the user must respond a question.
================================================================*/
int verif(char quest[][70], int cmp){
  int on = 1;
  int point;
  char poubelle[50];
  while(on){
    /*printf("%d", point);*/
    if(point == 0 || point > 5){
      scanf("%s", poubelle);
      point = atoi(poubelle);
      printf("Veuillez écrire un nombre entre 1 et 5\n");
      printf("%s\n", quest[cmp]);
    }
    else{
      on = 0; 
    }
  }
  return point;
}

/*==========================/ pointQuestion \=============================
This function return the people with the most point. 
The point is calculated 
=======================================================================*/
int pointQuestion(char quest[][70], int persoPoint[][Q+1], int questPoint[], int qPos[]){
  int point, a = 0, i = 0;  
  int valueMax = 0, perso = 0;
  int cmp = 0;
  char poubelle;


  for(i = 0; i < Q; i++){
    cmp = bestQuestion(persoPoint, qPos);
    printf("%s", quest[cmp]);
   
    qPos[cmp] = -1;
    point = verif(quest, cmp);

    for(a = 0; a<Q; a++){
      if(point == persoPoint[a][cmp]){
        questPoint[a] = questPoint[a] + 5;
      }
      else if(abs(point - persoPoint[a][cmp]) == 1){
        questPoint[a] += 3;    
      }
      else{
        questPoint[a] += 1;
      }
      if(questPoint[a] > valueMax){
        valueMax = questPoint[a];
        perso = a;
      }
    }
  }
  return perso;  
}

/*==========================/ bestQuestion \=============================
This function create an array that contain the value of each question.
Then the function will check witch question is the most usefull and then 
return a pointer for the next question.
========================================================================*/
int bestQuestion(int tabPP[][Q+1],  int qPos[]){

  int k1, k2, k3, k4, k5;
  int valueQuest = 0, valueQuestMax = 0;
  int m = 0, j = 0, cmp;
  for(m = 0; m < P; m++){
    if(qPos[m] != -1){
      k1 = 1;k2 = 1; k3 = 1; k4 = 1; k5 = 1;
      for(j = 0; j < P; j++){
        switch(tabPP[j][m]){
          case 1 :
          k1++;
          break;
          case 2 :
          k2++;
          break;
          case 3 :
          k3++;
          break;
          case 4 :
          k4++;
          break;
          case 5 :
          k5++;
          break;
          default :
          break;
        }
      }
      valueQuest = (k1)*(k2)*(k3)*(k4)*(k5);

      if(valueQuest > valueQuestMax){
        valueQuestMax = valueQuest;
        cmp = m;
      }
    }
  }
  /*printf("cmp : %d", cmp);*/
  return cmp;
}


/*
void init(void){
  printf("a");
  FILE* celeb = NULL;
  FILE* question = NULL;
  question = fopen("quest.txt", "r+");
  celeb = fopen("people.txt", "r+");

  if (question != NULL || celeb != NULL){
    printf("Pensez à un personnage.");    
    printf("Vous êtes prets ?");
  }else{
  printf("Impossible d'ouvrir le fichier test.txt");
  }
}

void quest(FILE celeb, FILE question){
  int i = 0;
  while(i < 20){

  }
}
*/
/*##########FUNCTIONS##############
Fct appelant toutes les fonctions

fct demande quest 20 fois
    Va les cherchers dans la bdd

fct attribuant les points de chaque à chaque personnage
  Entre 0-5 et -1

fct si programme se trompe
  Demander d'ajouter le personnage
  Attribuer des points a chaque question

fct ajouter une question
  Demander à quelle question celle-ci ressemble ?
  Demander cmb de points celle-ci vaut pour son personnage (1-5)

Fct triant les meilleurs questions à utiliser
  Rechercher dichotomique
  Initialisation de point à chaque personnages (0)
  Modifier les notes à chaque question (autre fct ?)
    Ajouter ou enlever des points
    Ex : note < 10 --> perso ecarter du jeu

  note = Multi du nbr de personne encore en lice pour chaque point (1-5)
  Plus note elevé, plus question bonne

Fct faisant rapprochement entre les questions
  Si questions proches, celle-ci doivent obtenir un meme nombre de points (1-5)
  Augmentation des points entres les questions qui se ressemblent ou minution

#####COMMENTAIRE######
Ou stocker les points de rapprochement ?
#Dans quest.txt faire une série de chiffre séparé par -1 et mettre l'ID des questions qui se ressemble 
Bof en vrai juste comparé le tableau de question avec les personnages et quelle question repondre à 1 pour les memes perso
Ou stocker les points des question ?
#Dans people ou deja fait 


/http://www-igm.univ-mlv.fr/~borie/esipe/devin.pdf
/https://stackoverflow.com/questions/15738029/how-do-i-use-a-file-as-a-parameter-for-a-function-in-c

//https://stackoverflow.com/questions/4600797/read-int-values-from-a-text-file-in-c

//https://smallbusiness.chron.com/read-first-line-file-c-programming-29321.html

*/
