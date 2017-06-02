#include <bits/stdc++.h>
#include "opencv2/core/core.hpp"
#include "opencv2/flann/miniflann.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/photo/photo.hpp"
#include "opencv2/video/video.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core_c.h"
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/imgproc/imgproc_c.h"
#include "tesseract/baseapi.h"
#include"leptonica/allheaders.h"
#include "sys/time.h"
#include <algorithm>
#include <string>
#include <stdlib.h>
using namespace std;
using namespace cv;
using namespace tesseract;

// DEVElOPER:RPzinga

int SUDO[9][9];
Mat img,dst,imgGray;
Mat detected;
int ratio=3;
int Kernel_size=3;
int lowThreshold;
int const max_lowThreshold=100;
string window_name="edge";


int DETECT(Mat x,TessBaseAPI *api,Mat y){
	api->SetImage((uchar*)x.data, x.size().width, x.size().height, x.channels(), x.step1());
	char *s;
	api->Recognize(0);	
	s= api->GetUTF8Text();
	if(s[0]!='\0'){
		int x=s[0];
		if(x>=48&&x<=57){
			return x-48;
		}		
		else{
			return 10;	
		}
	}
	else{
		return -1;
	}
	
}
bool CheckRow(int SUDO[9][9],int row, int num)
{
	for(int col=0;col<9;col++)
	{
		if(SUDO[row][col]==num)
			return true;
	}
	return false;
}

bool CheckCol(int SUDO[9][9],int col,int num){
	for(int row=0;row<9;row++)
	{
		if(SUDO[row][col]==num)
			return true;
	}
	return false;
}

bool Checkbox(int SUDO[9][9],int r,int c,int num){

	for(int row=0;row<3;row++)
	{
		for(int col=0;col<3;col++)
		{
			if(SUDO[row+r][col+c]==num)
			{
				return true;
			}
		}
	}
	return false;
}
bool conflicts(int SUDO[9][9], int row,int col,int num)
{
	return !CheckRow(SUDO,row,num)&&
			!CheckCol(SUDO,col,num)&&
			!Checkbox(SUDO,row-row%3,col-col%3,num);
	
}

bool Unassign(int SUDO[9][9],int &row, int &col){
	for (row= 0;  row<9 ; row++)
	{
		for(col=0;col<9;col++){
			if(SUDO[row][col]==0)
				return true;
		}	
	}
	return false;	
}


bool SolveSudoku(int SUDO[9][9]){
	int row,col;

	if(!Unassign(SUDO,row,col))
		return true;

	for(int num=1;num<=9;num++)
	{

		if(conflicts(SUDO,row,col,num))
		{	
			SUDO[row][col]=num;

			if(SolveSudoku(SUDO))
			{	return true; }

			SUDO[row][col]=0;
		}	
	}
	return false;
}

void setup_frame(Mat x)
{
    cvNamedWindow("window",CV_WINDOW_KEEPRATIO);//windowintialization
    imshow("window",x);//window:image is shown in it
}

void CannyThreshold(int,void*){

    blur(imgGray,detected,Size(1,1));
    Canny(detected,detected,lowThreshold, lowThreshold*3,Kernel_size);
    dst=Scalar::all(0);
    img.copyTo(dst,detected);
    //imshow(window_name,dst);
}

int main()
{
    string s;
    cin>>s;
    img = imread(s);
    setup_frame(img);
     
    TessBaseAPI *api = new TessBaseAPI();

    if(api->Init(NULL,"eng")){
	fprintf(stderr,"Could not initialize tesseract");
	exit(1);
}	
    api->SetVariable("tessedit_char_whitelist","0123456789");

    cvtColor(img,imgGray,CV_BGR2GRAY);
    threshold(imgGray,imgGray,125,255,CV_THRESH_BINARY);
    CannyThreshold(0,0);
    createTrackbar("Min threshold",window_name,&lowThreshold ,max_lowThreshold ,CannyThreshold);
    cout<<img.size().width<<"---->"<<img.size().height<<endl;
    dst.create(img.size(),img.type());
    Canny(img,dst,50, 200, 3);
    
    vector<Vec4i> lines;
    vector<int> Xi,Yi;

    Mat cdst;
    HoughLinesP(dst,lines,1 , CV_PI/180,50 ,50,5 );
    cout<<"done"<<endl;
    int c=0;
    cdst.create(img.size(),img.type());

   for(size_t i=0;i<lines.size();i++){
    Vec4i y=lines[i];
    Xi.push_back(y[0]);
    Xi.push_back(y[2]);
    Yi.push_back(y[1]);
    Yi.push_back(y[3]);
   }

  auto resultx=minmax_element(Xi.begin(),Xi.end()),resulty=minmax_element(Yi.begin(),Yi.end());
	
  int minX=*resultx.first,maxX=*resultx.second;
  int minY=*resulty.first,maxY=*resulty.second;
 
 // debugging code
 for(size_t i=0;i < lines.size();i++){
       		 Vec4i X=lines[i];
       	    cout<<"point 1x-->"<<X[0]<<"-->"<<"point 1y-->"<<X[1]<<endl;
       	    cout<<"point 2x--> :"<<X[2]<<"-->"<<"point 2y-->"<<X[3]<<endl;
	if(c<1){
       	    circle(cdst,Point(X[0],X[1]),1,Scalar(0,0,255),2,CV_AA);
       	    circle(cdst,Point(X[2],X[3]),1,Scalar(0,0,255),2,CV_AA);
	}
	if(2*c==20)
		cout<<endl;
    	    line(dst,Point(X[0],X[1]),Point(X[2],X[3]),Scalar(255,0,0), 2,CV_AA);
	c++;

    }
    float countx=(maxX-minX)/9.0;
    float county=(maxY-minY)/9.0;

    cout<<countx<<"--->"<<county<<endl;
 	
 	// ROI code
	Mat roi,gdst;
	int sudoi=0,sudoj=0,Trump=0,ans=1e-9; 
 	
	Size size(30,20);
	std::vector<float> v;
 for (float i=minY;i<maxY;i+=county+1.5)
    {
	sudoj=0;
      for (float j=minX;j<maxX;j+=countx+1.5)
      {
        Rect rt(j+countx/26,i+county/26,countx-(countx)/4.5,county-(county)/4.5);
      	rectangle(img,rt,Scalar(0,0,255),1,0);
		roi=img(rt);
		gdst.create(roi.size(),roi.type());
		resize(roi,gdst,size);
		blur(gdst,gdst,Size(1,1));
		imwrite("test.png",gdst);
		namedWindow("original",CV_WINDOW_FREERATIO);
		imshow("original",gdst);
		waitKey(100);
		Pix *image = pixRead("test.png");
    	api->SetImage(image);
		char *out;
		out = api->GetUTF8Text();
		printf("Out:\n%s",out);
		if(out[0]!='\0'){
			int x=out[0];
			if(x>=48&&x<=57)
			{
					 SUDO[sudoi][sudoj]=x-48;
					 Trump++;
			}	
		}	
		else{
			v.push_back(i+j);
			SUDO[sudoi][sudoj]=0;
		}			
		pixDestroy(&image);
		delete [] out;
		sudoj++;
      }
      sudoi++;
    }
	
cout<<"detected Sudoku"<<endl;	
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			cout<<SUDO[i][j]<<" " ;
		}
	cout<<endl;
	}

	if(Trump>=17){
		bool x=SolveSudoku(SUDO);
		if(x){
			cout<<"Solved Sudoku"<<endl;
			for (int i = 0; i <9 ; ++i){
				for (int j = 0; j <9 ; ++j){
					printf("%2d",SUDO[i][j]);
				}
			printf("\n");	
		}
		}
		else{
			cout<<"Wrong sudoku"<<endl;
		}
	}
	else{
		printf("%s\n","Wrong Sudoku" );
		exit(0);	
	}
	cout<<v.size()<<endl;
	while(!v.empty()){
		int z=v.back();
		putText(img,1,z, FONT_HERSHEY_SIMPLEX,1.0,Scalar(255,0,0),1,8);
		v.pop_back();
	}

	namedWindow("original",CV_WINDOW_FREERATIO);
	imshow("original",img);
	waitKey(1000);
  
waitKey(0);

return 0;

}
