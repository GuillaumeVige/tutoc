#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Test1 **********************************************************************

typedef  struct S_numtra *ptra ;
typedef struct S_numtra {
  int tranum;
  ptra suiv;
} numtra ;

typedef struct S_tytra
{
   double wd, ld;
   char* nomt;
   int ng,n1,n2,nb;
} tytra;

void print_tran(tytra T)
{
   printf("tran : %8s %4i %4i %4i %4i\n",T.nomt,T.n1,T.n2,T.ng,T.nb);
}

typedef struct S_tynoeud
{
  char * nom;
  int nbtr;
  ptra num;
} tynoeud;

void print_noeud(tynoeud N)
{
   printf("node : %8s",N.nom);
   numtra* vatra = N.num;
   while(vatra != NULL) {
  printf(" %4i",vatra->tranum);
  vatra = vatra->suiv;
   }
   printf("\n");
}

void test1()
{
  printf("Test1 (allocation dynamique de structure + liste chainee) ---------------------------\n");
  tytra T1;
  T1.nomt = "R1";
  T1.n1 = 1;
  T1.n2 = 2;
  T1.ng = -1;
  T1.nb = -1;
  print_tran(T1);
  tytra D1;
  D1.nomt = "D1";
  D1.n1 = 1;
  D1.n2 = 3;
  D1.ng = -1;
  D1.nb = -1;
  print_tran(D1);
  
  tynoeud N1,N2;
  N1.nom = "N1";
  numtra* num1 = malloc(sizeof(numtra));
  numtra* num2 = malloc(sizeof(numtra));
  num1->tranum = 1;
  num1->suiv = num2;
  num2->tranum = 2;
  num2->suiv = NULL;
  N1.num = num1;
  print_noeud(N1);
  
  N2.nom = "N2";
  N2.num = NULL;
  print_noeud(N2);
}

//**********************************************************************
typedef struct {
  char*  name;
  int   index;
}ty_tempsource;

int use_memcpy;

void copy_tempsource(ty_tempsource* dest, const ty_tempsource* src)
{
  if (!use_memcpy)
  {
    //free(dest->name);
    dest->name = (char*)malloc(sizeof(char) * (strlen(src->name) + 1));
    strcpy(dest->name, src->name);
    dest->index = src->index;
  }
  else {
    //free(dest->name);
    //copie de tous des attributs de la structure
    memcpy(dest, src, sizeof(ty_tempsource));
    //comme il y a un pointeur dans ty_tempsource, il faut le copier à part car sa taille n'est pas comptée dans la taille de la structure
    dest->name = (char*)malloc(sizeof(char) * (strlen(src->name) + 1));
    strcpy(dest->name, src->name);
  }
}

ty_tempsource* copy_tempsource2(const ty_tempsource* src)
{
  ty_tempsource* dest = NULL;
  if (src!=NULL)
  {
    dest = (ty_tempsource*)malloc(sizeof(ty_tempsource));
    dest->name = (char*)malloc(sizeof(char) * (strlen(src->name) + 1));
    strcpy(dest->name, src->name);
    dest->index = src->index;
  }
  return dest;
}

void print_tempsource(const ty_tempsource* src)
{
  if (src!=NULL)
  {
    printf("index : %3i\n", src->index);
    printf("name  : %10s\n", src->name);
  }
  else{
    printf("NULL pointer\n");
  }
}

void test2()
{
  ty_tempsource* ts1 = (ty_tempsource*)malloc(sizeof(ty_tempsource));
  ts1->name = (char*)malloc(sizeof(char) * (10 + 1));
  strcpy(ts1->name, "source1");
  ts1->index = 1;
  printf("Pointeur origine\n");
  print_tempsource(ts1);

  ty_tempsource* sav_ts = (ty_tempsource*)malloc(sizeof(ty_tempsource));
  copy_tempsource(sav_ts, ts1);

  // modify objet
  free(ts1->name);
  free(ts1);
  ts1 = NULL;

  // restore objet
  ts1 = (ty_tempsource*)malloc(sizeof(ty_tempsource));
  copy_tempsource(ts1, sav_ts);
  printf("Test restore if dest is a allocated\n");
  print_tempsource(ts1);

  //test copy when dest is a NULL pointer
  /*free(ts1->name);
  free(ts1);
  ts1 = NULL;
  copy_tempsource(ts1, sav_ts);
  printf("Test restore if dest is a NULL pointer\n");
  print_tempsource(ts1);*/

  // Libération de la mémoire
  free(sav_ts->name);
  free(sav_ts);
  free(ts1->name);
  free(ts1);
}

void test3()
{
  printf("\nTest3(copie par fonction retournant une structure) ---------------\n");
  ty_tempsource* ts1 = (ty_tempsource*)malloc(sizeof(ty_tempsource));
  ts1->name = (char*)malloc(sizeof(char) * (10 + 1));
  strcpy(ts1->name, "source1");
  ts1->index = 1;

  ty_tempsource* sav_ts = copy_tempsource2(ts1);
  printf("copie:\n");
  print_tempsource(sav_ts);
  
  // modify objet
  free(ts1->name);
  free(ts1);
  ts1 = NULL;
  ts1 = copy_tempsource2(sav_ts);
  printf("restore:\n");
  print_tempsource(sav_ts);

  free(sav_ts->name);
  free(sav_ts);
  free(ts1->name);
  free(ts1);
}

//**********************************************************************
//d'apres https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/19733-stockez-les-donnees-avec-les-listes-chainees
typedef struct Element Element;
struct Element
{
  int nombre;
  Element *suivant;
};

typedef struct Liste Liste;
struct Liste
{
  Element *premier;
};

Liste *initialisation()
{
  Liste *liste = malloc(sizeof(*liste));
  Element *element = malloc(sizeof(*element));
  
  if (liste == NULL || element == NULL)
  {
    exit(EXIT_FAILURE);
  }
  
  element->nombre = 0;
  element->suivant = NULL;
  liste->premier = element;
  
  return liste;
}

void insertion(Liste *liste, int nvNombre)
{
  /* Création du nouvel élément */
  Element *nouveau = malloc(sizeof(*nouveau));
  if (liste == NULL || nouveau == NULL)
  {
    exit(EXIT_FAILURE);
  }
  nouveau->nombre = nvNombre;

  /* Insertion de l'élément au début de la liste */
  nouveau->suivant = liste->premier;
  liste->premier = nouveau;
}

void suppression(Liste *liste)
{
  if (liste == NULL)
  {
    exit(EXIT_FAILURE);
  }

  if (liste->premier != NULL)
  {
    Element *aSupprimer = liste->premier;
    liste->premier = liste->premier->suivant;
    free(aSupprimer);
  }
}

void afficherListe(Liste *liste)
{
  if (liste == NULL)
  {
    exit(EXIT_FAILURE);
  }

  Element *actuel = liste->premier;

  while (actuel != NULL)
  {
    printf("%d -> ", actuel->nombre);
    actuel = actuel->suivant;
  }
  printf("NULL\n");
}

void test4()
{
  printf("\nTest4 (liste chainee) ---------------\n");
  Liste *maListe = initialisation();

  insertion(maListe, 4);
  insertion(maListe, 8);
  insertion(maListe, 15);
  suppression(maListe);

  afficherListe(maListe);
}

//**********************************************************************

typedef struct S_mailmat { //besoin de nommer la structure afin de creer *vmat
  double* ptxval;
  int icol;
  int jlig;
  struct S_mailmat *vmat; //pointeur sur l'element suivant sur la meme ligne
}mailmat;

typedef struct {
  int nblig;
  int nbcol;
  mailmat **m_matcreux; //m_matcreux[i] = ptr 1er elem ieme ligne
}matrice;

matrice *init_matrice(int nblig, int nbcol)
{
  int i;
  matrice *mat1 = (matrice*)malloc(sizeof(matrice));
  mat1->m_matcreux = (mailmat**)malloc((nblig+1)*sizeof(mailmat*));
  
  if (mat1 == NULL || mat1->m_matcreux == NULL)
  {
    exit(EXIT_FAILURE);
  }
  
  mat1->nblig = nblig;
  mat1->nbcol = nbcol;
  
  for (i=0; i<=mat1->nblig; i++) {
	mat1->m_matcreux[i] = NULL;
  }
  return mat1;
}

void add_elem(matrice *mat, int ilig, int icol, double val)
{
  mailmat *mamat, *preclig;
  mailmat *mail1;
  preclig = NULL;
  mamat = mat->m_matcreux[ilig]; /* get the first cell in the row */
  printf("%3i %3i %p\n",ilig,icol,mamat);
  while (mamat != NULL && mamat->icol<=icol)
  {
    if (mamat->icol == icol) //la maille existe deja
    {
  	  *(mamat->ptxval) = val;
  	  return;
    }
    preclig = mamat; //le terme precedent mamat sur la meme ligne
    mamat = mamat->vmat; /* move to the next cell on the row */
  }
  printf("nouvel elem\n");
  //la maille n'existe pas => on la cree
  mail1 = (mailmat*)malloc(sizeof(mailmat));

  double *val1 = (double*)malloc(sizeof(double));
  *val1 = val;
  mail1->ptxval = val1;
  mail1->jlig = ilig;
  mail1->icol = icol;
  printf("elem cree\n");

  if (mat->m_matcreux[ilig] == NULL) //premier element de la ligne
  {
    mail1->vmat = NULL;
    mat->m_matcreux[ilig] = mail1;
  }
  else 
  {
    if (mamat !=0 ) //mamat = ptr sur la fin de la ligne
    {
      mail1->vmat = mamat; //on raccroche la fin de ligne
    }
	if (preclig == NULL) //insertion de la maille en debut de ligne
	{
      mat->m_matcreux[ilig] = mail1;
	}
	else 
	{
      preclig->vmat = mail1; //on met la maille a la suite de la ligne
	}
  }
}

void affiche_mat(matrice *mat)
{
  int i;
  mailmat *mamat;
  for (i=1; i<=mat->nblig; i++) 
  {
    mamat = mat->m_matcreux[i]; //1er element de la ligne
    while (mamat != NULL) //on parcourt la ligne
    {
       printf("%5i %5i "   " % 8.3e\n",mamat->jlig, mamat->icol, *(mamat->ptxval));
       mamat = mamat->vmat;
    }
  }
}

void free_matrice(matrice *mat)
{
  int i;
  mailmat *mamat;
  if (mat != NULL) {
    if (mat->m_matcreux!=NULL) {
      for (i=0; i<=mat->nblig; i++) {
        if (mat->m_matcreux!=NULL) {
          mamat = mat->m_matcreux[i];
          while (mamat!=NULL) {
            free(mamat->ptxval);
            mamat = mamat->vmat;
          }
		  free(mat->m_matcreux[i]);
		}
      }
	  free(mat->m_matcreux);
    }
	free(mat);
	mat = NULL;
  }
}

void test4()
{
  printf("\nTest4 (matrice) ---------------------------\n");
  
  matrice *mat1 = init_matrice(3,3);
  affiche_mat(mat1);
  add_elem(mat1, 2, 3, 2.3);
  add_elem(mat1, 1, 3, -1.5);
  add_elem(mat1, 2, 3, 6.5);
  add_elem(mat1, 1, 1, -2.9);
  affiche_mat(mat1);
  free_matrice(mat1);
}

int main()
{

  test1();
  printf("\nTest2a (duplication d'une structure contenant un pointeur) ---------------------------\n");
  use_memcpy = 0;
  test2();
  printf("\nTest2b (duplication d'une structure contenant un pointeur avec memcpy) ---------------\n");
  use_memcpy = 1;
  test2();
  test3();
  test4();
  return 0;
}

