#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>

#include <iostream>
#include <string>

using namespace cv;
using namespace std;

/*  Code by Di Zhu  */

int main()
{
	Mat source;
	source = imread("Face_adjusted.jpg", IMREAD_COLOR); 

	if (source.empty())                    
	{
		cout << "Could not open or find the image" << std::endl;
		return 0;
	}

	int rows = source.rows;
	int cols = source.cols;

	//greyscale
	/*
	Mat_<Vec3b>::iterator it = source.begin<Vec3b>();  //iterate the image
	while (it != source.end<Vec3b>())
	{
		int grey = ((*it)[0] + (*it)[1] + (*it)[2]) / 3;
		(*it)[0] = grey;    //Blue channel
		(*it)[1] = grey;    //Green channel
		(*it)[2] = grey;    //Red channel
		it++;
	}
	*/

	imwrite("greyscale.jpg", source);

	//flip
	Mat flipped = Mat(rows, cols, CV_8UC3);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			flipped.at<Vec3b>(i, j) = source.at<Vec3b>(rows - i - 1, j);
		}
	}
	source = flipped.clone();
	imwrite("flipped.jpg", source);
	

	//Third way, thresholding
	/* Doesn't work properly, maybe I should partition the image first.
	for (int i = 0; i < rows; i++)
	{
		uchar *p = source.ptr<uchar>(i);
		for (int j = 0; j < cols; j++)
		{
			if (p[j] > 100) p[j] = 255;
			else p[j] = 0;
		}
	}
	*/

	// Another method
	Mat_<Vec3b>::iterator it2 = source.begin<Vec3b>(); //iterate the image
	while (it2 != source.end<Vec3b>())
	{
		int grey = ((*it2)[0] + (*it2)[1] + (*it2)[2]) / 3;
		if (grey > 100)
		{
			(*it2)[0] = 255; 
			(*it2)[1] = 255; 
			(*it2)[2] = 255; 
		} 
		else
		{
			(*it2)[0] = 0;
			(*it2)[1] = 0;
			(*it2)[2] = 0;
		}
		it2++;
	}

	imwrite("final.jpg", source);
	return 0;
}