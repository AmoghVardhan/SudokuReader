#ifndef DIGITRECOGNIZER_H_INCLUDED
#define DIGITRECOGNIZER_H_INCLUDED
#include<cv.h>
#include<highgui.h>
#include<opencv/ml.h>
using namespace cv;
#define MAX_NUM_IMAGES 60000
class DigitRecognizer
{
public:
    DigitRecognizer();
    ~DigitRecognizer();
    bool train(char* trainPath,char* labelsPath);
    int classify(Mat img);
private:
    Mat preprocessImage(Mat img);
    int readFlippedInteger(FILE *fp);
private:
    KNearest *knn;
    int numRows,numCols,numImages;
};

#endif // DIGITRECOGNIZER_H_INCLUDED
