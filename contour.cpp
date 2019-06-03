#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


int main(int argc, char** argv)
{
	// Read the image file
	cv::Mat image = cv::imread("../lena.png");

	// Check for failure
	if (image.empty())
	{
		std::cout << "Could not open or find the image" << std::endl;
		cv::waitKey(0); //wait for any key press
		return -1;
	}
	
	//Name of the window
	cv::String windowName = "Original Image";
	// Create a window
	namedWindow(windowName); 
	// Show our image inside the created window.
	cv::imshow(windowName, image); 

 	//Edge detection by using Canny detection

	int lowThreshold = 75;
	const int ratio = 3;
	const int kernel_size = 3;

	cv::Mat image_canny;
	cv::Mat image_blur;
	cv::Mat image_canny_blur;

	blur(image, image_blur, cv::Size(5, 5));

	Canny(image_blur, image_canny_blur, lowThreshold, lowThreshold*ratio, kernel_size);
	Canny(image, image_canny, lowThreshold, lowThreshold*ratio, kernel_size);

	cv::String windowNameContourBlur = "Contour blur Lena"; //Name of the window
	cv::String windowNameContour = "Contour Lena "; //Name of the window
	cv::String windowNameBlur = "Blur Lena "; //Name of the window

	namedWindow(windowNameContourBlur); // Create a window
	namedWindow(windowNameContour); // Create a window
	namedWindow(windowNameBlur); // Create a window

	cv::imshow(windowNameContourBlur, image_canny_blur);
	cv::imshow(windowNameContour, image_canny);
	cv::imshow(windowNameBlur, image_blur);

	cv::waitKey(0); // Wait for any keystroke in the window

	cv::destroyAllWindows();

	//Open a video file for reading
	cv::VideoCapture cap("../movie.mp4");

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		std::cout << "Cannot open the video file" << std::endl;
		std::cin.get(); //wait for any key press
		return -1;
	}


	//Get the frames rate of the video
	double fps = cap.get(cv::CAP_PROP_FPS);
	std::cout << "Frames per seconds : " << fps << std::endl;

	cv::String window_name_video = "My Video";

	namedWindow(window_name_video, cv::WINDOW_NORMAL); //create a window not resized

	while (true)
	{
		cv::Mat frame;
		bool bSuccess = cap.read(frame); // read a new frame from video 

		//Breaking the while loop at the end of the video
		if (bSuccess == false)
		{
			std::cout << "Found the end of the video" << std::endl;
			break;
		}

		//show the frame in the created window

		cv::Mat frame_blur;
		cv::Mat frame_canny_blur;
		cv::Mat frame_canny;
		blur(frame, frame_blur, cv::Size(3, 3));

		Canny(frame, frame_canny, lowThreshold, lowThreshold*ratio, kernel_size);

		cv::String windowNameContourBlur = "Contour blur video"; //Name of the window
		cv::String windowNameContour = "Contour video "; //Name of the window
		cv::String windowNameBlur = "Blur video "; //Name of the window

		namedWindow(windowNameContourBlur, cv::WINDOW_NORMAL); // Create a window
		namedWindow(windowNameContour, cv::WINDOW_NORMAL); // Create a window
		namedWindow(windowNameBlur, cv::WINDOW_NORMAL); // Create a window

		cv::imshow(windowNameContour, frame_canny);
		
		//If the 'Esc' key is pressed, break the while loop.
		//If the any other key is pressed, continue the loop 
		//If any key is not pressed withing 10 ms, continue the loop

		if (cv::waitKey(10) == 27)
		{
			std::cout << "Esc key is pressed by user. Stoppig the video" << std::endl;
			break;
		}
	}



	cv::waitKey(0); // Wait for any keystroke in the window

	cv::destroyAllWindows();

	return 0;

}
