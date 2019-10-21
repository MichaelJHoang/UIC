#pragma once
#ifndef PPMVIEWERH
#define PPMVIEWERH

// CUDA libraries used for this project
#include <curand_kernel.h>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#ifdef GLUT_fileCheck
#include <GLUT/glut.h>
#else
#include <GL\glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

GLubyte* fb;

int width = 0, height = 0;

void ReadPPM(char* filename)
{
	int color = 0;
	int numComponents = 0;
	char buffer[50];

	FILE
}

#endif // !PPMVIEWERH
