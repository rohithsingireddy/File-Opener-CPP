# File Opener

An application made with `gtkmm` graphic library in CPP.

## Compiling
In VSCode, pressing `F5` on *main.cpp* would compile an executable named **main**.

In other environments, an executable can be compiled by executing the following commands in a shell under the directory where *main.cpp* is present after cloning.

```bash
cd ./schemas/
glib-compile-schemas .
cd ../ui_resources/
glib-compile-resources --target=resources.c --generate-source file_opener.gresource.xml
g++ main.cpp -o main $(pkg-config gtkmm-4.0 --cflags --libs)

```

## Notes
- To create a resources.c file from ui_resources/file_opener.gresources.xml
```bash
cd ./ui_resources/
glib-compile-resources --target=resources.c --generate-source file_opener.gresources.xml
```

- Resources file should be generated whenever a **.ui** is changed.

- To create a schema binary file from *schemas/org.mt.fileopener.gschema.xml*
```bash
cd ./schemas
glib-compile-schemas .
```

- Schema file should be generated whenever a **.gschema.xml** file should be generated
