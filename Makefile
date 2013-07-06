TOOLCHAIN = /opt/OSELAS.Toolchain-2012.12.1/arm-v4t-linux-gnueabi/gcc-4.7.2-glibc-2.16.0-binutils-2.22-kernel-3.6-sanitized/bin
CROSS_COMPILE = arm-v4t-linux-gnueabi-

PATH := ${TOOLCHAIN}:${PATH}

all:
	@echo CAMINHO SETADO É:$(PATH)
	@echo COMANDO EMITIDO: ${CROSS_COMPILE}gcc i2c.c -o i2cteste
	@${CROSS_COMPILE}gcc i2c.c -o i2cteste

clean:
	@rm -rf *.o i2cteste


