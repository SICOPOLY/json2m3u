CC=gcc
CPP=g++
CFLAGS=-Wall
CPPFLAGS=-Wno-psabi

TARGET=json2m3u
SRC_FILES=$(shell find . -name "*.c")
OBJS=$(patsubst %.c, %.o, $(SRC_FILES))


#INCLUDES
MFC=/usr/include/MFC
JSON=/usr/include/json
BOOST=/usr/include/boost

INCLUDES=-I. \
	 -I$(MFC) \
	 -I$(JSON) \
	 -I$(BOOST)

#Colores
RED	= "\e[31;1m"
GREEN	= "\e[32;1m"
YELLOW	= "\e[33;1m"
BLUE	= "\e[34;1m"
PINK	= "\e[35;1m"
WHITE	= "\e[37;1m"
ORANGE	= "\e[93;1m"
NORMAL	= "\e[0;0m"
GREY	= "\e[0;1m"


%.o: %.c
	@echo "Generando el fichero objeto" $(ORANGE)"'$@'"$(NORMAL) "compilando el fuente" $(ORANGE)"'$<'"$(NORMA)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c -o $@ $<

$(TARGET): $(OBJS)
	@echo "Generando el ejecutable" $(ORANGE)"'$@'"$(NORMAL) "con el fichero objeto" $(ORANGE)"'$^'"$(NORMAL)
	$(CPP) $(CPPFLAGS) $(INCLUDES) -o $@ $^
	@echo "TARGET all: "$(GREEN)"done"$(NORMAL)

all: clean depend $(TARGET) echo_ok

depend: $(TARGET).d

$(TARGET).d: $(SRC_FILES)
	rm -f $(TARGET).d
	@echo "Generando dependencias..."
	$(CPP) $(CPPFLAGS) -MM $^>>$(TARGET).d
	@echo "TARGET depend: "$(GREEN)"done"$(NORMAL)

clean:
	@echo "Cleaning..."
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f $(TARGET).d
	rm -f *.m3u
	rm -f *m3u8
	@echo "TARGET clean: "$(GREEN)"done"$(NORMAL)

echo_ok:
	@echo $(GREEN)"COMPILACION CORRECTA"$(NORMAL)

