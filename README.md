The goal of this branch is to put all the experience acquired from other branches together make some working stuff.

To run a pure executable the following dlls are required:
> Qt5Core.dll
> Qt5Network.dll
> Qt5Test.dll
> Qt5WebSockets.dll
> odb-2.4-vc12.dll
> odb-mssql-2.4-vc12.dll
> odb-qt5-2.4-vc11.dll

In order to keep the project clean and consistent you must follow the next conventions:
- All files should be named CamelCase and start from the capital letter.
- All header files must have .h extension.
- All source files must have .cpp extesion.
- To classify the files suffixes must be used like "filename-suffix.ext".
Currently 3 suffixes are used: 
	1. -inl for inline headers
	2. -map for mapping headers
	3. -odb for odb-generated files
- When compiling persistent classes use the following odb compiler options:
	-d mssql --profile qt --hxx-suffix .h --ixx-suffix -inl.h --cxx-suffix .cpp --output-dir Mapping
	**Example:** odb -d mssql --profile qt --hxx-suffix .h --ixx-suffix -inl.h --cxx-suffix .cpp --output-dir Mapping Entity.h
	**Note 1:** all directories with persistent classes must contain a "Mapping" directory where all odb-generated files will be stored.
	**Note 2:** Each persistent class must be in a separate header, say "ClassName.h". Then in the end of that header a mapping 
	header "ClassName-map.h" must be included. Mapping header must contain all mapping-specific stuff like odb pragmas, odb-generated 
	headers, etc.
	**Example:** Persistent class IEntity. Header named "IEntity.h". Mapping header "IEntity-map.h". 
	(Look detailed implementation in TransportEmpire/Database/ directory.)
- Camel case must be used for all the code.
- Classe and type names must start with upper case.
- Object and variable names must start with lower case.
