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
  GtkWidget *SignInI;
   GtkWidget *adminCitoyenAffichier;
 GtkWidget *citoyenDashboard;

#ifdef ENABLE_NLS
  bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
  bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
  textdomain (GETTEXT_PACKAGE);
#endif

  gtk_set_locale ();
  gtk_init (&argc, &argv);

  add_pixmap_directory ("/home/ilyess/Music/project2/pixmaps");

  /*
   * The following code was added by Glade to create one of each component
   * (except popup menus), just so that you see something after building
   * the project. Delete any components that you don't want shown initially.
   */
  UserProfileI = create_UserProfileI ();
  //gtk_widget_show (UserProfileI);
 
  adminCitoyenAffichier = create_adminCitoyen();
 // gtk_widget_show (adminCitoyenAffichier);

SignInI = create_signInI ();
  gtk_widget_show (SignInI);

 SignUpI = create_SignUpI();  
    //gtk_widget_show(SignUpI); 
  
citoyenDashboard = create_citoyenDashboardI();  
  // gtk_widget_show(citoyenDashboard); 
  

  gtk_main ();
  return 0;
}
