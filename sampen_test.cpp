#include "sampen.hpp"
#include<iostream>
#include "data.hpp"
#include "result.hpp"
#include "time.h"
#include <math.h>
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

		//定义数据结构
        typedef struct node {
        int val;
        struct node * next;
        } node_t;

        typedef struct BUCKET{
                int numbers;
                struct node * begin;
                struct node * end;
        } bucket_t;

		float r = 0.2;
        
        int N = Length;
        int m = 2;
        //int Samp;
        
        //
        int factor = 1;
        int m_factor = 2 * factor;
        float r_factor = r / factor;

		int len = Length;
		float X[Length-1];
        float Xmin = in[0] + in[1] ;
        float Xmax = in[0] + in[1] ;

        l1:for(int i = 0; i < len-1; i++){
                #pragma HLS loop_tripcount max=len-1
                X[i] = in[i]+in[i+1];
                if(X[i] > Xmax){ Xmax = X[i];}
                if(X[i] < Xmin){ Xmin = X[i];}
        }
        l2:for(int i = 0;i<len - 1;i++){
                #pragma HLS loop_tripcount max=len-1
                X[i] = X[i] - Xmin + 1;
        }
        // std::cout<<"Xmax:"<<ceil(Xmax)<<std::endl;
        Xmax = Xmax - Xmin + 1;
        int Nb = ceil(Xmax/r_factor);
        // if (Nb>59) {Nb = 59;}
        if (Nb>2990) {Nb = 2990;}
        // std::cout<<"Xmax:"<<ceil(Xmax)<<std::endl;
        // int Nb = 10;
        // *repos = (struct repo*)malloc(sizeof(struct repo) * MAX_REPOS);
        BUCKET *Bucket = (struct BUCKET*)malloc(Nb * sizeof(struct BUCKET));
        // BUCKET Bucket[Nb];
        // std::cout<<"test:"<<2<<std::endl;


        int bucketCount;
        int bucketLocation;

        

        loopBuckAssignment:for(int i = 0; i < len - 1; i++){
                // std::cout<<"test---:"<<i<<std::endl;
                #pragma HLS loop_tripcount max=len-1
                // std::cout<<"i:"<<i<<std::endl;
                bucketCount = (int)ceil(X[i]/(r_factor))-1;
                // std::cout<<"bucketCount:"<<bucketCount<<std::endl;
                if(bucketCount > Nb-1){bucketCount = Nb-1;}

                // Bucket[bucketCount].numbers = Bucket[bucketCount].numbers + 1;
                // bucketLocation = bucket[bucketCount][0];
                // bucket[bucketCount][bucketLocation] = i;

                Bucket[bucketCount].numbers = Bucket[bucketCount].numbers + 1;
                if(Bucket[bucketCount].begin == NULL){
                        Bucket[bucketCount].begin= (node_t *) malloc(sizeof(node_t));
                        Bucket[bucketCount].end = Bucket[bucketCount].begin;
                        Bucket[bucketCount].end->val = i;
                }else{
                        Bucket[bucketCount].end->next = (node_t *) malloc(sizeof(node_t));
                        Bucket[bucketCount].end = Bucket[bucketCount].end->next;
                        Bucket[bucketCount].end->val = i;
                } 
     
        }

		int Bucket1[Nb];//Bucket1, 存储的容量
		int Bucket2[Nb];//Bucket2指向的地址
		int Bucket3[len];//Bucket3,值
		int start = 0;
		for(int i =0;i<Nb;i++){

			node_t * current = Bucket[i].begin;
		Bucket1[i] = Bucket[i].numbers; //Bucket1, 存储的容量
		if(i==0) Bucket2[i] = 0;
		if(i< Nb-1) Bucket2[i+1] = Bucket2[i] + Bucket[i].numbers;  //Bucket2指向的地址
		while(current != NULL){
		Bucket3[start] = current->val;  //Bucket3,值
		start = start+1; 
		//	std::cout<<" value:v "<<i<<" numbers: "<<Bucket[i].numbers<<" :  "<<current->val<<" : "<<current->next<<std::endl;
		current = current->next;}
		}

		sampen(in,Length,Bucket1,Bucket2,Bucket3,Nb,samp);
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
