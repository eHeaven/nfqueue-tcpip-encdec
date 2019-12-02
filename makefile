CC = gcc
CFLAGS = -g -O -Wall -Werror

TOPDIR := $(PWD)
OBJDIR := $(TOPDIR)/obj
BINDIR := $(TOPDIR)/bin
BIN := main

OBJ := nfqueue.o encdec.o tcpip.o main.o
SUBDIR := nfqueue encdec tcpip main obj 
OBJHEAD := $(TOPDIR)/nfqueue/nfqueue.h $(TOPDIR)/tcpip/tcpip.h $(TOPDIR)/encdec/encdec.h

OBJLINK := -lnetfilter_queue -lnfnetlink -lcrypto --std=c99
 
export CC TOPDIR OBJDIR BINDIR BIN OBJLINK OBJ
 
all:CHECKDIR $(SUBDIR)
	@echo "$(shell ./size/abcd 1)"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 3 Congratulations! Compile completed!!!)"
	@echo "$(shell ./size/abcd 2 Executable file name is : $(BIN))" 
	@echo "$(shell ./size/abcd 2 Executable file in directory : $(BINDIR))" 
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"
CHECKDIR:
	@echo "$(shell ./size/abcd 1)"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd Create subfolders:)"
# 如果在指令前面使用 @ ，那么这个指令只是执行，但是在终端不打印出来	
	@mkdir -p $(SUBDIR) 
	@mkdir -p $(BINDIR)
	@echo "$(shell ./size/abcd 2 mkdir -p $(SUBDIR))"
	@echo "$(shell ./size/abcd 2 mkdir -p $(BINDIR))"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 3 Successful Creation of subfolders!)" 
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"
$(SUBDIR):RUN
	make -C $@
	@echo "$(shell ./size/abcd 1)"
RUN:
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd All sub ectories are:)"
	@echo "$(shell ./size/abcd 2 $(SUBDIR))"
	@echo "$(shell ./size/abcd All links are:)"
	@echo "$(shell ./size/abcd 2 $(OBJLINK))"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 3 begin Compile)"           
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"
.PHONY:test
test:
	@echo "$(shell ./size/abcd 1)"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 3 run success)"           
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"

.PHONY:clean
clean:
	@echo "$(shell ./size/abcd 1)"
	@echo "$(shell ./size/abcd 2)"
	@rm -rf $(OBJDIR)/*.o $(BINDIR) 
	@echo "$(shell ./size/abcd 3 rm -rf $(OBJDIR)/*.o $(BINDIR))"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"
help:
	@echo "$(shell ./size/abcd 1)"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 3 Option Description)"
	@echo "$(shell ./size/abcd 2)"
	@echo "$(shell ./size/abcd 1)"
