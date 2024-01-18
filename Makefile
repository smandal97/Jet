
INITIAL  = bondi_ss
HYDRO    = euler_sph
GEOMETRY = spherical
BOUNDARY = polar
RIEMANN  = hllc
TIMESTEP = rk2
OUTPUT   = ascii
RESTART  = no_restart

UNAME = $(shell uname)
ifeq ($(UNAME),Linux)
H55 = /apps/spack/bell/apps/hdf5/1.8.21-intel-19.0.5-o3n4r6z
endif
ifeq ($(UNAME),Darwin)
H55 = /opt/homebrew/opt/hdf5
endif

CC = mpicc
FLAGS = -O3 -Wall -g

INC = -I$(H55)/include
LIB = -L$(H55)/lib

OBJ = main.o readpar.o onestep.o exchange.o plm.o domain.o faces.o cooling.o nozzle.o gravity.o misc.o mpisetup.o gridsetup.o $(RIEMANN).o $(TIMESTEP).o $(INITIAL).o $(HYDRO).o $(GEOMETRY).o $(BOUNDARY).o $(OUTPUT).o snapshot.o report.o $(RESTART).o profiler.o

default: jet

%.o: %.c paul.h
	$(CC) $(FLAGS) $(INC) -c $<

$(RIEMANN).o: Riemann/$(RIEMANN).c paul.h
	$(CC) $(FLAGS) $(INC) -c Riemann/$(RIEMANN).c

$(TIMESTEP).o: Timestep/$(TIMESTEP).c paul.h
	$(CC) $(FLAGS) $(INC) -c Timestep/$(TIMESTEP).c

$(INITIAL).o : Initial/$(INITIAL).c paul.h
	$(CC) $(FLAGS) $(INC) -c Initial/$(INITIAL).c

$(HYDRO).o : Hydro/$(HYDRO).c paul.h
	$(CC) $(FLAGS) $(INC) -c Hydro/$(HYDRO).c

$(GEOMETRY).o : Geometry/$(GEOMETRY).c paul.h
	$(CC) $(FLAGS) $(INC) -c Geometry/$(GEOMETRY).c

$(BOUNDARY).o : Boundary/$(BOUNDARY).c paul.h
	$(CC) $(FLAGS) $(INC) -c Boundary/$(BOUNDARY).c

$(OUTPUT).o : Output/$(OUTPUT).c paul.h
	$(CC) $(FLAGS) $(INC) -c Output/$(OUTPUT).c

$(RESTART).o : Restart/$(RESTART).c paul.h
	$(CC) $(FLAGS) $(INC) -c Restart/$(RESTART).c

jet: $(OBJ) paul.h
	$(CC) $(FLAGS) $(LIB) -o jet $(OBJ) -lm -lhdf5

clean:
	rm -f *.o *.dat jet
