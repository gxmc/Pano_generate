#pragma once
#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
class myLadybugGeometry
{
public:
	myLadybugGeometry();
	~myLadybugGeometry();

public:
	//����5������������ڲα����ڳ�Ա����mvInnerParas��
	//�ڲζ���˳��Ϊ��
	//CameraNum,k1,k2,k3,k4,p1,p2,c1,c2,lamda,fdistroted,x0distorted,y0distorted,frectified,x0rectified,y0rectified
	bool ReadInnerParaFromFile(std::string FilePath);

	bool ReadInvInnerParaFromFile(std::string FilePath);

	//����5��������������(��εĸ�����ʽΪ��Rx,Ry,Rz,Tx,Ty,Tz,��������Ԫ��+������Ԫ��)
	//���벢ת��Ϊ�任����[R|t],������ mvUnitCamExParas��
	bool ReadUnitCameraExParaFromFile(std::string strFilePath);

	//������ͼ�����������ת��Ϊ������ͼ�����������
	//�����1����Ϊ����ţ���2,3����Ϊ����������������꣬��4,5����Ϊ�����������������
	bool LadybugRectifyImage(int CameraNum, double Pixalx, double Pixaly, 
		double* RectifiedPixalx, double* RectifiedPixaly);

	bool LadybugUnRectifyImage(int CameraNum, double Pixalx, double Pixaly, double* DistortedPixalx, double* DistortedPixaly);

	//������ͼ�����������ͶӰ��ȫ��������,Radius���Զ������뾶(��λ��m)
	bool LadybugProjectFishEyePtToSphere(int CameraNum, 
		double FishEyePixalx, double FishEyePixaly,double Radius,
		double* SphereX, double* SphereY, double* SphereZ);

	bool LadybugReprojectSpherePtToFishEyeImg(double SphereX, double SphereY, double SphereZ, double Radius,
		int* CameraNum, double* FishEyePixalx, double* FishEyePixaly);
	

	//��ȫ��ͼ���ϵ�����Ͷ�䵽������;
	bool LadybugReprojectPanoPtToSphere(double SphereRadius, int PanoImgWith,int PanoImgHeight, double xPano, double yPano, 
		double* SphereX, double* SphereY, double* SphereZ);
	bool LadybugReprojectPanoPtToFishEyeImg(int PanoImgWith,int PanoImgHeight, double SphereRadius, double xPano, double yPano,
		int* CamID,double* FishEyePixalx, double* FishEyePixaly);

	//����ͼ���С
	void InputImgSize(int width, int height);

	//���������ͼ�����������
	void GetRectifiedImgCenter(int CameraNum, double* x0, double *y0);
	
	//�������ͼ�����������
	void GetFishEyeImgCenter(int CameraNum, double* x0, double* y0);

	//���������ͼ��Ľ���
	double GetRectifiedImgFocalLength(int CameraNum);

	//˫�����ڲ庯��
	cv::Vec3b BilinearInterpolation(cv::Mat Img, double x, double y);

private:
	double mImgHeight;
	double mImgWidth;
	std::vector<cv::Mat> mvInnerParas;
	std::vector<cv::Mat> mvInvInnerParas;
	std::vector<cv::Mat> mvUnitCamExParas;
	cv::Mat mCurrentInnerPara;
	cv::Mat mCurrentInvInnerPara;

	//����Ladybugȫ������Ǻ��Ű��ŵģ���ϵͳʹ��ͼ���Ǻ��ŵģ�����ϰ��ʹ��������ͼ��(���ŵ�)
	//��ˣ�����ʱ��Ҫ�ȴ����ŵ�ͼ����������ת��Ϊ���ŵ���������(��ʱ����ת90��)
	//�������֮����Ҫ˳ʱ����ת90��ת��������ϰ�ߵ����ŵ�ͼ����������
	cv::Point2d ImgPixCoor2LadybugPixCoor(cv::Point2d pt, int ImgWidth, int ImgHeight);
	cv::Point2d LadybugPixCoor2ImgPixCoor(cv::Point2d pt, int ImgWidth, int Height);

	/*ͨ��������ŷ����Rx��Ry��Rz������ת���󣬼��㷽ʽ���£�	
	     |((cRz)(cRy)) ((cRz)(sRy)(sRx)-(sRz)(cRx)) ((cRz)(sRy)(cRx)+(sRz)(sRx)) Tx|
	 R = |((sRz)(cRy)) ((sRz)(sRy)(sRx)+(cRz)(cRx)) ((sRz)(sRy)(cRx)-(cRz)(sRx)) Ty|
	     |((-sRy))     ((cRy)(sRx))                 ((cRy)(cRx)))                Tz|
	     |0            0                            0                            1 |        */
	void CalculateRotationMatFromEulerAngle(double Rx, double Ry, double Rz, double* R);

	
	
};

