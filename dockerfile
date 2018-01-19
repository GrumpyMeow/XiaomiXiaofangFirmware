# Based upon: ril3y/sonix-sn98600-toolchain
#
# Build Docker image:
# 	1. Create a directory "sonix-sn98600-toolchain"
# 	2. Place this dockerfile in the directory
# 	3. Place the SDK file also in this directory
# 	4. Execute: docker build -t sn98600-sdk  --build-arg SDK=SN986_1.60_QR_Scan_019a_20160606_0951 . 
#
# Run:
# 	1. Start container: docker run --privileged -it -v /temp/image/:/root/snx_sdk/image/:rw sn98600-sdk
# 	2. Execute in container: make sn98660_402mhz_sf_defconfig
#	3. Execute in container: make
#	4. Execute in container: make install
#
#	Or:
#	1. cd /root/xiaofang/
#	2. chmod +x option1.sh
#	2. ./option1.sh

FROM bashell/alpine-bash

# Filename of the SDK (without .tgz file extension)
ARG SDK=SN986_1.60_QR_Scan_019a_20160606_0951

# Unpack the SDK
ADD $SDK.tgz /root/
WORKDIR /root/$SDK
RUN bash ./sdk.unpack

FROM fedora:latest
WORKDIR /root/
ARG SDK=SN986_1.60_QR_Scan_019a_20160606_0951
COPY --from=0 /root/$SDK/snx_sdk/ ./

WORKDIR /root/buildscript/

RUN yum update -y -q
#RUN yum group install "Development Tools" -y -q ; yum clean all
RUN yum install cpan vim lzop lzma bzip2 ncurses-devel wget findutils redhat-rpm-config cpanminus cpan gcc gcc-c++ patch glibc.i686 zlib.i686 hostname cpio -y -q ; yum clean all

RUN ./setup_env.sh

ENV PERL_MM_USE_DEFAULT=1
RUN cpan install Test::More
RUN cpan install Encode::Detect
RUN cpan install Digest::CRC

# Fix deprecated defined(@array)
RUN if [ "$SDK" = "SN986_1.60_QR_Scan_019a_20160606_0951" -o "$SDK" = "SN986_1.50_20160511_1053_d_054a_20160511_1320" ] ; then sed -i '373s/.*/if (!@val) {/' /root/kernel/linux-2.6.35.12/src/kernel/timeconst.pl ; fi

ENV SDK=$SDK

COPY xiaofang/ /root/xiaofang/

ENTRYPOINT ["/bin/bash"]

