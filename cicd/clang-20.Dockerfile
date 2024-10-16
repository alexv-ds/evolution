FROM ubuntu:24.10

SHELL ["/bin/bash", "-o", "pipefail", "-c"]

RUN \
  apt-get update && \
  apt-get install --no-install-recommends -y wget=1.24.5-1ubuntu2 ca-certificates=* && \
  wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key | tee /etc/apt/trusted.gpg.d/apt.llvm.org.asc && \
  echo "deb http://apt.llvm.org/noble/ llvm-toolchain-noble main" >> /etc/apt/sources.list && \
  echo "deb-src http://apt.llvm.org/noble/ llvm-toolchain-noble main" >> /etc/apt/sources.list && \
  apt-get update && \
  apt-get install --no-install-recommends -y \
    clang-20=1:20~++20241016081625+4ddea298e60c-1~exp1~20241016081756.479 \
    clang-tools-20=1:20~++20241016081625+4ddea298e60c-1~exp1~20241016081756.479 \
    libc++-20-dev=1:20~++20241016081625+4ddea298e60c-1~exp1~20241016081756.479 \
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

