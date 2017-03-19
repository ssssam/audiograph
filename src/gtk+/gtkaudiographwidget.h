#ifndef __GTK_AUDIO_GRAPH_WIDGET_H__
#define __GTK_AUDIO_GRAPH_WIDGET_H__

#include <gtk/gtk.h>

#define GTK_AUDIO_GRAPH_TYPE_WIDGET (gtk_audio_graph_widget_get_type ())

G_DECLARE_FINAL_TYPE (GtkAudioGraphWidget, gtk_audio_graph_widget, GTK_AUDIO_GRAPH, WIDGET, GtkDrawingArea)

GtkWidget *gtk_audio_graph_widget_new ();

#endif
