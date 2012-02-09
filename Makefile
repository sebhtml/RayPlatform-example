MPICXX=mpicxx

J=1

all:
	# compile the application
	$(MPICXX) program.cpp -c -o program.o -I . -I RayPlatform -g
	$(MPICXX) Test.cpp -c -o Test.o -I . -I RayPlatform -g
	$(MPICXX) Test_adapters.cpp -c -o Test_adapters.o -I . -I RayPlatform -g

	# compile the platform
	cd RayPlatform; make -j $(J) CXXFLAGS=" -g "
	
	# link them
	$(MPICXX) program.o Test.o Test_adapters.o RayPlatform/libRayPlatform.a -o program -g

clean:
	rm *.o program -rf
	cd RayPlatform; make clean

