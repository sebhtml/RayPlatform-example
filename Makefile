MPICXX=mpicxx

J=1

all:
	# compile the application
	$(MPICXX) program.cpp -c -o program.o -I . -I RayPlatform
	$(MPICXX) Test.cpp -c -o Test.o -I . -I RayPlatform
	$(MPICXX) Test_adapters.cpp -c -o Test_adapters.o -I . -I RayPlatform

	# compile the platform
	cd RayPlatform; make -j $(J)
	
	# link them
	$(MPICXX) program.o Test.o Test_adapters.o RayPlatform/libRayPlatform.a -o program

clean:
	rm *.o program
	cd RayPlatform; make clean

