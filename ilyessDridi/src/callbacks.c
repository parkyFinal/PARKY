#include <gtk/gtk.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "citoyen.h"
#include <curl/curl.h>

int clientId ; 
int selected_agent_id;

void on_buttonSaveAjI_clicked(GtkWidget *objet_graphique, gpointer user_data) {
     char *citoyenFichier = "citoyen.txt";

    GtkWidget *entryNom = lookup_widget(objet_graphique, "entryNomAjI");
    GtkWidget *entryPrenom = lookup_widget(objet_graphique, "entryPrenomAjI");
    GtkWidget *entryCin = lookup_widget(objet_graphique, "entryCinAjI");
    GtkWidget *entryModele = lookup_widget(objet_graphique, "entryModeleAjI");
    GtkWidget *entryMatricule = lookup_widget(objet_graphique, "entryMatriculeAjI");
    GtkWidget *comboBoxVille = lookup_widget(objet_graphique, "comboboxentryVilleAjI");
    GtkWidget *spinButtonAge = lookup_widget(objet_graphique, "spinbuttonAgeAjI");
    GtkWidget *radioButtonMale = lookup_widget(objet_graphique, "radiobuttonMaleAjI");
    GtkWidget *radioButtonFemale = lookup_widget(objet_graphique, "radiobuttonFemaleAjI");
GtkWidget *labelError = lookup_widget(objet_graphique, "labelErrorAjI");
    
    citoyen c;
    char errorMessage[256];

    // Check if all entries are filled
    if (!entryNom || !gtk_entry_get_text(GTK_ENTRY(entryNom))[0] ||
        !entryPrenom || !gtk_entry_get_text(GTK_ENTRY(entryPrenom))[0] ||
        !entryCin || !gtk_entry_get_text(GTK_ENTRY(entryCin))[0] ||
        !entryModele || !gtk_entry_get_text(GTK_ENTRY(entryModele))[0] ||
        !entryMatricule || !gtk_entry_get_text(GTK_ENTRY(entryMatricule))[0] ||
        !comboBoxVille || !gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboBoxVille)) ||
        !spinButtonAge || gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinButtonAge)) == 0 ||
        (!radioButtonMale && !radioButtonFemale)) {
        snprintf(errorMessage, 256, "All fields must be filled.");
        gtk_label_set_text(GTK_LABEL(labelError), errorMessage);
        return;
    }


    if (entryNom) {
        strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(entryNom)));

    } else {
        strcpy(c.nom, "Unknown");
    }

    if (entryPrenom) {
        strcpy(c.prenom, gtk_entry_get_text(GTK_ENTRY(entryPrenom)));

    } else {
        strcpy(c.prenom, "Unknown");
    }

    if (entryCin) {
        c.cin = atoi(gtk_entry_get_text(GTK_ENTRY(entryCin)));

        clientId=atoi(gtk_entry_get_text(GTK_ENTRY(entryCin)));
    } else {
        c.cin = 0;
    }

    if (entryModele) {
        strcpy(c.modele, gtk_entry_get_text(GTK_ENTRY(entryModele)));

    } else {
        strcpy(c.modele, "Unknown");
    }

    if (entryMatricule) {
        strcpy(c.matricule, gtk_entry_get_text(GTK_ENTRY(entryMatricule)));

    } else {
        strcpy(c.matricule, "Unknown");
    }

    if (spinButtonAge) {
        c.age = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinButtonAge));

    } else {
        c.age = 0;
    }

    if (comboBoxVille) {
        const char *selectedVille = gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboBoxVille));
        if (selectedVille) {
            strcpy(c.ville, selectedVille);

        } else {
            strcpy(c.ville, "Unknown");
        }
    } else {
        strcpy(c.ville, "Unknown");
    }

    if (radioButtonMale && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioButtonMale))) {
        strcpy(c.sexe, "Male");

    } else if (radioButtonFemale && gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioButtonFemale))) {
        strcpy(c.sexe, "Female");

    } else {
        strcpy(c.sexe, "Unknown");
    }

   if (ajouter(citoyenFichier, c, errorMessage)) {
        gtk_label_set_text(GTK_LABEL(labelError), "Citoyen added successfully.");
    } else {
        gtk_label_set_text(GTK_LABEL(labelError), errorMessage);
    } 
}

void on_radiobuttonFemaleAjI_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    // Your code here
}

void on_radiobuttonMaleAjI_toggled(GtkToggleButton *togglebutton, gpointer user_data) {
    // Your code here
}


void on_buttonSignupI_clicked(GtkButton *objet_graphique, gpointer user_data) { 
    GtkWidget *citoyenDashboardI;
    GtkWidget *SignUpI;
    citoyenDashboardI = create_citoyenDashboardI ();
    //SignUpI = create_SignUpI();  
    
    // Retrieve widgets
    GtkWidget *entryNom = lookup_widget(GTK_WIDGET(objet_graphique), "entryNomSignupI");
    GtkWidget *entryPrenom = lookup_widget(GTK_WIDGET(objet_graphique), "entryPrenomSignupI");
    GtkWidget *entryEmail = lookup_widget(GTK_WIDGET(objet_graphique), "entryEmailSignupI");
    GtkWidget *entryPwd = lookup_widget(GTK_WIDGET(objet_graphique), "entryPwdSignupI");
    GtkWidget *entryVerifierPwd = lookup_widget(GTK_WIDGET(objet_graphique), "entryVerifierPwdSignupI");

    GtkWidget *labelFeedbackEmail = lookup_widget(GTK_WIDGET(objet_graphique), "labelFeedbackSignupEmailI");
    GtkWidget *labelFeedbackPwd = lookup_widget(GTK_WIDGET(objet_graphique), "labelFeedbackSignupPWDI");
    GtkWidget *labelFeedbackVerifier = lookup_widget(GTK_WIDGET(objet_graphique), "labelErrorVirifierI");
    GtkWidget *labelError = lookup_widget(GTK_WIDGET(objet_graphique), "labelErrorSingUpI");

    // Reset feedback labels
    gtk_label_set_text(GTK_LABEL(labelFeedbackEmail), "");
    gtk_label_set_text(GTK_LABEL(labelFeedbackPwd), "");
    gtk_label_set_text(GTK_LABEL(labelFeedbackVerifier), "");
    gtk_label_set_text(GTK_LABEL(labelError), "");

    // Retrieve input values
    const char *nom = gtk_entry_get_text(GTK_ENTRY(entryNom));
    const char *prenom = gtk_entry_get_text(GTK_ENTRY(entryPrenom));
    const char *email = gtk_entry_get_text(GTK_ENTRY(entryEmail));
    const char *password = gtk_entry_get_text(GTK_ENTRY(entryPwd));
    const char *verifierPassword = gtk_entry_get_text(GTK_ENTRY(entryVerifierPwd));

    char feedbackMessage[256];

    // Validate all fields
    if (!nom[0] || !prenom[0] || !email[0] || !password[0]) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "All fields must be filled.");
        gtk_label_set_text(GTK_LABEL(labelError), feedbackMessage);
        return;
    }

    // Validate email format
    if (!is_valid_email(email)) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Include a valid '@' symbol and domain.");
        gtk_label_set_text(GTK_LABEL(labelFeedbackEmail), feedbackMessage);
        return;
    }

    // Validate password strength
    int passwordStrength = password_strength(password);
    if (passwordStrength == 0) {
        snprintf(feedbackMessage, sizeof(feedbackMessage),
                 "Password must be at least 8 characters long ");
        gtk_label_set_text(GTK_LABEL(labelFeedbackPwd), feedbackMessage);
        return;
    } else if (passwordStrength == 1) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Weak password! It contains only lowercase letters.");
        gtk_label_set_text(GTK_LABEL(labelFeedbackPwd), feedbackMessage);
        return;
    } else if (passwordStrength == 2) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Normal password. Consider adding symbols for better security.");
        gtk_label_set_text(GTK_LABEL(labelFeedbackPwd), feedbackMessage);
    } else if (passwordStrength == 3) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Strong password! Well done.");
        gtk_label_set_text(GTK_LABEL(labelFeedbackPwd), feedbackMessage);
    }

    // Verify password confirmation
    if (strcmp(verifierPassword, password) != 0) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Passwords do not match!");
        gtk_label_set_text(GTK_LABEL(labelFeedbackVerifier), feedbackMessage);
        return;
    }

    // Perform signup
    int signupResult = signup(email, password, nom, prenom);
    if (signupResult == 0) {
        snprintf(feedbackMessage, sizeof(feedbackMessage),
                 "Signup failed. Ensure the email and password meet requirements.");
        gtk_label_set_text(GTK_LABEL(labelError), feedbackMessage);
    } else {
        SignUpI =lookup_widget(GTK_WIDGET(objet_graphique),"SignUpI");
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Signup successful!");
        gtk_label_set_text(GTK_LABEL(labelError), feedbackMessage);
        gtk_widget_show (citoyenDashboardI); 
        gtk_widget_destroy(SignUpI);
      
     
    }
}



void
on_buttonSigninI_clicked               (GtkWidget *objet_graphique,
                                        gpointer         user_data)
{  

  GtkWidget *entryEmail = lookup_widget(GTK_WIDGET(objet_graphique), "entryEmailSigninI");
GtkWidget *entryPwd = lookup_widget(GTK_WIDGET(objet_graphique), "entryPwdSigninI");
GtkWidget *labelError = lookup_widget(GTK_WIDGET(objet_graphique), "labelErrorSigninI"); 
GtkWidget *labelFeedbackEmail = lookup_widget(GTK_WIDGET(objet_graphique), "labelErrorEmailSignInI"); 
 
     GtkWidget *CitoyenDashboardI;
     GtkWidget *AdminDashboardI;
    GtkWidget *SignInI;
    CitoyenDashboardI = create_citoyenDashboardI ();
    AdminDashboardI = create_adminDashboardI ();
    // Reset feedback labels
    gtk_label_set_text(GTK_LABEL(labelFeedbackEmail), "");
    gtk_label_set_text(GTK_LABEL(labelError), "");

 const char *email = gtk_entry_get_text(GTK_ENTRY(entryEmail));
 const char *password = gtk_entry_get_text(GTK_ENTRY(entryPwd));
    char feedbackMessage[256];
    char userType[256];


  // Validate all fields
    if (!email[0] || !password[0]) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), "All fields must be filled.");
        gtk_label_set_text(GTK_LABEL(labelError), feedbackMessage);
        return;
    }  
    // Validate email format 
    if (!is_valid_email(email)) {
        snprintf(feedbackMessage, sizeof(feedbackMessage), " include '@'and domain.");
        gtk_label_set_text(GTK_LABEL(labelFeedbackEmail), feedbackMessage);
        return;
    } 
// Perform signin
    int signinResult = signin(email, password,userType);
    if (signinResult == 0) {
        snprintf(feedbackMessage, sizeof(feedbackMessage),
                 "Invalid Email or Password!!");
        gtk_label_set_text(GTK_LABEL(labelError), feedbackMessage); 
         } else { 
        if(strcmp(userType,"citoyen")==0){
	SignInI =lookup_widget(GTK_WIDGET(objet_graphique),"signInI");
        snprintf(feedbackMessage, sizeof(feedbackMessage), "Signin successful!");
        gtk_label_set_text(GTK_LABEL(labelError), feedbackMessage);
	 gtk_widget_show (CitoyenDashboardI); 
        gtk_widget_destroy(SignInI); 
    } 
   else {   
     gtk_widget_show (AdminDashboardI); 
        gtk_widget_destroy(SignInI);
}

    }

}
void
on_buttonEditAjI_clicked               (GtkButton       *objet,
                                        gpointer         user_data)
{
// Step 1: Retrieve the parent notebook widget
    GtkWidget *notebook = lookup_widget(GTK_WIDGET(objet), "notebookProfileI");
    
    if (notebook == NULL) {
        g_print("Error: Notebook widget 'notebookProfileI' not found.\n");
        return;
    }

    // Step 2: Set the current page of the notebook
    int pageIndex = 1; // The second page (index 1)
    gtk_notebook_set_current_page(GTK_NOTEBOOK(notebook), 2);

    g_print("Switched to page %d in the notebook.\n",2);
}


void
on_buttonDeleteAjI_clicked             (GtkButton       *button,
                                        gpointer         user_data)
{

    GtkWidget *DeleteAlert;
    DeleteAlert = create_deleteAlert ();
	 gtk_widget_show (DeleteAlert); 
       
}


void
on_radiobuttonMaleUpI_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void
on_radiobuttonFemaleUpI_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}


void on_buttonSaveUpI_clicked(GtkButton *objet_graphique, gpointer user_data) {
    char *citoyenFichier = "citoyen.txt";

    GtkWidget *entryNom = lookup_widget(objet_graphique, "entryNomUpI");
    GtkWidget *entryPrenom = lookup_widget(objet_graphique, "entryPrenomUpI");
    //GtkWidget *entryCin = lookup_widget(objet_graphique, "entryCinUpI");
    GtkWidget *entryModele = lookup_widget(objet_graphique, "entryModeleUpI");
    GtkWidget *entryMatricule = lookup_widget(objet_graphique, "entryMatriculeUpI");
    GtkWidget *comboBoxVille = lookup_widget(objet_graphique, "comboboxentryVilleUpI");
    GtkWidget *spinButtonAge = lookup_widget(objet_graphique, "spinbuttonAgeUpI");
    GtkWidget *radioButtonMale = lookup_widget(objet_graphique, "radiobuttonMaleUpI");
    GtkWidget *radioButtonFemale = lookup_widget(objet_graphique, "radiobuttonFemaleUpI");
    GtkWidget *labelError = lookup_widget(objet_graphique, "labelErrorUpI");
    
    citoyen c;
    //const char *CIN = gtk_entry_get_text(GTK_ENTRY(entryCin));
    if (!entryNom || !gtk_entry_get_text(GTK_ENTRY(entryNom))[0] ||
    !entryPrenom || !gtk_entry_get_text(GTK_ENTRY(entryPrenom))[0] ||
   // !entryCin || !gtk_entry_get_text(GTK_ENTRY(entryCin))[0] ||
    !entryModele || !gtk_entry_get_text(GTK_ENTRY(entryModele))[0] ||
    !entryMatricule || !gtk_entry_get_text(GTK_ENTRY(entryMatricule))[0] ||
    !comboBoxVille || !gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboBoxVille)) ||
    !spinButtonAge || gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinButtonAge)) == 0 ||
    (!radioButtonMale && !radioButtonFemale)) {
    gtk_label_set_text(GTK_LABEL(labelError), "Error: All fields must be filled.");
    return;
}

    // Validate CIN
 /*   if (strlen(CIN) != 8 || atoi(CIN) == 0) {
        gtk_label_set_text(GTK_LABEL(labelError), "Error: CIN must be exactly 8 digits.");
        return;
    }*/
    //int cin = atoi(CIN);
    char errorMessage[250];
    // Input validation for empty fields
    if (!gtk_entry_get_text(GTK_ENTRY(entryNom))[0] || 
    !gtk_entry_get_text(GTK_ENTRY(entryPrenom))[0] ||
    !gtk_entry_get_text(GTK_ENTRY(entryModele))[0] || 
    !gtk_entry_get_text(GTK_ENTRY(entryMatricule))[0]) {
    gtk_label_set_text(GTK_LABEL(labelError), "Error: All fields must be filled.");
    return;
}


    // Populate citizen structure
    strcpy(c.nom, gtk_entry_get_text(GTK_ENTRY(entryNom)));
    strcpy(c.prenom, gtk_entry_get_text(GTK_ENTRY(entryPrenom)));
    c.cin = clientId;
    strcpy(c.modele, gtk_entry_get_text(GTK_ENTRY(entryModele)));
    strcpy(c.matricule, gtk_entry_get_text(GTK_ENTRY(entryMatricule)));
    c.age = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spinButtonAge));
    strcpy(c.ville, gtk_combo_box_get_active_text(GTK_COMBO_BOX(comboBoxVille)));

    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radioButtonMale)))
        strcpy(c.sexe, "Male");
    else
        strcpy(c.sexe, "Female");

    if (modifier(citoyenFichier, clientId, c,errorMessage)) {
        gtk_label_set_text(GTK_LABEL(labelError), "Citoyen updated successfully.");
        GtkWidget *UpdateAlertI = create_updateAlertI();
        gtk_widget_show(UpdateAlertI);
    } else {
        gtk_label_set_text(GTK_LABEL(labelError), errorMessage);
    
    }
}


void
on_buttonSearchFacI_clicked            (GtkButton       *objet,
                                        gpointer         user_data)
{ 
 char totaleMessage[250];
 GtkWidget *labelTotale = lookup_widget(objet, "label5TotaleI");
 GtkWidget *window =lookup_widget(objet, "UserProfileI");
GtkWidget *notebook = GTK_WIDGET(lookup_widget(window, "notebookProfileI"));
GtkWidget *treeview1 = GTK_WIDGET(lookup_widget(window, "treeviewFactureI"));
GtkWidget *spin = lookup_widget(objet, "spinbuttonMoisFacI");
int mois = gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(spin));
    if (notebook == NULL) {
        g_print("Error: Notebook widget not found.\n");
        return;
    }
    if (treeview1 == NULL) {
        g_print("Error: TreeView widget not found.\n");
        return;
    } 
  
  
    searchByMonth("facture.txt",mois,totaleMessage);
    gtk_label_set_text(GTK_LABEL(labelTotale), totaleMessage);
    // Populate the TreeView with data from the file
    show_search(treeview1);  // Replace with your actual file name
}


void
on_chekbuttonSendEmailSignUp_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{

}





void
on_buttonDontI_clicked                 (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *SignUpI;
    GtkWidget *SignInI;
    SignUpI = create_SignUpI ();
    SignInI =lookup_widget(GTK_WIDGET(objet_graphique),"signInI");
	 gtk_widget_show (SignUpI); 
        gtk_widget_destroy(SignInI);
}


void
on_buttonYesDeleteI_clicked            (GtkButton       *objet,
                                        gpointer         user_data)
{ 
   char feedbackMessage[250];
// GtkWidget *labelTotale = lookup_widget(objet, "label5TotaleI");
   supprimer("citoyen.txt",clientId ); 
  GtkWidget *deleteAlert;
    deleteAlert =lookup_widget(GTK_WIDGET(objet),"deleteAlert");
    gtk_widget_destroy(deleteAlert); 

 


}


void
on_buttonCancelDeleteI_clicked         (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
 GtkWidget *deleteAlert;
    deleteAlert =lookup_widget(GTK_WIDGET(objet_graphique),"deleteAlert");
    gtk_widget_destroy(deleteAlert);
}


void
on_buttonYesUpdateI_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonCancelUpdateI_clicked         (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_notebookProfileI_switch_page        (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        guint            page_num,
                                        gpointer         user_data)
{
     char totaleMessage[250];
   GtkWidget *labelTotale = lookup_widget(notebook, "label5TotaleI");
   if (page_num == 1) {
        // Ensure parent widget is properly passed or accessible
        GtkWidget *window = lookup_widget(GTK_WIDGET(notebook), "UserProfileI");
        if (window == NULL) {
            g_print("Error: Parent window 'UserProfileI' not found.\n");
            return;
        }

        GtkWidget *notebookWidget = GTK_WIDGET(lookup_widget(window, "notebookProfileI"));
        if (notebookWidget == NULL) {
            g_print("Error: Notebook widget 'notebookProfileI' not found.\n");
            return;
        }

        GtkWidget *treeviewAI = GTK_WIDGET(lookup_widget(window, "treeviewAI"));
        if (treeviewAI == NULL) {
            g_print("Error: TreeView widget 'treeview1' not found.\n");
            return;
        }

        
        populate_treeview(treeviewAI, "citoyen.txt", clientId);
        g_print("TreeView populated with data for CIN %d.\n", clientId);
    }else if(page_num == 3){
      GtkWidget *window =lookup_widget(notebook, "UserProfileI");
GtkWidget *notebook = GTK_WIDGET(lookup_widget(window, "notebookProfileI"));
GtkWidget *treeview1 = GTK_WIDGET(lookup_widget(window, "treeviewFactureI"));

    if (notebook == NULL) {
        g_print("Error: Notebook widget not found.\n");
        return;
    }
    if (treeview1 == NULL) {
        g_print("Error: TreeView widget not found.\n");
        return;
    }
 
     generateFacture("reservation.txt", "services.txt","parking.txt","facture.txt",15915999,totaleMessage); 
    gtk_label_set_text(GTK_LABEL(labelTotale), totaleMessage);
    // Populate the TreeView with data from the file
    show_facture(treeview1);  // Replace with your actual file name
}
}


void
on_buttonRefrechI_clicked              (GtkButton       *objet,
                                        gpointer         user_data)
{ 
GtkWidget *window =lookup_widget(objet, "adminCitoyen");
//GtkWidget *notebook = GTK_WIDGET(lookup_widget(window, "notebookProfileI"));
GtkWidget *treeview3 = GTK_WIDGET(lookup_widget(window, "treeviewAdmineI"));
 populate_treeview_with_citoyens(treeview3,"citoyen.txt");
}
void
on_treeviewAdmineI_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data)
{
 GtkTreeModel *model;
    GtkTreeIter iter;
    int value; // To store the value from the first column

    // Get the model from the tree view
    model = gtk_tree_view_get_model(treeview);

    // Get the iter for the activated row
    if (gtk_tree_model_get_iter(model, &iter, path)) {
        // Get the value from the first column (column 0)
        gtk_tree_model_get(model, &iter,2, &value, -1);

        // Print the value (or process it)
        g_print("Activated row value: %d\n", value);
        selected_agent_id=value;

}
}

void
on_buttonDeleteAdminI_clicked          (GtkButton       *button,
                                        gpointer         user_data)
{ 

supprimer("citoyen.txt",selected_agent_id);
}




void
on_buttonForgetPI_clicked              (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{ 
GtkWidget *source_entry = lookup_widget(objet_graphique, "entryEmailSigninI"); 
/*GtkWidget *second_window= lookup_widget(GTK_WIDGET(objet_graphique), "sendEmail"); 
  //GtkWindow *second_window= lookup_widget(GTK_WIDGET(objet_graphique), "sendEmail");
   //GtkWidget *destination_entry = lookup_widget(second_window, "entryGmailSendI"); 
const char *text = gtk_entry_get_text(GTK_ENTRY(source_entry));
    //gtk_entry_set_text(GTK_ENTRY(destination_entry), text);*/ 

//g_print("%s",text);

GtkWidget *SignInI;
    GtkWidget *send;
    send = create_sendEmail ();
    SignInI =lookup_widget(GTK_WIDGET(objet_graphique),"signInI");
	 gtk_widget_show (send); 
        gtk_widget_destroy(SignInI); 
   
}


void
on_buttonSendPI_clicked                (GtkButton       *objet,
                                        gpointer         user_data)
{
char email[100];
char errorMessage[250];
GtkWidget *labelErrorSend = lookup_widget(objet, "labelErrorSendI");
GtkWidget *Email = lookup_widget(objet, "entryGmailSendI");
strcpy(email, gtk_entry_get_text(GTK_ENTRY(Email))); 
  if (!is_valid_email(email)) {
        snprintf(errorMessage, sizeof(errorMessage), "Include a valid '@' symbol and domain.");
        gtk_label_set_text(GTK_LABEL(labelErrorSend), errorMessage);
        return;
    } 
 if (!Email || !gtk_entry_get_text(GTK_ENTRY(Email))[0]){
        snprintf(errorMessage, 256, "All fields must be filled.");
        gtk_label_set_text(GTK_LABEL(labelErrorSend), errorMessage);
        return;
} 
if(emailExist(email,errorMessage)==1) { 
//gtk_label_set_text(GTK_LABEL(labelErrorSend),errorMessage);
const char *recipient = email;
    const char *subject = "New Password";
    const char *body = "Your new password is: Az88r50@80";  // Or generate this programmatically

    send_email(recipient, subject, body); 
    //snprintf(errorMessage, 256, "Email send successfully!");
changePassword(email,"Az88r50@80");
}else{gtk_label_set_text(GTK_LABEL(labelErrorSend),errorMessage);
}}

void
on_buttonCancelSendI_clicked           (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *SignInI;
    GtkWidget *send;
    SignInI = create_signInI();
    send =lookup_widget(GTK_WIDGET(objet_graphique),"sendEmail");
	 gtk_widget_show (SignInI); 
        gtk_widget_destroy(send);
}


void
on_buttonGAI_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonGSI_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonBackADI_clicked               (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonLogoutADI_clicked             (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *adminDashboardI;
    GtkWidget *SignInI;
    SignInI = create_signInI ();
    adminDashboardI =lookup_widget(GTK_WIDGET(objet_graphique),"adminDashboardI");
	 gtk_widget_show (SignInI); 
        gtk_widget_destroy(adminDashboardI);
}


void
on_buttonGPI_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonGRI_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{

}


void
on_buttonGCI_clicked                   (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *citoyenDashboardI;
    GtkWidget *UserProfileI;
    UserProfileI = create_UserProfileI ();
    citoyenDashboardI =lookup_widget(GTK_WIDGET(objet_graphique),"citoyenDashboardI");
	 gtk_widget_show (UserProfileI); 
        gtk_widget_destroy(citoyenDashboardI);
}


void
on_buttonLogoutCDI_clicked             (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
 GtkWidget *citoyenDashboardI;
    GtkWidget *SignInI;
    SignInI = create_signInI ();
    citoyenDashboardI =lookup_widget(GTK_WIDGET(objet_graphique),"citoyenDashboardI");
	 gtk_widget_show (SignInI); 
        gtk_widget_destroy(citoyenDashboardI);
}


void
on_buttonBackCDI_clicked               (GtkButton       *objet_graphique,
                                        gpointer         user_data)
{
 GtkWidget *citoyenDashboardI;
    GtkWidget *SignInI;
    SignInI = create_signInI ();
    citoyenDashboardI =lookup_widget(GTK_WIDGET(objet_graphique),"citoyenDashboardI");
	 gtk_widget_show (SignInI); 
        gtk_widget_destroy(citoyenDashboardI);
}

