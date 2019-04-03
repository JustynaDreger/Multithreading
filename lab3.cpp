#include <iostream>
#include <thread>
#include <math.h>
#include <vector>
using namespace std;
int iXmax =1024;
int iYmax =1024;
const int MaxColorComponentValue=255;
static unsigned char color[1024][1024][3];
int N=1024;
void f(int wX,int wY,int level){
	thread W[3];
	int rozm=N/(pow(2,level));
	if(rozm >= 8){
		W[0] =thread(f,wX,wY,level+1);
		W[1]=thread(f,wX+rozm/2,wY,level+1);
		W[2]=thread(f,wX+rozm/2,wY+rozm/2,level+1);
		W[0].join();
		W[1].join();
		W[2].join();
		//f(wX,wY,rozm/2);
		//f(wX+rozm/2,wY,rozm/2);
		//f(wX+rozm/2,wY+rozm/2,rozm/2);
	}
	for(int i=wX;i<wX+rozm;i++){
		color[i][wY][0]=0;
		color[i][wY][1]=0;
		color[i][wY][2]=0;
	}
	int k=wX+rozm-1;
	for(int j=wY;j<wY+rozm;j++){
		color[k][j][0]=0;
		color[k][j][1]=0;
		color[k][j][2]=0;
	}
	for(int m=wX;m<wX+rozm;m++){
			color[m][m][0]=0;
			color[m][m][1]=0;
			color[m][m][2]=0;
	}
}
int main(){
    /* screen ( integer) coordinate */
   FILE * fp;
   char *filename="trojkat.ppm";
   char *comment="# ";/* comment should start with # */
   /*  */
   /*create new file,give it a name and open it in binary mode  */
   fp= fopen(filename,"wb"); /* b -  binary mode */
   /*write ASCII header to the file*/
   fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);
   /* compute and write image data bytes to the file*/
   for(int i =0; i < iXmax;i++){
   	for (int j =0; j<iYmax;j++){
   		color[i][j][0]=255;
   		color[i][j][1]=255;
   		color[i][j][2]=255;
   	}
   }
  f(0,0,0);
  for(int i=0;i<iYmax;i++){
	for(int j=0;j<iXmax;j++){
   		 fwrite(color[i][j],1,3,fp);
   	}
   }
cout<<"end";
   fclose(fp);
   return 0;
}
