FROM ubuntu:24.10

RUN \
  apt-get update && \
  apt-get install --no-install-recommends -y \
    gcc-14=14.2.* \
    g++-14=14.2.* \
    cmake=3.30.* \
    ninja-build=1.12.* \
    git=1:2.45.* \
    ccache=4.10.2-1 \
    libx11-dev=2:1.8.7-1build1 \
    libxrandr-dev=2:1.5.4-1 \
    libxcursor-dev=1:1.2.2-1 \
    libxi-dev=2:1.8.2-1 \
    libgl1-mesa-dev=24.2.3-1ubuntu1 \
    libudev-dev=256.5-2ubuntu3 \
    libfreetype-dev=2.13.3+dfsg-1 \
  && \
  apt-get clean && \
  rm -rf /var/lib/apt/lists/*

