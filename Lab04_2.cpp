// Example 9-2. Toy program for using a mouse to draw boxes on the screen
#include <opencv2/opencv.hpp>



cv::Scalar sColour = cv::Scalar(255, 255, 255);


// Define our callback which we will install for
// mouse events
//
void my_mouse_callback(
	int event, int x, int y, int flags, void* param
);
cv::Rect box;
bool drawing_box = false;
bool drawing_circle = false;


// A little subroutine to draw a box onto an image
//
void draw_box(cv::Mat& img, cv::Rect box, cv::Scalar color) {


	cv::rectangle(
		img,
		box.tl(),
		box.br(),
		color
	);
}




void help(char** argv) {
	std::cout << "Example 9-2. Toy program for using a mouse to draw boxes on the screen"
		<< "\nCall:\n" << argv[0] <<
		"\n\nshows how to use a mouse to draw regions in an image. Esc to quit\n" << std::endl;
}


void selectColor() {

	char colour;
	std::cout << "Please enter a letter that corresponds to a colour: " << std::endl;
	std::cout << "  k: black" << std::endl;
	std::cout << "  w: white" << std::endl;
	std::cout << "  r: red" << std::endl;
	std::cout << "  g: green" << std::endl;
	std::cout << "  b: blue" << std::endl;
	std::cout << "  c: cyan" << std::endl;
	std::cout << "  y: yellow" << std::endl;
	std::cout << "  m: magenta" << std::endl;
	std::cout << "  x: random" << std::endl;

	std::cout << "Choice: ";
	std::cin >> colour;

	if (colour == 'k') sColour = cv::Scalar(0, 0, 0);
	else if (colour == 'w') sColour = cv::Scalar(255, 255, 255);
	else if (colour == 'r') sColour = cv::Scalar(0, 0, 255);
	else if (colour == 'g') sColour = cv::Scalar(0, 255, 0);
	else if (colour == 'b') sColour = cv::Scalar(255, 0, 0);
	else if (colour == 'c') sColour = cv::Scalar(255, 255, 0);
	else if (colour == 'y') sColour = cv::Scalar(0, 255, 255);
	else if (colour == 'm') sColour = cv::Scalar(255, 0, 255);
	else if (colour == 'x') sColour = cv::Scalar(rand() % 256, rand() % 256, rand() % 256);
	else sColour = cv::Scalar(rand() % 256, rand() % 256, rand() % 256);

}



int main(int argc, char** argv) {
	help(argv);
	box = cv::Rect(-1, -1, 0, 0);
	cv::Mat image(480, 640, CV_8UC3), temp;
	image.copyTo(temp);
	box = cv::Rect(-1, -1, 0, 0);
	image = cv::Scalar::all(0);

	selectColor();

	cv::namedWindow("Box Example");
	cv::moveWindow("Box Example", 10, 30);

	// Here is the crucial moment where we actually install
   // the callback. Note that we set the value of 'params' to
   // be the image we are working with so that the callback
   // will have the image to edit.
   //
	cv::setMouseCallback(
		"Box Example",
		my_mouse_callback,
		(void*)&image
	);




	//My Drawing Application
	cv::String text = "My Drawing Application";
	int fontFace = cv::FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 1;
	int thickness = 1;

	int baseline = 0;
	cv::Size textSize = cv::getTextSize(text, fontFace,
		fontScale, thickness, &baseline);
	baseline += thickness;

	cv::Point textOrg((image.cols - textSize.width) / 2,
		(40));
	cv::line(image, textOrg + cv::Point(0, thickness),
		textOrg + cv::Point(textSize.width, thickness),
		cv::Scalar(0, 0, 255));

	putText(image, text, textOrg, fontFace, fontScale,
		cv::Scalar::all(255), thickness, 8);

	// The main program loop. Here we copy the working image
	// to the temp image, and if the user is drawing, then
	// put the currently contemplated box onto that temp image.
	// Display the temp image, and wait 15ms for a keystroke,
	// then repeat.
	//
	for (;;) {
		image.copyTo(temp);
		if (drawing_box) draw_box(temp, box, sColour);
		cv::imshow("Box Example", temp);
		if (cv::waitKey(15) == 27) break;
	}

	cv::destroyWindow("Box Example");


	char saveFile;

	std::cout << "Would you like to save the image? (y/n): ";

	std::cin >> saveFile;


	if (saveFile == 'y') {
		cv::imwrite("my_drawing.jpg", image);
	}


	return 0;
}

// This is our mouse callback. If the user
// presses the left button, we start a box.
// When the user releases that button, then we
// add the box to the current image. When the
// mouse is dragged (with the button down) we
// resize the box.
//
void my_mouse_callback(
	int event, int x, int y, int flags, void* param)
{


	cv::Mat& image = *(cv::Mat*) param;
	switch (event) {
	case cv::EVENT_MOUSEMOVE: {
		if (drawing_box) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
	}
							break;
	case cv::EVENT_LBUTTONDOWN: {
		drawing_box = true;
		box = cv::Rect(x, y, 0, 0);
	}
							  break;
	case cv::EVENT_LBUTTONUP: {

		drawing_box = false;
		if (box.width < 0) {
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0) {
			box.y += box.height;
			box.height *= -1;
		}

		cv::Point center = cv::Point(x - (int)box.width / 2, y - (int)box.height / 2);

		if (flags & cv::EVENT_FLAG_SHIFTKEY) {
			cv::circle(image, center, box.width, sColour, 2);
			break;
		}
		else if(flags & cv::EVENT_FLAG_CTRLKEY) {
			cv::ellipse(image, center, cv::Size(box.height, box.width), 0, 0, 360, sColour);
			break;
		}
		else {
			draw_box(image, box, sColour);
		}
	}
							break;
	}

}
