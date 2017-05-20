cd /snx_sdk/buildscript/
./setup_env.sh


cd ../app/
git clone https://github.com/FFTW/fftw3
cd fftw3



./configure --host=armv5tl-montavista-linux-gnueabi --build=x86_64-linux-gnu

autoconf


HOSTCC       = gcc
HOSTCXX      = g++
HOSTCFLAGS   = -Wall -Wmissing-prototypes -Wstrict-prototypes -O2 -fomit-frame-pointer
HOSTCXXFLAGS = -O2

export CC=gcc
export CXX=g++
export CONFIG_SHELL HOSTCC HOSTCFLAGS
./configure --host=armv5tl-montavista-linux-gnueabi --build=x86_64-linux-gnu

/toolchain/crosstool-4.5.2
