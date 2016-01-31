This project includes popular diffusion models for analysis of diffusion weighted MRI images in the FABBER framework

Two models are currently included 
1.  The monoexponential decay ("dwi")
2.  The Intra Voxel Incoherent Motion ("dwi_IVIM")     

Command line example
--output=/home/fsl/Desktop/Data_out/Data
--data=/home/fsl/Desktop/Data/DWI.nii
--mask=/home/fsl/Desktop/Data/mask_DWI.nii
--method=vb
--model=dwi
--noise=white 
--data-order=singlefile 
--save-model-fit 
--bvals=/home/fsl/Desktop/Data/bvals.dat