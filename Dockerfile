FROM ubuntu:26.04

# we're using clang-21 on lenovo ubuntu
ENV CLANG_VERSION='21'
ENV CLANG="clang-$CLANG_VERSION"
ENV DEBUG_TOOLS="vim-tiny man-db"
# Expand certain interactive-specific features
#RUN yes | unminimize

RUN apt-get update && \
    apt-get upgrade --yes && \
    apt-get install --yes \
      $DEBUG_TOOLS

RUN update-alternatives --install /usr/bin/clang clang "$(which "$CLANG")" 100
RUN update-alternatives --install /usr/bin/clang++ clang++ "$(which "clang++-${CLANG_VERSION}")" 100

WORKDIR /home/ubuntu

RUN echo 'ubuntu:ubuntu' | chpasswd
RUN echo "ubuntu ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
