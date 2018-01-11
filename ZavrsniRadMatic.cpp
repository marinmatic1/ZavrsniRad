#define _USE_MATH_DEFINES
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include "CImg.h"
#include<cmath>


using namespace std;
using namespace cimg_library;
struct matrica {
	int rows;
	int cols;
	
};

void createFilter(double **gKernel)
{
	double sigma = 1;
	double r, s =1 * sigma * sigma;

	double sum = 0.0;

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			r = sqrt(x*x + y*y);
			gKernel[x + 1][y + 1] = (exp(-(r*r) / s)) / (M_PI * s);
			sum += gKernel[x + 1][y + 1];
		}
	}

		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				gKernel[i][j] /= sum;

}
void Konvolucija(float **sImg, double **gKernel, matrica mat1)
{
	double sum = 0.0;
	for (int i = 1; i <mat1.rows-1; i++)
	{
		for (int j = 1; j < mat1.cols-1; j++)
		{
			double sum = 0.0;
			for (int n = -1; n <=1; n++)
			{
				for (int m = -1; m <= 1; m++)
				{
					sum += (double)sImg[i+n][j+m]*gKernel[n+1][m+1];
				}
			}
			sImg[i][j] = sum;
		}
	}
}
int main()
{
	
	CImg<float> image("fpmoz01.pgm");

	int rows = image.height();
	int cols = image.width();

	int size = image.size();  
	float **sImg;
		sImg = new float*[rows];
	for (int i = 0; i<rows; i++)
		sImg[i] = new float[cols];

	for (int i = 0; i<rows; i++)
		for (int j = 0; j<cols; j++)
		{
			sImg[i][j] = image(i*cols + j);
		}
	matrica mat1;
	mat1.rows = rows;
	mat1.cols = cols;
	
	int N = 3;
	double **gKernel;
	gKernel = new double*[N];
	for (int i = 0; i < N; i++)
	{
		gKernel[i] = new double[N];
	}
	createFilter(gKernel);
	
	Konvolucija(sImg, gKernel, mat1);
	
	CImg<float> outImg(cols, rows);
	for (int i = 0; i<rows; i++)
	{
		for (int j = 0; j<cols; j++)
		{
			outImg(i*cols + j) = sImg[i][j];
		}
	}
	outImg.save("outImg.bmp");
	return 0; 
	}
