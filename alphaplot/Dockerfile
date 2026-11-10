FROM ubuntu:24.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
        flatpak \
        dbus \
        dbus-x11 \
        x11-utils \
        ca-certificates \
    && rm -rf /var/lib/apt/lists/*

RUN flatpak remote-add --if-not-exists \
        flathub https://flathub.org/repo/flathub.flatpakrepo
RUN flatpak install -y flathub io.github.narunlifescience.AlphaPlot
RUN flatpak override --share=network io.github.narunlifescience.AlphaPlot
RUN flatpak override --filesystem=/root/AlphaPlot/ io.github.narunlifescience.AlphaPlot

COPY bin/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]