DEBUG := -g 
DEPS := -MMD

CC := g++

SRCDIR := src
BUILDDIR := build
TARGET := pkmnrcc
VERSION := 1.0

TIMESTAMP := $(shell date '+%Y.%m.%d-%H.%M.%S')
BAKPREFIX := .bak-
BAKDIR := /home/$(USER)/Backups/$(TARGET)/$(BAKPREFIX)$(TIMESTAMP)/
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -w -std=c++1z -Wfatal-errors $(DEBUG)
LIB := -lstdc++fs -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -llua5.3 #-I"./lib/lua" -L"./lib/lua"

all: $(OBJECTS)
	@echo " $(CC) build/*.o -o bin/$(TARGET) $(LIB)"; $(CC) $^ -o bin/$(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(DEPS) -c -o $@ $<"; $(CC) $(CFLAGS) $(DEPS) -c -o $@ $<
ifneq (,$(findstring -MMD,$(DEPS)))
	@mkdir -p $(BUILDDIR)/.deps
	@mv -f $(BUILDDIR)/*.d $(BUILDDIR)/.deps
endif

-include $(BUILDDIR)/.deps/*.d

clean:
	@echo " $(RM) -r $(BUILDDIR) bin/$(TARGET)"; $(RM) -r $(BUILDDIR) bin/$(TARGET)

.PHONY: clean

backup:
	@echo " $(RM) -r $(BUILDDIR) bin/$(TARGET)"; $(RM) -r $(BUILDDIR) bin/$(TARGET)
	mkdir -p $(BAKDIR)
	cp -rfu ../$(TARGET)-$(VERSION)/ $(BAKDIR)
	@rm -f $(BAKDIR)$(TARGET)-$(VERSION)/.*swp
	@rm -f  $(BAKDIR)$(TARGET)-$(VERSION)/$(SRCDIR)/.*swp
	@rm -f  $(BAKDIR)$(TARGET)-$(VERSION)/assets/scripts/.*swp
	@rm -f  $(BAKDIR)$(TARGET)-$(VERSION)/assets/tilemaps/.*swp
	@rm -f  $(BAKDIR)$(TARGET)-$(VERSION)/HOME/.${TARGET}/tsav/.*swp
	@rm -f  $(BAKDIR)$(TARGET)-$(VERSION)/HOME/.${TARGET}/sav/.*swp

.PHONY: backup

install:
	mkdir -p ${DESTDIR}/usr/games/${TARGET}/bin
	cp bin/${TARGET} ${DESTDIR}/usr/games/${TARGET}/bin

run:
	bin/run.sh $(TARGET);

debug:
	bin/run.sh $(TARGET) "gdb -tui";

map:
	tools/buildMap.sh;

fusionMap:
	tools/fusionMap.sh;

luaScript:
	tools/luaScript.sh
