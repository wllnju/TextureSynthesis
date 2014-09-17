#ifndef TEXTURE_H
#define TEXTURE_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <unordered_map>
using namespace std;
using namespace cv;
typedef Point3_<uchar> pixel;

struct point2 {
	int px;
	int py;
	point2() {}
	point2(int x, int y) : px(x), py(y) {}
};

class texture {
	public:
	//constructor
	texture (int w, int h);
	
	void getSample (char* fname);
	void generateTexture (int wsize);
	void saveTexture (char* fname);
	
	private: 
	// helper function
	void initializeTexture();
	void findBestMatch( int i, int j);
	vector<pixel*> buildNeighborhood (Mat *file, int i, int j);
	int distance( int bestd);
	void getCandidate(int i, int j);
	
	// data
	int O_w, O_h;
	int I_w, I_h;
	int window_size;
	vector<pixel*> Ni;
	vector<pixel*> N;
	Mat I;
	Mat O;
		
	unordered_map<pixel*, point2> original_pos;
	vector<point2> candidate;	
};

#endif
