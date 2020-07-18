#include <gtk/gtk.h>

int modo = 0;
int main (int argc, char *argv[]);
void static menu();

static void setup(gpointer   data)
{
  menu();
}


static void modo_normal(gpointer   data)
{
  modo = 0;
  menu();
}

static void modo_tabata(gpointer   data)
{
  modo = 1;
  menu();
}

static void modos (gpointer   data)
{
  GtkBuilder *builder;
  GtkStyleContext *context;
  GObject *Label;
  GObject *window;
  GObject *button;
  GError *error = NULL;

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "builder2.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return;
  }

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  
  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(window));
  context = gtk_widget_get_style_context (GTK_WIDGET(window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  Label = gtk_builder_get_object (builder, "Label");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "button1");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (button, "clicked", G_CALLBACK (modo_normal), NULL);

  button = gtk_builder_get_object (builder, "button2");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (button, "clicked", G_CALLBACK (modo_tabata), NULL);

  button = gtk_builder_get_object (builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (button, "clicked", G_CALLBACK (menu), NULL);


}

void static menu()
{
  GtkBuilder *builder;
  GtkStyleContext *context;
  GObject *Label;
  GObject *window;
  GObject *button;
  GError *error = NULL;

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "builder.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return;
  }

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  GtkCssProvider *provider2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider2, "mystyle2.css", NULL);
  
  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(window));
  context = gtk_widget_get_style_context (GTK_WIDGET(window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  Label = gtk_builder_get_object (builder, "Label");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label = gtk_builder_get_object (builder, "Label2");
  if(modo == 0){
    gtk_label_set_text (GTK_LABEL(Label), "Modo: Normal");
  } else if (modo == 1){
    gtk_label_set_text (GTK_LABEL(Label), "Modo: Tabata");
  }
  context = gtk_widget_get_style_context (GTK_WIDGET(Label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "button1");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (button, "clicked", G_CALLBACK (setup), NULL);

  button = gtk_builder_get_object (builder, "button2");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (button, "clicked", G_CALLBACK (modos), NULL);

  button = gtk_builder_get_object (builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

}

int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  menu();
  gtk_main ();

  return 0;
}
