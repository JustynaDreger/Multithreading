 #include <iostream>
#include <thread>
#include <math.h>
using namespace std;
//zmienne

  const int iXmax = 800;
  const int iYmax = 800;
  /* world ( double) coordinate = parameter plane*/

  const double CxMin=-2.5;
  const double CxMax=1.5;
  const double CyMin=-2.0;
  const double CyMax=2.0;
  /* */
  double PixelWidth=(CxMax-CxMin)/iXmax;
  double PixelHeight=(CyMax-CyMin)/iYmax;
  /* color component ( R or G or B) is coded from 0 to 255 */
  /* it is 24 bit color RGB file */
  const int MaxColorComponentValue=255;
  static unsigned char kolor[800][800][3];
  const int IterationMax=200;
  /* bail-out value , radius of circle ;  */
  const double EscapeRadius=2;
  double ER2=EscapeRadius*EscapeRadius;

  void f(int ymin,int r, int g, int b){
	int iX,iY;
	double Zx, Zy;
	double Zx2, Zy2;
	double Cx,Cy;
	int Iteration;
	for(iY=ymin;iY<(ymin+200);iY++)
	{
     Cy=CyMin + iY*PixelHeight;
     if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
     for(iX=0;iX<iXmax;iX++)
     {
                Cx=CxMin + iX*PixelWidth;
                /* initial value of orbit = critical point Z= 0 */
                Zx=0.0;
                Zy=0.0;
                Zx2=Zx*Zx;
                Zy2=Zy*Zy;
                /* */
                for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
                {
                    Zy=2*Zx*Zy + Cy;
                    Zx=Zx2-Zy2 +Cx;
                    Zx2=Zx*Zx;
                    Zy2=Zy*Zy;
                };
                /* compute  pixel color (24 bit = 3 bytes) */
                if (Iteration==IterationMax)
                { /*  interior of Mandelbrot set = black */
                   kolor[iY][iX][0]=0;
                   kolor[iY][iX][1]=0;
                   kolor[iY][iX][2]=0;

                }
             else
                { /* exterior of Mandelbrot set = white */
                     kolor[iY][iX][0]=r; /* Red*/
                     kolor[iY][iX][1]=g;  /* Green */
                     kolor[iY][iX][2]=b;/* Blue */
                };
        }
	}
}
int main(){

    /* screen ( integer) coordinate */
	thread t[4];
   FILE * fp;
   char *filename="new1.ppm";
   char *comment="# ";/* comment should start with # */

   /*create new file,give it a name and open it in binary mode  */
   fp= fopen(filename,"wb"); /* b -  binary mode */
   /*write ASCII header to the file*/
   fprintf(fp,"P6\n %s\n %d\n %d\n %d\n",comment,iXmax,iYmax,MaxColorComponentValue);
   /* compute and write image data bytes to the file*/

   t[0]=thread (f,0,255,0,0);
   t[1]=thread (f,200,0,255,0);
   t[2]=thread (f,400,0,0,255);
   t[3]=thread (f,600,255,0,255);

   for(int i=0;i<4;i++)	t[i].join();

   for(int i=0;i<iYmax;i++){
	   for(int j=0;j<iXmax;j++) fwrite(kolor[i][j],1,3,fp);
   }
   cout<<"juz";
   fclose(fp);
   return 0;
}

