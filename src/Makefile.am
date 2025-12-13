## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = project15_2

project15_2_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	centre.c centre.h \
	inscription.c inscription.h \
	utilisateur.c utilisateur.h

project15_2_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

