#!/bin/bash

xhost +
docker run --rm -it \
  --cap-add=SYS_ADMIN \
  --cap-add=NET_ADMIN \
  --security-opt seccomp=unconfined \
  --security-opt apparmor=unconfined \
  --device /dev/fuse \
  -e DISPLAY=host.docker.internal:0 \
  -v ~/alphaplot-data:/root/AlphaPlot/ \
  alphaplot