#include "sampen.hpp"
#include<iostream>
#include "data.hpp"
#include "result.hpp"
#include "time.h"
// #define length Length
int main()
{
	//float in[50];
	int ct=0;
int samp;

	float in[Length];
	int flag;
	if (Length==360) flag = 0;
	else if (Length==1800) flag = 1;
	else if (Length==3600) flag = 2;
	else if (Length==7200) flag = 3;
	else if (Length==10800) flag = 4;
	// else std::cout<<"Length not included"<<std::endl;
	// std::cout<<"Length"<<Length<<std::endl;
	// int k =0;
	// for(int i = 0; i< 20000000;i++){  //20000000
	// 	k = i%9;
    // 	for(int j = 0 ;j < Length;j++){
	// 		in[j] = data[k][j];
	// 	}
	// 	clock_t begin = clock();
	// 	sampen(in,Length,samp);
	// 	clock_t end = clock();
	// 	std::cout<<"Length:"<<Length<<" value:"<<samp<<" time:"<<(double)(end - begin) / CLOCKS_PER_SEC<<std::endl;
	// 	// std::cout<<samp<<" time:"<<(double)(end - begin) / CLOCKS_PER_SEC<<std::endl;
	// 	// if(samp != result[i][flag]){ct = ct + 1;} 
	// }
	int k =0;
	for(int i = 0; i< 1;i++){  
	
    	for(int j = 0 ;j < Length;j++){
			in[j] = data[i][j];
		}
		clock_t begin = clock();
		sampen(in,Length,samp);
		clock_t end = clock();
		std::cout<<"Length:"<<Length<<" value:"<<samp<<" time:"<<(double)(end - begin) / CLOCKS_PER_SEC<<std::endl;
		// std::cout<<samp<<" time:"<<(double)(end - begin) / CLOCKS_PER_SEC<<std::endl;
		// if(samp != result[i][flag]){ct = ct + 1;} 
	}


	/*
	if(ct == 0)
		std::cout<<"PASS"<<std::endl;
	else
		std::cout<<"FAIL"<<std::endl;
		*/
	return 0;
}
