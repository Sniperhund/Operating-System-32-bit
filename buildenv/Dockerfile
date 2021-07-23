FROM randomdude/gcc-cross-i686-elf

RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install -y grub-common
RUN apt-get install -y grub-pc-bin
RUN apt-get install -y xorriso

VOLUME /root/env
WORKDIR /root/env