#ifndef __OPENCV_UTILS_H__
#define __OPENCV_UTILS_H__

#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\ml\ml.hpp>
#include <opencv2\objdetect\objdetect.hpp>

using namespace cv;

#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>

using std::cout;
using std::string;

#define POINT_LOOP(mat, p)          for(p.y=0;p.y<mat.rows;p.y++)for(p.x=0;p.x<mat.cols;p.x++)
#define POINT_LOOP_INV(mat, p)      for(p.y=mat.rows-1;p.y>=0;p.y--)for(p.x=mat.cols-1;p.x>=0;p.x--)
#define POINT_RECT_LOOP(rect, p)    for (p.y=rect.y;p.y<rect.y+rect.height;p.y++)for(p.x=rect.x;p.x<rect.x+rect.width;p.x++)
#define CVU_ASSERT(expr)            CV_Assert(expr);

#define iPOINT_LOOP(mat, p)         Point p;for(p.y=0;p.y<mat.rows;p.y++)for(p.x=0;p.x<mat.cols;p.x++)
#define iPOINT_LOOP_INV(mat, p)     Point p;for(p.y=mat.rows-1;p.y>=0;p.y--)for(p.x=mat.cols-1;p.x>=0;p.x--)
#define iPOINT_RECT_LOOP(rect, p)   Point p;for(p.y=rect.y;p.y<rect.y+rect.height;p.y++)for(p.x=rect.x;p.x<rect.x+rect.width;p.x++)


#ifndef CVU_ABS
#	define CVU_ABS(a)  ((a) < 0 ? (a)*(-1) : (a))
#endif

#define cvuColorBlack	Vec3b(0,0,0)
#define cvuColorWhite   Vec3b(255,255,255)
#define cvuColorRed     Vec3b(0,0,255)
#define cvuColorGreen   Vec3b(0,255,0)
#define cvuColorBlue    Vec3b(255,0,0)
#define cvuColorPurple  Vec3b(255,0,255)
#define cvuColorCyan    Vec3b(255,255,0)
#define cvuColorYellow  Vec3b(0,255,255)

inline vector<int> cvuSaveOption(string type, int value) {
    vector<int> ret;
    for(auto &c : type) c = std::tolower(c);
    if (type == "jpg" || type == "jpeg")
    {
        ret.push_back(CV_IMWRITE_JPEG_QUALITY);
        ret.push_back(value);
    }
    if (type == "png")
    {
        ret.push_back(CV_IMWRITE_PNG_COMPRESSION);
        ret.push_back(value);
    }
    if (type == "ppm" || type == "pgm" || type == "pbm")
    {
        ret.push_back(CV_IMWRITE_PXM_BINARY);
        ret.push_back(value);
    }
    return ret;
}

inline void cvuDebugWindow(Mat img, int last = 0)
{
	imshow("img", img);
	waitKey(last);
	destroyAllWindows();
}

inline void cvuDebugWindows(Mat img, Mat img2, int last = 0)
{
	imshow("img", img);
	imshow("img2", img2);
	waitKey(last);
	destroyAllWindows();
}
inline void cvuDebugWindows(Mat img, Mat img2, Mat img3, int last = 0)
{
	imshow("img", img);
	imshow("img2", img2);
	imshow("img3", img3);
	waitKey(last);
	destroyAllWindows();
}
inline void cvuDebugWindows(Mat img, Mat img2, Mat img3, Mat img4,int last = 0)
{
	imshow("img", img);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	waitKey(last);
	destroyAllWindows();
}
inline void cvuDebugWindows(Mat img, Mat img2, Mat img3, Mat img4, Mat img5, int last = 0)
{
	imshow("img", img);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);
	waitKey(last);
	destroyAllWindows();
}
inline void cvuDebugWindows(Mat img, Mat img2, Mat img3, Mat img4, Mat img5, Mat img6,int last = 0)
{
	imshow("img", img);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);
	imshow("img6", img6);
	waitKey(last);
	destroyAllWindows();
}

inline void cvuDebugResizeWindow(Mat img, Size size, int last = 0)
{
	Mat res;
	resize(img, res, size);
    cvuDebugWindow(res, last);
}

inline void cvuDebugRectangle(Mat image, Rect rect)
{
	Mat cvs = image.clone();
	rectangle(cvs, rect, Scalar(0,255,0), 3);
	cvuDebugWindow(cvs, 0);
}

inline void cvuDebugScaleWindow(Mat image, float scale, int last = 0)
{
	Mat cvs = image.clone();
	cvs *= scale;
	cvuDebugWindow(cvs, last);
}

inline void cvuDebugColorWindow(Vec3b color)
{
	Mat cvs = Mat(Size(150, 150), CV_8UC3);
	cvs.setTo(color);
	cvuDebugWindow(cvs);
}

Mat cvuDebugJointImages(vector<Mat> images, int rows=0, int cols=0);

inline double cvuColorDist(Vec3b v1, Vec3b v2)
{ cvuColorDist((Vec3f) v1, (Vec3f) v2); }
inline double cvuColorDist(Vec3f v1, Vec3f v2)
{
	return sqrt( (double) (
		(v1.val[0]-v2.val[0]) * (v1.val[0]-v2.val[0]) +
		(v1.val[1]-v2.val[1]) * (v1.val[1]-v2.val[1]) +
		(v1.val[2]-v2.val[2]) * (v1.val[2]-v2.val[2]) ) );

}

inline void cvuPrintVec3f(Vec3f vec, string vec_name = "vec3f")
{
	cout << vec_name << " : " 
		 << " val1 = " << vec.val[0]
		 << " val2 = " << vec.val[1]
		 << " val3 = " << vec.val[2] << std::endl;
}

inline Rect cvuSquarify(Rect rect)
{
    int delta;
    if (rect.height < rect.width)
    {
        delta = rect.width - rect.height;
        rect.height = rect.width;
        rect.y -= delta / 2;
    }
    if (rect.width < rect.height)
    {
        delta = rect.height - rect.width;
        rect.width = rect.height;
        rect.x -= delta / 2;
    }

    return rect;
}

inline void cvuSafeBGR2Gray(Mat& src, Mat& tar)
{
    if (src.channels() >= 3)
        cvtColor(src, tar, CV_BGR2GRAY);
    else
        tar = src;
}

struct PointPair 
{
	int x1;
	int x2;
	int y1;
	int y2;

	PointPair() { x1 = x2 = y1 = y2 = 0; }
	PointPair(Rect rect) 
	{
		x1 = rect.x;
		y1 = rect.y;
		x2 = rect.width + rect.x - 1;
		y2 = rect.height + rect.y - 1;
	}
	PointPair(Point p1, Point p2) 
	{
		x1 = p1.x; y1 = p1.y;
		x2 = p2.x; y2 = p2.y;
	}
    PointPair(int xx1, int xx2, int yy1, int  yy2)
    {
        x1 = xx1; y1 = yy1;
        x2 = xx2; y2 = yy2;
    }

	Rect toRect() { 
		int x = min(x1, x2);int  y = min (y1, y2);
		int width = max(x1, x2) - x + 1;
		int height = max(y1, y2) - y + 1;
		return Rect(x, y, width, height);
	}

	Point leftPoint() {
		return x1 < x2 ? Point(x1, y1) : Point(x2, y2);
	}
	Point rightPoint() {
		return x1 > x2 ? Point(x1, y1) : Point(x2, y2);
	}
	Point upPoint() {
		return y1 < y2 ? Point(x1, y1) : Point(x2, y2);
	}
	Point downPoint() {
		return y1 > y2 ? Point(x1, y1) : Point(x2, y2);
	}

	int left()	{ return x1 < x2 ? x1 : x2; }
	int right() { return x1 > x2 ? x1 : x2; }
	int up()	{ return y1 < y2 ? y1 : y2; }
	int down()	{ return y1 > y2 ? y1 : y2; }
	int width() { return CVU_ABS(x1 - x2) + 1; }
	int height(){ return CVU_ABS(y1 - y2) + 1; }

	void bound(int minx, int maxx, int miny, int maxy)
	{
		x1 = max(minx, x1); x1 = min(maxx, x1);
		x2 = max(minx, x2); x2 = min(maxx, x2);
		y1 = max(miny, y1); y1 = min(maxy, y1);
		y2 = max(miny, y2); y2 = min(maxy, y2);
	}
};

inline int cvuArea(Rect r) { return r.width * r.height; }

template<typename T>
inline vector<T> cvuMat2Vec(Mat mat) {
    Point p; vector<T> ret;
    POINT_LOOP(mat, p) ret.push_back(mat.at<T>(p));
    return ret;
}

template<typename T>
inline Mat cvuDrawPoints(Mat& mat, vector<T> pts, bool write_on_new_image = true,
                         int radius = 3, Scalar color = Scalar(0, 0, 255))
{
    Mat cvs;
    if (write_on_new_image) cvs = mat.clone();
    else cvs = mat;

    for (auto & pt : pts) {
        circle(cvs, pt, radius, color, -1);
    }
    /*
    circle(cvs, pts.front(), radius, Scalar(255, 0, 0), -1);
    circle(cvs, pts.back(), radius, Scalar(0, 255, 0), -1);*/
    return cvs;
}

template<typename T>
inline Point_<T> operator * (Point_<T> a, Point_<T> b)
{
    Point_<T> res;
    res.x = a.x * b.x;
    res.y = a.y * b.y;
    return res;
}

inline Mat cvuGetChannel(Mat im, int chl)
{
    vector<Mat> channels;
    split(im, channels);
    return channels[chl];
}

template<typename T>
inline void cvuPrintMat(Mat mat, string filename = "")
{
    using namespace std;

    FILE* fp = nullptr;
    bool flag = filename.size() == 0;
    if (!flag) {
        filename = filename + ".mtx";
        fp = fopen(filename.c_str(), "w");
    }

    string fmt;
    if (typeid(T) == typeid(double) || typeid(T) == typeid(float))
        fmt = "%8.3e " ;
    else fmt = "%4d " ;

    iPOINT_LOOP(mat, p)
    {
        if (p.x == 0) printf("\n");

        if(flag) printf(fmt.c_str(), mat.at<T>(p));
        else     fprintf(fp, fmt.c_str(), mat.at<T>(p));
    }
    printf("\n");

    if (!flag) fclose(fp);
}

#endif
