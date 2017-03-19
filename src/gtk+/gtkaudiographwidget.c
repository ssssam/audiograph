#include "audiograph.h"

#include "gtkaudiographwidget.h"

struct _GtkAudioGraphWidget {
  GtkDrawingArea parent;
  struct graph *gr;
  GBytes *buffer;
};

enum {
  PROP_0,
  PROP_BUFFER
};

G_DEFINE_TYPE (GtkAudioGraphWidget, gtk_audio_graph_widget, GTK_TYPE_DRAWING_AREA);

static gboolean
draw (GtkWidget *widget,
      cairo_t   *cr)
{
  GtkAudioGraphWidget *self = GTK_AUDIO_GRAPH_WIDGET (widget);
  guint width, height;
  GdkRGBA color;
  GtkStyleContext *context;
  double color_array[3];

  if (self->buffer != NULL) {
    context = gtk_widget_get_style_context (widget);

    width = gtk_widget_get_allocated_width (widget);
    height = gtk_widget_get_allocated_height (widget);

    gtk_render_background (context, cr, 0, 0, width, height);

    gtk_style_context_get_color (context,
                                 gtk_style_context_get_state (context),
                                 &color);
    color_array[0] = color.red;
    color_array[1] = color.green;
    color_array[2] = color.blue;

    graph_draw (self->gr, cr, width, height, color_array);
  }

  return FALSE;
}

static void
size_allocate (GtkWidget     *widget,
               GtkAllocation *allocation)
{
  GTK_WIDGET_CLASS (gtk_audio_graph_widget_parent_class)->size_allocate (widget, allocation);
}

static void
realize (GtkWidget *widget)
{
  GTK_WIDGET_CLASS (gtk_audio_graph_widget_parent_class)->realize (widget);
}

static void
set_property (GObject *object, guint prop_id, const GValue *value, GParamSpec *pspec)
{
  GtkAudioGraphWidget *self = GTK_AUDIO_GRAPH_WIDGET (object);

  switch (prop_id)
    {
    case PROP_BUFFER:
      /* FIXME: we don't really need the extra GBytes to stay around ... */
      if (self->buffer != NULL) {
        g_bytes_unref (self->buffer);
      }

      self->buffer = g_value_get_boxed (value);

      if (self->buffer) {
        gsize length;
        gconstpointer data;

        data = g_bytes_get_data (self->buffer, &length);

        graph_buffer_samples (self->gr, (float *) data, length / 4);

        g_bytes_ref (self->buffer);
        g_debug ("Received buffer %p of %i bytes", self->buffer, g_bytes_get_size (self->buffer));
      }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
    }
}

static void
finalize (GObject *object) {
  GtkAudioGraphWidget *self = GTK_AUDIO_GRAPH_WIDGET (object);

  if (self->buffer)
    g_bytes_unref (self->buffer);

  graph_destroy (self->gr);
}

static void
gtk_audio_graph_widget_init (GtkAudioGraphWidget *self) {
  self->gr = graph_init ();
}

static void
gtk_audio_graph_widget_class_init (GtkAudioGraphWidgetClass *class)
{
  GObjectClass *object_class = G_OBJECT_CLASS (class);
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (class);

  object_class->set_property = set_property;
  object_class->finalize = finalize;

  widget_class->draw = draw;
  widget_class->realize = realize;
  widget_class->size_allocate = size_allocate;

  g_object_class_install_property (object_class,
                                   PROP_BUFFER,
                                   g_param_spec_boxed ("buffer",
                                                       "Audio buffer",
                                                       "Audio buffer as an array of 32-bit floats",
                                                       G_TYPE_BYTES,
                                                       G_PARAM_WRITABLE));

  gtk_widget_class_set_css_name (GTK_WIDGET_CLASS (class), "audiograph");
}

/**
 * gtk_audio_graph_widget_new:
 *
 * Creates a new audio graph widget.
 *
 * Returns: (transfer full): a new #GtkWidget
 */
GtkWidget *gtk_audio_graph_widget_new() {
  return g_object_new (GTK_AUDIO_GRAPH_TYPE_WIDGET, NULL);
}

