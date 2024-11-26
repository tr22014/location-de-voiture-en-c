#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nom[20];
} client;

int counter = 1;

typedef struct {
    char marque[20];
    char utilisateur[20];
    int modele;
    char carburant[30];
    int place;
    char transmission[20];
    float prix;
    char disponibilite[25];
    int id;
} voiture;

voiture* remplissage(voiture *v);
voiture* ajout(voiture *v, int *n);
void aff(voiture *v, int n);
void modifier(voiture *v, int n);
void supprimer(voiture *v, int *n);
void trie(voiture*v,int n);
void chercher(voiture*v,int n);
void menu(void);

voiture* remplissage(voiture *v) {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "a")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    printf("Marque: ");
    fgets(v->marque, sizeof(v->marque), stdin);
    fprintf(fp, "Marque: %s", v->marque);
    printf("Nom d'utilisateur: ");
    fgets(v->utilisateur, sizeof(v->utilisateur), stdin);
    fprintf(fp, "Nom d'utilisateur: %s", v->utilisateur);
    printf("Modele: ");
    scanf("%d", &v->modele);
    fprintf(fp, "Modele: %d\n", v->modele);
    getchar();
    printf("Type de carburant: ");
    fgets(v->carburant, sizeof(v->carburant), stdin);
    fprintf(fp, "Type de carburant: %s", v->carburant);
    printf("Nombre de place: ");
    scanf("%d", &v->place);
    fprintf(fp, "Nombre de place: %d\n", v->place);
    getchar();
    printf("Transmission (automatique ou manuelle): ");
    fgets(v->transmission, sizeof(v->transmission), stdin);
    fprintf(fp, "Transmission: %s", v->transmission);
    printf("Prix de location par jour: ");
    scanf("%f", &v->prix);
    fprintf(fp, "Prix de location par jour: %.2f\n", v->prix);
    getchar();
    printf("Disponibilite (disponible ou non disponible): ");
    fgets(v->disponibilite, sizeof(v->disponibilite), stdin);
    fprintf(fp, "Disponibilite: %s", v->disponibilite);
    fclose(fp);
    v->id = counter;
    counter++;
    printf("\nVoiture ajoutee avec succes.\n");
    menu();
    return v;
}


voiture* ajout(voiture *v, int *n) {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "a")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    if (v == NULL) {
        v = (voiture*)malloc(sizeof(voiture));
        if (v == NULL) {
            printf("Allocation de memoire echouee.\n");
            exit(1);
        }
    } else {
        v = (voiture*)realloc(v, (*n + 1) * sizeof(voiture));
        if (v == NULL) {
            printf("Allocation de memoire echouee.\n");
            exit(1);
        }
    }
    (*n)++;
    remplissage(&v[*n - 1]);
    fclose(fp);
    return v;
}

void aff(voiture *v, int n) {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "r")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int i;
    if (n == 0) {
        printf("Aucune voiture disponible.\n");
        menu();
        return;
    }
    printf("Liste des voitures disponibles a la location :\n");
    for (i = 0; i < n; i++) {
        printf("ID:%d\n", (v + i)->id);
        printf("Marque:%s", (v + i)->marque);
        printf("Nom d'utilisateur:%s", (v + i)->utilisateur);
        printf("Modele:%d\n", (v + i)->modele);
        printf("Type de carburant:%s", (v + i)->carburant);
        printf("Nombre de place:%d\n", (v + i)->place);
        printf("Transmission (automatique ou manuelle):%s", (v + i)->transmission);
        printf("Prix de location par jour:%.2f\n", (v + i)->prix);
        printf("Disponibilite (disponible ou non disponible):%s", (v + i)->disponibilite);
        printf("-------------------------------------\n");
    }
    menu();
}

void modifier(voiture *v, int n) {
    int id, i;
    printf("Entrez l'ID du vehicule a modifier : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < n; i++) {
        if ((v + i)->id == id) {
            printf("Entrez les nouvelles informations pour le vehicule ID %d :\n", id);
            remplissage(v + i);
            return;
        }
    }
    printf("Aucun vehicule trouve avec l'ID %d.\n", id);
    menu();
}

void supprimer(voiture *v, int *n) {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "w")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int id, i, j;
    printf("Entrez l'ID du vehicule a supprimer : ");
    scanf("%d", &id);
    getchar();
    for (i = 0; i < *n; i++) {
        if ((v + i)->id == id) {
            for (j = i; j < *n - 1; j++) {
                *(v + j) = *(v + j + 1);
            }
            (*n)--;
            printf("Le vehicule avec l'ID %d a ete supprime avec succes.\n", id);
            menu();
            v = (voiture*)realloc(v, (*n) * sizeof(voiture));
            fclose(fp);
            return;
        }
    }
    printf("Aucun vehicule trouve avec l'ID %d.\n", id);
    menu();
}

void trie(voiture* v, int n) {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "r")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    int i, x;
    voiture temp;
    printf("Entrez votre choix de tri par prix (1 pour croissant, 2 pour decroissant) : ");
    scanf("%d", &x);
    getchar();

    switch (x) {
        case 1:
            for (i = 0; i < n - 1; i++) {
                int j;
                for (j = 0; j < n - i - 1; j++) {
                    if ((v + j)->prix > (v + j + 1)->prix) {
                        temp = *(v + j);
                        *(v + j) = *(v + j + 1);
                        *(v + j + 1) = temp;
                    }
                }
            }
            break;
        case 2:
            for (i = 0; i < n - 1; i++) {
                int j;
                for (j = 0; j < n - i - 1; j++) {
                    if ((v + j)->prix < (v + j + 1)->prix) {
                        temp = *(v + j);
                        *(v + j) = *(v + j + 1);
                        *(v + j + 1) = temp;
                    }
                }
            }
            break;
        default:
            printf("Choix non valide.\n");
            break;
    }
    aff(v, n);
    fclose(fp);
}

void chercher(voiture*v,int n) {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "r")) == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        exit(1);
    }
    char x[20]; 
    int i;

    printf("Entrez la marque a chercher: ");
    fgets(x, sizeof(x), stdin); 

    for(i = 0; i < n; i++) {
        if (strcmp((v+i)->marque, x) == 0) {
        	printf("La voiture est trouvee, voici les informations:\n");
            printf("ID:%d\n", (v + i)->id);
            printf("Marque:%s", (v + i)->marque);
            printf("Nom d'utilisateur:%s", (v + i)->utilisateur);
            printf("Modele:%d\n", (v + i)->modele);
            printf("Type de carburant:%s", (v + i)->carburant);
            printf("Nombre de place:%d\n", (v + i)->place);
            printf("Transmission (automatique ou manuelle):%s", (v + i)->transmission);
            printf("Prix de location par jour:%.2f\n", (v + i)->prix);
            printf("Disponibilite (disponible ou non disponible):%s", (v + i)->disponibilite);
            printf("-------------------------------------\n");
            menu();
            fclose(fp);
            return;
        }
    }
    printf("Aucun vehicule trouve avec la marque %s.\n", x);
    menu();
    fclose(fp);
}

void menu(void) {
    printf("\n****************************** MENU ***************************\n");
    printf("1) Afficher la liste des voitures disponibles\n");
    printf("2) Ajouter une voiture\n");
    printf("3) Modifier une voiture\n");
    printf("4) Supprimer une voiture\n");
    printf("5) Trier les voitures\n");
    printf("6) Chercher une voiture\n");
    printf("7) Quitter\n");
    printf("***************************************************************\n\n");
}

int main() {
    FILE *fp;
    if ((fp = fopen("voiture.txt", "r")) == NULL) {
        printf("Fichier voiture.txt non trouve. Creation du fichier...\n");
        fclose(fp);
    }
    voiture *v = NULL;
    int ch;
    int n = 0;
    client cl;
    
    printf("Veuillez saisir votre nom: ");
    fgets(cl.nom, sizeof(cl.nom), stdin);
    printf("Bienvenue monsieur %sVoici notre application de location de voitures !\n", cl.nom);
    menu();

    while (1) {
        printf("Veuillez saisir votre choix: ");
        scanf("%d", &ch);
        getchar();
        switch (ch) {
            case 1:
                aff(v, n);
                break;
            case 2:
                v = ajout(v, &n);
                break;
            case 3:
                modifier(v, n);
                break;
            case 4:
                supprimer(v, &n);
                break;
            case 5:
                trie(v, n);
                break;
            case 6:
                chercher(v,n);
                break;                
            case 7:
                free(v); 
                printf("Au revoir !\n");
                return 0;
            default:
                printf("Option invalide.\n");
                break;
        }
    } 
    return 0;
}

