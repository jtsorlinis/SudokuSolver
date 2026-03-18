target("CPPSudoku")
set_kind("binary")
add_files("main.cpp")
set_targetdir("./build/bin")

-- Optimization settings
set_optimize("fastest")
set_policy("build.optimization.lto", true)