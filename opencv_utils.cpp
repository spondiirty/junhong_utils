#include "opencv_utils.h"

#include "stdio.h"

using namespace cv;

Mat cvuDebugJointImages(vector<Mat> images, int rows, int cols)
{
    if (rows == 0) { rows = 1 ; cols = static_cast<int>(images.size()); }
	else if (cols == 0) { 
        cols = static_cast<int>(images.size()) / rows;
		cols += images.size() % rows ? 1 : 0;
	}

	int i,j;
	Size size = images[0].size();
	for (i = 0; i < images.size(); ++i)
		CVU_ASSERT(images[i].size() == size);
	Mat res = images[0].clone(); res.setTo(0);
	resize(res, res, Size(size.width*cols, size.height*rows));
	Rect subrect;
	for (i = 0; i < rows; i++)
		for (j = 0; j< cols; j++)
		{
			subrect = Rect(j*size.width, i*size.height,size.width,size.height);
			int index = i*cols+j;
			if (index >= images.size()) return res;
			if (images[index].channels() == 1)
			{
				Mat temp;
				cvtColor(images[index], temp, CV_GRAY2BGR);
				temp.copyTo(res(subrect));
			}
			else
				images[index].copyTo(res(subrect));
		}
	return res;
}

