#!/bin/bash
echo "First, we need those packages: gmp, mpfr, libmpc & gcc"
echo "the script will run the command to install those on ubuntu / debian based distros"
sudo apt-get update && sudo apt-get install libgmp3-dev libmpfr-dev libmpc-dev gcc
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"
echo "cloning and compiling binutils for target i386-elf..."
mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.40.tar.gz
tar xf binutils-2.40.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.40/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
make all install 2>&1 | tee make.log
echo "cloning and compiling gcc for target i386-elf"
cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-12.2.0/gcc-12.2.0.tar.gz
tar xf gcc-12.2.0.tar.gz
mkdir gcc-build
cd gcc-build
../gcc-12.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-languages=c --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
echo "cloning and compiling gdb for target i386-elf"
cd /tmp/src
curl -O http://ftp.rediris.es/mirror/GNU/gdb/gdb-13.1.tar.gz
tar xf gdb-13.1.tar.gz
mkdir gdb-build
cd gdb-build
export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
../gdb-13.1/configure --target="$TARGET" --prefix="$PREFIX" --program-prefix=i386-elf-
make
make install
echo "all packages installed under /usr/local/i386elf(programName)/"
echo "Also, you will have to add to your .bashrc:"
echo "export PREFIX=\"/usr/local/i386elfgcc\""
echo "export TARGET=i386-elf"
echo "export "export PATH=\"$PREFIX/bin:$PATH\""
