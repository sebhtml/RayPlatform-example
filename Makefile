MPICXX=mpicxx

DIRECTORY := $(shell pwd)

RAY_APPLICATION_SCRIPTS=$(DIRECTORY)/scripting
RAY_PLATFORM=$(DIRECTORY)/RayPlatform
J=1

all:
	echo $(DIRECTORY)

	# compile the application
	$(MPICXX) program.cpp -c -o program.o -I . -I $(RAY_APPLICATION_SCRIPTS) -I $(RAY_PLATFORM)

	# compile the platform
	cd $(RAY_PLATFORM); make clean; make CXXFLAGS="-O3 -g -D ASSERT" RAY_APPLICATION_SCRIPTS=$(RAY_APPLICATION_SCRIPTS) -j $(J)
	
	# link them
	$(MPICXX) program.o $(RAY_PLATFORM)/libRayPlatform.a -o program
