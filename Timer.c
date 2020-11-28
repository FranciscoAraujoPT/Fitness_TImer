#include <stdio.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <stdlib.h>
#include <vlc/vlc.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>

short int modo = 0;
pthread_mutex_t mutex;
pthread_cond_t cv_buzz, cv_final, cv_rondas, cv_final_buzz;

typedef struct _structBuilder
{
  GObject *label;
  GObject *label_rest;
  gulong id;
  gulong relogioOut;
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
  short int counter;

  gboolean work;
  gboolean state;

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

  label = gtk_builder_get_object (builder, "Acabou");
  gtk_widget_hide(GTK_WIDGET(label));
  label = gtk_builder_get_object (builder, "Tempo_final");
  gtk_widget_hide(GTK_WIDGET(label));
}

static void esconderRelogio(gpointer builder)
{
  GObject* label;

  label = gtk_builder_get_object (builder, "Tempo_relogio");
  gtk_widget_hide(GTK_WIDGET(label));
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
  button = gtk_builder_get_object (builder, "resetTimerTabata");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quitTimerTabata");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderStopWatch(gpointer builder)
{
  GObject* label;
  GObject* button;

  label = gtk_builder_get_object (builder, "Tempo_timer");
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "Stop");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quitStopwatch");
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
  button = gtk_builder_get_object (builder, "Normal_Timer");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "Tabata");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "StopWatch");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "Sair");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void esconderMenu(gpointer builder)
{
  GObject* label;
  GObject* button;

  if(modo == 0){
    label = gtk_builder_get_object (builder, "Timer");
  } else if(modo == 1) {
    label = gtk_builder_get_object (builder, "Timer_Tabata");
  } else {
    label = gtk_builder_get_object (builder, "Modo_StopWatch");
  }
  gtk_widget_hide(GTK_WIDGET(label));
  button = gtk_builder_get_object (builder, "inicio_setup");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "inicio_stopwatch");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "modos_setup");
  gtk_widget_hide(GTK_WIDGET(button));
  button = gtk_builder_get_object (builder, "quit");
  gtk_widget_hide(GTK_WIDGET(button));
}

static void stop (structBuilder* st)
{
  GObject *button;
  
  button = gtk_builder_get_object (st->builder, "Stop");
  
  if(st->state == TRUE){
    st->state = FALSE;
    gtk_button_set_label(GTK_BUTTON(button),"Resume");
  } else {
    st->state = TRUE;
    gtk_button_set_label(GTK_BUTTON(button),"Stop");
  }
}

static void reset(structBuilder* st)
{
  st->segU = st->aux_segU;
  st->segD = st->aux_segD;
  st->minU = st->aux_minU;
  st->minD = st->aux_minD;

  esconderTimer(st->builder);
  setup(st);
}

static void quit(structBuilder* st)
{
  
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

  menu(st);
}

static void preQuit(structBuilder* st)
{
  g_source_remove(st->id);
  quit(st);
}

gboolean restart(gpointer data)
{
  structBuilder* st = data;

  sleep(2);
  
  preQuit(st);

  return G_SOURCE_REMOVE;
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

void *final_buzz()
{
  libvlc_instance_t * inst;
  libvlc_media_player_t *mp;
  libvlc_media_t *m;
  
  pthread_mutex_lock(&mutex);
  
  pthread_cond_wait(&cv_final_buzz, &mutex);

  /* Load the VLC engine */
  inst = libvlc_new (0, NULL);

  /* Create a new item */
  m = libvlc_media_new_path (inst, "countdownFinal.mp3");
    
  /* Create a media player playing environement */
  mp = libvlc_media_player_new_from_media (m);
  
  /* No need to keep the media now */
  libvlc_media_release (m);

  /* play the media_player */
  libvlc_media_player_play (mp);

  sleep (2); /* Let it play a bit */

  /* Stop playing */
  libvlc_media_player_stop (mp);

  /* Free the media_player */
  libvlc_media_player_release (mp);

  libvlc_release (inst);
 
  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

void static final_timer(structBuilder* st)
{
  GtkStyleContext *context;
  GObject *label;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  label= gtk_builder_get_object (st->builder, "Acabou");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  gtk_widget_set_name (GTK_WIDGET(label),"Acabou");

  label = gtk_builder_get_object (st->builder, "Tempo_final");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  gtk_widget_set_name (GTK_WIDGET(label),"Tempo_final");

  st->id = -1;
  st->nRondas_reset = 1;

  esconderTimer(st->builder);

  pthread_cond_signal(&cv_final_buzz);

  st->id = g_timeout_add(2, restart, st);
}

gboolean contador_stopwatch(structBuilder* st)
{
  if(st->segU != 9){
    st->segU++;
  }else if(st->segD != 5){
    st->segD++;
    st->segU=0;
  } else if(st->minU != 9){
    st->minU++;
    st->segU = 0;
    st->segD = 0;
  } else if(st->minD != 5){
    st->minD++;
    st->segU = 0;
    st->segD = 0;
    st->minU = 0;
  } else {
    return G_SOURCE_REMOVE;
  }

  return G_SOURCE_CONTINUE;
}

gboolean contador(structBuilder* st)
{
  if(st->minD == 0 && st->minU == 0 && st->segD == 0 && st->segU == 1 && modo == 1 && st->nRondas != 1){
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

gboolean update_label_time_stopwatch (gpointer data)
{
  structBuilder* st = data;
  
  if(st->state == TRUE){
    char digito[11];
    
    sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
    gtk_label_set_text(GTK_LABEL(st->label), digito);
      
    if(contador_stopwatch(st) == G_SOURCE_REMOVE){
      g_source_remove(st->id);
      quit(st);
    }
  }
  
  return G_SOURCE_CONTINUE;
}

gboolean update_label_time (gpointer data)
{
  structBuilder* st = data;
  char digito[11];

  if(modo == 1){
    sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
    gtk_label_set_text(GTK_LABEL(st->label), digito);
    gtk_widget_hide(GTK_WIDGET(st->label_rest));
    gtk_widget_show(GTK_WIDGET(st->label));
  }

  if(contador(st) == G_SOURCE_REMOVE){
    if(modo == 1){
      st->segU = st->aux_segU;
      st->segD = st->aux_segD;
      st->minU = st->aux_minU;
      st->minD = st->aux_minD;
  
      return G_SOURCE_REMOVE;
    }
    g_source_remove(st->id);
    final_timer(st);
  }

  if(modo == 0){
    sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
    gtk_label_set_text(GTK_LABEL(st->label), digito);
  } 

  return G_SOURCE_CONTINUE;
}

gboolean update_label_time_rest (gpointer data)
{
  structBuilder* st = data;
  
  char digito[11];
  sprintf(digito, "%d%d%c%d%d", st->minD_rest, st->minU_rest, ':', st->segD_rest, st->segU_rest);
  gtk_label_set_text(GTK_LABEL(st->label_rest), digito);

  gtk_widget_hide(GTK_WIDGET(st->label));
  gtk_widget_show(GTK_WIDGET(st->label_rest));

  if(contador_rest(st) == G_SOURCE_REMOVE){
    st->segU_rest = st->aux_segU_rest;
    st->segD_rest = st->aux_segD_rest;
    st->minU_rest = st->aux_minU_rest;
    st->minD_rest = st->aux_minD_rest;
    return G_SOURCE_REMOVE;
  }

  return G_SOURCE_CONTINUE;
}

void *step_buzz_rondas()
{
  libvlc_instance_t * inst;
  libvlc_media_player_t *mp;
  libvlc_media_t *m;
  
  pthread_mutex_lock(&mutex);

  pthread_cond_wait(&cv_rondas, &mutex);

  /* Load the VLC engine */
  inst = libvlc_new (0, NULL);

  /* Create a new item */
  m = libvlc_media_new_path (inst, "countdown321.mp3");
  
  /* Create a media player playing environement */
  mp = libvlc_media_player_new_from_media (m);
  
  /* No need to keep the media now */
  libvlc_media_release (m);

  /* play the media_player */
  libvlc_media_player_play (mp);

  sleep (1); /* Let it play a bit */

  /* Stop playing */
  libvlc_media_player_stop (mp);

  /* Free the media_player */
  libvlc_media_player_release (mp);

  libvlc_release (inst);

  pthread_mutex_unlock(&mutex);

  pthread_exit(NULL);
}

void *step_buzz(void* data)
{
  structBuilder* st = data;
  libvlc_instance_t * inst;
  libvlc_media_player_t *mp;
  libvlc_media_t *m;
  
  pthread_mutex_lock(&mutex);

  if (st->countdown > 3 || st->countdown <= 0) {
    pthread_cond_wait(&cv_buzz, &mutex);
  }

  /* Load the VLC engine */
  inst = libvlc_new (0, NULL);

  /* Create a new item */
  m = libvlc_media_new_path (inst, "countdown321.mp3");
  
  /* Create a media player playing environement */
  mp = libvlc_media_player_new_from_media (m);
  
  /* No need to keep the media now */
  libvlc_media_release (m);

  /* play the media_player */
  libvlc_media_player_play (mp);

  sleep (1); /* Let it play a bit */

  /* Stop playing */
  libvlc_media_player_stop (mp);

  /* Free the media_player */
  libvlc_media_player_release (mp);

  libvlc_release (inst);

  pthread_mutex_unlock(&mutex);
  
  pthread_exit(NULL);
}

void *stepFinal_buzz(void* data)
{
  structBuilder* st = data;
  libvlc_instance_t * inst;
  libvlc_media_player_t *mp;
  libvlc_media_t *m;
  
  pthread_mutex_lock(&mutex);
  
  if (st->countdown != 0) {
    pthread_cond_wait(&cv_final, &mutex);
  }

  /* Load the VLC engine */
  inst = libvlc_new (0, NULL);

  /* Create a new item */
  m = libvlc_media_new_path (inst, "countdown.mp3");
  
  /* Create a media player playing environement */
  mp = libvlc_media_player_new_from_media (m);
  
  /* No need to keep the media now */
  libvlc_media_release (m);

  /* play the media_player */
  libvlc_media_player_play (mp);

  sleep (1); /* Let it play a bit */

  /* Stop playing */
  libvlc_media_player_stop (mp);

  /* Free the media_player */
  libvlc_media_player_release (mp);

  libvlc_release (inst);

  pthread_mutex_unlock(&mutex); 
 
  pthread_exit(NULL);
}

gboolean controlador_tabata (gpointer data)
{
  structBuilder* st = data;

  if(st->work == TRUE){
    if(update_label_time(st) == G_SOURCE_REMOVE){
      st->work = FALSE;
      st->nRondas--;
      if(st->nRondas != 0){
        pthread_cond_signal(&cv_rondas);
      }
    }
  } else {
    if(update_label_time_rest(st) == G_SOURCE_REMOVE){
      st->work = TRUE;
      pthread_cond_signal(&cv_rondas);
    }
  }

  if(st->nRondas == 0){
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
    pthread_cond_signal(&cv_final);
  } else if(st->countdown <= 3 && st->countdown > 0){
    pthread_cond_broadcast(&cv_buzz);
  }

  if(st->countdown == -1){
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
  g_signal_handler_disconnect (st->window, st->relogioOut);
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
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

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
  gtk_widget_set_name (GTK_WIDGET(st->label),"Tempo_relogio");

  st->relogioOut = g_signal_connect_swapped(st->window, "motion-notify-event",G_CALLBACK (apagar_relogio), st);

  g_free (time_string);

  esconderMenu(st->builder);

  st->id = g_timeout_add_seconds(0.5, update_label_relogio, st);
}

static void timer_tabata(structBuilder* st)
{
  GObject *button;
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);

  static gboolean conections = FALSE;
  char digito[11];

  st->label = gtk_builder_get_object (st->builder, "Tempo_timer");
  sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_set_name (GTK_WIDGET(st->label),"Tempo_timer");
  
  st->label_rest = gtk_builder_get_object (st->builder, "Tempo_timer_rest");
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label_rest));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_hide(GTK_WIDGET(st->label_rest));
  gtk_widget_set_name (GTK_WIDGET(st->label_rest),"Tempo_timer_rest");

  button = gtk_builder_get_object (st->builder, "resetTimerTabata");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (reset), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quitTimerTabata");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (preQuit), st);
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
  
  if(st->segU != 0){
    st->segU--;
  } else if(st->segD != 0){
    st->segD--;
    st->segU = 9;
  } else if(st->minU != 0){
    st->minU--;
    st->segD = 5;
    st->segU = 9;
  } else if(st->minD != 0){
    st->minD--;
    st->minU = 9;
    st->segD = 5;
    st->segU = 9;
  } else {
    final_timer(st);
  }
  
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
  st->state = TRUE;
  st->aux_minD = st->minD = st->minD_rest;
  st->aux_minU = st->minU = st->minU_rest;
  st->aux_segD = st->segD = st->segD_rest;
  st->aux_segU = st->segU = st->segU_rest;

  st->label = gtk_builder_get_object (st->builder, "Tempo_timer");
  sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  gtk_widget_set_name (GTK_WIDGET(st->label),"Tempo_timer");
  
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
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (preQuit), st);
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
  pthread_t thread[4], thread_final;
  int rc;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  

  st->countdown = 9;
  
  st->label = gtk_builder_get_object (st->builder, "countdown");
  gtk_label_set_text(GTK_LABEL(st->label), "10");
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  gtk_widget_set_name (GTK_WIDGET(st->label),"countdown");

  esconderSetup(st->builder);
 
  if(modo == TRUE){
    esconderRondas(st->builder);
    st->work = TRUE;
  }

  for(int t=0; t<3; t++){
    rc = pthread_create(&thread[t], NULL, step_buzz, (void *)st);
    if (rc){
        printf("ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
  }

  rc = pthread_create(&thread[3], NULL, stepFinal_buzz, (void *)st);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }
  
  rc = pthread_create(&thread_final, NULL, final_buzz, NULL);
  if (rc){
    printf("ERROR; return code from pthread_create() is %d\n", rc);
    exit(-1);
  }

  if(modo == 1){
    pthread_t thread_rondas[2*(st->nRondas-1)];

    for(int t=0; t<2*(st->nRondas-1); t++){
      rc = pthread_create(&thread_rondas[t], NULL, step_buzz_rondas, NULL);
      if (rc){
          printf("ERROR; return code from pthread_create() is %d\n", rc);
          exit(-1);
      }
    }
  }

  st->id = g_timeout_add_seconds(1, Countdown, st);
}

static void stopwatch(structBuilder* st)
{
  st->counter = 0;
  g_source_remove(st->id);

  GObject *button;
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);  
  
  static gboolean conections = FALSE;
  st->state = TRUE;
  st->segU = 1;
  st->segD = 0;
  st->minU = 0;
  st->minD = 0;

  st->label = gtk_builder_get_object (st->builder, "Tempo_timer");
  gtk_label_set_text(GTK_LABEL(st->label), "00:00");
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  gtk_widget_set_name (GTK_WIDGET(st->label),"Tempo_timer");
  
  button = gtk_builder_get_object (st->builder, "Stop");
  gtk_button_set_label(GTK_BUTTON(button), "Stop");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (stop), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  button = gtk_builder_get_object (st->builder, "quitStopwatch");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){   
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (preQuit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));

  if(conections == FALSE){
    conections = TRUE;
  }

  esconderMenu(st->builder);
  esconderSetup(st->builder);
  
  st->id = g_timeout_add_seconds(1, update_label_time_stopwatch, st);
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
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);
  
  label = gtk_builder_get_object (st->builder, "LabelRondas");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  gtk_widget_set_name (GTK_WIDGET(label),"LabelRondas");
  
  st->label = gtk_builder_get_object (st->builder, "Rondas");
  sprintf(digito, "%d", st->nRondas);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  gtk_widget_set_name (GTK_WIDGET(st->label),"Rondas");
  
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
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (quit), st);
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
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);
  char digito[11];

  st->label = gtk_builder_get_object (st->builder, "Tempo");
  sprintf(digito, "%d%d%c%d%d", st->minD_rest, st->minU_rest, ':', st->segD_rest, st->segU_rest);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  gtk_widget_set_name (GTK_WIDGET(st->label),"TempoBlue");
  
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
  if(conections == FALSE){
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (quit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  if(conections == FALSE){
    conections = TRUE;
  }

}

static void setup(structBuilder* st)
{
  st->counter = 0;
  g_source_remove(st->id);
  
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
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);

  st->label = gtk_builder_get_object (st->builder, "Tempo");
  sprintf(digito, "%d%d%c%d%d", st->minD, st->minU, ':', st->segD, st->segU);
  gtk_label_set_text(GTK_LABEL(st->label), digito);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(st->label));
  gtk_widget_set_name (GTK_WIDGET(st->label),"Tempo");
  
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

  if(modo == 0){
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
  } else if(modo == 1){
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
    g_signal_connect_swapped(button, "clicked", G_CALLBACK (quit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  if(conections == FALSE){
    conections = TRUE;
  }

  esconderMenu(st->builder);
}

static void modo_normal(structBuilder* st)
{
  modo = 0;
  menu(st);
}

static void modo_tabata(structBuilder* st)
{
  modo = 1;
  menu(st);
}

static void modo_stopwatch(structBuilder* st)
{
  modo = 2;
  menu(st);
}

static void modos (structBuilder* st)
{
  st->counter = 0;
  g_source_remove(st->id);

  GtkStyleContext *context; 
  GObject *label;
  GObject *button;

  static gboolean conections = FALSE;

  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);

  label = gtk_builder_get_object (st->builder, "Modos");
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  gtk_widget_set_name (GTK_WIDGET(label),"Modos");

  button = gtk_builder_get_object (st->builder, "Normal_Timer");
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
  
  button = gtk_builder_get_object (st->builder, "StopWatch");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (modo_stopwatch), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  button = gtk_builder_get_object (st->builder, "Sair");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (quit), st);
  }
  gtk_widget_show (GTK_WIDGET(button));
  
  esconderMenu(st->builder);

}

gboolean counter(gpointer data)
{
  structBuilder* st = data;
  st->counter++;

  if(st->counter == 30){
    st->counter = 0;
    g_source_remove(st->id);
    relogio(st);
  }

  return G_SOURCE_CONTINUE;
}

static void menu(structBuilder* st)
{
  GtkStyleContext *context;
  GObject *button;
  GObject* label;
  static gboolean conections = FALSE;
  static gboolean conections_swicth1 = FALSE;
  static gboolean conections_swicth2 = FALSE;
  
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);

  if(modo == 0){
    label = gtk_builder_get_object (st->builder, "Timer");
    gtk_widget_set_name (GTK_WIDGET(label),"Timer");
  } else if(modo == 1){
    label = gtk_builder_get_object (st->builder, "Timer_Tabata");
    gtk_widget_set_name (GTK_WIDGET(label),"Timer_Tabata");
  } else {
    label = gtk_builder_get_object (st->builder, "Modo_StopWatch");
    gtk_widget_set_name (GTK_WIDGET(label),"Modo_StopWatch");
  }
  context = gtk_widget_get_style_context (GTK_WIDGET(label));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  gtk_widget_show (GTK_WIDGET(label));
  if(modo == 2){
    button = gtk_builder_get_object (st->builder, "inicio_stopwatch");
    context = gtk_widget_get_style_context (GTK_WIDGET(button));
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if(conections == FALSE){
      g_signal_connect_swapped (button, "clicked", G_CALLBACK (stopwatch), st);
      conections_swicth2 = TRUE;
    } else if(conections_swicth1 == TRUE){
      g_signal_connect_swapped (button, "clicked", G_CALLBACK (stopwatch), st);
      conections_swicth1 = FALSE;
    }
    gtk_widget_show (GTK_WIDGET(button));
  } else {
    button = gtk_builder_get_object (st->builder, "inicio_setup");
    context = gtk_widget_get_style_context (GTK_WIDGET(button));
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    if(conections == FALSE){
      g_signal_connect_swapped (button, "clicked", G_CALLBACK (setup), st);
      conections_swicth1 = TRUE;
    } else if(conections_swicth2 == TRUE){
      g_signal_connect_swapped (button, "clicked", G_CALLBACK (setup), st);
      conections_swicth2 = FALSE;
    }
    gtk_widget_show (GTK_WIDGET(button));
  }
  
  button = gtk_builder_get_object (st->builder, "modos_setup");
  context = gtk_widget_get_style_context (GTK_WIDGET(button));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  if(conections == FALSE){
    g_signal_connect_swapped (button, "clicked", G_CALLBACK (modos), st);
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
  
  esconderStopWatch(st->builder);

  esconderTimer(st->builder);

  esconderFinal(st->builder);

  st->id = g_timeout_add_seconds(1, counter, st);
}

int main (int argc, char *argv[])
{
  //chdir("/home/ubuntu/fitness_timer");
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
  
  st->aux_segU_rest = 0;
  st->aux_segD_rest = 0;
  st->aux_minU_rest = 0;
  st->aux_minD_rest = 0;
  
  st->nRondas_reset = 1;
  st->id = -1;
  st->counter = 0;

  GdkScreen *screen = gdk_screen_get_default ();
  GdkDisplay* monitor = gdk_display_get_default ();
  int n_monitor = gdk_display_get_n_monitors(monitor);
  GtkStyleContext *context;
  GtkCssProvider *provider = gtk_css_provider_new ();
  gtk_css_provider_load_from_path (provider, "timer.css", NULL);
  
  st->window = gtk_builder_get_object (st->builder, "window");
  gtk_window_fullscreen_on_monitor(GTK_WINDOW(st->window), screen, 0);
  context = gtk_widget_get_style_context (GTK_WIDGET(st->window));
  gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
  g_signal_connect_swapped (st->window, "destroy", G_CALLBACK (gtk_main_quit), st);

  gtk_widget_add_events(GTK_WIDGET(st->window), GDK_POINTER_MOTION_MASK);

  if(n_monitor > 1){
    // GObject *window = gtk_builder_get_object (st->builder, "window_treinos");
    // gtk_window_fullscreen_on_monitor(GTK_WINDOW(window), screen, 1); 
    // context = gtk_widget_get_style_context (GTK_WIDGET(window));
    // gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    // g_signal_connect_swapped (window, "destroy", G_CALLBACK (gtk_main_quit), st);
  }

  menu(st);
  gtk_main ();

  return 0;
}
