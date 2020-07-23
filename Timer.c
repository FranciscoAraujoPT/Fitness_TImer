#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>

int modo = 0;
int aux_segU = 0;
int aux_segD = 0;
int aux_minU = 0;
int aux_minD = 0;
int segU = 0;
int segD = 0;
int minU = 0;
int minD = 0;
gboolean iniciacao = FALSE;
gboolean final = FALSE;

typedef struct _labelSetup
{
  GObject *segU;
  GObject *segD;
  GObject *mimU;
  GObject *mimD;
  guint id;
  GObject *window;

}labelSetup;

static void iniciacao_timer(gpointer   data);
static void timer(gpointer   data);
int main (int argc, char *argv[]);
void static menu(gpointer   data);

static void test(gpointer   data)
{
  g_print("hello\n");
}

static void apagar_janela(gpointer window){

  if(window == NULL){
    return;
  }
  
  gtk_window_close(GTK_WINDOW(window));
}

static void subtrair(GObject *Label, gpointer   data)
{
  int aux = atoi(gtk_label_get_text(GTK_LABEL(Label)));
  aux--;

  if(aux == -1){
    return;
  }

  char digito[2];
  sprintf(digito, "%d", aux);
  gtk_label_set_text(GTK_LABEL(Label), digito);
}

static void somarDmin(gpointer data)
{
  labelSetup *Label = data;

  int aux = atoi(gtk_label_get_text(GTK_LABEL(Label->mimD)));
  aux++;

  if(aux == 6){
    return;
  }

  char digito[2];
  sprintf(digito, "%d", aux);
  gtk_label_set_text(GTK_LABEL(Label->mimD), digito);

}

static void somarUmin(gpointer data)
{
  labelSetup *Label = data;

  int aux = atoi(gtk_label_get_text(GTK_LABEL(Label->mimU)));
  int aux2 = atoi(gtk_label_get_text(GTK_LABEL(Label->mimD)));
  aux++;


  if(aux == 10 && aux2 == 5){
    return;
  } else if(aux == 10){
    somarDmin(Label);
    aux = 0;
  }

  char digito[2];
  sprintf(digito, "%d", aux);
  gtk_label_set_text(GTK_LABEL(Label->mimU), digito);

}

static void somarDseg(gpointer data)
{
  labelSetup *Label = data;

  int aux = atoi(gtk_label_get_text(GTK_LABEL(Label->segD)));
  int aux2 = atoi(gtk_label_get_text(GTK_LABEL(Label->mimU)));
  int aux3 = atoi(gtk_label_get_text(GTK_LABEL(Label->mimD)));
  aux++;

  if(aux2 == 9 && aux3 == 5 && aux == 6){
    return;
  } else if(aux == 6){
    aux = 0;
    somarUmin(Label);
  }

  char digito[2];
  sprintf(digito, "%d", aux);
  gtk_label_set_text(GTK_LABEL(Label->segD), digito);

}

static void somarUseg(gpointer data)
{

  labelSetup *Label = data;

  int aux = atoi(gtk_label_get_text(GTK_LABEL(Label->segU)));
  int aux2 = atoi(gtk_label_get_text(GTK_LABEL(Label->segD)));
  int aux3 = atoi(gtk_label_get_text(GTK_LABEL(Label->mimU)));
  int aux4 = atoi(gtk_label_get_text(GTK_LABEL(Label->mimD)));
  aux++;
    
  char digito[2];

  if(aux3 == 9 && aux4 == 5 && aux == 10 && aux2 == 5){
    return;
  }else if(aux == 10 && aux2 == 5){
    somarUmin(Label);
    aux = 0;
    aux2 = 0;
    sprintf(digito, "%d", aux2);
    gtk_label_set_text(GTK_LABEL(Label->segD), digito);

  } else if(aux == 10){
    somarDseg(Label);
    aux = 0;
  }

  sprintf(digito, "%d", aux);
  gtk_label_set_text(GTK_LABEL(Label->segU), digito);

}

void static final_timer(gpointer data)
{
  labelSetup* Label = data;
  GtkBuilder *builder;
  GtkStyleContext *context;
  GObject *label;
  GObject *button;
  GError *error = NULL;

  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "final_timer.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return;
  }

  apagar_janela(Label->window);

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);  

  Label->window = gtk_builder_get_object(builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(Label->window));
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (Label->window, "destroy", G_CALLBACK (apagar_janela), Label->window);

  label= gtk_builder_get_object (builder, "Acabou");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->mimD = gtk_builder_get_object (builder, "dezenas_min");
  gtk_label_set_text(GTK_LABEL(Label->mimD), "0");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->mimD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->mimU = gtk_builder_get_object (builder, "unidades_min");
  gtk_label_set_text(GTK_LABEL(Label->mimU), "0");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->mimU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  label= gtk_builder_get_object (builder, "divisao");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->segD = gtk_builder_get_object (builder, "dezenas_seg");
  gtk_label_set_text(GTK_LABEL(Label->segD), "1");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->segU = gtk_builder_get_object (builder, "unidades_seg");
  gtk_label_set_text(GTK_LABEL(Label->segU), "0");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  
  button = gtk_builder_get_object (builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), Label->window);

}

gboolean contador()
{
  if(segU == 0){
    if(segD != 0){
      segD--;
      segU = 9;
    } else if(minU != 0){
      minU--;
      segU = 9;
      segD = 5;
    } else if(minD != 0){
      minD--;
      segU = 9;
      segD = 5;
      minU = 9;
    } else {
      return G_SOURCE_REMOVE;
    }
  } else{
    segU--;
  }

  return G_SOURCE_CONTINUE;
}

gboolean update_label_time (gpointer data)
{
    
  labelSetup* Label = data;
  GtkBuilder *builder;
  GObject* label;
  GtkStyleContext *context;
  GError *error = NULL;

  char digito[2];

  if(contador() == G_SOURCE_REMOVE){
    g_source_remove(Label->id);
    final_timer(Label);
  }
  
  sprintf(digito, "%d", minD);
  gtk_label_set_text(GTK_LABEL(Label->mimD), digito);

  sprintf(digito, "%d", minU);
  gtk_label_set_text(GTK_LABEL(Label->mimU), digito);

  sprintf(digito, "%d", segD);
  gtk_label_set_text(GTK_LABEL(Label->segD), digito);

  sprintf(digito, "%d", segU);
  gtk_label_set_text(GTK_LABEL(Label->segU), digito);

  if(iniciacao == TRUE && segD == 0 && segU == 0){
    g_source_remove(Label->id);
    timer(Label);
  }

  return G_SOURCE_CONTINUE;
}

static void timer(gpointer data)
{
  labelSetup *Label = data; 
  GtkBuilder *builder;
  GtkStyleContext *context;
  GObject *label;
  GError *error = NULL;

  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "timer.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return;
  }

  iniciacao = FALSE;
  segU = aux_segU;
  segD = aux_segD;
  minU = aux_minU;
  minD = aux_minD;
  
  apagar_janela(Label->window);

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  char digito[2];
  
  Label->window = gtk_builder_get_object(builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(Label->window));
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (Label->window, "destroy", G_CALLBACK (apagar_janela), Label->window);

  Label->mimD = gtk_builder_get_object (builder, "dezenas_min");
  sprintf(digito, "%d", minD);
  gtk_label_set_text(GTK_LABEL(Label->mimD), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->mimD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->mimU = gtk_builder_get_object (builder, "unidades_min");
  sprintf(digito, "%d", minU);
  gtk_label_set_text(GTK_LABEL(Label->mimU), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->mimU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  label= gtk_builder_get_object (builder, "divisao");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->segD = gtk_builder_get_object (builder, "dezenas_seg");
  sprintf(digito, "%d", segD);
  gtk_label_set_text(GTK_LABEL(Label->segD), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->segU = gtk_builder_get_object (builder, "unidades_seg");
  sprintf(digito, "%d", segU);
  gtk_label_set_text(GTK_LABEL(Label->segU), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->id = g_timeout_add_seconds(1, update_label_time, Label);
  
}


static void iniciacao_timer(gpointer   data)
{
  labelSetup* Label = data;
  GtkBuilder *builder;
  GtkStyleContext *context;
  GObject *label;
  GError *error = NULL;

  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "iniciacao_timer.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return;
  }

  aux_segU = atoi(gtk_label_get_text(GTK_LABEL(Label->segU)));
  aux_segD = atoi(gtk_label_get_text(GTK_LABEL(Label->segD)));
  aux_minU = atoi(gtk_label_get_text(GTK_LABEL(Label->mimU)));
  aux_minD = atoi(gtk_label_get_text(GTK_LABEL(Label->mimD))); 

  segD = 1; //countdown de 10s

  apagar_janela(Label->window);

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  char digito[2];
  
  Label->window = gtk_builder_get_object(builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(Label->window));
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (Label->window, "destroy", G_CALLBACK (apagar_janela), Label->window);

  Label->segD = gtk_builder_get_object (builder, "dezenas_seg");
  sprintf(digito, "%d", segD);
  gtk_label_set_text(GTK_LABEL(Label->segD), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->segU = gtk_builder_get_object (builder, "unidades_seg");
  sprintf(digito, "%d", segU);
  gtk_label_set_text(GTK_LABEL(Label->segU), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  iniciacao = TRUE;
  Label->id = g_timeout_add_seconds(1, update_label_time, Label);
}

static void setup(gpointer window)
{
  GtkBuilder *builder;
  GtkStyleContext *context;
  labelSetup* Label = (labelSetup*) malloc(sizeof(labelSetup));
  GObject *button;
  GError *error = NULL;

  /* Construct a GtkBuilder instance and load our UI description */
  builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (builder, "setup.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return;
  }

  apagar_janela(window);

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  Label->window = gtk_builder_get_object (builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(Label->window));
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (Label->window, "destroy", G_CALLBACK (apagar_janela), Label->window);

  Label->mimD = gtk_builder_get_object (builder, "dezenas_min");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->mimD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "buttonDmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarDmin), Label);

  button = gtk_builder_get_object (builder, "buttonDmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair), Label->mimD);

  Label->mimU = gtk_builder_get_object (builder, "unidades_min");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->mimU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "buttonUmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarUmin), Label);

  button = gtk_builder_get_object (builder, "buttonUmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair),Label->mimU);

  Label->segU= gtk_builder_get_object (builder, "divisao");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  Label->segD = gtk_builder_get_object (builder, "dezenas_seg");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segD));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "buttonDsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarDseg), Label);

  button = gtk_builder_get_object (builder, "buttonDsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair), Label->segD);

  Label->segU = gtk_builder_get_object (builder, "unidades_seg");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->segU));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "buttonUsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarUseg), Label);

  button = gtk_builder_get_object (builder, "buttonUsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair), Label->segU);



  button = gtk_builder_get_object (builder, "Inicio");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (iniciacao_timer), Label);

  button = gtk_builder_get_object (builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), window);
}


static void modo_normal(gpointer window)
{
  modo = 0;
  menu(window);
}

static void modo_tabata(gpointer window)
{
  modo = 1;
  menu(window);
}

static void modos (gpointer window)
{
  GtkBuilder *builder;
  GtkStyleContext *context; 
  GObject *Label;
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

  apagar_janela(window);

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  window = gtk_builder_get_object (builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(window));
  context = gtk_widget_get_style_context (GTK_WIDGET(window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (window, "destroy", G_CALLBACK (apagar_janela), window);

  Label = gtk_builder_get_object (builder, "Label");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (builder, "button1");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_normal), window);

  button = gtk_builder_get_object (builder, "button2");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_tabata), window);

  button = gtk_builder_get_object (builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), window);


}

void static menu(gpointer window)
{
  GtkBuilder *builder;
  GtkStyleContext *context;
  GObject *Label;
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

  apagar_janela(window);

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  GtkCssProvider *provider2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider2, "mystyle2.css", NULL);
  
  /* Connect signal handlers to the constructed widgets. */
  window = gtk_builder_get_object (builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(window));
  context = gtk_widget_get_style_context (GTK_WIDGET(window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (window, "destroy", G_CALLBACK (apagar_janela), window);

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
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (setup), window);

  button = gtk_builder_get_object (builder, "button2");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (modos), window);

  button = gtk_builder_get_object (builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);

}

int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);
  menu(NULL);
  gtk_main ();

  return 0;
}
