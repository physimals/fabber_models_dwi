/*   dwi_models.h Models for diffusion weighted MRI images

 Michael Chappell - IBME & FMRIB Image Analysis Group

 Copyright (C) 2010-2011 University of Oxford */

/*   CCOPYRIGHT   */
#pragma once

#include "fabber_core/fwdmodel.h"

using namespace MISCMATHS;

#ifdef _WIN32
#ifdef fabber_dwi_EXPORTS
#define DLLAPI __declspec(dllexport)
#else
#define DLLAPI __declspec(dllimport)
#endif
#define CALL __stdcall
#else
#define DLLAPI
#define CALL
#endif

extern "C" {
DLLAPI int CALL get_num_models();
DLLAPI const char *CALL get_model_name(int index);
DLLAPI NewInstanceFptr CALL get_new_instance_func(const char *name);
}
