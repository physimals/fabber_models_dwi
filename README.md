# DWI Models

This project includes popular diffusion models for analysis of diffusion weighted 
MRI images in the FABBER framework

Two models are currently included 
1.  The monoexponential decay (`dwi`)
2.  The Intra Voxel Incoherent Motion (`dwi_IVIM`)     

Command line example

    fabber_dwi --output=/home/fsl/Desktop/Data_out/Data
    --data=/home/fsl/Desktop/Data/DWI.nii
    --mask=/home/fsl/Desktop/Data/mask_DWI.nii
    --method=vb
    --model=dwi
    --noise=white 
    --data-order=singlefile 
    --save-model-fit 
    --bvals=/home/fsl/Desktop/Data/bvals.dat

Command line example combining spatial variationel Bayes and motion correction

    fabber_dwi --output=/home/fsl/Desktop/Data_out/Data_dwi 
    --data=/home/fsl/Desktop/Data/DWI_motion.nii 
    --mask=/home/fsl/Desktop/Data/mask_DWI.nii 
    --method=spatialvb 
    --model=dwi 
    --noise=white 
    --data-order=singlefile 
    --save-model-fit 
    --bvals=/home/fsl/Desktop/Data/bvals.dat 
    --param-spatial-priors=MN 
    --mcsteps=2
    
# Building the DWI models

The current version of the DWI models are designed to build with the latest 
version of Fabber. Although it should be possible to build them against FSL 5.0 
you may need to edit the source slightly. So your first step should be to build 
[fabber_core](https://ibme-gitcvs.eng.ox.ac.uk/fabber/fabber_core) from Git. 
Build instructions for fabber_core are in the Wiki on its Git page. 

You will make the process straightforward if you create a directory (e.g. 
'fabber') and download the Git repositories for fabber_core and fabber_models_dwi
into this directory. Then the model build should be able to find the Fabber 
libraries without you having to install them or tell the build scripts where 
they are.

### Building in a standard FSL environment

The process should be:

    source $FSLDIR/etc/fslconf/fsl-devel.sh
    make

This will produce an executable `fabber_dwi`.

### Building with non-standard FSL

In this case we can use the cross-platform `cmake` system. Convenience scripts
are provided, so the build should be:

    scripts/build.sh relwithdebinfo
    
This creates a release build (fully optimized) but including debugging symbols
so crashes can be traced. The output is in the `build_relwithdebinfo` directory
and will include the executable `fabber_dwi` as well as a shared library
(e.g. `libfabber_models_dwi.so` on Linux)

#### It failed with something about `recompile with -fPIC`

Short answer: if you were using the `cmake` build method, try the `standard
FSL environment` method.

You can also go into the build directory and just build the executable:

    cd build_relwithdebinfo
    make fabber_dwi
    
Long answer: In order to build the shared library, the FSL libraries have to 
contain 'Position-independent code'. If they don't you can't build the library 
and will need to use the fabber_dwi executable instead. The only way around 
this is to recompile the FSL libraries with the -fPIC flag which you can
do using the CMake-enabled code [here](https://ibme-gitcvs.eng.ox.ac.uk/fsl/fsl).
It's not worth doing this unless you really need the shared library.

## Successful build?

You can verify that the DWI models are available whichever method you choose:

    fabber_dwi --listmodels
    
    dwi
    dwi_IVIM
    linear
    poly

or if you used cmake and built the shared library, you can also do:

    fabber --loadmodels=libfabber_models_dwi.so --listmodels
    
    dwi
    dwi_IVIM
    linear
    poly
