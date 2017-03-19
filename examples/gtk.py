#!/usr/bin/python3
# Example GTK application to display a wave form

import gi
gi.require_version('Gtk', '3.0')
gi.require_version('GtkAudioGraph', '1.0')
from gi.repository import Gio, GLib, GObject, Gtk, GtkAudioGraph

import os
import struct
import sys


def activate(app):
    widget = GtkAudioGraph.Widget.new()

    result = widget.load_file(app.audio_file)

    window = Gtk.ApplicationWindow.new(app)
    window.add(widget)

    window.show_all()


def main():
    if len(sys.argv) < 2:
        raise RuntimeError("Please pass the path to a .wav file to display.")

    audio_file = sys.argv[1]

    if not os.path.exists(audio_file):
        raise RuntimeError("Could not find file " + audio_file)

    Gtk.init()

    app = Gtk.Application.new("org.gtk.example", Gio.ApplicationFlags.FLAGS_NONE)
    app.connect('activate', activate)
    app.audio_file = audio_file

    app.run()


def install_excepthook():
    """ Make sure we exit when an unhandled exception occurs. """
    old_hook = sys.excepthook

    def new_hook(etype, evalue, etb):
        old_hook(etype, evalue, etb)
        while Gtk.main_level():
            Gtk.main_quit()
        sys.exit()
    sys.excepthook = new_hook


install_excepthook()
main()
