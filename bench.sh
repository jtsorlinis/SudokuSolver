#!/bin/bash

echo "Building CppSudoku"
xmake -P CppSudoku

echo "Building CSharpSudoku"
cd CSharpSudoku
dotnet build -c release
cd ..

echo "Building GoSudoku"
cd GoSudoku
go build
cd ..

echo "Building RustSudoku"
cd RustSudoku
cargo build --release
cd ..

hyperfine --warmup 3 --export-markdown results_$num.md \
"CppSudoku/build/bin/CPPSudoku" \
"RustSudoku/target/release/rust_sudoku" \
"GoSudoku/GoSudoku" \
"node JsSudoku/." \
"bun JsSudoku/." \
"dotnet CSharpSudoku/bin/release/net10.0/CSharpSudoku.dll" \
"python3 PySudoku/main.py" 

exit 0
