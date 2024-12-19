#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citoyen.h"
#include <math.h>
#include <curl/curl.h>

int is_valid_email(char *email) {
    return strchr(email, '@') != NULL;
}

int password_strength(char *password) {
    int length = strlen(password);
    int has_lower = 0, has_upper = 0, has_digit = 0, has_special = 0;

    if (length < 8) return 0; // Too short

    for (int i = 0; i < length; i++) {
        if (islower(password[i])) has_lower = 1;
        else if (isupper(password[i])) has_upper = 1;
        else if (isdigit(password[i])) has_digit = 1;
        else if (strchr("!@#$%^&*()-_=+[]{};:'\",.<>?/\\|", password[i])) has_special = 1;
    }

    if (has_lower && has_digit && has_upper && has_special) return 3; // Strong
    if (has_lower && has_digit) return 2;                            // Normal
    if (has_lower) return 1;                                         // Weak
    return 0;                                                        // Invalid
}

int signup(char *email, char *password, char *nom, char *prenom) {
    // Validate email
    if (!is_valid_email(email)) {
        printf("Invalid email! Please include an '@' symbol.\n");
        return 0;
    }

    // Validate password strength
    int strength = password_strength(password);
    if (strength == 0) {
        printf("Password must be at least 8 characters long and contain a mix of uppercase letters, digits, and symbols.\n");
        return 0;
    } else if (strength == 1) {
        printf("Weak password! Your password only contains lowercase letters.\n");
        return 0;
    } else if (strength == 2) {
        printf("Normal password. Consider adding symbols for better security.\n");
    } else if (strength == 3) {
        printf("Strong password! Well done.\n");
    }

    // Open file for appending
    FILE *f = fopen("signup.txt", "a");
    if (f == NULL) {
        printf("Error opening file for signup.\n");
        return 0;
    }

    // Save user details
    fprintf(f, "%s %s %s %s %s \n", nom, prenom, email, password,"citoyen");
    fclose(f);

    printf("Signup successful!\n");
    return 1;
}


int signin(char *email, char *password,char *userType) {
    // Open the file in read mode
    FILE *f = fopen("signup.txt", "r");
    if (f == NULL) {
        printf("Error: Could not open signup.txt.\n");
        return 0;
    }

    Users temp;
    int found = 0;

    // Read user data from the file
    while (fscanf(f, "%49s %49s %49s %49s %49s", temp.nom, temp.prenom, temp.email, temp.mdp,temp.type) == 5) {
        if (strcmp(temp.email, email) == 0 && strcmp(temp.mdp, password) == 0) {
            printf("Signin successful!\n"); 
	snprintf(userType, 256,temp.type);
            found = 1;
            break;
        }
    }

    fclose(f); // Ensure the file is closed
    return found;
} 

int emailExist(char *email,char *errorMessage){
    // Open the file in read mode
    FILE *f = fopen("signup.txt", "r");
    if (f == NULL) {
        printf("Error: Could not open signup.txt.\n");
       
        return 0;
    }

    Users temp;
    int found = 0;

    // Read user data from the file
    while (fscanf(f, "%49s %49s %49s %49s %49s", temp.nom, temp.prenom, temp.email, temp.mdp,temp.type) == 5) {
        if (strcmp(temp.email, email) == 0) {
            printf("email verified!\n");
            snprintf(errorMessage, 256, "email verified!");
            found = 1;
            break;
        }else {snprintf(errorMessage, 256, "email dont exist!");}
    }

    fclose(f); // Ensure the file is closed
    return found;
} 

int ajouter(char *citoyenFichier, citoyen c,char *errorMessage) {
     printf( "%s %s %d %s %s %s %d %s\n", c.nom, c.prenom, c.cin, c.ville, c.modele, c.matricule, c.age, c.sexe);
    FILE *f = fopen(citoyenFichier, "a+");
    if (f == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    citoyen temp;
    while (fscanf(f, "%s %s %d %s %s %s %d %s", temp.nom, temp.prenom, &temp.cin, temp.ville, temp.modele, temp.matricule, &temp.age, temp.sexe) != EOF) {
        if (temp.cin == c.cin) {
            printf("CIN already exists. Cannot add citoyen.\n");
snprintf(errorMessage, 256, "CIN already exists. Cannot add citoyen.");
            fclose(f);
            return 0;
        }
    }
    int length = (c.cin == 0) ? 1 : (int)log10(abs(c.cin)) + 1;
    if (length != 8) {
        printf("CIN should contain exactly 8 digits.\n");
 snprintf(errorMessage, 256, "CIN should contain exactly 8 digits.");
        fclose(f);
        return 0;
    }
    fprintf(f, "%s %s %d %s %s %s %d %s\n", c.nom, c.prenom, c.cin, c.ville, c.modele, c.matricule, c.age, c.sexe);
    fclose(f);
    return 1;
}

int modifier(char *citoyenFichier, int cin, citoyen nouv, char *errorMessage) {
    citoyen c;
    int done = 0;
    int length = (nouv.cin == 0) ? 1 : (int)log10(abs(nouv.cin)) + 1;
    if (length != 8) {
        printf("CIN should contain exactly 8 digits.\n");
snprintf(errorMessage, 256, "CIN should contain exactly 8 digits");
        return 0;
    }
int length2 = (cin == 0) ? 1 : (int)log10(abs(cin)) + 1;
    if (length2 != 8) {
        printf("CIN of the citoyen to update should contain exactly 8 digits.\n");
       snprintf(errorMessage, 256, "CIN of the citoyen to update should contain exactly 8 digits.");
        return 0;
    }

    FILE *f = fopen(citoyenFichier, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f == NULL || f2 == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    while (fscanf(f, "%s %s %d %s %s %s %d %s", c.nom, c.prenom, &c.cin, c.ville, c.modele, c.matricule, &c.age, c.sexe) == 8) {
        if (c.cin == cin) {
            fprintf(f2, "%s %s %d %s %s %s %d %s\n", nouv.nom, nouv.prenom, nouv.cin, nouv.ville, nouv.modele, nouv.matricule, nouv.age, nouv.sexe);
            done = 1;
        } else {
            fprintf(f2, "%s %s %d %s %s %s %d %s\n", c.nom, c.prenom, c.cin, c.ville, c.modele, c.matricule, c.age, c.sexe);
        }
    }
    if(done==0){
printf("citoyen nexiste pas \n");
       snprintf(errorMessage, 256, "citoyen nexiste pas ");
   }

    fclose(f);
    fclose(f2);
    remove(citoyenFichier);
    rename("temp.txt", citoyenFichier);

    return done;
}

int supprimer(char *citoyenFichier, int cin) {
    int done = 0;
    citoyen c;
    FILE *f = fopen(citoyenFichier, "r");
    FILE *f2 = fopen("temp.txt", "w");

    if (f == NULL || f2 == NULL) return 0;

    while (fscanf(f, "%s %s %d %s %s %s %d %s", c.nom, c.prenom, &c.cin, c.ville, c.modele, c.matricule, &c.age, c.sexe) == 8) {
        if (c.cin != cin) {
            fprintf(f2, "%s %s %d %s %s %s %d %s\n", c.nom, c.prenom, c.cin, c.ville, c.modele, c.matricule, c.age, c.sexe);

        } else {
            done = 1;
        }
    }

    fclose(f);
    fclose(f2);

    remove(citoyenFichier);
    rename("temp.txt", citoyenFichier);

    return done;
}

int loadParkingData(char *filename, Parking parkings[], int maxCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening parking file: %s\n", filename);
        return -1;
    }

    int count = 0;
    while (count < maxCount && fscanf(file, "%d,%d,%49s",
            &parkings[count].idParking, &parkings[count].priceParking, parkings[count].nameParking) == 3) {
        count++;
    }
    fclose(file);
    return count;
}

int loadServiceData(char *filename, Service services[], int maxCount) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening service file: %s\n", filename);
        return -1;
    }

    int count = 0;
    while (count < maxCount && fscanf(file, "%d,%d,%49s",
            &services[count].idService, &services[count].priceService, services[count].nameService) == 3) {
        count++;
    }
    fclose(file);
    return count;
}

void generateFacture(const char *resFile, const char *srvFile, const char *prkFile, const char *factureFile, int targetIdCitoyen,char *totaleMessage) {
    Parking parkings[100];
    Service services[100];
    Reservation res;
    int parkingCount = loadParkingData(prkFile, parkings, 100);
    int serviceCount = loadServiceData(srvFile, services, 100);

    if (parkingCount < 0 || serviceCount < 0) {
        printf("Error loading data.\n");
        return;
    }

    FILE *resFilePtr = fopen(resFile, "r");
    FILE *factureFilePtr = fopen(factureFile, "w");

    if (!resFilePtr || !factureFilePtr) {
        printf("Error opening reservation or facture file.\n");
        return;
    }

    fprintf(factureFilePtr, "Date\t\tHour\t\tNameParking\t\tNameService\t\tPrice\n");
    int totalPrice = 0;
    int recordFound = 0;

    while (fscanf(resFilePtr, "%d,%10[^,],%5[^,],%d,%d", &res.idCitoyen, res.date, res.hour, &res.idParking, &res.idService) == 5) {
        // Only process reservation if the idCitoyen matches the target ID
        if (res.idCitoyen != targetIdCitoyen) {
            continue;  // Skip this reservation if the ID does not match
        }

        int parkingPrice = 0, servicePrice = 0;
        char parkingName[50] = "Unknown";
        char serviceName[50] = "Unknown";

        // Find the parking corresponding to the reservation
        for (int i = 0; i < parkingCount; i++) {
            if (parkings[i].idParking == res.idParking) {
                parkingPrice = parkings[i].priceParking;
                strcpy(parkingName, parkings[i].nameParking);
                break;
            }
        }

        // Find the service corresponding to the reservation
        for (int i = 0; i < serviceCount; i++) {
            if (services[i].idService == res.idService) {
                servicePrice = services[i].priceService;
                strcpy(serviceName, services[i].nameService);
                break;
            }
        }

        int price = parkingPrice + servicePrice;
        totalPrice += price;
        fprintf(factureFilePtr, "%s\t%-5s\t%-16s\t%-16s\t%d\n", res.date, res.hour, parkingName, serviceName, price);
        recordFound = 1;
    }

    if (!recordFound) {
        fprintf(factureFilePtr, "No reservations found for Citizen ID: %d.\n", targetIdCitoyen);
    } else {
        fprintf(factureFilePtr, "\nTotal\t\t\t\t\t\t\t%d\n", totalPrice);
   char str[350];
      sprintf(str, "%d", totalPrice);
       snprintf(totaleMessage, 256,str );
    }

    fclose(resFilePtr);
    fclose(factureFilePtr);

    printf("Facture generated in %s\n", factureFile);
}


void searchByMonth(const char *factureFile, int month,char *totaleMessage) {
    FILE *file = fopen(factureFile, "r");
    FILE *searchFile = fopen("search.txt", "w");

    if (!file || !searchFile) {
        printf("Error opening file.\n");
        return;
    }

    char line[256];       // Buffer to hold each line
    int recordFound = 0;  // Flag to indicate if any records are found
    int totalPrice=0 ;
    // Skip the header line
    fgets(line, sizeof(line), file);

    // Write the header to search.txt
    fprintf(searchFile, "Date\t\tHour\t\tNameParking\t\tNameService\t\tPrice\n");

    // Process each line in the file
    while (fgets(line, sizeof(line), file)) {
        char date[11], hour[6], nameParking[50], nameService[50];
        int price;

        // Parse the line including the hour field
        if (sscanf(line, "%10s\t%5s\t%49[^\t]\t%49[^\t]\t%d", date, hour, nameParking, nameService, &price) == 5) {
            int recordMonth;
            sscanf(date, "%*4d-%2d-%*2d", &recordMonth); // Extract month from date (YYYY-MM-DD format)

            if (recordMonth == month) {
                // Write the matching record to search.txt
                fprintf(searchFile, "%s\t%-5s\t%-16s\t%-16s\t%d\n", date, hour, nameParking, nameService, price);
                 totalPrice += price; 
                 recordFound = 1;
            }
        }
    }

    if (!recordFound) {
        fprintf(searchFile, "No records found for the specified month.\n");
         snprintf(totaleMessage, 256, "0");
    }else {
        char str[350];
      sprintf(str, "%d", totalPrice);
       snprintf(totaleMessage, 256,str );
    }

    fclose(file);
    fclose(searchFile);

    printf("Search results have been saved to search.txt\n");
}



	void add_row(GtkListStore *list_store, const gchar *attribute, const gchar *value) {
    GtkTreeIter iter;

    // Add a new row
    gtk_list_store_append(list_store, &iter);

    // Set values for the row (2 columns: attribute and value)
    gtk_list_store_set(list_store, &iter,
                       0, attribute,  // Column 0: Attribute name
                       1, value,      // Column 1: Value
                       -1);
}

void populate_treeview(GtkWidget *treeview, const char *filename, int target_cin) {
    FILE *file = fopen(filename, "r");
    citoyen c;
    char buffer[50];
    int found = 0;

    // Create the ListStore model
    GtkListStore *list_store = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    // Read the file using fscanf
    while (fscanf(file, "%s %s %d %s %s %s %d %s\n",
                  c.nom, c.prenom, &c.cin, c.ville, c.modele, c.matricule, &c.age, c.sexe) != EOF) {
        // Debugging: Print parsed data
        g_print("Parsed data: Name: %s, Surname: %s, CIN: %d, City: %s, Model: %s, Plate: %s, Age: %d, Gender: %s\n",
                c.nom, c.prenom, c.cin, c.ville, c.modele, c.matricule, c.age, c.sexe);

        // Compare CIN
        if (c.cin == target_cin) {
            found = 1;

            // Add rows for each attribute of the citoyen
            add_row(list_store, "Name", c.nom);
            add_row(list_store, "Surname", c.prenom);
            snprintf(buffer, sizeof(buffer), "%d", c.cin);  // Convert CIN to string
            add_row(list_store, "CIN", buffer);
            add_row(list_store, "City", c.ville);
            add_row(list_store, "Car Model", c.modele);
            add_row(list_store, "License Plate", c.matricule);
            snprintf(buffer, sizeof(buffer), "%d", c.age);  // Convert age to string
            add_row(list_store, "Age", buffer);
            add_row(list_store, "Gender", c.sexe);

            break;  // Exit loop after finding the target citoyen
        }
    }

    fclose(file);

    if (found==0) {
        g_print("Citizen with CIN %d not found in the file.\n", target_cin);
    } else {
        g_print("Citizen with CIN %d found.\n", target_cin);
    }

    // Set the ListStore model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));
    g_object_unref(list_store);

    // Add columns dynamically if they are not already set
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;

        // Create the "Attribute" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Attribute", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Value" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Value", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}  

void add_row2(GtkListStore *list_store, const char *date, const char *hour, const char *nameParking, const char *nameService, int price) {
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, date, 1, hour, 2, nameParking, 3, nameService, 4, price, -1);
} 

void populate_treeview_with_file(GtkWidget *treeview, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // Create a ListStore with 5 columns
    GtkListStore *list_store = gtk_list_store_new(5, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);

    // Read and parse the data from the file
    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char date[11], hour[6], nameParking[50], nameService[50];
        int price;

        // Parse the line
        if (sscanf(line, "%10s\t%5s\t%49[^\t]\t%49[^\t]\t%d", date, hour, nameParking, nameService, &price) == 5) {
            // Add the row to the ListStore
            add_row2(list_store, date, hour, nameParking, nameService, price);
        }
    }

    fclose(file);

    // Set the ListStore model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));
    g_object_unref(list_store);  // Unreference the list_store after setting the model

    // Add columns if not already added
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;

        // Create the "Date" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Date", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Hour" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Hour", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "NameParking" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NameParking", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "NameService" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("NameService", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Price" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Price", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
} 




void show_facture(GtkWidget *treeview) {
    populate_treeview_with_file(treeview, "facture.txt");
}
void show_search(GtkWidget *treeview) {
    populate_treeview_with_file(treeview, "search.txt");
} 

// Function to clear all rows in a GtkTreeView
void viderTreeView(GtkWidget *treeview) {
    if (!treeview) {
        g_print("Error: TreeView widget is NULL.\n");
        return;
    }

    if (!GTK_IS_TREE_VIEW(treeview)) {
        g_print("Error: The widget provided is not a GtkTreeView.\n");
        return;
    }

    GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeview));

    if (GTK_IS_LIST_STORE(model)) {
        // If the model is a GtkListStore, clear it
        GtkListStore *list_store = GTK_LIST_STORE(model);
        gtk_list_store_clear(list_store);
    } else if (GTK_IS_TREE_STORE(model)) {
        // If the model is a GtkTreeStore, clear it
        GtkTreeStore *tree_store = GTK_TREE_STORE(model);
        gtk_tree_store_clear(tree_store);
    } else {
        g_print("Error: TreeView does not have a valid ListStore or TreeStore.\n");
    }
}

void add_row5(GtkListStore *list_store, const char *nom, const char *prenom, int cin,
             const char *ville, const char *modele, const char *matricule, int age, const char *sexe) {
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter,
                       0, nom,
                       1, prenom,
                       2, cin,
                       3, ville,
                       4, modele,
                       5, matricule,
                       6, age,
                       7, sexe,
                       -1);
}
void populate_treeview_with_citoyens(GtkWidget *treeview, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // Create a ListStore with 8 columns
    GtkListStore *list_store = gtk_list_store_new(8, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,
                                                  G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                                  G_TYPE_INT, G_TYPE_STRING);

    citoyen c;

    // Read and parse the data from the file
    while (fscanf(file, "%49s %49s %d %49s %49s %49s %d %9s",
                  c.nom, c.prenom, &c.cin, c.ville, c.modele, c.matricule, &c.age, c.sexe) == 8) {
        // Add the row to the ListStore
        add_row5(list_store, c.nom, c.prenom, c.cin, c.ville, c.modele, c.matricule, c.age, c.sexe);
    }

    fclose(file);

    // Set the ListStore model to the TreeView
    gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), GTK_TREE_MODEL(list_store));
    g_object_unref(list_store);  // Unreference the list_store after setting the model

    // Add columns if not already added
    if (gtk_tree_view_get_columns(GTK_TREE_VIEW(treeview)) == 0) {
        GtkCellRenderer *renderer;
        GtkTreeViewColumn *column;

        // Create the "Name" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Name", renderer, "text", 0, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Surname" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Surname", renderer, "text", 1, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "CIN" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("CIN", renderer, "text", 2, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "City" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("City", renderer, "text", 3, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Car Model" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Car Model", renderer, "text", 4, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "License Plate" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("License Plate", renderer, "text", 5, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Age" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Age", renderer, "text", 6, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);

        // Create the "Gender" column
        renderer = gtk_cell_renderer_text_new();
        column = gtk_tree_view_column_new_with_attributes("Gender", renderer, "text", 7, NULL);
        gtk_tree_view_append_column(GTK_TREE_VIEW(treeview), column);
    }
}


// Callback function to write data (needed for reading the email body)
size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    const char **payload_text = (const char **)userp;
    size_t len = strlen(*payload_text);
    
    // Copy the data into ptr
    if (len) {
        size_t copy_len = size * nmemb < len ? size * nmemb : len;
        memcpy(ptr, *payload_text, copy_len);
        *payload_text += copy_len; // Move pointer forward
        return copy_len;
    }
    return 0;
}

void send_email(const char *recipient, const char *subject, const char *body) {
    CURL *curl;
    CURLcode res;
    struct curl_slist *recipients = NULL;
    
    const char *from = "parky.esprit@gmail.com";
    const char *password = "zvnkktsjxmgocwrr"; // Use App Password here
    
    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_USERNAME, from);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
        curl_easy_setopt(curl, CURLOPT_URL, "smtps://smtp.gmail.com:465");
        
        // Enable SSL
        curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_ALL);
        
        // Sender
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, from);
        
        // Recipient
        recipients = curl_slist_append(recipients, recipient);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
        
        // Create email body with headers and body content
        char payload[1024];  // Increased buffer size
        snprintf(payload, sizeof(payload),
                 "To: %s\r\n"
                 "From: %s\r\n"
                 "Subject: %s\r\n"
                 "\r\n"
                 "%s\r\n", recipient, from, subject, body);
        
        // Set up the payload source (use callback to handle the payload)
        const char *payload_text = payload;
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, (void *)&payload_text);
        
        // Enable uploading of data
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        
        // Debug output
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
        
        // Perform the request
        res = curl_easy_perform(curl);
        
        // Handle result
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            printf("Email sent successfully!\n");
        }
        
        // Cleanup
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }
}

void changePassword(const char *email, const char *newPassword) {
    FILE *file = fopen("signup.txt", "r");
    if (file == NULL) {
        perror("Error opening signup.txt");
        return;
    }

    FILE *tempFile = fopen(TEMP_FILE, "w");
    if (tempFile == NULL) {
        perror("Error opening temporary file");
        fclose(file);
        return;
    }

    char firstName[51], lastName[51], currentEmail[101], currentPassword[51],type[51];
    int emailFound = 0;

    // Read each record from the file
    while (fscanf(file, "%50s %50s %100s %50s %50s", firstName, lastName, currentEmail, currentPassword,type) == 5) {
        if (strcmp(currentEmail, email) == 0) {
            emailFound = 1;
            fprintf(tempFile, "%s %s %s %s %s\n", firstName, lastName, currentEmail, newPassword,type);
        } else {
            fprintf(tempFile, "%s %s %s %s %s\n", firstName, lastName, currentEmail, currentPassword,type);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (emailFound) {
        // Replace the original file with the updated file
        if (remove("signup.txt") != 0 || rename(TEMP_FILE, "signup.txt") != 0) {
            perror("Error updating signup.txt");
        } else {
            printf("Password updated successfully.\n");
        }
    } else {
        printf("Email not found.\n");
        remove(TEMP_FILE); // Remove the temporary file if email not found
    }
}
