@echo off
echo ==============================================
echo Building WebAssembly Module for React Frontend
echo ==============================================

if not exist "public" mkdir public

echo Compiling C++ to WASM...
call emcc wasm/wasm_decoder.cpp -o public/decoder.js -O3 --bind -s WASM=1 -s EXPORT_NAME="Module" -s EXPORTED_RUNTIME_METHODS="['_malloc', '_free']"

echo.
echo Installing React Dependencies...
call npm install

echo.
echo Starting React Dev Server...
call npm run dev
