## Process this file with automake to produce Makefile.in
INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = group_1

group_1_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	centre.c centre.h \
	coach.c coach.h \
	entraineur.c entraineur.h \
	equipment.c equipment.h \
	evenement.c evenement.h \
	inscription.c inscription.h \
	membre.c membre.h \
	reservation.c reservation.h \
	stats.c stats.h \
	admin.c admin.h \
        utilisateur.c utilisateur.h


group_1_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)
