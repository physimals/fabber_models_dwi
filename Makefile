include ${FSLCONFDIR}/default.mk

PROJNAME = fabber_dwi
LIBS = -lfsl-fabbermodels_dwi -lfsl-fabberexec -lfsl-fabbercore \
       -lfsl-newimage -lfsl-miscmaths -lfsl-utils -lfsl-cprob \
       -lfsl-NewNifti -lfsl-znz -ldl
XFILES = fabber_dwi
SOFILES = libfsl-fabbermodels_dwi.so

# Forward models
OBJS =  fwdmodel_dwi.o fwdmodel_dwi_IVIM.o

# For debugging:
#OPTFLAGS = -ggdb

# Pass Git revision details
GIT_SHA1:=$(shell git describe --match=NeVeRmAtCh --always --abbrev=40 --dirty)
GIT_DATE:=$(shell git log -1 --format=%ad --date=local)
CXXFLAGS += -DGIT_SHA1=\"${GIT_SHA1}\" -DGIT_DATE="\"${GIT_DATE}\""

all: ${XFILES} ${SOFILES}

# models in a library
libfsl-fabbermodels_dwi.so : ${OBJS}
	${CXX} ${CXXFLAGS} -shared -o $@ $^

# fabber built from the FSL fabbercore library including the models specifieid in this project
fabber_dwi : fabber_client.o libfsl-fabbermodels_dwi.so
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}

# DO NOT DELETE
