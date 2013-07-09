TOOLCHAIN = /opt/OSELAS.Toolchain-2012.12.1/arm-v4t-linux-gnueabi/gcc-4.7.2-glibc-2.16.0-binutils-2.22-kernel-3.6-sanitized/bin
CROSS_COMPILE = arm-v4t-linux-gnueabi-

PATH := ${TOOLCHAIN}:${PATH}

all:
	@echo CAMINHO SETADO É:$(PATH)
	@echo COMANDO EMITIDO: ${CROSS_COMPILE}gcc gpio.c -o gpiofinal
	@${CROSS_COMPILE}gcc gpio.c -o gpiofinal

clean:
	@rm -rf *.o gpiofinal


