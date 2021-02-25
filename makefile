build_dir := ./build
target_name := algorithm
all: execute

run_cmake:
	cd ${build_dir};  \
	cmake ../ ; 
compile: run_cmake
	cd ${build_dir};  make;
execute: compile
	cd ${build_dir}; ./${target_name}

clean:
	rm -rf ./build/*