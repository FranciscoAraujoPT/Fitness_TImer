#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>

int modo = 0;
int aux_segU = 0;
int aux_segD = 0;
int aux_minU = 0;
int aux_minD = 0;
short int segU = 0;
short int segD = 0;
short int minU = 0;
short int minD = 0;
gboolean iniciacao = FALSE;
gboolean final = FALSE;

typedef struct _labelSetup
{
  GObject *label;
  gulong id;
  GObject *window;
  GtkBuilder* builder;

}labelSetup;

static void iniciacao_timer(labelSetup* Label);
static void timer(labelSetup* Label);
int main (int argc, char *argv[]);
void static menu(labelSetup* Label);

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

static void esconderFinal(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Acabou");
  gtk_widget_hide(GTK_WIDGET(label));
  label = gtk_builder_get_object (builder, "Tempo_final");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "quit_final");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderTimer(gpointer builder)
{
  GObject* label;

  label = gtk_builder_get_object (builder, "Tempo_timer");
  gtk_widget_hide(GTK_WIDGET(label));
}

static void esconderCountdown(gpointer builder)
{
  GObject* label;

  label = gtk_builder_get_object (builder, "countdown");
  gtk_widget_hide(GTK_WIDGET(label));
}

static void esconderSetup(labelSetup* Label)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (Label->builder, "Tempo");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (Label->builder, "buttonDmimPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonDmimMinus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonUmimPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonUmimMinus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonDsegPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonDsegMinus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonUsegPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "buttonUsegMinus");
  gtk_widget_hide(GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "Inicio");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (Label->builder, "quitSetup");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderModos(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Modos");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "Normal");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "Tabata");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "Sair");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderMenu(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Label");
  gtk_widget_hide(GTK_WIDGET(label));
  label = gtk_builder_get_object (builder, "LabelModo");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "button1");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "button2");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quit");
  gtk_widget_hide(GTK_WIDGET(button));
}


static void subtrair_minD(gpointer label)
{
  minD--;

  if(minD == -1){
    minD = 0;
    return;
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);
}

static void subtrair_minU(gpointer label)
{
  minU--;

  if(minU == -1){
    minU = 0;
    return;
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);
}

static void subtrair_segD(gpointer label)
{
  segD--;

  if(segD == -1){
    segD = 0;
    return;
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);
}

static void subtrair_segU(gpointer label)
{
  segU--;

  if(segU == -1){
    segU = 0;
    return;
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);
}

static void somarDmin(gpointer label)
{
  minD++;

  if(minD == 6){
    minD = 5;
    return;
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);

}

static void somarUmin(gpointer label)
{
  minU++;

  if(minU == 10 && minD == 5){
    minU = 9;
    return;
  } else if(minU == 10){
    somarDmin(label);
    minU = 0;
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);

}

static void somarDseg(gpointer label)
{
  segD++;

  if(minU == 9 && minD == 5 && segD == 6){
    segD = 5;
    return;
  } else if(segD == 6){
    segD = 0;
    somarUmin(label);
  }

  char digito[11];
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);

}

static void somarUseg(gpointer label)
{

  segU++;
    
  char digito[11];

  if(minU == 9 && minD == 5 && segU == 10 && segD == 5){
    segU = 9;
    return;
  }else if(segU == 10 && segD == 5){
    somarUmin(label);
    segU = 0;
    segD = 0;
    sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
    gtk_label_set_text(GTK_LABEL(label), digito);

  } else if(segU == 10){
    somarDseg(label);
    segU = 0;
  }

  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(label), digito);

}

void static final_timer(gpointer data)
{
  labelSetup* Label = data;
  GtkStyleContext *context;
  GObject *label;
  GObject *button;
  GError *error = NULL;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);  

  label= gtk_builder_get_object (Label->builder, "Acabou");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  Label->label = gtk_builder_get_object (Label->builder, "Tempo_final");
  gtk_label_set_text(GTK_LABEL(Label->label), "00:00");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(Label->label));

  button = gtk_builder_get_object (Label->builder, "quit_final");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), Label);
  gtk_widget_show (GTK_WIDGET(button));

  esconderTimer(Label->builder);
}

gboolean contador()
{
  if(segU == 0){
    if(segD > 0){
      segD--;
      segU = 9;
    } else if(minU > 0){
      minU--;
      segU = 9;
      segD = 5;
    } else if(minD > 0){
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
  GObject* label;
  GtkStyleContext *context;

  char digito[11];

  if(contador() == G_SOURCE_REMOVE){
    g_source_remove(Label->id);
    final_timer(Label);
  }
  
  if(minD == -1 && minU == -1){
    sprintf(digito, "%d%d", segD, segU);
    gtk_label_set_text(GTK_LABEL(Label->label), digito);
  } else {
    sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
    gtk_label_set_text(GTK_LABEL(Label->label), digito);
  }

  if(iniciacao == TRUE && segD == 0 && segU == 0){
    g_source_remove(Label->id);
    timer(Label);
  }

  return G_SOURCE_CONTINUE;
}

static void timer(labelSetup *Label)
{
  GtkStyleContext *context;
  GObject *label;
  GError *error = NULL;

  iniciacao = FALSE;
  segU = aux_segU;
  segD = aux_segD;
  minU = aux_minU;
  minD = aux_minD;
  

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  char digito[11];
  
  Label->label = gtk_builder_get_object (Label->builder, "Tempo_timer");
  sprintf(digito, "%d%d%s%d%d", minD, minU, ":", segD, segU);
  gtk_label_set_text(GTK_LABEL(Label->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(Label->label));

  esconderCountdown(Label->builder);

  Label->id = g_timeout_add_seconds(1, update_label_time, Label);
}


static void iniciacao_timer(labelSetup* Label)
{
  GtkStyleContext *context;
  GObject *label;
  GObject *button;
  GError *error = NULL;

  aux_segU = segU;
  aux_segD = segD;
  aux_minU = minU;
  aux_minD = minD;

  segU = 0;
  segD = 1; //countdown de 10s
  minU = -1;
  minD = -1;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  char digito[3];
  
  Label->label = gtk_builder_get_object (Label->builder, "countdown");
  sprintf(digito, "%d%d", segD, segU);
  gtk_label_set_text(GTK_LABEL(Label->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  esconderSetup(Label);

  iniciacao = TRUE;
  Label->id = g_timeout_add_seconds(1, update_label_time, Label);
}

static void setup_descanso(labelSetup *Label)
{
  GtkStyleContext *context;
  labelSetup* descanso = (labelSetup*) calloc(1, sizeof(labelSetup));
  GObject* label;
  GObject *button;
  GError *error = NULL;

  descanso->builder = Label->builder;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  descanso->label = gtk_builder_get_object (descanso->builder, "Tempo");
  context = gtk_widget_get_style_context (GTK_WIDGET(descanso->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(descanso->label));

  button = gtk_builder_get_object (descanso->builder, "buttonDmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarDmin), descanso);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "buttonDmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair_minD), descanso->label);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "buttonUmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarUmin), descanso);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "buttonUmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair_minU),descanso->label);
  gtk_widget_show (GTK_WIDGET(button));

  descanso->label = gtk_builder_get_object (descanso->builder, "dezenas_seg");
  context = gtk_widget_get_style_context (GTK_WIDGET(descanso->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(descanso->label));
  
  button = gtk_builder_get_object (descanso->builder, "buttonDsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarDseg), descanso);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "buttonDsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair_segD), descanso->label);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "buttonUsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (somarUseg), descanso);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "buttonUsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (subtrair_segU), descanso->label);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "Inicio");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), descanso->builder);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (descanso->builder, "quitSetup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), descanso->builder);
  gtk_widget_show (GTK_WIDGET(button));
}

static void setup(labelSetup* Label)
{
  GtkStyleContext *context;
  GObject *button;
  GError *error = NULL;

  static gboolean conections = FALSE;

  segU = 0;
  segD = 0;
  minU = 0;
  minD = 0;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  Label->label = gtk_builder_get_object (Label->builder, "Tempo");
  gtk_label_set_text(GTK_LABEL(Label->label),"00:00");
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->label));
  if(conections == FALSE){ 
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  }
  gtk_widget_show (GTK_WIDGET(Label->label));
  
  button = gtk_builder_get_object (Label->builder, "buttonDmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarDmin), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonDmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_minD), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonUmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarUmin), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonUmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_minU), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonDsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarDseg), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonDsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_segD), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonUsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarUseg), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "buttonUsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_segU), Label->label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "Inicio");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(modo == 1 && conections == FALSE){
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (setup_descanso), Label);
  } else if(conections == FALSE){
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (iniciacao_timer), Label);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "quitSetup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (menu), Label);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  if(conections == FALSE){
    conections = TRUE;
  }

  esconderMenu(Label->builder);
}


static void modo_normal(gpointer builder)
{
  modo = 0;
  menu(builder);
}

static void modo_tabata(gpointer builder)
{
  modo = 1;
  menu(builder);
}

static void modos (labelSetup* Label)
{
  GtkStyleContext *context; 
  GObject *label;
  GObject *button;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  label = gtk_builder_get_object (Label->builder, "Modos");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  button = gtk_builder_get_object (Label->builder, "Normal");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_normal), Label);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "Tabata");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_tabata), Label);
  gtk_widget_show (GTK_WIDGET(button));
  
  button = gtk_builder_get_object (Label->builder, "Sair");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), Label);
  gtk_widget_show (GTK_WIDGET(button));
  
  esconderMenu(Label->builder);

}

static void menu(labelSetup* Label)
{
  GtkStyleContext *context;
  GObject *button;
  GObject* label;
  
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  GtkCssProvider *provider2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider2, "mystyle2.css", NULL);

  label = gtk_builder_get_object (Label->builder, "Label");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  label = gtk_builder_get_object (Label->builder, "LabelModo");
  if(modo == 0){
    gtk_label_set_text (GTK_LABEL(label), "Modo: Normal");
  } else if (modo == 1){
    gtk_label_set_text (GTK_LABEL(label), "Modo: Tabata");
  }
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  
  button = gtk_builder_get_object (Label->builder, "button1");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (setup), Label);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "button2");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (modos), Label);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (Label->builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), NULL);
  gtk_widget_show (GTK_WIDGET(button));

  esconderModos(Label->builder);
  
  esconderSetup(Label);

  esconderTimer(Label->builder);

  esconderFinal(Label->builder);
}

int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);

  labelSetup* Label = (labelSetup*) malloc(sizeof(labelSetup));
  GError *error = NULL;

  Label->builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (Label->builder, "builder.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return -1;
  }
  
  GtkStyleContext *context;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  
  Label->window = gtk_builder_get_object (Label->builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(Label->window));
  context = gtk_widget_get_style_context (GTK_WIDGET(Label->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (Label->window, "destroy", G_CALLBACK (apagar_janela), Label->window);

  menu(Label);
  gtk_main ();

  free(Label);
  return 0;
}
