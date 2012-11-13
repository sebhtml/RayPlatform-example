MPICXX=mpicxx
J=1
MAKE=make

all:
	# compile the application
	$(MPICXX) distributedApplication.cpp -c -o distributedApplication.o -I . -I RayPlatform -g
	$(MPICXX) Application.cpp -c -o Application.o -I . -I RayPlatform -g
	$(MPICXX) TestPlugin.cpp -c -o TestPlugin.o -I . -I RayPlatform -g

	# compile the platform
	cd RayPlatform; $(MAKE) $(MFLAGS)
	
	# link them
	$(MPICXX) distributedApplication.o TestPlugin.o Application.o RayPlatform/libRayPlatform.a -o distributedApplication -g

clean:
	rm *.o distributedApplication -rf
	cd RayPlatform; make clean

test:
	mpiexec -n 4 ./distributedApplication
