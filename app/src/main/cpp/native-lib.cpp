#include <jni.h>
#include <opencv2/opencv.hpp>

using namespace cv;

extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencv_MainActivity_ConvertRGBtoGray(JNIEnv *env, jobject instance,
                                                      jlong matAddrInput, jlong matAddrResult) {

    // TODO
    Mat &matInput = *(Mat *)matAddrInput;
    Mat &matResult = *(Mat *)matAddrResult;

    cvtColor(matInput, matResult, COLOR_RGBA2GRAY);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencv_MainActivity_ConvertCanny(JNIEnv *env, jobject instance, jlong matAddrInput,
                                                  jlong matAddrResult) {

    Mat &matInput = *(Mat *)matAddrInput;
    Mat &matResult = *(Mat *)matAddrResult;
    cvtColor(matInput, matResult, COLOR_RGBA2GRAY);
    Canny(matResult,matResult,100,200,3); // Canny 연산
    //threshold(matResult, matResult, 0, 255, CV_THRESH_BINARY_INV); // sobel 영상과 비교하려고 반전

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_opencv_MainActivity_corner(JNIEnv *env, jobject instance, jlong matAddrInput,
                                            jlong matAddrResult) {

    int blockSize = 2;
    int apertureSize = 3;
    double k = 0.04;

    Mat &matInput = *(Mat *)matAddrInput;
    Mat &matResult = *(Mat *)matAddrResult;
    cvtColor(matInput, matResult, COLOR_RGBA2GRAY);
    Canny(matResult,matResult,100,220,3);

    cornerHarris( matResult, matResult, blockSize, apertureSize, k, BORDER_DEFAULT );
    normalize( matResult, matResult, 0, 255, NORM_MINMAX, CV_32FC1, Mat() );
    convertScaleAbs( matResult, matResult );
    for( int j = 0; j < matResult.rows ; j++ )
    { for( int i = 0; i < matResult.cols; i++ )
        {
            if( (int) matResult.at<float>(j,i) > 200 )
            {
                circle( matResult, Point( i, j ), 5,  Scalar(0, 0, 255), 2, 8, 0 );
            }
        }
    }
}