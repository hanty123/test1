GCCDIR		=	/cygdrive/c/eyenix/or32

OUTPUTDIR	=	output/
OBJDIR		=	obj/
SPCOUTPUTDIR=	../_Spc/

#########################################################################
include ./config.mk

TARGET  =	EN772

# order is important here:
SUBDIRS	=

LIB     =	$(OBJDIR)$(TARGET).o

ASMS    =


OBJS	=	$(OBJDIR)dev.o
OBJS	+=	$(OBJDIR)dev_flash.o
OBJS	+=	$(OBJDIR)dev_gpio.o
OBJS	+=	$(OBJDIR)dev_irq.o
OBJS	+=	$(OBJDIR)dev_isp.o
OBJS	+=	$(OBJDIR)dev_spi.o
OBJS	+=	$(OBJDIR)dev_timer.o
OBJS	+=	$(OBJDIR)dev_twi.o
OBJS	+=	$(OBJDIR)dev_uart.o
OBJS	+=	$(OBJDIR)dev_wdt.o
OBJS	+=	$(OBJDIR)dev_adc.o
OBJS	+=	$(OBJDIR)dev_enc.o
OBJS	+=	$(OBJDIR)dev_mipi.o

OBJS	+=	$(OBJDIR)app.o
OBJS	+=	$(OBJDIR)app_ae.o
OBJS	+=	$(OBJDIR)app_ae_led.o
OBJS	+=	$(OBJDIR)app_awb.o
OBJS	+=	$(OBJDIR)app_comm.o
OBJS	+=	$(OBJDIR)app_cont.o
OBJS	+=	$(OBJDIR)app_dbg.o
OBJS	+=	$(OBJDIR)app_defect.o
OBJS	+=	$(OBJDIR)app_etc.o
OBJS	+=	$(OBJDIR)app_init.o
OBJS	+=	$(OBJDIR)app_key.o
OBJS	+=	$(OBJDIR)app_main.o
OBJS	+=	$(OBJDIR)app_menu.o
OBJS	+=	$(OBJDIR)app_mode.o
OBJS	+=	$(OBJDIR)app_maf.o
OBJS	+=	$(OBJDIR)app_shd.o
OBJS	+=	$(OBJDIR)app_tdn.o
OBJS	+=	$(OBJDIR)app_util.o
OBJS	+=	$(OBJDIR)app_para.o

LIBS    =	$(LIB)

#########################################################################


#all: $(TARGET) clean
all: clean $(TARGET)

$(LIB):	$(ASMS) $(OBJS)
	@$(LD) -r -o $@ $(ASMS) $(OBJS)

#subdirs:
#	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

$(TARGET): $(LIBS)
	@$(LD) -T ./mem.ld $(LIBS) $(SPCOBJS) -o $(OUTPUTDIR)$@.or32 $(GCC_LIB_OPTS)
	@$(OBJCOPY) -O binary $(OUTPUTDIR)$@.or32 $(OUTPUTDIR)$@.bin
#	@cp $@.or32 $(PRJDIR)/$@.or32
#	@cp $@.bin $(PRJDIR)/$@.bin
	@echo " "
	@echo ".....Success Main..... $(OUTPUTDIR)$@.bin: `cat $(OUTPUTDIR)$@.bin | wc -c` bytes"
	@echo " "
	@$(BINSIZE) $(OUTPUTDIR)$@.or32

dis:
#	@./bin2hex.exe $(OUTPUTDIR)$(TARGET).bin 1 -size_word > $(OUTPUTDIR)$(TARGET).hex
	@$(OBJDUMP) -DSx $(OUTPUTDIR)$(TARGET).or32 > $(OUTPUTDIR)$(TARGET).dis
	@echo " "
	@echo ".....Create Dis..... $(OUTPUTDIR)$(TARGET).dis"


#depend dep:
#	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir .depend ; done
#########################################################################

clean:
	@for dir in $(SUBDIRS); do make clean -C $$dir || exit 1 ; done
	@rm -f $(OBJS) $(ASMS) $(LIB) $(OUTPUTDIR)$(TARGET).or32 $(OUTPUTDIR)$(TARGET).bin $(OUTPUTDIR)$(TARGET).dis
	@rm -f ./output/*.hex
	@rm -f System.map

#distclean: clean
#	find . -type f \
#		\( -name .depend -o -name '*.srec' -o -name '*.bin' \
#		-o -name '*.pdf' \) \
#		-print | xargs rm -f
#	rm -f $(OBJS) *.bak tags TAGS
#	rm -fr *.*~

#########################################################################
