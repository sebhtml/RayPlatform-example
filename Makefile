MPICXX=mpicxx

J=1

all:
	# compile the application
	$(MPICXX) distributedApplication.cpp -c -o distributedApplication.o -I . -I RayPlatform -g
	$(MPICXX) TestPlugin.cpp -c -o TestPlugin.o -I . -I RayPlatform -g

	# compile the platform
	cd RayPlatform; make -j $(J) CXXFLAGS=" -g "
	
	# link them
	$(MPICXX) distributedApplication.o TestPlugin.o RayPlatform/libRayPlatform.a -o distributedApplication -g

clean:
	rm *.o distributedApplication -rf
	cd RayPlatform; make clean

