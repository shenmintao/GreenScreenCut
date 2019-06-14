#pragma once
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <vector>
#include <opencv2/core/cuda.hpp>
using namespace std;

struct labelPoint
{
	int x;
	int y;
	int label;
};

struct Tuple
{
	cv::Scalar f;
	cv::Scalar b;
	double   sigmaf;
	double   sigmab;

	int flag;

};

struct Ftuple
{
	cv::Scalar f;
	cv::Scalar b;
	double   alphar;
	double   confidence;
};

/*�������϶�cv::Point�� xΪ�У�yΪ�У����ܴ��󣬵��Գ�����û��Ӱ��*/
class SharedMatting
{
public:
	SharedMatting();
	virtual ~SharedMatting();

	void loadImage(cv::Mat source);
	void loadTrimap(cv::Mat trimap);

	void solveAlpha();
	void save(const char * filename);
	cv::Mat result();
protected:
	void expandKnown();
	void gathering();
	void refineSample();
	void localSmooth();
	void sample(vector<vector<cv::Point> > &F, vector<vector<cv::Point> > &B);
	void getMatte();


private:
	double chromaticDistortion(int i, int j, cv::Scalar f, cv::Scalar b);
	double neighborhoodAffinity(int i, int j, cv::Scalar f, cv::Scalar b);


	double aP(int i, int j, double pf, cv::Scalar f, cv::Scalar b);
	double gP(cv::Point p, cv::Point fp, cv::Point bp, double distance, double probability);

	double energyOfPath(int i1, int j1, int i2, int j2);
	double probabilityOfForeground(cv::Point p, vector<cv::Point>& f, vector<cv::Point>& b);
	double pixelDistance(cv::Point s, cv::Point d);
	double colorDistance2(cv::Scalar cs1, cv::Scalar cs2);
	double sigma2(cv::Point p);
	double comalpha(cv::Scalar c, cv::Scalar f, cv::Scalar b);
	cv::Scalar LOAD_RGB_SCALAR(uchar* data, int pos);
private:
	cv::cuda::GpuMat pImg;
	cv::cuda::GpuMat matte;

	vector<cv::Point> unknownSet;
	vector<struct Tuple> tuples;
	vector<struct Ftuple> ftuples;

	int height;
	int width;
	int ** unknownIndex;//Unknown��������Ϣ��
	int ** m_ppTriData;
	int ** alpha;

	size_t step;
	int channels;
	uchar* data;

};
