
build_dir := ./build
target_name := algorithm
all: run_cmake run_make execute

run_cmake:
	cd ${build_dir};  \
	cmake ../ ; 
run_make:
	cd ${build_dir};  make;
execute:
	cd ${build_dir}; ./${target_name}