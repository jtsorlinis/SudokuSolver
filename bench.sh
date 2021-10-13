#!/bin/bash

echo "Building CPPSudoku"
cd CPPSudoku
mkdir -p build
cd build
cmake ..
make
cd ../..

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
"CPPSudoku/build/CPPSudoku" \
"RustSudoku/target/release/rust_sudoku" \
"GoSudoku/GoSudoku" \
"node JsSudoku/." \
"dotnet CSharpSudoku/bin/release/net5.0/CSharpSudoku.dll" \
"pypy3 PySudoku/main.py" \
"python3 PySudoku/main.py" 

exit 0