#include "texture.h"
#include <iostream>
//#include <time.h>
#include <vector>
#include <unordered_map>

using namespace std;

typedef Point3_<uchar> pixel;

texture::texture(int w, int h) {	
	O_w = w;
	O_h = h;	
}

void texture::getSample (char* fname) {
	I = imread( fname, CV_LOAD_IMAGE_COLOR );
	I_w = I.cols;
	I_h = I.rows;
	cout << "I_w = " << I_w << ", I_h = " << I_h << endl;
	cout << "O_w = " << O_w << ", O_h = " << O_h << endl;	
}

void texture::generateTexture (int wsize) {
	O.create(O_h, O_w, I.type());
	window_size = wsize;
	cout << "Initializing texture ... ";
	initializeTexture();
	cout << "finished." << endl;
	
	cout << "Texture Synthesis based on candidate search ... " << endl;
	int a = 0;	

	for (int j = 0; j < O_w; j++) {
		if ( j >= double(a*O_h)/100) {
			cout << a << "% finish " << endl;
			a += 10;
		}
		for (int i = 0; i < O_h; i++) {
			findBestMatch(i, j);
		} 
	}
	
	cout << "Finish texture synthesis." << endl;
}

void texture::saveTexture (char* fname) {
	imwrite( fname, O );
	namedWindow( fname, CV_WINDOW_AUTOSIZE );
	imshow( fname, O );
	//waitKey(0); // Wait for a keystroke in the window
}

// helper functions
void texture::initializeTexture() {
	srand(time(NULL));
	//srand(2000);
	int px, py;
	
	for(int j = 0; j < O_h; j ++)
 	{ 				
 		for(int i = 0; i < O_w; i++)
 		{
 			px = rand()%I_w; 
 			py = rand()%I_h;			
 			pixel* p_I = I.ptr<pixel >(px, py);
 			pixel* p_O = O.ptr<pixel >(i,j);
 			p_O->x = p_I->x;
 			p_O->y = p_I->y;
 			p_O->z = p_I->z; 
 			original_pos.insert( {p_O, point2(px,py)} );		
 		}
 	}
}

void texture::findBestMatch( int i, int j) {
	// build Neighborhood(O, i, j)
	N.clear();
	N = buildNeighborhood(&O, i, j);
	pixel* p_O = O.ptr<pixel >(i,j);
	
	candidate.clear();
	getCandidate(i, j);
	 
	int bestd = 1000000000;
	int tmp_d = 0, besti = i, bestj = j;
	
	int M = candidate.size();
	int ii, jj;
	for (int m = 0; m < M; m++) {
		ii = candidate[m].px;
		jj = candidate[m].py;
		// build Neighborhood(I, ii, jj)
		Ni.clear();		
		Ni = buildNeighborhood(&I, ii, jj);
		tmp_d = distance(bestd);			
		if(tmp_d < bestd) {
			bestd = tmp_d;
			besti = ii;
			bestj = jj;
		}			
	}	
		
	pixel* p_I = I.ptr<pixel >(besti, bestj);		
	p_O->x = p_I->x;
	p_O->y = p_I->y;
 	p_O->z = p_I->z;
 	original_pos[p_O] = point2(besti,bestj);
}

void texture::getCandidate(int i, int j) {
	int whalf = window_size/2;
	pixel* p_O;
	int x, y, actualx, actualy;
	
	for ( int tj = j - whalf; tj <= j; tj++ ) {
		for (int ti = i -whalf; ti <= i + whalf; ti++) {
			if (tj == j && ti == i) break;
			x = (ti + O_w) % O_w;
			y = (tj + O_h) % O_h;			
			p_O = O.ptr<pixel >(x,y);
			actualx = original_pos[p_O].px + i - ti;
			actualy = original_pos[p_O].py + j - tj;
			actualx = (actualx + I_w) % I_w;
			actualy = (actualy + I_h) % I_h;
			bool exist = false;
			for (unsigned int m = 0; m < candidate.size(); m++) {
				if (candidate[m].px == actualx && candidate[m].py == actualy ) {
					exist = true;
					break;
				}
			}
			if (!exist)	candidate.push_back( point2(actualx, actualy) );
		}
	}
}

vector<pixel*> texture::buildNeighborhood (Mat *file, int i, int j) {
	vector<pixel*> NN;
	int whalf = window_size/2;
	int x, y;
	int w = file->cols;
	int h = file->rows;
	
	for (int tj = j - whalf; tj <= j; tj ++) {
		for (int ti = i - whalf; ti <= i + whalf; ti ++) {
			if( tj == j && ti == i)	break;
			x = ti;
			y = tj;
			if (x < 0)	x += w;
			else if (x > w)	x = x % w;
			if (y < 0)	y += h;
			else if (y > h)	y = y % h;
			NN.push_back(file->ptr<pixel >(x,y));
		}
	}
	return NN;
}

int texture::distance(int bestd) {
	int m = Ni.size();	
	int d = 0;
	for (int i = 0; i < m; i++) {
		d += pow((int)Ni[i]->x - (int)N[i]->x, 2.0) + pow((int)Ni[i]->y - (int)N[i]->y, 2.0) + pow((int)Ni[i]->z - (int)N[i]->z, 2.0);
		if(d >= bestd) break;
	}
	return d;
}
