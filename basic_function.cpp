#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


/* Basic function on Opencv */
/* Brightness, Contrast, Histogram, Erode, Dilatation */


int main(int argc, char** argv)
{
	// Read the image file
	cv::Mat image = cv::imread("../lena.jpg");
	// Check for failure
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cv::String windowName = "Lena"; //Name of the window
	namedWindow(windowName); // Create a window
	cv::imshow(windowName, image); // Show our image inside the created window.

	cv::waitKey(0); // Wait for any keystroke in the window
	destroyWindow(windowName); //destroy the created window

	// Change the brightness

	cv::Mat imageBrighnessHigh50;
	image.convertTo(imageBrighnessHigh50, -1, 1, 50); //increase the brightness by 50

	cv::Mat imageBrighnessHigh100;
	image.convertTo(imageBrighnessHigh100, -1, 1, 100); //increase the brightness by 100

	cv::Mat imageBrighnessLow50;
	image.convertTo(imageBrighnessLow50, -1, 1, -50); //decrease the brightness by 50

	cv::Mat imageBrighnessLow100;
	image.convertTo(imageBrighnessLow100, -1, 1, -100); //decrease the brightness by 100

	//Defining window names for above images

	cv::String windowNameOriginalImage = "Original Image";
	cv::String windowNameBrightnessHigh50 = "Brightness Increased by 50";
	cv::String windowNameWithBrightnessHigh100 = "Brightness Increased by 100";
	cv::String windowNameBrightnessLow50 = "Brightness Decreased by 50";
	cv::String windowNameBrightnessLow100 = "Brightness Decreased by 100";

	//Create and open windows for above images
	namedWindow(windowNameOriginalImage);
	namedWindow(windowNameBrightnessHigh50);
	namedWindow(windowNameWithBrightnessHigh100);
	namedWindow(windowNameBrightnessLow50);
	namedWindow(windowNameBrightnessLow100);


	//Show above images inside the created windows.
	imshow(windowNameOriginalImage, image);
	imshow(windowNameBrightnessHigh50, imageBrighnessHigh50);
	imshow(windowNameWithBrightnessHigh100, imageBrighnessHigh100);
	imshow(windowNameBrightnessLow50, imageBrighnessLow50);
	imshow(windowNameBrightnessLow100, imageBrighnessLow100);

	cv::waitKey(0); // Wait for any key stroke
	cv::destroyAllWindows(); //destroy all open windows

	//Change the contrast

	cv::Mat imageContrastHigh2;
	image.convertTo(imageContrastHigh2, -1, 2, 0); //increase the contrast by 2

	cv::Mat imageContrastHigh4;
	image.convertTo(imageContrastHigh4, -1, 4, 0); //increase the contrast by 4

	cv::Mat imageContrastLow0_5;
	image.convertTo(imageContrastLow0_5, -1, 0.5, 0); //decrease the contrast by 0.5

	cv::Mat imageContrastLow0_25;
	image.convertTo(imageContrastLow0_25, -1, 0.25, 0); //decrease the contrast by 0.25


	//Defining window names for above images
	
	cv::String windowNameContrastHigh2 = "Contrast Increased by 2";
	cv::String windowNameContrastHigh4 = "Contrast Increased by 4";
	cv::String windowNameContrastLow0_5 = "Contrast Decreased by 0.5";
	cv::String windowNameContrastLow0_25 = "Contrast Decreased by 0.25";

	//Create and open windows for above images
	namedWindow(windowNameOriginalImage);
	namedWindow(windowNameContrastHigh2);
	namedWindow(windowNameContrastHigh4);
	namedWindow(windowNameContrastLow0_5);
	namedWindow(windowNameContrastLow0_25);

	//Show above images inside the created windows.
	imshow(windowNameOriginalImage, image);
	imshow(windowNameContrastHigh2, imageContrastHigh2);
	imshow(windowNameContrastHigh4, imageContrastHigh4);
	imshow(windowNameContrastLow0_5, imageContrastLow0_5);
	imshow(windowNameContrastLow0_25, imageContrastLow0_25);

	cv::waitKey(0); // Wait for any key stroke
	cv::destroyAllWindows(); //destroy all open windows

	//Histogram grayscale
	cv::Mat image3;
	//change the color image to grayscale image
	cv::cvtColor(image, image3, cv::COLOR_BGR2GRAY);

	//equalize the histogram
	cv::Mat hist_equalized_image;
	equalizeHist(image3, hist_equalized_image);

	//Define names of windows
	cv::String windowNameOfOriginalImage = "Original Image";
	cv::String windowNameOfHistogramEqualized = "Histogram Equalized Image";

	// Create windows with the above names
	namedWindow(windowNameOfOriginalImage);
	namedWindow(windowNameOfHistogramEqualized);

	// Show images inside created windows.
	imshow(windowNameOfOriginalImage, image3);
	imshow(windowNameOfHistogramEqualized, hist_equalized_image);

	cv::waitKey(0); // Wait for any keystroke in one of the windows

	cv::destroyAllWindows(); //Destroy all open windows

	//Histogram color

	 //Convert the image from BGR to YCrCb color space
	cv::Mat hist_equalized_image2;
	cv::cvtColor(image, hist_equalized_image2, cv::COLOR_BGR2YCrCb);

	//Split the image into 3 channels; Y, Cr and Cb channels respectively and store it in a std::vector
	std::vector<cv::Mat> vec_channels;
	split(hist_equalized_image2, vec_channels);


	//Equalize the histogram of only the Y channel 
	equalizeHist(vec_channels[0], vec_channels[0]);

	//Merge 3 channels in the vector to form the color image in YCrCB color space.
	merge(vec_channels, hist_equalized_image2);

	//Convert the histogram equalized image from YCrCb to BGR color space again
	cvtColor(hist_equalized_image2, hist_equalized_image2, cv::COLOR_YCrCb2BGR);

	//Define the names of windows
	//String windowNameOfOriginalImage = "Original Image";
	cv::String windowNameOfHistogramEqualized2 = "Histogram Equalized Color Image";

	// Create windows with the above names
	namedWindow(windowNameOfOriginalImage);
	namedWindow(windowNameOfHistogramEqualized2);

	// Show images inside the created windows.
	imshow(windowNameOfOriginalImage, image);
	imshow(windowNameOfHistogramEqualized2, hist_equalized_image2);

	cv::waitKey(0); // Wait for any keystroke in any one of the windows


	//Erode

	//Erode the image with 3x3 kernel
	cv::Mat image_eroded_with_3x3_kernel;
	cv::erode(image, image_eroded_with_3x3_kernel, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));

	//Erode the image with 5x5 kernel
	cv::Mat image_eroded_with_5x5_kernel;
	cv::erode(image, image_eroded_with_5x5_kernel, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));

	//Define names of the windows
	//cv::String window_name = "Lotus";
	cv::String window_name_eroded_with_3x3_kernel = "Lotus eroded with 3 x 3 kernel";
	cv::String window_name_eroded_with_5x5_kernel = "Lotus eroded with 5 x 5 kernel";

	// Create windows with above names
	namedWindow(windowName);
	namedWindow(window_name_eroded_with_3x3_kernel);
	namedWindow(window_name_eroded_with_5x5_kernel);

	// Show our images inside the created windows.
	imshow(windowName, image);
	imshow(window_name_eroded_with_3x3_kernel, image_eroded_with_3x3_kernel);
	imshow(window_name_eroded_with_5x5_kernel, image_eroded_with_5x5_kernel);

	cv::waitKey(0); // Wait for any keystroke in the window

	cv::destroyAllWindows(); //Destroy all opened windows

	//Dilatation

	//Dilate the image with 3x3 kernel
	cv::Mat image_dilated_with_3x3_kernel;
	cv::dilate(image, image_dilated_with_3x3_kernel, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3)));

	//Dilate the image with 5x5 kernel
	cv::Mat image_dilated_with_5x5_kernel;
	cv::dilate(image, image_dilated_with_5x5_kernel, cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5, 5)));

	//Define names of the windows
	//cv::String window_name = "Lotus";
	cv::String window_name_dilated_with_3x3_kernel = "Lotus dilated with 3 x 3 kernel";
	cv::String window_name_dilated_with_5x5_kernel = "Lotus dilated with 5 x 5 kernel";

	// Create windows with above names
	namedWindow(windowNameOfOriginalImage);
	namedWindow(window_name_dilated_with_3x3_kernel);
	namedWindow(window_name_dilated_with_5x5_kernel);

	// Show our images inside the created windows.
	imshow(windowNameOfOriginalImage, image);
	imshow(window_name_dilated_with_3x3_kernel, image_dilated_with_3x3_kernel);
	imshow(window_name_dilated_with_5x5_kernel, image_dilated_with_5x5_kernel);

	cv::waitKey(0); // Wait for any keystroke in the window

	cv::destroyAllWindows(); //Destroy all opened windows


	cv::Mat image_dilate_minus_erode_with_3x3_kernel = image_dilated_with_3x3_kernel - image_eroded_with_3x3_kernel;
	cv::Mat image_dilate_minus_erode_with_5x5_kernel = image_dilated_with_5x5_kernel - image_eroded_with_5x5_kernel;

	//Define names of the windows
	//cv::String window_name = "Lotus";
	cv::String window_name_dilate_minus_erode_with_3x3_kernel = "Bird edge with 3 x 3 kernel";
	cv::String window_name_dilate_minus_erode_with_5x5_kernel = "Bird edge with 5 x 5 kernel";

	// Create windows with above names
	namedWindow(windowNameOfOriginalImage);
	namedWindow(window_name_dilate_minus_erode_with_3x3_kernel);
	namedWindow(window_name_dilate_minus_erode_with_3x3_kernel);

	// Show our images inside the created windows.
	imshow(windowNameOfOriginalImage, image);
	imshow(window_name_dilate_minus_erode_with_3x3_kernel, image_dilate_minus_erode_with_3x3_kernel);
	imshow(window_name_dilate_minus_erode_with_5x5_kernel, image_dilate_minus_erode_with_5x5_kernel);

	cv::waitKey(0); // Wait for any keystroke in the window
	cv::destroyAllWindows(); //Destroy all opened windows

	return 0;
}
