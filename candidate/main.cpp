#include <iostream>
#include <cstdlib>
#include <time.h>
#include "texture.h"
#include <sstream>

using namespace std;

// the parameter "size" controls the size of the synthesized texture, it can be any arbitrary number. "window_size" determines the window for synthesis we used. These two parameters are user defined, you can modify it here.
int size = 512;
vector<int> window_size = {5, 11, 21};

string convertInt(int number)
{
	stringstream ss;
	ss << number;
	return ss.str();
}

int main( int argc, char** argv )
{
	if( argc != 2 )
 	{
   		cout << " No image data \n ";
   		return -1;
	}
	char *input = argv[1];
	string imagename = input;
	if(imagename.rfind("/"))	imagename = imagename.substr(imagename.rfind("/")+1);	
	const int N = window_size.size();
	string output[N];
	string dir = "./results/";
	
	double elap;
	time_t time1, time2;	
	
	for (int i = 0; i < N; i++) {
		output[i] = imagename;
		output[i].insert(output[i].find("."), "_candidate_textured_" + convertInt(window_size[i]));		
		output[i] = dir + output[i];		
		time1 = time(NULL);
		
		texture* t = new texture(size, size);
		t->getSample(input);
		t->generateTexture(window_size[i]);
		t->saveTexture((char *)output[i].c_str());
		
		time2 = time(NULL);
		elap = difftime(time2, time1);
		cout << output[i] << "\nsynthesized by candidate_search method using window " << window_size[i] << " X " << window_size[i] << endl;
		cout << "The synthesis process spend time: " << elap << " seconds." << endl; 
		
	}

 	return 0;
}
