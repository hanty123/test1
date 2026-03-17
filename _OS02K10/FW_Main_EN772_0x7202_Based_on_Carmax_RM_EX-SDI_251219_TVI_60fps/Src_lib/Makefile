GCCDIR		=	/cygdrive/c/eyenix/or32

OUTPUTDIR	=	../_Prj/
OBJDIR		=	obj/

SPCOUTPUTDIR=	../_Spc/

#INCDIR		=	../Src
INCDIR		=	./

LIB_OUT		=	EN772L

#########################################################################
include ./config.mk

TARGET  =	lib$(LIB_OUT)

# order is important here:
SUBDIRS	=

LIB     =	$(OBJDIR)$(TARGET).o

ASMS    =	$(OBJDIR)reset.o
ASMS    +=  $(OBJDIR)exr1k_float.o

OBJS    =	$(OBJDIR)dev_cache.o
OBJS    +=	$(OBJDIR)dev_cpu.o
OBJS	+=	$(OBJDIR)app_ae_lib.o
OBJS	+=	$(OBJDIR)app_ae_led_lib.o
OBJS	+=	$(OBJDIR)app_awb_lib.o
OBJS	+=	$(OBJDIR)app_defog_lib.o
OBJS	+=	$(OBJDIR)app_menu_lib.o
OBJS	+=	$(OBJDIR)app_mode_lib.o
OBJS	+=	$(OBJDIR)app_maf_lib.o
OBJS	+=	$(OBJDIR)app_utl_lib.o

OBJS	+=	$(OBJDIR)SENS_Common.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX225.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX224.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX290.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX327.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX307.o
# OBJS	+=	$(OBJDIR)EN772_SENS_IMX462.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX662.o
#OBJS	+=	$(OBJDIR)EN772_SENS_GC2053.o
#OBJS	+=	$(OBJDIR)EN772_SENS_GC2093.o
#OBJS	+=	$(OBJDIR)EN772_SENS_SC200AI.o
#OBJS	+=	$(OBJDIR)EN772_SENS_PS6210K.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX335.o
#OBJS	+=	$(OBJDIR)EN772_SENS_IMX675.o
#OBJS	+=	$(OBJDIR)EN772_SENS_SC500AI.o
#OBJS	+=	$(OBJDIR)EN772_SENS_LFM_IMX390.o
#OBJS	+=	$(OBJDIR)EN772_SENS_LFM_AR0233.o
#OBJS	+=	$(OBJDIR)EN772_SENS_LFM_OX03C10.o
#OBJS	+=	$(OBJDIR)EN772_SENS_OS02H10.o
# OBJS	+=	$(OBJDIR)EN772_SENS_OS04C10.o
OBJS	+=	$(OBJDIR)EN772_SENS_OS02K10.o


LIBS    =	$(LIB)

#########################################################################


#all: $(TARGET) clean
all: clean $(TARGET)

$(LIB):	$(ASMS) $(OBJS) $(SPCOBJS)
	@$(LD) -r -o $@ $(ASMS) $(OBJS)

#subdirs:
#	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir || exit 1 ; done

$(TARGET): $(LIBS)
	@$(AR) rcv $(OUTPUTDIR)$@.a $(ASMS) $(OBJS)
	@echo " "
	@echo ".....Success Lib..... $(OUTPUTDIR)$@.a"
	@echo " "

dis:
	@$(OBJDUMP) -DSx $(OUTPUTDIR)$(TARGET).a > $(OUTPUTDIR)$(TARGET).dis
	@echo " "
	@echo ".....Create Dis..... $(OUTPUTDIR)$(TARGET).dis"


#depend dep:
#	@for dir in $(SUBDIRS) ; do $(MAKE) -C $$dir .depend ; done
#########################################################################

clean:
	@for dir in $(SUBDIRS); do make clean -C $$dir || exit 1 ; done
	@rm -f $(OBJS) $(ASMS) $(LIB) $(OUTPUTDIR)$(TARGET).or32 $(OUTPUTDIR)$(TARGET).a $(OUTPUTDIR)$(TARGET).dis $(SPCOBJS)
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
