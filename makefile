
CC = g++
CFLAGS = 
LIBS = -lncurses

headerfiles = $(wildcard include/*)
libobjects = $(addsuffix .o, $(basename $(notdir $(wildcard src/*))))

demo: demo.out
	@printf "running demo program.\n"
	@./demo.out

demo.out: install
	@# compiling demo program
	@printf "compiling demo program\n"
	@$(CC) demo.cpp -lncgui $(CFLAGS) $(LIBS) -o demo.out

obj/%.o: src/%.cpp
	@# compiling source files
	@printf "  compiling $(notdir $^)"
	@$(CC) -c -o $@ $^ $(LIBS) $(CFLAGS)
	@printf "\n"

libncgui.a: $(addprefix obj/, $(libobjects))
	@# compiling static library file
	@printf "creating library file.\n"
	@ar r libncgui.a $(addprefix obj/, $(libobjects))

install_headers: $(headerfiles)
	@# moving header files to appropriate location
	@printf "installing header files\n"
	@if [ -e /usr/local/include/ncgui ]; then printf "existing header files found, deleting them.\n"; sudo rm -r /usr/local/include/ncgui; else true; fi
	@sudo mkdir /usr/local/include/ncgui
	@sudo cp ./include/*.h /usr/local/include/ncgui/
	@printf "header files installed.\n"

install_lib: install_headers libncgui.a
	@# libncgui.a is compiled, moving it to appropriate location
	@sudo mv libncgui.a /usr/local/lib/

install: install_lib
	@printf "ncgui library installed sucessfully.\n"

uninstall:
	@sudo rm /usr/local/include/ncgui -r || true
	@sudo rm /usr/local/lib/libncgui.a || true

clean:
	@sudo rm obj/* || true
	@sudo rm libncgui.a || true

