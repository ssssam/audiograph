#ifndef __GTK_AUDIO_GRAPH_WIDGET_H__
#define __GTK_AUDIO_GRAPH_WIDGET_H__

#include <gtk/gtk.h>

G_DEFINE_QUARK (GTK_AUDIO_GRAPH_ERROR, gtk_audio_graph_error)

typedef enum {
	GTK_AUDIO_GRAPH_ERROR_IO = 1
} GtkAudioGraphErrorType;

#define GTK_AUDIO_GRAPH_TYPE_WIDGET (gtk_audio_graph_widget_get_type ())

G_DECLARE_FINAL_TYPE (GtkAudioGraphWidget, gtk_audio_graph_widget, GTK_AUDIO_GRAPH, WIDGET, GtkDrawingArea)

GtkWidget *gtk_audio_graph_widget_new ();

gboolean gtk_audio_graph_widget_load_file (GtkAudioGraphWidget *self, const char *filename, GError **error);

#endif
