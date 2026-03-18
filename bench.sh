#!/bin/bash

echo "Building CppSudoku"
xmake f -P CppSudoku -m release
xmake build -P CppSudoku

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
"CppSudoku/build/release/CppSudoku" \
"RustSudoku/target/release/rust_sudoku" \
"GoSudoku/GoSudoku" \
"node JsSudoku/." \
"dotnet CSharpSudoku/bin/release/net7.0/CSharpSudoku.dll" \
"python3 PySudoku/main.py" 

exit 0
