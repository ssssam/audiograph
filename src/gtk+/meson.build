sources = ['gtkaudiographwidget.c']
headers = ['gtkaudiographwidget.h']

audiograph_gtk = library('audiograph-gtk',
    sources: sources,
    dependencies: gtk,
    link_with: audiograph,
    include_directories: srcinc)

gnome.generate_gir(audiograph_gtk,
    sources: sources + headers,
    nsversion: '1.0',
    namespace: 'GtkAudioGraph',
    symbol_prefix: 'gtk_audio_graph',
    identifier_prefix: 'GtkAudioGraph',
    includes: ['Gtk-3.0'],
    dependencies: gtk,
    install: true)
