#include <stdio.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>

gboolean modo = FALSE;

typedef struct _structBuilder
{
  GObject *label;
  GObject *label_rest;
  gulong id;
  GObject *window;
  GtkBuilder* builder;
  
  short int segU;
  short int segD;
  short int minU;
  short int minD;

  short int segU_rest;
  short int segD_rest;
  short int minU_rest;
  short int minD_rest;
   
  short int aux_segU;
  short int aux_segD;
  short int aux_minU;
  short int aux_minD;

  short int aux_segU_rest;
  short int aux_segD_rest;
  short int aux_minU_rest;
  short int aux_minD_rest;

  short int nRondas;
  short int nRondas_reset;
  short int countdown;

  gboolean work;
  gboolean _01;


}structBuilder;

static void iniciacao_timer(structBuilder* st);
static void timer(structBuilder* st);
static void timer_tabata(structBuilder* st);
static void setup(structBuilder* st);
gboolean update_label_time_rest (gpointer data);
int main (int argc, char *argv[]);
void static menu(structBuilder* st);

// static void apagarFinal(gpointer builder)
// {
//   GObject* label;
//   GObject* button;

//   label = gtk_builder_get_object (builder, "Acabou");
//   g_object_unref (G_OBJECT(label));
//   label = gtk_builder_get_object (builder, "Tempo_final");
//   g_object_unref (G_OBJECT(label));
//   button = gtk_builder_get_object (builder, "quit_final");
//   g_object_unref (G_OBJECT(button));
// }

// static void apagarRelogio(gpointer builder)
// {
//   GObject* label;
//   GObject* button;

//   label = gtk_builder_get_object (builder, "Tempo_relogio");
//   g_object_unref (G_OBJECT(label));
//   button = gtk_builder_get_object (builder, "quitRelogio");
//   g_object_unref (G_OBJECT(button));
// }

// static void apagarTimer(gpointer builder)
// {
//   GObject* label;

//   label = gtk_builder_get_object (builder, "Tempo_timer");
//   g_object_unref (G_OBJECT(label));
//   label = gtk_builder_get_object (builder, "Tempo_timer_rest");
//   g_object_unref (G_OBJECT(label));
// }

// static void apagarCountdown(gpointer builder)
// {
//   GObject* label;

//   label = gtk_builder_get_object (builder, "countdown");
//   g_object_unref (G_OBJECT(label));
// }

// static void apagarRondas(gpointer builder)
// {
//   GObject* label;
//   GObject* button;

//   label = gtk_builder_get_object (builder, "LabelRondas");
//   g_object_unref (G_OBJECT(label));
//   label = gtk_builder_get_object (builder, "Rondas");
//   g_object_unref (G_OBJECT(label));
//   button = gtk_builder_get_object (builder, "buttonRondasPlus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonRondasMinus");
//   g_object_unref (G_OBJECT(button));

//   button = gtk_builder_get_object (builder, "InicioRondas");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "quitSetupRondas");
//   g_object_unref (G_OBJECT(button));
// }

// static void apagarSetup(gpointer builder)
// {
//   GObject* label;
//   GObject* button;

//   label = gtk_builder_get_object (builder, "Tempo");
//   g_object_unref (G_OBJECT(label));
//   button = gtk_builder_get_object (builder, "buttonDmimPlus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonDmimMinus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonUmimPlus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonUmimMinus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonDsegPlus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonDsegMinus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonUsegPlus");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "buttonUsegMinus");
//   g_object_unref (G_OBJECT(button));

//   button = gtk_builder_get_object (builder, "Inicio");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "setup_descanso");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "nRondas");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "quitSetup");
//   g_object_unref (G_OBJECT(button));
// }

// static void apagarModos(gpointer builder)
// {
//   GObject* label;
//   GObject* button;

//   label = gtk_builder_get_object (builder, "Modos");
//   g_object_unref (G_OBJECT(label));
//   button = gtk_builder_get_object (builder, "Normal");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "Tabata");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "Sair");
//   g_object_unref (G_OBJECT(button));
// }

// static void apagarMenu(gpointer builder)
// {
//   GObject* label;
//   GObject* button;

//   label = gtk_builder_get_object (builder, "Label");
//   g_object_unref (G_OBJECT(label));
//   label = gtk_builder_get_object (builder, "LabelModo");
//   g_object_unref (G_OBJECT(label));
//   button = gtk_builder_get_object (builder, "inicio_setup");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "modos_setup");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "Relogio");
//   g_object_unref (G_OBJECT(button));
//   button = gtk_builder_get_object (builder, "quit");
//   g_object_unref (G_OBJECT(button));
// }

// static void apagar_programa(structBuilder* st){
//   apagarMenu(st->builder);
//   apagarModos(st->builder);
//   apagarRelogio(st->builder);
//   apagarSetup(st->builder);
//   apagarTimer(st->builder);
//   apagarRondas(st->builder);
//   apagarCountdown(st->builder);
//   apagarFinal(st->builder);
//   g_object_unref(st->window);
//   free(st);
//   gtk_main_quit();
// }

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

static void esconderRelogio(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Tempo_relogio");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "quitRelogio");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderTimer(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Tempo_timer");
  gtk_widget_hide(GTK_WIDGET(label));
  label = gtk_builder_get_object (builder, "Tempo_timer_rest");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "resetTimer");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quitTimer");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderCountdown(gpointer builder)
{
  GObject* label;

  label = gtk_builder_get_object (builder, "countdown");
  gtk_widget_hide(GTK_WIDGET(label));
}

static void esconderRondas(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "LabelRondas");
  gtk_widget_hide(GTK_WIDGET(label));
  label = gtk_builder_get_object (builder, "Rondas");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "buttonRondasPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonRondasMinus");
  gtk_widget_hide(GTK_WIDGET(button));

  button = gtk_builder_get_object (builder, "InicioRondas");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quitSetupRondas");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderSetup(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Tempo");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "buttonDmimPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonDmimMinus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonUmimPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonUmimMinus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonDsegPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonDsegMinus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonUsegPlus");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "buttonUsegMinus");
  gtk_widget_hide(GTK_WIDGET(button));

  button = gtk_builder_get_object (builder, "Inicio");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "setup_descanso");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "nRondas");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quitSetup");
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

  if(modo == FALSE){
    label = gtk_builder_get_object (builder, "Timer");
  } else if(modo == TRUE) {
    label = gtk_builder_get_object (builder, "Timer_Tabata");
  }
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "inicio_setup");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "modos_setup");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "Relogio");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quit");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void update_label (structBuilder* st) 
{
  char digito[11];
  sprintf(digito, "%d%d%c%d%d", st->minD_rest, st->minU_rest, ':', st->segD_rest, st->segU_rest);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
}

static void update_label_rondas (structBuilder* st) 
{
  char digito[11];
  sprintf(digito, "%d", st->nRondas);
  st->nRondas_reset = st->nRondas;
  gtk_label_set_text(GTK_LABEL(st->label), digito);
}

static void subtrairRondas (structBuilder* st)
{
  st->nRondas--;

  if(st->nRondas == 0){
    st->nRondas = 1;
    return;
  }

  update_label_rondas(st);
}

static void somarRondas(structBuilder* st)
{
  st->nRondas++;

  update_label_rondas(st);
}

static void subtrair_minD(structBuilder* st)
{
  st->minD_rest--;

  if(st->minD_rest == -1){
    st->minD_rest = 0;
    return;
  }

  update_label(st);
}

static void subtrair_minU(structBuilder* st)
{
  st->minU_rest--;

  if(st->minU_rest == -1){
    st->minU_rest = 0;
    return;
  }

  update_label(st);
}

static void subtrair_segD(structBuilder* st)
{
  st->segD_rest--;

  if(st->segD_rest == -1){
    st->segD_rest = 0;
    return;
  }

  update_label(st);
}

static void subtrair_segU(structBuilder* st)
{
  st->segU_rest--;

  if(st->segU_rest == -1){
    st->segU_rest = 0;
    return;
  }

  update_label(st);
}

static void somarDmin(structBuilder* st)
{
  st->minD_rest++;

  if(st->minD_rest == 6){
    st->minD_rest = 5;
    return;
  }

  update_label(st);
}

static void somarUmin(structBuilder* st)
{
  st->minU_rest++;

  if(st->minU_rest == 10 && st->minD_rest == 5){
    st->minU_rest = 9;
    return;
  } else if(st->minU_rest == 10){
    somarDmin(st);
    st->minU_rest = 0;
  }

  update_label(st);
}

static void somarDseg(structBuilder* st)
{
  st->segD_rest++;

  if(st->minU_rest == 9 && st->minD_rest == 5 && st->segD_rest == 6){
    st->segD_rest = 5;
    return;
  } else if(st->segD_rest == 6){
    st->segD_rest = 0;
    somarUmin(st);
  }

  update_label(st);
}

static void somarUseg(structBuilder* st)
{
  st->segU_rest++;
    
  if(st->minU_rest == 9 && st->minD_rest == 5 && st->segU_rest == 10 && st->segD_rest == 5){
    st->segU_rest = 9;
    return;
  }else if(st->segU_rest == 10 && st->segD_rest == 5){
    somarUmin(st);
    st->segU_rest = 0;
    st->segD_rest = 0;
  } else if(st->segU_rest == 10){
    somarDseg(st);
    st->segU_rest = 0;
  }

  update_label(st);
}

void static final_timer(structBuilder* st)
{
  GtkStyleContext *context;
  GObject *label;
  GObject *button;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);  

  label= gtk_builder_get_object (st->builder, "Acabou");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  label = gtk_builder_get_object (st->builder, "Tempo_final");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  button = gtk_builder_get_object (st->builder, "quit_final");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), st);
  gtk_widget_show (GTK_WIDGET(button));

  st->id = -1;
  st->nRondas_reset = 1;

  esconderTimer(st->builder);
}

gboolean contador(structBuilder* st)
{
  if(st->minD == 0 && st->minU == 0 && st->segD == 0 && st->segU == 1 && modo == TRUE){
    return G_SOURCE_REMOVE;
  }

  if(st->segU == 0){
    if(st->segD > 0){
      st->segD--;
      st->segU = 9;
    } else if(st->minU > 0){
      st->minU--;
      st->segU = 9;
      st->segD = 5;
    } else if(st->minD > 0){
      st->minD--;
      st->segU = 9;
      st->segD = 5;
      st->minU = 9;
    } else {
      return G_SOURCE_REMOVE;
    }
  } else{
    st->segU--;
  }

  return G_SOURCE_CONTINUE;
}

gboolean contador_rest(structBuilder* st)
{
  if(st->minD_rest == 0 && st->minU_rest == 0 && st->segD_rest == 0 && st->segU_rest == 1){
    return G_SOURCE_REMOVE;
  }

  if(st->segU_rest == 0){
    if(st->segD_rest > 0){
      st->segD_rest--;
      st->segU_rest = 9;
    } else if(st->minU_rest > 0){
      st->minU_rest--;
      st->segU_rest = 9;
      st->segD_rest = 5;
    } else if(st->minD_rest > 0){
      st->minD_rest--;
      st->segU_rest = 9;
      st->segD_rest = 5;
      st->minU_rest = 9;
    } else {
      return G_SOURCE_REMOVE;
    }
  } else{
    st->segU_rest--;
  }

  return G_SOURCE_CONTINUE;
}

gboolean update_label_time (gpointer data)
{
  structBuilder* st = data;
  static gboolean show = TRUE;
  char digito[11];

  if(modo == TRUE){
    sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
    gtk_label_set_text(GTK_LABEL(st->label), digito);
    
    if(show == FALSE){
      gtk_widget_hide(GTK_WIDGET(st->label_rest));
      gtk_widget_show(GTK_WIDGET(st->label));
      show = TRUE;
    }
  }

  if(contador(st) == G_SOURCE_REMOVE){
    if(modo == TRUE){
      show = FALSE;
      st->segU = st->aux_segU;
      st->segD = st->aux_segD;
      st->minU = st->aux_minU;
      st->minD = st->aux_minD;
      return G_SOURCE_REMOVE;
    }
    g_source_remove(st->id);
    final_timer(st);
  }

  if(modo == FALSE){
    sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
    gtk_label_set_text(GTK_LABEL(st->label), digito);
  }
  
  return G_SOURCE_CONTINUE;
}

gboolean update_label_time_rest (gpointer data)
{
  structBuilder* st = data;
  static gboolean show = FALSE;

  char digito[11];

  sprintf(digito, "%d%d%c%d%d", st->minD_rest, st->minU_rest, ':', st->segD_rest, st->segU_rest);
  gtk_label_set_text(GTK_LABEL(st->label_rest), digito);

  if(show == FALSE){
    gtk_widget_hide(GTK_WIDGET(st->label));
    gtk_widget_show(GTK_WIDGET(st->label_rest));
    show = TRUE;
  }

  if(contador_rest(st) == G_SOURCE_REMOVE){
    
    show = FALSE;
    st->segU_rest = st->aux_segU_rest;
    st->segD_rest = st->aux_segD_rest;
    st->minU_rest = st->aux_minU_rest;
    st->minD_rest = st->aux_minD_rest;
    return G_SOURCE_REMOVE;
  }

  return G_SOURCE_CONTINUE;
}

gboolean controlador_tabata (gpointer data)
{
  structBuilder* st = data;

  if(st->work == TRUE){
    if(update_label_time(st) == G_SOURCE_REMOVE){
      st->work = FALSE;
      st->nRondas--;
    }
  } else {
    if(update_label_time_rest(st) == G_SOURCE_REMOVE){
      st->work = TRUE;
    }
  }

  if(st->nRondas <= 0){
    g_source_remove(st->id);
    final_timer(st);
  }
  
  return G_SOURCE_CONTINUE;
}

gboolean Countdown(gpointer data)
{
  structBuilder* st = data;
  char digito[3];

  sprintf(digito, "%c%d", '0', st->countdown);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  
  if(st->countdown == 0){
    g_source_remove(st->id);
    if(modo == TRUE){
      timer_tabata(st);
    } else{
      timer(st);
    }
  } else{
    st->countdown--;
  }

  return G_SOURCE_CONTINUE;
}

static void apagar_relogio(structBuilder* st)
{
  g_source_remove(st->id);
  menu(st);
}

char* get_relogio_string(){
  time_t time_var = time(NULL);
  struct tm *info;
  char *time_string = calloc(100, sizeof(char));
  info = localtime( &time_var );
  strftime(time_string, 100, "%H:%M:%S", info);
  return time_string;
}

gboolean update_label_relogio (gpointer data) {
  structBuilder* st = data;
  gchar *t = get_relogio_string();
  gtk_label_set_text(GTK_LABEL(st->label), t);
  g_free (t);
  return G_SOURCE_CONTINUE;
}

static void relogio(structBuilder* st)
{
  GObject *button;
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);  

  static gboolean conections = FALSE;
  time_t time_var = time(NULL);
  struct tm *info;
  char *time_string = (char*) calloc(100, sizeof(char));
  
  st->label = gtk_builder_get_object (st->builder, "Tempo_relogio");
  info = localtime( &time_var );
  strftime(time_string, 100, "%H:%M:%S", info);
  gtk_label_set_label(GTK_LABEL(st->label), time_string);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));

  button = gtk_builder_get_object (st->builder, "quitRelogio");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(apagar_relogio), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  g_free (time_string);

  esconderMenu(st->builder);

  if(conections == FALSE){
    conections = TRUE;
  }

  st->id = g_timeout_add_seconds(0.5, update_label_relogio, st);
}

static void reset(structBuilder* st)
{
  g_source_remove(st->id);

  st->segU = st->aux_segU;
  st->segD = st->aux_segD;
  st->minU = st->aux_minU;
  st->minD = st->aux_minD;

  esconderTimer(st->builder);
  setup(st);
}

static void quit(structBuilder* st)
{
  g_source_remove(st->id);

  st->segU = 0;
  st->segD = 0;
  st->minU = 0;
  st->minD = 0;

  st->aux_segU_rest = 0;
  st->aux_segD_rest = 0;
  st->aux_minU_rest = 0;
  st->aux_minD_rest = 0;

  st->id = -1;
  st->nRondas_reset = 1;

  esconderTimer(st->builder);
  menu(st);
}

static void timer_tabata(structBuilder* st)
{
  GObject *button;
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);
  GtkCssProvider *provider2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider2, "timer-blue.css", NULL);    

  static gboolean conections = FALSE;

  st->label = gtk_builder_get_object (st->builder, "Tempo_timer");
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  st->label_rest = gtk_builder_get_object (st->builder, "Tempo_timer_rest");
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label_rest));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_hide(GTK_WIDGET(st->label_rest));

  button = gtk_builder_get_object (st->builder, "resetTimer");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (reset), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quitTimer");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (quit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  if(conections == FALSE){
    conections = TRUE;
  }

  esconderCountdown(st->builder);

  gtk_widget_show (GTK_WIDGET(st->label));

  st->aux_segU = st->segU;
  st->aux_segD = st->segD;
  st->aux_minU = st->minU;
  st->aux_minD = st->minD;

  st->aux_segU_rest = st->segU_rest;
  st->aux_segD_rest = st->segD_rest;
  st->aux_minU_rest = st->minU_rest;
  st->aux_minD_rest = st->minD_rest;
  
  st->id = g_timeout_add_seconds(1, controlador_tabata, st);
}

static void timer(structBuilder* st)
{
  GObject *button;
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  static gboolean conections = FALSE;
  char digito[11];
  
  st->aux_minD = st->minD = st->minD_rest;
  st->aux_minU = st->minU = st->minU_rest;
  st->aux_segD = st->segD = st->segD_rest;
  st->aux_segU = st->segU = st->segU_rest;

  st->label = gtk_builder_get_object (st->builder, "Tempo_timer");
  sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

  button = gtk_builder_get_object (st->builder, "resetTimer");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (reset), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quitTimer");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (quit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  if(conections == FALSE){
    conections = TRUE;
  }

  esconderCountdown(st->builder);

  st->id = g_timeout_add_seconds(1, update_label_time, st);
}

static void iniciacao_timer(structBuilder* st)
{
  GtkStyleContext *context;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  st->countdown = 9;
  
  st->label = gtk_builder_get_object (st->builder, "countdown");
  gtk_label_set_text(GTK_LABEL(st->label), "10");
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));

  esconderSetup(st->builder);
 
  if(modo == TRUE){
    esconderRondas(st->builder);
    st->work = TRUE;
  }

  st->id = g_timeout_add_seconds(1, Countdown, st);
}

static void nRondas(structBuilder* st)
{
  GtkStyleContext *context;
  GObject* label;
  GObject *button;

  char digito[3];
  static gboolean conections = FALSE;
  st->nRondas = st->nRondas_reset;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  label = gtk_builder_get_object (st->builder, "LabelRondas");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  st->label = gtk_builder_get_object (st->builder, "Rondas");
  sprintf(digito, "%d", st->nRondas);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  
  button = gtk_builder_get_object (st->builder, "buttonRondasPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarRondas), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonRondasMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrairRondas), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "InicioRondas");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (iniciacao_timer), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quitSetupRondas");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (menu), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  if(conections == FALSE){
    conections = TRUE;
  }

  esconderSetup(st->builder);
}

static void setup_descanso(structBuilder* st)
{
  GtkStyleContext *context;
  GObject *button;

  static gboolean conections = FALSE;

  st->minD = st->minD_rest;
  st->minU = st->minU_rest;
  st->segD = st->segD_rest;
  st->segU = st->segU_rest;

  st->minD_rest = st->aux_minD_rest;
  st->minU_rest = st->aux_minU_rest;
  st->segD_rest = st->aux_segD_rest;
  st->segU_rest = st->aux_segU_rest;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  GtkCssProvider *provider2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider2, "mystyle3.css", NULL);
  char digito[11];

  st->label = gtk_builder_get_object (st->builder, "Tempo");
  sprintf(digito, "%d%d%c%d%d", st->minD_rest, st->minU_rest, ':', st->segD_rest, st->segU_rest);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider2), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  
  button = gtk_builder_get_object (st->builder, "buttonDmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonDmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonDsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonDsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "setup_descanso");
  gtk_widget_hide(GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "nRondas");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (nRondas), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quitSetup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(button));
  
  if(conections == FALSE){
    conections = TRUE;
  }

}

static void setup(structBuilder* st)
{
  GtkStyleContext *context;
  GObject *button;

  static gboolean conections = FALSE;
  static gboolean conections_swicth1 = FALSE;
  static gboolean conections_swicth2 = FALSE;
  char digito[11];

  if(conections == FALSE){
    st->segU = 0;
    st->segD = 0;
    st->minU = 0;
    st->minD = 0;
  }

  st->segU_rest = st->segU;
  st->segD_rest = st->segD;
  st->minU_rest = st->minU;
  st->minD_rest = st->minD;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  st->label = gtk_builder_get_object (st->builder, "Tempo");
  sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  
  button = gtk_builder_get_object (st->builder, "buttonDmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarDmin), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonDmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_minD), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUmimPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarUmin), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUmimMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_minU), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonDsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarDseg), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonDsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_segD), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUsegPlus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (somarUseg), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "buttonUsegMinus");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){ 
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (subtrair_segU), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  if(modo == FALSE){
    button = gtk_builder_get_object (st->builder, "Inicio");
    context = gtk_widget_get_style_context (GTK_WIDGET(button));
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if(conections == FALSE){
      g_signal_connect_swapped(button, "clicked", G_CALLBACK (iniciacao_timer), st);
      conections_swicth2 = TRUE;
    } else if(conections_swicth1 == TRUE){
      g_signal_connect_swapped(button, "clicked", G_CALLBACK (iniciacao_timer), st);
      conections_swicth1 = FALSE;
    }
    gtk_widget_show (GTK_WIDGET(button));
  } else {
    button = gtk_builder_get_object (st->builder, "setup_descanso");
    context = gtk_widget_get_style_context (GTK_WIDGET(button));
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if(conections == FALSE){
      g_signal_connect_swapped(button, "clicked", G_CALLBACK (setup_descanso), st);
      conections_swicth1 = TRUE;
    } else if(conections_swicth2 == TRUE){
      g_signal_connect_swapped(button, "clicked", G_CALLBACK (setup_descanso), st);
      conections_swicth2 = FALSE;
    }
    gtk_widget_show (GTK_WIDGET(button));
  }


  button = gtk_builder_get_object (st->builder, "quitSetup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (menu), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  if(conections == FALSE){
    conections = TRUE;
  }

  esconderMenu(st->builder);
}

static void modo_normal(structBuilder* st)
{
  modo = FALSE;
  menu(st);
}

static void modo_tabata(structBuilder* st)
{
  modo = TRUE;
  menu(st);
}

static void modos (structBuilder* st)
{
  GtkStyleContext *context; 
  GObject *label;
  GObject *button;

  static gboolean conections = FALSE;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);

  label = gtk_builder_get_object (st->builder, "Modos");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));

  button = gtk_builder_get_object (st->builder, "Normal");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_normal), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "Tabata");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_tabata), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  button = gtk_builder_get_object (st->builder, "Sair");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (menu), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  esconderMenu(st->builder);

}

static void menu(structBuilder* st)
{
  GtkStyleContext *context;
  GObject *button;
  GObject* label;
  static gboolean conections = FALSE;
  
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  GtkCssProvider *provider2 = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider2, "mystyle2.css", NULL);

  if(modo == FALSE){
    label = gtk_builder_get_object (st->builder, "Timer");
  } else{
    label = gtk_builder_get_object (st->builder, "Timer_Tabata");
  }
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  
  button = gtk_builder_get_object (st->builder, "inicio_setup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (setup), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "modos_setup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (modos), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "Relogio");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (relogio), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quit");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_main_quit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  if(conections == FALSE){
    conections = TRUE;
  }

  esconderModos(st->builder);
  
  esconderSetup(st->builder);

  esconderRondas(st->builder);

  esconderRelogio(st->builder);

  esconderCountdown(st->builder);

  esconderTimer(st->builder);

  esconderFinal(st->builder);
}

int main (int argc, char *argv[])
{
  gtk_init (&argc, &argv);

  structBuilder* st = (structBuilder*) malloc(sizeof(structBuilder));
  GError *error = NULL;

  st->builder = gtk_builder_new ();
  if (gtk_builder_add_from_file (st->builder, "builder.ui", &error) == 0)
  {
    g_printerr ("Error loading file: %s\n", error->message);
    g_clear_error (&error);
    return -1;
  }

  st->aux_segU = 0;
  st->aux_segD = 0;
  st->aux_minU = 0;
  st->aux_minD = 0;
  st->nRondas_reset = 1;
  st->id = -1;

  GtkStyleContext *context;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "mystyle.css", NULL);
  
  st->window = gtk_builder_get_object (st->builder, "window");
  gtk_window_fullscreen (GTK_WINDOW(st->window));
  context = gtk_widget_get_style_context (GTK_WIDGET(st->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (st->window, "destroy", G_CALLBACK (gtk_main_quit), st);

  menu(st);
  gtk_main ();

  return 0;
}
