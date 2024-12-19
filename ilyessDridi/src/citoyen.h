#ifndef HEADERS_H
#define HEADERS_H
#include <gtk/gtk.h>
#define MAX_LINE_LENGTH 256
#define TEMP_FILE "temp_signup.txt"
typedef struct {
    char nom[50];
    char prenom[50];
    int cin;
    char ville[50];
    char modele[50];
    char matricule[50];
    int age;
    char sexe[10];
} citoyen;
typedef struct {
    int idCitoyen ;
  char nomParking[100] ;
  char typeService[100] ;
  char weekendPrix[100] ;
  int mois ;
}gestion ;


typedef struct {
    int idParking;
    int priceParking;
    char nameParking[50];
} Parking;

typedef struct {
    int idService;
    int priceService;
    char nameService[50];
} Service;

typedef struct {
    int idCitoyen;
    char date[11];
    char hour[6];
    int idParking;
    int idService;
} Reservation; 

typedef struct{
   char nom[100];
   char prenom[100]; 
   char email[300]; 
   char mdp[50];
   char type[100];
} Users;


int ajouter( char *citoyenFichier, citoyen c,char *errorMessage);
int modifier(char *citoyenFichier, int cin, citoyen nouv,char *errorMessage);
int chercherMois(char *servicesFichier, char *findFichierMois ,int mois);
int chercherNomParcking(char *servicesFichier, char *findFichierNom ,char nomParcking[100]);
int supprimer(char *citoyenFichier, int cin);
int affichier(GtkWidget *liste);

int loadParkingData(char *filename, Parking parkings[], int maxCount);
int loadServiceData(char *filename, Service services[], int maxCount);
void generateFacture(const char *resFile, const char *srvFile, const char *prkFile, const char *factureFile, int targetIdCitoyen,char *totaleMessage);
void searchByMonth(const char *factureFile, int month,char *totaleMessage);
int is_valid_email(char *email);
int password_strength(char *password);
int signup( char *email,char *password,char *nom,char *prenom);
int signin( char *email,char *password,char *userType);
int emailExist(char *email,char *errorMessage);
void viderTreeView(GtkWidget *treeview);
void populate_treeview_with_file2(GtkWidget *treeview, const char *filename);
size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp);
void send_email(const char *recipient, const char *subject, const char *body);
void changePassword(const char *email, const char *newPassword);
#endif



