all:
	g++.exe "outputdir\gcc_main.o" "outputdir\gcc_LuaFont2.o" "outputdir\gcc_BFModuleWindow.o" "outputdir\gcc_brainfuck.o" "outputdir\gcc_PegTextStream.o" "outputdir\gcc_bouton.o"  -o "outputdir\CPBF.exe" -L"C:\PROGRA~1\CASIO\CLASSP~2\Dev-Cpp\lib" -D__DEBUG__ -L"C:\PROGRA~1\Dev-Cpp\lib" -g3 "C:\PROGRA~1\CASIO\CLASSP~2\lib\gcc_main.a" "C:\PROGRA~1\CASIO\CLASSP~2\lib\ClassPadDLLgcc.a"
