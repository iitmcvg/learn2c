#include <opencv2/opencv.hpp>
using namespace cv;

Mat inputImage, outputImage, channel[3];
std::string colorSpace;

void showGray(){
       cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
       imshow("Gray", outputImage);
}

void showChannels(Mat channel[], std::string labels[], double scalar[][3], int convertBack){
       Mat aux[3];
       outputImage = Mat(inputImage.rows, inputImage.cols, inputImage.type());
       for(int i = 0; i < 3; i++){
              // fill the base Mat with standard values based on CS143 from Brown
              aux[0] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[i][0];
              aux[1] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[i][1];
              aux[2] = Mat::ones(inputImage.rows, inputImage.cols, CV_8UC1) * scalar[i][2];
              aux[i] = channel[i];
              // merge the channels back together
              merge(aux, 3, outputImage);
              // convert from output color space to BGR
              cvtColor(outputImage, outputImage, convertBack);
              imshow(labels[i] + " (3-Channels)", outputImage);
              
       }
}

void showRGB(){
       cvtColor(inputImage, inputImage, COLOR_BGR2RGB);
       split(inputImage, channel);
       std::string rgb_labels[3] = {"[R]ed", "[G]reen", "[B]lue"};
       double std_values[3][3] = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
       showChannels(channel, rgb_labels, std_values, COLOR_RGB2BGR);
}
void showHSV(){
       // Color Range => H: 0 to 179, S: 0 to 255, V: 0 to 255
       cvtColor(inputImage, inputImage, COLOR_BGR2HSV);
       split(inputImage, channel);
       std::string hsv_labels[3] = {"[H]ue", "[S]aturation", "[V]alue"};
       double std_values[3][3] = {{1, 255, 255}, {179, 1, 255}, {179, 0, 1}};
       showChannels(channel, hsv_labels, std_values, COLOR_HSV2BGR);
}
void showYCrCb(){
       cvtColor(inputImage, inputImage, COLOR_BGR2YCrCb);
       split(inputImage, channel);
       std::string hsv_labels[3] = {"Y - Luminance", "Cr - [C]hroma [r]ed", "Cb - [C]hroma [b]lue"};
       double std_values[3][3] = {{1, 127.5, 127.5}, {127.5, 1, 127.5}, {127.5, 127.5, 1}};
       showChannels(channel, hsv_labels, std_values, COLOR_YCrCb2BGR);
}
void showLAB(){
       cvtColor(inputImage, inputImage, COLOR_BGR2Lab);
       split(inputImage, channel);
       std::string hsv_labels[3] = {"[L]uminance", "A (dimension)", "B (dimension)"};
       double std_values[3][3] = {{1, 127.5, 127.5}, {191.25, 1, 127.5}, {191.25, 127.5, 1}};
       showChannels(channel, hsv_labels, std_values, COLOR_Lab2BGR);
}


int main(int argc, char** argv){
     
       inputImage = imread(argv[1]);    // read the BGR image
       colorSpace = argv[2];
       imshow("Input", inputImage);

       if(colorSpace == "gray")           showGray();
       else if(colorSpace == "hsv")       showHSV();
       else if(colorSpace == "ycrcb")     showYCrCb();
       else if(colorSpace == "lab")       showLAB();
       else if(colorSpace == "rgb")       showRGB();

       waitKey(0);
       return 0;
}
