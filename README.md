Steps to Run the Interpreter:
1. Go to the 'interpreter' folder.
2. Give Assembly language input inside the test.asm file inside input folder.
3. If Debugger is needed -> make 'debugMode = true' inside main.cpp file inside src folder.
4. Compilation : g++ src/main.cpp src/parser.cpp src/interpreter.cpp src/utils.cpp src/analyzer.cpp -Iinclude -o build/asm.exe
5. Run : .\build\asm.exe
