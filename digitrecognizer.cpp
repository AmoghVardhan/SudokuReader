DigitRecognizer::DigitRecognizer()
{
    knn = new KNearest();
}
DigitRecognizer::~DigitRecognizer()
{
    delete knn;
}

int DigitRecognizer::readFlippedInteger(FILE *fp)
{
    int ret = 0;
    BYTE *temp;
    temp = (BYTE*)(&ret);
    fread(&temp[3],sizeof(BYTE),1,fp);
    fread(&temp[2],sizeof(BYTE),1,fp);
    fread(&temp[1],sizeof(BYTE),1,fp);
    fread(&temp[0],sizeof(BYTE),1,fp);
    return ret;
}
bool DigitRecognizer::train(char *trainPath,char *labelsPath)
{
    FILE *fp = fopen(trainPath,"rb");
    FILE *fp2 = fopen(labelsPath,"rb");
    if(!fp||!fp2)
        return false;
    int magicNumber = readFlippedInteger(fp);
    numImages = readFlippedInteger(fp);
    numRows = readFlippedInteger(fp);
    numCols = readFlippedInteger(fp);
    fseek(fp2,0x08,SEEK_SET);
    if(numImages>MAX_NUM_IMAGES)numImages = MAX_NUM_IMAGES;
    int size = numRows*numCols;
    CvMat *trainingVectors = cvCreateMat(numImages,size,CV_32FC1);
    CvMat *trainingClasses = cvCreateMat(numImages,1,CV_32FC1);
    memset(trainingClasses->data.ptr,0,sizeof(float)*numImages);
    BYTE *temp = new BYTE[size];
    BYTE tempClass = 0;
    for(int i = 0;i<numImages;i++)
    {
        fread((void*)temp,size,1,fp);
        fread((void*)(&tempClass),sizeof(BYTE),1,fp2);
        trainingClasses->data.fl[i] = tempClass;
        for(int k = 0;k<size;k++)
            trainingVectors->data.fl[i*size + k] = temp[k];
    }
    knn->train(trainingVectors,trainingClasses);
    fclose(fp);
    fclose(fp2);
    return true;

}

int DigitRecognizer::classify(cv::Mat img)
{
    Mat cloneImg = preprocessImage(img);
    return knn->find_nearest(Mat_<float>(cloneImg),1);
}
Mat DigitRecognizer::preprocessImage(Mat img)
{
    int rowTop = -1,rowBottom = -1,colLeft = -1,colRight = -1;
    Mat temp;
    int thresholdBottom = 50;
    int thresholdTop = 50;
    int thresholdLeft = 50;
    int thresholdRight = 50;
    int center = img.rows/2;
    for(int i = center;i<img.rows;i++)
    {
        if(rowBottom == -1)
        {
            temp = img.row(i);
            IplImage stub = temp;
            if(cvSum(&stub).val[0]<thresholdBottom || i==img.rows -1)
                rowBottom = i;
        }
        if(rowTop == -1)
        {
            temp = img.row(img.rows-i);
            IplImage stub = temp;
            if(cvSum(&stub).val[0]<thresholdTop||i==img.rows-1)
                rowTop = img.rows - i;
        }
        if(colRight == -1)
        {
            temp = img.col(i);
            IplImage stub = temp;
            if(cvSum(&stub).val[0]<thresholdRight||i==img.cols-1)
                colRight = i;
        }
        if(colLeft == -1)
        {
            temp = img.col(img.cols-i);
            IplImage stub = temp;
            if(cvSum(&stub).val[0]<thresholdLeft||i==img.cols-1)
                colLeft = img.cols-i;
        }

    }
}
