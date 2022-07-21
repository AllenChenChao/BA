#include "sampen.hpp"
#include <string.h>
#include <math.h>
#include "bucket.hpp"
//#include <stdio.h>
#include<iostream>
// #define Length  500

void sampen(float *in, int len, int& SampEn)
{
#pragma HLS INTERFACE s_axilite port=return bundle=sqrt
#pragma HLS INTERFACE s_axilite port=len bundle=sqrt
#pragma HLS INTERFACE s_axilite port=SampEn bundle=sqrt
#pragma HLS INTERFACE m_axi depth=500 port=in offset=slave bundle=input
#pragma HLS INTERFACE s_axilite port=in
        clock_t begin = clock();

        typedef struct node {
        int val;
        struct node * next;
        } node_t;

        typedef struct BUCKET{
                int numbers;
                struct node * begin;
                struct node * end;
        } bucket_t;

        

        // std::cout<<"test:"<<1<<std::endl;

        //测试代码
        // Bucket[0].numbers = 2;
        // Bucket[0].begin = (node_t *) malloc(sizeof(node_t));
        // Bucket[0].end = Bucket[0].begin;
        // Bucket[0].end->val = 3;
        // Bucket[0].end->next = (node_t *) malloc(sizeof(node_t));
        // Bucket[0].end = Bucket[0].end->next;
        // Bucket[0].end->val = 4;
        // std::cout<<"val: "<<Bucket[0].end->val<<std::endl;

        // node_t * current = Bucket[0].begin;
        // while(current != NULL){
        //         std::cout<<"val: "<<current->val<<std::endl;
        //         current = current->next;
        // }


        len = Length;
        float buff[Length];
        // float r = 0.15;//float r = 21;
        float r = 0.2;
        
        int N = len;
        int m = 2;
        //int Samp;
        
        //
        int factor = 1;
        int m_factor = 2 * factor;
        float r_factor = r / factor;

        memcpy(buff, (const float*) in, len * sizeof(float));
    
        float X[Length-1];
        float Xmin = buff[0] + buff[1] ;
        float Xmax = buff[0] + buff[1] ;

        l1:for(int i = 0; i < len-1; i++){
                #pragma HLS loop_tripcount max=len-1
                X[i] = buff[i]+buff[i+1];
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

        //调试
 for(int i =0;i<Nb;i++){
 	node_t * current = Bucket[i].begin;
 while(current != NULL){
 	std::cout<<" value:v "<<i<<" numbers: "<<Bucket[i].numbers<<" :  "<<current->val<<" : "<<current->next<<std::endl;
 current = current->next;
 }}

//std::cout<<"last value"<<current->val<<std::endl;
        // loopBuckAssignment:for(int i = 0; i < len - 1; i++){
        //         #pragma HLS loop_tripcount max=len-1
        //         // std::cout<<"i:"<<i<<std::endl;
        //         bucketCount = (int)ceil(X[i]/(r_factor))-1;
        //         // std::cout<<"bucketCount:"<<bucketCount<<std::endl;
        //         if(bucketCount > Nb-1){bucketCount = Nb-1;}

        //         bucket[bucketCount][0] = bucket[bucketCount][0] + 1;
        //         bucketLocation = bucket[bucketCount][0];
        //         bucket[bucketCount][bucketLocation] = i;

        //         Bucket[bucketCount].numbers = Bucket[bucketCount].numbers + 1;
        //         if(Bucket[bucketCount].begin == NULL){
        //                 Bucket[bucketCount].begin= (node_t *) malloc(sizeof(node_t));
        //                 Bucket[bucketCount].end = Bucket[bucketCount].begin;
        //                 Bucket[bucketCount].end->val = i;
        //         }else{
        //                 Bucket[bucketCount].end->next = (node_t *) malloc(sizeof(node_t));
        //                 Bucket[bucketCount].end = Bucket[bucketCount].end->next;
        //                 Bucket[bucketCount].end->val = i;
        //         } 
     
        // }
        // std::cout<<"test:"<<3<<std::endl;
        clock_t middle= clock();
        // std::cout<<"bucketCount:"<<bucket[9][1]<<std::endl;
        int count1 = 0;
        int count2 = 0;
        int tempiNum;
        int tempjNum;
        int templocationik;
        int templocationjg;
        int templocationik_2;
        int templocationjg_2;
        float tempComparsion1;
        float tempComparsion2;
        float tempComparsion3;
        //统计
        unsigned int Nc = 0;

        // std::cout<<"test:"<<4<<std::endl;

        // loopBuckOutSearch: for(int i = 0; i < Nb; i ++){
        //         #pragma HLS loop_tripcount min=1 max=60
        //         int tempjLow = 0<i-m_factor?i-m_factor:0;
        //         int tempjHigh =i+m_factor+1<Nb? i+m_factor+1:Nb;
        //         // std::cout<<"i:"<<i<<std::endl;
        //         loopBuckInnerSearch:for(int j = tempjLow; j < tempjHigh; j ++){
        //                 #pragma HLS loop_tripcount min=3 max=5
        //                 // if(j < i - 2){continue;} 
        //                 // if(j >= i+3 ){continue;}    
        //                 tempiNum = bucket[i][0];  
        //                 tempjNum = bucket[j][0];          
        //                 loopBuckOutMatch:for(int k = 0; k < tempiNum;k++){
        //                         #pragma HLS loop_tripcount max=len-1
        //                         templocationik = bucket[i][k+1];                            
        //                         loopBuckInnerMatch:for(int g = 0; g < tempjNum ; g++){  
        //                                         //统计
        //                                         Nc = Nc + 1;
                          
        //                                 #pragma HLS loop_tripcount max=len-1
        //                                 templocationjg = bucket[j][g+1];
        //                                 tempComparsion1 = abs(buff[templocationik] - buff[templocationjg]);
        //                                 tempComparsion2 = abs(buff[templocationik+1] - buff[templocationjg+1]);
        //                                 if( tempComparsion1 <= r && tempComparsion2 <= r){
        //                                         count1 = count1 + 1;
        //                                         // std::cout<<"match:"<<templocationik<<" "<<templocationjg<<std::endl;
        //                                         tempComparsion3 = abs(buff[templocationik+2] - buff[templocationjg+2]);
        //                                         templocationik_2 = templocationik+2;
        //                                         templocationjg_2 = templocationjg+2;
        //                                         if( templocationik_2 < len && templocationjg_2 < len &&  tempComparsion3 <= r) {
        //                                                 count2 = count2 + 1;
        //                                         }
        //                                 } 
        //                         }
        //                 }
                       
        // 	}
        // }
        // std::cout<<"Nb:"<<Nb<<std::endl;
        loopBuckOutSearch: for(int i = 0; i < Nb; i ++){
                #pragma HLS loop_tripcount min=1 max=60
                int tempjLow = 0<i-m_factor?i-m_factor:0;
                int tempjHigh =i+m_factor+1<Nb? i+m_factor+1:Nb;
                // std::cout<<"i:"<<i<<std::endl;
                // if(i == 10) std::cout<<"i:"<<i<<"m_factor"<<m_factor<<std::endl;
                loopBuckInnerSearch:for(int j = tempjLow; j < tempjHigh; j ++){
                        // if(i == 10) std::cout<<"j:"<<j<<std::endl;
                        #pragma HLS loop_tripcount min=3 max=5
                        // if(j < i - 2){continue;} 
                        // if(j >= i+3 ){continue;}    
                        tempiNum = Bucket[i].numbers;    //这里 i 可能重复了，也许放外面更好。
                        tempjNum = Bucket[j].numbers;   

// current = current->next;

                        node_t * currenti = Bucket[i].begin;  //这里 i 可能重复了，也许放外面更好。
                        
                        // if(i == 10 and j == 10) std::cout<<"i:j:"<<j<<std::endl;
                        loopBuckOutMatch:for(int k = 0; k < tempiNum;k++){
                                #pragma HLS loop_tripcount max=len-1
                                templocationik = currenti->val; 
                                currenti = currenti->next;  
                                // if(i == 10 and j == 10) std::cout<<"i:j:"<<j<<std::endl;    
                                node_t * currentj = Bucket[j].begin;                     
                                loopBuckInnerMatch:for(int g = 0; g < tempjNum ; g++){  

                                        //for debug
                                        // if(i == 10 and j == 10) {
                                        // std::cout<<"detail: "<<tempjNum<<" detail: "<<g<<std::endl;
                                        // std::cout<<"i:j:"<<j<<" currentj: "<<currentj->val<<std::endl;}
                                                //统计
                                                Nc = Nc + 1;
                          
                                        #pragma HLS loop_tripcount max=len-1
                                        templocationjg = currentj->val;
                                        currentj = currentj->next;
                                        tempComparsion1 = abs(buff[templocationik] - buff[templocationjg]);
                                        tempComparsion2 = abs(buff[templocationik+1] - buff[templocationjg+1]);
                                        if( tempComparsion1 <= r && tempComparsion2 <= r){
                                                count1 = count1 + 1;
                                                // std::cout<<"match:"<<templocationik<<" "<<templocationjg<<std::endl;
                                                tempComparsion3 = abs(buff[templocationik+2] - buff[templocationjg+2]);
                                                templocationik_2 = templocationik+2;
                                                templocationjg_2 = templocationjg+2;
                                                if( templocationik_2 < len && templocationjg_2 < len &&  tempComparsion3 <= r) {
                                                        count2 = count2 + 1;
                                                }
                                        } 
                                }
                        }
                       
        	}
        }

        // std::cout<<"count1:"<<count1<<std::endl;
        // std::cout<<"count2:"<<count2<<std::endl;
        count1 = count1 - len + m -1;
        float B = (float)count1/((N-m+1)*(N-m));
        count2 = count2 - len + m ;
        // std::cout<<"count1:"<<count1<<std::endl;
        // std::cout<<"count2:"<<count2<<std::endl;
        float A = (float)count2/((N-m)*(N-m-1));
        if(A == 0){SampEn = 100000;}
        else {SampEn = int(1000*log(B/A));}
        if (SampEn < 0){SampEn = 0;}
        clock_t end= clock();
        //统计
        // std::cout<<"Nb: "<<Nb<<" Nc: "<<Nc<<std::endl;
        std::cout<<"B: "<<B<<" A: "<<A<<std::endl;
        //
        std::cout<<"core time:"<<" time initial:"<<(double)(middle - begin) / CLOCKS_PER_SEC<<" time match:"<<(double)(end - middle) / CLOCKS_PER_SEC<<std::endl;
        //
}
