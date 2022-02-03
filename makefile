PROGRAM = file_opener
RESOURCE_FILE = ui_resources/file_opener.gresource.xml
DEPS = File_Opener.h File_Opener_Window.h File_Opener_Prefs.h
CXXFILES = main.cpp File_Opener.cpp File_Opener_Window.cpp File_Opener_Prefs.cpp
OFILES = ui_resources/resources.o File_Opener_Window.o File_Opener_Prefs.o File_Opener.o main.o
SETTING_SCHEMA = schemas/gschemas.compiled
CFLAGS = $(shell pkg-config --cflags --libs gtkmm-4.0)

# Makes sure all required files are compiled
all: $(PROGRAM) $(SETTING_SCHEMA)

# Compiles an executable with name 'file_opener'
file_opener : $(OFILES)
	g++ $(OFILES) $(CFLAGS) -o $@

# Compiles source files for all cpp files
# Recompiles whenever DEP header files are also changed
%.o: %.cpp $(DEPS)
	g++ -c -o $@ $< $(CFLAGS)

# Compiles an source file from resource c file
ui_resources/resources.o : ui_resources/resources.c 
	gcc ui_resources/resources.c -c -o ui_resources/resources.o $(CFLAGS)

# Compiles the resource c file from resource xml file and places it in ui_resources folder
ui_resources/resources.c: $(RESOURCE_FILE)
	glib-compile-resources --target=ui_resources/resources.c --generate-source --sourcedir=ui_resources/ $(RESOURCE_FILE)

# Compiles schema binary under the schemas folder
schemas/gschemas.compiled: schemas/org.mt.fileopener.gschema.xml
	glib-compile-schemas schemas/

# Removes all the compiled files
clean:
	rm -f $(OFILES)
	rm -f ui_resources/resources.c
	rm -f schemas/gschemas.compiled
	rm -f file_opener

# Installs the application on the desktop
# Not tested
install-desktop-file:
	@mkdir -p ~/.local/share/applications
	sed -e "s#@bindir@#$$PWD#" File_Opener.desktop.in > ~/.local/share/applications/$(PROGRAM).desktop
	@mkdir -p ~/.local/share/icons/hicolor/48x48/apps
	cp ui_resources/File_Opener_Icon.png ~/.local/share/icons/hicolor/48x48/apps

# For compiling schema file in system schema directory
# First line in main.cpp main() should be commented for this
install-gschema-file:
	if test -n "$(GSETTINGS_SCHEMA_DIR)" -a "$(GSETTINGS_SCHEMA_DIR)" != .; then \
		mkdir -p "$(GSETTINGS_SCHEMA_DIR)"; \
		cp org.gtkmm.exampleapp.gschema.xml "$(GSETTINGS_SCHEMA_DIR)"; \
		$(GLIB_COMPILE_SCHEMAS) "$(GSETTINGS_SCHEMA_DIR)"; \
	fi
