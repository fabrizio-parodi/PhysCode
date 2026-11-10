#!/bin/bash
mkdir -p /var/run/dbus
dbus-daemon --system --fork
exec dbus-run-session -- flatpak run io.github.narunlifescience.AlphaPlot
