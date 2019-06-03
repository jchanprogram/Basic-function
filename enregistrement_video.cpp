#include <stdio.h>
#include <math.h>
#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


int main(int argc, char** argv)
{

	////////////////////////////////////////////////////////////////////
	//                                                                //
	//                         Save Video                             //
	//                                                                //
	////////////////////////////////////////////////////////////////////

	cv::VideoCapture cap(0);
	cv::String path_save = "../save_video/";
	cv::String name_film = "film.avi";

	// if not success, exit program
	if (cap.isOpened() == false)
	{
		std::cout << "Cannot open the video camera" << std::endl;
		std::cin.get(); //wait for any key press
		return -1;
	}

	int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH)); //get the width of frames of the video
	int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT)); //get the height of frames of the video

	cv::Size frame_size(frame_width, frame_height);
	int frames_per_second = 10;

	//Create and initialize the VideoWriter object 
	cv::VideoWriter VideoWrite(path_save + name_film, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'),
		frames_per_second, frame_size, true);

	/*

fourcc - 4-character code of the codec which is used to compress the video.
The complete list of codes can be found in this page.
But most of the codecs listed in this page might not work in your computer. These are some popular codecs which might work for you.

	VideoWriter::fourcc('P', 'I', 'M', '1') for MPEG-1
	VideoWriter::fourcc('M', 'J', 'P', 'G') for Motion JPEG
	VideoWriter::fourcc('M', 'P', '4', '2') for MPEG-4 variation of Microsof
	*/

	//If the VideoWriter object is not initialized successfully, exit the program
	if (VideoWrite.isOpened() == false)
	{
		std::cout << "Cannot save the video to a file" << std::endl;
		std::cin.get(); //wait for any key press
		return -1;
	}

	cv::String window_name_video = "My Camera Feed";
	namedWindow(window_name_video); //create a window called "My Camera Feed"

	while (true)
	{
		cv::Mat frame;
		bool isSuccess = cap.read(frame); // read a new frame from the video camera

		//Breaking the while loop if frames cannot be read from the camera
		if (isSuccess == false)
		{
			std::cout << "Video camera is disconnected" << std::endl;
			std::cin.get(); //Wait for any key press
			break;
		}


		//write the video frame to the file
		VideoWrite.write(frame);

		//show the frame in the created window
		imshow(window_name_video, frame);

		
		//If the 'Esc' key is pressed, break the while loop.
		//If any other key is pressed, continue the loop 
		if (cv::waitKey(10) == 27)
		{
			std::cout << "Esc key is pressed by the user. Stopping the video" << std::endl;
			break;
		}
	}

	//Flush and close the video file
	VideoWrite.release();
	cv::destroyAllWindows(); //destroy the created window

	return 0;
}
