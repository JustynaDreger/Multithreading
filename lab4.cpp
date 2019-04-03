#include <stdio.h>
#include <iostream>
#include <math.h>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <sstream>
#include<fstream>
using namespace std;
int iXmax =50;
int iYmax =50;
const int MaxColorComponentValue=255;
static unsigned char color[1024][1024][3];
const int X=50,Y=50;
int tab[X][Y];
/*int tab[X][Y]={ 0,0,0,0,0,0,
				0,-1,-1,-1,-1,0,
				0,-1,0,0,-1,0,
				0,-1,0,0,-1,0,
				-1,-1,-1,-1,-1,-1,
				0,0,0,0,0,0};*/
mutex mtx;
//punkt początkowy
int Px=47,Py=0;
vector<thread *> T;
void f(int x, int y)
{
	//pobranie id watka
	stringstream ss;
	ss<<this_thread::get_id();
	int id = stoi(ss.str());

	int xx=x, yy=y;
	bool stop = false;

	mtx.lock();
	while(!stop)
	{
		tab[xx][yy]=id;
		//nie ma dalej przejscia
		if (tab[xx][yy - 1] >= 0 && tab[xx + 1][yy] >= 0 && tab[xx][yy + 1] >= 0 && tab[xx - 1][yy] >= 0)
		{
			stop = true;;
		}
		else
		{
			if (tab[xx][yy - 1] >= 0 && tab[xx + 1][yy] == -1 && tab[xx][yy + 1] >= 0 && tab[xx - 1][yy] >= 0)
			{
				xx = xx + 1;
			}
			else if (tab[xx][yy - 1] >= 0 && tab[xx - 1][yy] == -1 && tab[xx][yy + 1] >= 0 && tab[xx + 1][yy] >= 0)
			{
				xx = xx - 1;
			}
			else if (tab[xx - 1][yy] >= 0 && tab[xx][yy - 1] == -1 && tab[xx + 1][yy] >= 0 && tab[xx][yy + 1] >= 0)
			{
				yy = yy - 1;
			}
			else if (tab[xx - 1][yy] >= 0 && tab[xx][yy + 1] == -1 && tab[xx + 1][yy] >= 0 && tab[xx][yy - 1] >= 0)
			{
				yy = yy + 1;
			}

			else if (tab[xx][yy - 1] <= 0 && tab[xx + 1][yy] <= 0 && tab[xx][yy + 1] <= 0 && tab[xx - 1][yy] > 0)
			{
				if(tab[xx][yy - 1] == -1)
				{
					thread *t1 = new thread(f, xx, yy - 1);
					T.push_back(move(t1));
				}
				if(tab[xx][yy + 1] == -1)
				{
					thread *t1 = new thread(f, xx, yy + 1);
					T.push_back(move(t1));
				}
				if(tab[xx + 1][yy] == -1)
				{
					thread *t1 = new thread(f, xx + 1, yy);
					T.push_back(move(t1));
				}
				stop = true;
			}
			else if (tab[xx][yy - 1] <= 0 && tab[xx - 1][yy] <= 0 && tab[xx][yy + 1] <= 0 && tab[xx + 1][yy] > 0)
			{
				if(tab[xx][yy - 1] == -1)
				{
					thread *t1 = new thread(f, xx, yy - 1);
					T.push_back(move(t1));
				}
				if(tab[xx][yy + 1] == -1)
				{
					thread *t1 = new thread(f, xx, yy + 1);
					T.push_back(move(t1));
				}
				if (tab[xx - 1][yy] == -1)
				{
					thread *t1 = new thread(f, xx - 1, yy);
					T.push_back(move(t1));
				}
				stop = true;
			}
			else if (tab[xx - 1][yy] <= 0 && tab[xx][yy - 1] <= 0 && tab[xx + 1][yy] <=0 && tab[xx][yy + 1] > 0)
			{
				if(tab[xx - 1][yy] == -1)
				{
					thread *t1 = new thread(f, xx - 1, yy);
					T.push_back(move(t1));
				}
				if(tab[xx + 1][yy] == -1)
				{
					thread *t1 = new thread(f, xx + 1, yy);
					T.push_back(move(t1));
				}
				if (tab[xx][yy - 1] == -1)
				{
					thread *t1 = new thread(f, xx, yy - 1);
					T.push_back(move(t1));
				}
				stop = true;
			}
			else if (tab[xx - 1][yy] <= 0 && tab[xx][yy + 1] <= 0 && tab[xx + 1][yy] <=0 && tab[xx][yy - 1] > 0)
			{
				if(tab[xx - 1][yy] == -1)
				{
					thread *t1 = new thread(f, xx - 1, yy);
					T.push_back(move(t1));
				}
				if(tab[xx + 1][yy] == -1)
				{
					thread *t1 = new thread(f, xx + 1, yy);
					T.push_back(move(t1));
				}
				if(tab[xx][yy + 1] == -1)
				{
					thread *t1 = new thread(f, xx, yy + 1);
					T.push_back(move(t1));
				}
				stop = true;
			}
		}
	}
	mtx.unlock();
}
int main(){
	 /* screen ( integer) coordinate */
		   FILE * fp;
		   char *filename="labirynt.ppm";
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
		   ifstream dane("l.txt");
		   for(int i=0;i<X;i++){
		   		for(int j=0;j<Y;j++) {dane>>tab[i][j];}
		   	}
		   //wątki
		   thread *t = new thread(f,Px,Py);
		   		T.push_back(move(t));

		   		for (int i=0; i<T.size(); i++)
		   	    {
		   	    	T[i]->join();
		   	    	delete T[i];
		   	    }
		   		cout<<"Labirynt po przejściu"<<endl;
		   				for(int i=0;i<X;i++){
		   					for(int j=0;j<Y;j++) cout<<tab[i][j]<<" ";
		   					cout<<endl;
		   				}
		   //kolorowanie
		   	for(int i=0;i<X;i++){
		   		for(int j=0;j<Y;j++){
		   			if(tab[i][j]==0){color[i][j][0]=0;color[i][j][1]=0;color[i][j][2]=0;}
		   			else{
		   				if(tab[i][j]==-1){color[i][j][0]=255;color[i][j][1]=255;color[i][j][2]=255;}
		   				if(tab[i][j]%5==0){color[i][j][0]=123;color[i][j][1]=abs(tab[i][j]*51-255);color[i][j][2]=204;}
		   				if(tab[i][j]%5==1){color[i][j][0]=255;color[i][j][1]=abs(tab[i][j]*51-255);color[i][j][2]=204;}
		   				if(tab[i][j]%5==2){color[i][j][0]=104;color[i][j][1]=204;color[i][j][2]=abs(tab[i][j]*51-255);}
		   				if(tab[i][j]%5==3){color[i][j][0]=51;color[i][j][1]=abs(tab[i][j]*15-255);color[i][j][2]=255;}
		   				if(tab[i][j]%5==4){color[i][j][0]=255;color[i][j][1]=255;color[i][j][2]=204;}
		   			}

		   		}
		   	}
		   	 for(int i=0;i<iYmax;i++){
		   		for(int j=0;j<iXmax;j++){
		   	   		 fwrite(color[i][j],1,3,fp);
		   	   	}
		   	}
		   	cout<<"end";
		   	fclose(fp);
		   	return 0;
}
