
CC = g++
CFLAGS = 
LIBS = -lncurses

libobjects = container_box.o container_split.o guielement_placeholder.o guielement_textconsole.o guielement_window.o

demo: demo.out
	./demo.out

demo.out: ncgui.a demo.o
	$(CC) demo.o ncgui.a $(CFLAGS) $(LIBS) -o demo.out

%.o: %.cpp
	$(CC) -c -o $@ $^ $(LIBS) $(CFLAGS)

ncgui.a: $(libobjects)
	ar r ncgui.a $(libobjects)

