# Writing a 32-bit operating system



## Setup build env

Build an image for our build-env
 - `docker build buildenv -t myos`

## Build

Windows (PowerShell): 
  - `docker run --rm -it -v "${pwd}:/root/env" myos`

Windows (CMD):
  - `docker run --rm -it -v "%cd%":/root/env myos`

Build for x86:
  - `make build`

To leave the build env, enter `exit`

## Emulate

Enter this:
  - `qemu-system-x86_64 -cdrom dist/x86/kernel.iso`