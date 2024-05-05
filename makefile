all: atanua

# Copied from atanua.vcxproj
glee-c-src = \
    src/glee/GLee.c

atanua-c-src = \
    src/8051/core.c \
    src/8051/disasm.c \
    src/8051/opcodes.c \
    src/stb/stb_image.c \
    src/stb/stb_image_write.c

atanua-basecode-cpp-src = \
    src/basecode/angelcodefont.cpp \
    src/basecode/mersennetwister.cpp \
    src/basecode/toolkit.cpp \
    #

atanua-core-cpp-src = \
    src/core/AtanuaConfig.cpp \
    src/core/basechipfactory.cpp \
    src/core/BoxStitchingInformation.cpp \
    src/core/chip.cpp \
    src/core/fileio.cpp \
    src/core/fileutils.cpp \
    src/core/main.cpp \
    src/core/nativefunctions.cpp \
    src/core/net.cpp \
    src/core/pin.cpp \
    src/core/pluginchip.cpp \
    src/core/pluginchipfactory.cpp \
    src/core/simutils.cpp \
    src/core/slidingaverage.cpp \
    src/core/texture.cpp \
    src/core/wire.cpp \
    #

atanua-chips-cpp-src = \
    src/chip/16segchip.cpp \
    src/chip/7segchip.cpp \
    src/chip/and3chip.cpp \
    src/chip/and8chip.cpp \
    src/chip/andchip.cpp \
    src/chip/audiochip.cpp \
    src/chip/box.cpp \
    src/chip/buttonchip.cpp \
    src/chip/chip2051.cpp \
    src/chip/chip27xx.cpp \
    src/chip/chip309.cpp \
    src/chip/chip6116.cpp \
    src/chip/chip7400.cpp \
    src/chip/chip7402.cpp \
    src/chip/chip7404.cpp \
    src/chip/chip7408.cpp \
    src/chip/chip7410.cpp \
    src/chip/chip74138.cpp \
    src/chip/chip74139.cpp \
    src/chip/chip74151.cpp \
    src/chip/chip74154.cpp \
    src/chip/chip74163.cpp \
    src/chip/chip74164.cpp \
    src/chip/chip74165.cpp \
    src/chip/chip74181.cpp \
    src/chip/chip74191.cpp \
    src/chip/chip74192.cpp \
    src/chip/chip74193.cpp \
    src/chip/chip74195.cpp \
    src/chip/chip7420.cpp \
    src/chip/chip74240.cpp \
    src/chip/chip74241.cpp \
    src/chip/chip74244.cpp \
    src/chip/chip74245.cpp \
    src/chip/chip74283.cpp \
    src/chip/chip74299.cpp \
    src/chip/chip7432.cpp \
    src/chip/chip744040.cpp \
    src/chip/chip7447.cpp \
    src/chip/chip74574.cpp \
    src/chip/chip7473.cpp \
    src/chip/chip7474.cpp \
    src/chip/chip7485.cpp \
    src/chip/chip7486.cpp \
    src/chip/chip7489.cpp \
    src/chip/chip7490.cpp \
    src/chip/clockchip.cpp \
    src/chip/composite.cpp \
    src/chip/dchip.cpp \
    src/chip/dflipflop.cpp \
    src/chip/dxchip.cpp \
    src/chip/extpin.cpp \
    src/chip/extrapin.cpp \
    src/chip/jkchip.cpp \
    src/chip/jkflipflop.cpp \
    src/chip/label.cpp \
    src/chip/ledchip.cpp \
    src/chip/ledgrid.cpp \
    src/chip/logicprobe.cpp \
    src/chip/muxchip.cpp \
    src/chip/namedpin.cpp \
    src/chip/nand3chip.cpp \
    src/chip/nand8chip.cpp \
    src/chip/nandchip.cpp \
    src/chip/nor3chip.cpp \
    src/chip/nor8chip.cpp \
    src/chip/norchip.cpp \
    src/chip/notchip.cpp \
    src/chip/or3chip.cpp \
    src/chip/or8chip.cpp \
    src/chip/orchip.cpp \
    src/chip/pullhighchip.cpp \
    src/chip/pulllowchip.cpp \
    src/chip/sedchip.cpp \
    src/chip/serchip.cpp \
    src/chip/srchip.cpp \
    src/chip/srflipflop.cpp \
    src/chip/srnegchip.cpp \
    src/chip/staticlevelchip.cpp \
    src/chip/stepper.cpp \
    src/chip/switchchip.cpp \
    src/chip/tchip.cpp \
    src/chip/tflipflop.cpp \
    src/chip/TriStateChip.cpp \
    src/chip/xorchip.cpp \
    #

tinyxml-src = \
    src/tinyxml_2_5_3/tinyxml/tinystr.cpp \
    src/tinyxml_2_5_3/tinyxml/tinyxml.cpp \
    src/tinyxml_2_5_3/tinyxml/tinyxmlerror.cpp \
    src/tinyxml_2_5_3/tinyxml/tinyxmlparser.cpp \
    #

atanua-headers = \
    Header.h \
    src/include/16segchip.h \
    src/include/7segchip.h \
    src/include/and3chip.h \
    src/include/and8chip.h \
    src/include/andchip.h \
    src/include/angelcodefont.h \
    src/include/atanua.h \
    src/include/atanua_internal.h \
    src/include/audiochip.h \
    src/include/basechipfactory.h \
    src/include/box.h \
    src/include/buttonchip.h \
    src/include/chip2051.h \
    src/include/chip27xx.h \
    src/include/chip309.h \
    src/include/chip6116.h \
    src/include/chip7400.h \
    src/include/chip7402.h \
    src/include/chip7404.h \
    src/include/chip7408.h \
    src/include/chip7410.h \
    src/include/chip74138.h \
    src/include/chip74139.h \
    src/include/chip74151.h \
    src/include/chip74154.h \
    src/include/chip74163.h \
    src/include/chip74164.h \
    src/include/chip74165.h \
    src/include/chip74181.h \
    src/include/chip74191.h \
    src/include/chip74192.h \
    src/include/chip74193.h \
    src/include/chip74195.h \
    src/include/chip7420.h \
    src/include/chip74240.h \
    src/include/chip74241.h \
    src/include/chip74244.h \
    src/include/chip74245.h \
    src/include/chip74283.h \
    src/include/chip74299.h \
    src/include/chip7432.h \
    src/include/chip744040.h \
    src/include/chip7447.h \
    src/include/chip74574.h \
    src/include/chip7473.h \
    src/include/chip7474.h \
    src/include/chip7485.h \
    src/include/chip7486.h \
    src/include/chip7489.h \
    #

tinyxml-src = # use system library instead
atanua-cpp-src = $(atanua-basecode-cpp-src) $(atanua-core-cpp-src) $(atanua-chips-cpp-src) $(tinyxml-src)

glee-obj = $(glee-c-src:.c=.o)
atanua-obj = $(atanua-cpp-src:.cpp=.o) $(atanua-c-src:.c=.o)

CXX = clang++
CC = clang

# more recent tinyxml does not work
TINYXML_CFLAGS = `pkg-config --cflags tinyxml`
TINYXML_LIBS = `pkg-config --libs tinyxml`
#TINYXML_CFLAGS = -Isrc/tinyxml_2_5_3/tinyxml
#TINYXML_LIBS = # bundled source

SDL2_CFLAGS  = `pkg-config --cflags sdl2`
SDL2_LIBS    = `pkg-config --libs sdl2`
GTK_CFLAGS   = `pkg-config --cflags gtk+-3.0`
GTK_LIBS     = `pkg-config --libs gtk+-3.0`
GLIB2_CFLAGS = `pkg-config --cflags glib-2.0`
GLIB2_LIBS   = `pkg-config --libs glib-2.0`
GLEW_CFLAGS  = `pkg-config --cflags glew`
GLEW_LIBS    = `pkg-config --libs glew`

LIBS = \
       $(TINYXML_LIBS) \
       $(SDL2_LIBS) \
       $(GTK_LIBS) \
       $(GLIB2_LIBS) \
       $(GLEW_LIBS)

CPPFLAGS = \
     $(TINYXML_CFLAGS) \
     $(SDL2_CFLAGS) \
     $(GTK_CFLAGS) \
     $(GLIB2_CFLAGS) \
     $(GLEW_CFLAGS)

CXXFLAGS = \
-O3 \
-Isrc \
-Isrc/include \
$(CPPFLAGS)
#


atanua: $(atanua-obj) $(glee-obj) $(atanua-headers)
	$(CXX) $(CXXFLAGS) -o $@ $(atanua-obj) -L. $(LIBS)

clean:
	rm -f $(atanua-obj) $(glee-obj) atanua

