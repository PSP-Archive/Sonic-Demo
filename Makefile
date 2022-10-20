TARGET = Sonic
OBJS = main.o boucle.o Jeux.o intro.o menu.o screenshot.o

INCDIR = 
CFLAGS = -G4 -Wall -O2 -DPSPFW3XX 
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

BUILD_PRX = 1
PSP_FW_VERSION=371

LIBDIR =
LDFLAGS =
STDLIBS= -losl -lpng -lz \
		-lpspsdk -lpspctrl -lpspumd -lpsprtc -lpsppower -lpspgu -lpspaudiolib -lpspaudio -lm -lDevslib -lpspaudiolib -lpspmpeg -lpspaudiocodec -lmad

LIBS=$(STDLIBS)$(YOURLIBS)


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = Sonic
#PSP_EBOOT_ICON = ICON0.png
# musique (*.AT3) lecture en boucle
#PSP_EBOOT_SND0 =  SND0.AT3
#PSP_EBOOT_PIC0 = pic0.png
# Image de fond en (*.PNG) 
#PSP_EBOOT_PIC1 = pic1.png
# animation (*.PMF) afficher dans le XMB 
#PSP_EBOOT_ICON1 = NULL 
# image (*.PNG) afficher quelque seconde avec transparenceapres l'icone et l'annimation
#PSP_EBOOT_UNKPNG = NULL 



PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
