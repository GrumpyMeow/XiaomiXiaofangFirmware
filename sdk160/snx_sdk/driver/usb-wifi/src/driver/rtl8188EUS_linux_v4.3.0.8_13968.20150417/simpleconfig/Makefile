CC = arm-linux-gcc
AR = arm-linux-ar
RM = rm -f
#INSTDIR = /usr/local/bin
INCLUDE = .
CFLAGS = -g -Wall #-ansi
CFLAGS += -DSIMPLE_CONFIG_PBC_SUPPORT
#CFLAGS += -DCONFIG_IOCTL_CFG80211 	#Using iw command, not iwconfig command.

TARGET = rtw_simple_config

all: $(TARGET)
$(TARGET): main.o libsc.a
	$(CC) $(CFLAGS) -o $(TARGET) main.o libsc.a -lpthread -lrt

main.o: sc_common.h
	$(CC) $(CFLAGS) -I$(INCLUDE) $(CFLAGS) -c main.c

clean:
	$(RM) $(TARGET) *.o

