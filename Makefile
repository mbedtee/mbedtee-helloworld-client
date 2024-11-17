#
# SPDX-License-Identifier: Apache-2.0
# Copyright (c) 2019 KapaXL (kapa.xl@outlook.com)
#

CC = $(CROSS_COMPILE)gcc
LD = $(CROSS_COMPILE)gcc
STRIP = $(CROSS_COMPILE)strip

CFLAGS = -g -O2 -Wall -Werror -nostdlib -I$(MBEDTEE_INC)

LDFLAGS = -g -O2 -lpthread -L`dirname $(GP_TEEC_LIB)` -lteec_api

TARGET = mbedtee-helloworld-client

.PHONE: all
all: $(TARGET)

SRCS = $(wildcard *.c)
OBJS = ${SRCS:.c=.o}

$(TARGET): $(OBJS)
	@mkdir -p $(CURDIR)/bin
	$(LD) -o $(CURDIR)/bin/$@ $^ $(LDFLAGS)
	$(STRIP) $(CURDIR)/bin/$@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONE: clean
clean:
	@rm -f $(OBJS) $(TARGET)
