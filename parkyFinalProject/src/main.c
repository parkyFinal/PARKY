/*
 * Initial main.c file generated by Glade. Edit as required.
 * Glade will not overwrite this file.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
  GtkWidget *UserProfileI;
  GtkWidget *SignUpI;
  GtkWidget *signInI;
  GtkWidget *deleteAlert;
  GtkWidget *updateAlertI;
  GtkWidget *adminCitoyen;
  GtkWidget *sendEmail;
  GtkWidget *adminDashboardI;
  GtkWidget *citoyenDashboardI;
  GtkWidget *Layout;
  GtkWidget *Supp;
  GtkWidget *ADD_MOD;
  GtkWidget *Affich;
  GtkWidget *Affec_agent;
  GtkWidget *CONFIR_supp;
  GtkWidget *itafwinaffichage;
  GtkWidget *itafwinajouter;
  GtkWidget *itafwinmodifier;
  GtkWidget *itafwinsupprimer;
  GtkWidget *itafwinrechercherparplace;
  GtkWidget *itafwineffichagetouteslesreser;
  GtkWidget *itafwinremerciment;
  GtkWidget *main_window_ww;
  GtkWidget *window_ajouter_ww;
  GtkWidget *window_modifier_ww;
  GtkWidget *window_supprimer_ww;
  GtkWidget *window_afficher_ww;
  GtkWidget *window_affecter_ww;
  GtkWidget *Ajouter_un_agent;
  GtkWidget *connexion_admin;
  GtkWidget *Erreur_de_connexion_admin;
  GtkWidget *Supprimer_un_agent;
  GtkWidget *agent_introuvable;
  GtkWidget *mis____jour_compte_agent;
  GtkWidget *labelprincipale;
  GtkWidget *__tes_vous_sur_de_vouloir__supprimer_l_agent_de_la_liste___;
  GtkWidget *mot_de_passe_incorrecte;
  GtkWidget *demande_mdp;
  GtkWidget *demande_modifier_cin_agent;
  GtkWidget *date_de_r__servation;
  GtkWidget *pas_de_r__servation;
  GtkWidget *liste_des_r__servations;
  GtkWidget *__tes_vous_sur_de_vouloir_modifier_les_information_de_l_agent;
  GtkWidget *Veuillez_remplir_tous_les_champs;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  UserProfileI = create_UserProfileI ();
  gtk_widget_show (UserProfileI);
  SignUpI = create_SignUpI ();
  gtk_widget_show (SignUpI);
  signInI = create_signInI ();
  gtk_widget_show (signInI);
  deleteAlert = create_deleteAlert ();
  gtk_widget_show (deleteAlert);
  updateAlertI = create_updateAlertI ();
  gtk_widget_show (updateAlertI);
  adminCitoyen = create_adminCitoyen ();
  gtk_widget_show (adminCitoyen);
  sendEmail = create_sendEmail ();
  gtk_widget_show (sendEmail);
  adminDashboardI = create_adminDashboardI ();
  gtk_widget_show (adminDashboardI);
  citoyenDashboardI = create_citoyenDashboardI ();
  gtk_widget_show (citoyenDashboardI);
  Layout = create_Layout ();
  gtk_widget_show (Layout);
  Supp = create_Supp ();
  gtk_widget_show (Supp);
  ADD_MOD = create_ADD_MOD ();
  gtk_widget_show (ADD_MOD);
  Affich = create_Affich ();
  gtk_widget_show (Affich);
  Affec_agent = create_Affec_agent ();
  gtk_widget_show (Affec_agent);
  CONFIR_supp = create_CONFIR_supp ();
  gtk_widget_show (CONFIR_supp);
  itafwinaffichage = create_itafwinaffichage ();
  gtk_widget_show (itafwinaffichage);
  itafwinajouter = create_itafwinajouter ();
  gtk_widget_show (itafwinajouter);
  itafwinmodifier = create_itafwinmodifier ();
  gtk_widget_show (itafwinmodifier);
  itafwinsupprimer = create_itafwinsupprimer ();
  gtk_widget_show (itafwinsupprimer);
  itafwinrechercherparplace = create_itafwinrechercherparplace ();
  gtk_widget_show (itafwinrechercherparplace);
  itafwineffichagetouteslesreser = create_itafwineffichagetouteslesreser ();
  gtk_widget_show (itafwineffichagetouteslesreser);
  itafwinremerciment = create_itafwinremerciment ();
  gtk_widget_show (itafwinremerciment);
  main_window_ww = create_main_window_ww ();
  gtk_widget_show (main_window_ww);
  window_ajouter_ww = create_window_ajouter_ww ();
  gtk_widget_show (window_ajouter_ww);
  window_modifier_ww = create_window_modifier_ww ();
  gtk_widget_show (window_modifier_ww);
  window_supprimer_ww = create_window_supprimer_ww ();
  gtk_widget_show (window_supprimer_ww);
  window_afficher_ww = create_window_afficher_ww ();
  gtk_widget_show (window_afficher_ww);
  window_affecter_ww = create_window_affecter_ww ();
  gtk_widget_show (window_affecter_ww);
  Ajouter_un_agent = create_Ajouter_un_agent ();
  gtk_widget_show (Ajouter_un_agent);
  connexion_admin = create_connexion_admin ();
  gtk_widget_show (connexion_admin);
  Erreur_de_connexion_admin = create_Erreur_de_connexion_admin ();
  gtk_widget_show (Erreur_de_connexion_admin);
  Supprimer_un_agent = create_Supprimer_un_agent ();
  gtk_widget_show (Supprimer_un_agent);
  agent_introuvable = create_agent_introuvable ();
  gtk_widget_show (agent_introuvable);
  mis____jour_compte_agent = create_mis____jour_compte_agent ();
  gtk_widget_show (mis____jour_compte_agent);
  labelprincipale = create_labelprincipale ();
  gtk_widget_show (labelprincipale);
  __tes_vous_sur_de_vouloir__supprimer_l_agent_de_la_liste___ = create___tes_vous_sur_de_vouloir__supprimer_l_agent_de_la_liste___ ();
  gtk_widget_show (__tes_vous_sur_de_vouloir__supprimer_l_agent_de_la_liste___);
  mot_de_passe_incorrecte = create_mot_de_passe_incorrecte ();
  gtk_widget_show (mot_de_passe_incorrecte);
  demande_mdp = create_demande_mdp ();
  gtk_widget_show (demande_mdp);
  demande_modifier_cin_agent = create_demande_modifier_cin_agent ();
  gtk_widget_show (demande_modifier_cin_agent);
  date_de_r__servation = create_date_de_r__servation ();
  gtk_widget_show (date_de_r__servation);
  pas_de_r__servation = create_pas_de_r__servation ();
  gtk_widget_show (pas_de_r__servation);
  liste_des_r__servations = create_liste_des_r__servations ();
  gtk_widget_show (liste_des_r__servations);
  __tes_vous_sur_de_vouloir_modifier_les_information_de_l_agent = create___tes_vous_sur_de_vouloir_modifier_les_information_de_l_agent ();
  gtk_widget_show (__tes_vous_sur_de_vouloir_modifier_les_information_de_l_agent);
  Veuillez_remplir_tous_les_champs = create_Veuillez_remplir_tous_les_champs ();
  gtk_widget_show (Veuillez_remplir_tous_les_champs);

  gtk_main ();
  return 0;
}

