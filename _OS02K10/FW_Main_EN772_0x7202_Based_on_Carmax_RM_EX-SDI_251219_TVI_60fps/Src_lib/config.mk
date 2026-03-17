INCDIRS	=\
		-I"$(INCDIR)"\
		-I$(GCCDIR)/or32-elf/include\
		-I$(GCCDIR)/or32-elf/include/sys\
		-I$(GCCDIR)/lib/gcc/or32-elf/4.5.1-or32-1.0rc1/include

#
# Include the make variables (CC, etc...)
#
CROSS_COMPILE = $(GCCDIR)/bin/or32-elf-

AS	= $(CROSS_COMPILE)as
LD	= $(CROSS_COMPILE)ld
CC	= $(CROSS_COMPILE)gcc
AR	= $(CROSS_COMPILE)ar
NM	= $(CROSS_COMPILE)nm
STRIP	= $(CROSS_COMPILE)strip
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump
RANLIB	= $(CROSS_COMPILE)ranlib
BINSIZE = $(CROSS_COMPILE)size

CFLAGS =	$(INCDIRS) -W -Wall -Wstrict-prototypes
CFLAGS +=	-O2 -pipe
CFLAGS +=	-fomit-frame-pointer -fno-strength-reduce -fno-builtin
CFLAGS +=	-mhard-mul -mhard-div
#CFLAGS +=	-mhard-float
CFLAGS +=	-nostdinc -nostdlib
CFLAGS +=	-D__LIB__
CFLAGS +=	-Dmodel_Sens=9999
#CFLAGS +=	-DALL_SENSOR=9999


GCC_LIB_OPTS = -L"$(GCCDIR)/lib/gcc/or32-elf/4.5.1-or32-1.0rc1" -lgcc
#LDFLAGS = -lgcc

#########################################################################
#$< 현재타겟보다 최근에 변경된 종속 항목 리스트
#$@ 현재 타켓의 이름
# 확장자 규칙
#########################################################################

%.o:	../%.S
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "> Compile : $@"

%.o:	../%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "> Compile : $@"

%.o:	../Src_lib/_Spc/%.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "> Compile : $@"

%.bin: %.or32
	or32-elf-objcopy -O binary $< $@

%.img: %.bin
	utils/bin2flimg 1 $< > $@

%.srec: %.bin
	utils/bin2srec $< > $@

%.hex: %.bin
	utils/bin2hex $< > $@


#########################################################################
