#!/bin/sh

# The following is (probably) needed to create the toochain
# * GCC
# * G++
# * GNU Make
# * GNU Bison
# * Flex
# * GNU GMP
# * GNU MPFR
# * GNU MPC
# * Texinfo
# * git
# * xorriso


export PREFIX="$(pwd)/toolchain"
export TARGET=i686-elf

export BINUTILS=binutils-2.27
export GCC=gcc-4.9.4

mkdir -p toolchain
cd toolchain

# BINUTILS
wget http://ftpmirror.gnu.org/binutils/$BINUTILS.tar.gz
tar xzf $BINUTILS.tar.gz
mkdir -p build-binutils
cd build-binutils
../$BINUTILS/configure --target=$TARGET --prefix=$PREFIX --with-sysroot \
  --disable-nls --disable-werror
make && make install
cd ..

# Test
export PATH=$PREFIX/bin:$PATH
which -- $TARGET-as || echo $TARGET-as is not in the PATH

# GCC
wget ftp://ftp.gnu.org/gnu/gcc/$GCC/$GCC.tar.gz
tar xzf $GCC.tar.gz
mkdir -p build-gcc
cd build-gcc
../$GCC/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ..

# OBJCONV
git clone https://github.com/vertis/objconv.git
cd objconv
g++ -o objconv -O2 src/*.cpp
cp objconv $PREFIX/$TARGET/bin
cd ..

# GRUB
git clone git://git.savannah.gnu.org/grub.git
cd grub
./autogen.sh
mkdir - ../build-grub
cd ../build-grub
../grub/configure --disable-werror TARGET_CC=$TARGET-gcc TARGET_OBJCOPY=$TARGET-objcopy TARGET_STRIP=$TARGET-strip TARGET_NM=$TARGET-nm TARGET_RANLIB=$TARGET-ranlib --target=$TARGET --prefix=$PREFIX
make && make install
