#include <gtk/gtk.h>


void on_buttonSaveAjI_clicked(GtkWidget *objet_graphique, gpointer user_data);

void
on_radiobuttonFemaleAjI_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonMaleAjI_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void on_buttonSignupI_clicked(GtkButton *objet_graphique, gpointer user_data);

void
on_buttonEditAjI_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonDeleteAjI_clicked             (GtkButton       *button,
                                        gpointer         user_data);

void
on_radiobuttonMaleUpI_toggled          (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_radiobuttonFemaleUpI_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonSaveUpI_clicked               (GtkButton *objet_graphique,
                                        gpointer         user_data);

void
on_buttonSearchFacI_clicked            (GtkButton       *objet,
                                        gpointer         user_data);

void
on_chekbuttonSendEmailSignUp_toggled   (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_buttonSigninI_clicked               (GtkWidget *objet_graphique,
                                        gpointer         user_data);

void
on_buttonDontI_clicked                 (GtkButton       *objet_graphique,
                                        gpointer         user_data);

void
on_AffichierTreeViewI_clicked          (GtkButton       *objet,
                                        gpointer         user_data);

void
on_buttonYesDeleteI_clicked            (GtkButton       *objet,
                                        gpointer         user_data);
void
on_buttonCancelDeleteI_clicked         (GtkButton       *button,
                                        gpointer         user_data);
void
on_buttonYesUpdateI_clicked            (GtkButton       *button,
                                        gpointer         user_data);
void
on_buttonCancelUpdateI_clicked         (GtkButton       *button,
                                        gpointer         user_data);
void
on_buttonAffichierFactureI_clicked     (GtkButton       *objet,
                                        gpointer         user_data);
void on_notebookProfileI_select_page(GtkNotebook *objet, GtkWidget *page, guint page_num, gpointer user_data);

void
on_notebookProfileI_switch_page        (GtkNotebook     *notebook,
                                        GtkNotebookPage *page,
                                        guint            page_num,
                                        gpointer         user_data);

void
on_buttonForgetPI_clicked              (GtkButton       *objet_graphique,
                                        gpointer         user_data);
void
on_treeviewAdmineI_row_activated       (GtkTreeView     *treeview,
                                        GtkTreePath     *path,
                                        GtkTreeViewColumn *column,
                                        gpointer         user_data);
void
on_buttonRefrechI_clicked              (GtkButton       *objet,
                                        gpointer         user_data);
void
on_buttonDeleteAdminI_clicked          (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonSendPI_clicked                (GtkButton       *objet,
                                        gpointer         user_data);

void
on_buttonCancelSendI_clicked           (GtkButton       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonGAI_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonGSI_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonBackADI_clicked               (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonLogoutADI_clicked             (GtkButton       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonGPI_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonGRI_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_buttonGCI_clicked                   (GtkButton       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonLogoutCDI_clicked             (GtkButton       *objet_graphique,
                                        gpointer         user_data);

void
on_buttonBackCDI_clicked               (GtkButton       *objet_graphique,
                                        gpointer         user_data);
