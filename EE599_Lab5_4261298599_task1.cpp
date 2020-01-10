#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string>


using namespace std;

class City {
private:
	string CityName;
	int X,Y;
	int index;
public:

	City() {}
	City(int x, int y, int num) {
		X = x;
		Y = y;
		index = num;
		CityName = "CityNo" + to_string(num);


	}
	void setX(int x) {
		X = x;
	}
	void setY(int y) {
		Y = y;
	}
	
	void setIndex(int in) {
		index = in;
	}
	void setCityName(int num) {
		CityName = "CityNo" + to_string(num);
	}
	int getX() {
		return X;
	}
	int getY() {
		return Y;
	}
	int getIndex() {
		return index;

	}
	string getCityName() {
		return CityName;
	}
};


	void stateChange(int num, City *cities) {

	   int i = (int)(num*(rand()/(double)(RAND_MAX)));
      int j = (int)(num*(rand()/(double)(RAND_MAX)));

	   City temp;
	   temp = cities[i];
	   cities[i]=cities[j];
	   cities[j]=temp;
  
   }

   int distance(City city1, City city2) {
	   int x1 = city1.getX();
	   int x2 = city2.getX();
	   int y1 = city1.getY();
	   int y2 = city2.getY();

	   return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));

   }
   
   int cost(int num, City *cities) {
	   int length = 0;
	
	   for (int i = 0; i < num-1; i++) {
		   length += distance(cities[i], cities[i + 1]);
	   }
	   length +=distance(cities[0], cities[num-1]);
	   return length;

   }  
   
   void copy(int num, City * cities1,City *cities2){
      for (int i= 0; i<num; i++){
         cities2[i].setX(cities1[i].getX());
         cities2[i].setY(cities1[i].getY());
         cities2[i].setIndex(cities1[i].getIndex());

      }

   }



class SimulatedAnnealing {
private:
	double T_start;
	double T_end;
	int num;
	double T;
	double P;
	double rate;
	double costOriginal, costChange;
	double r;
	
	City *cities;
	City *citiesChange;
	City *citiesTemp;
public:
	SimulatedAnnealing() {
		cities = NULL;
	}
	SimulatedAnnealing(double value1, double value2, istream &infile) {
		T_start = value1;
		T_end = value2;
		
		int x, y,index;
		infile >> num;
		cities = new City[num];
		citiesChange = new City[num];
		citiesTemp = new City[num];
		for (int i = 0; i < num; i++) {
			infile >> index;
			infile >> x;
			infile >> y;
			cities[i].setX(x);
			cities[i].setY(y);
			cities[i].setCityName(index);
			cities[i].setIndex(index);
			
		}
	}
	
	~SimulatedAnnealing() {
		delete[] cities;
	}
	
	void setNum(int n) {
		num = n;
	}
	

   
	void solve() {
      T = T_start;
      srand(time(NULL));
      int count = 0;
      int iter =0;
		while (T > 0.000001) {
		
			
			   copy(num,cities,citiesChange);   
				costOriginal = cost(num, cities);
			
				stateChange(num, citiesChange);
	   		
				costChange = cost(num, citiesChange);
				rate = (costChange - costOriginal) / costOriginal;

				if (rate < 0) {
					copy(num,citiesChange,cities);
					count = 0;
				}
				else {
					
					P = exp(-rate/T);
					r = (double)rand() / RAND_MAX;
					if (P > r) {
						copy(num,citiesChange,cities);
						T=T *0.95;
						count=0;
					}
				}
			iter ++;	
			count ++;
			if(count > 50000) break;
			}
	
	}

	void print() {
	ofstream outfile1("Lab5_partI_task1_output.txt");
	   outfile1 << "Final Distance of SA Method: " <<cost(num, cities)<<endl;
		for (int i = 0; i < num; i++) {
			int indexCity =cities[i].getIndex();
			
         outfile1 << indexCity << endl;
       
		}

   outfile1.close();
	}
	
};


class Greedy {
private:
	int num;
	City *cities2;
	//City *citiesChange;
	//double costOriginal, costChange;
public:
	Greedy() {
		cities2 = NULL;
	}
	Greedy(istream & infile) {
		int x, y,index;
		infile >> num;
		cities2 = new City[num];
		for (int i = 0; i < num; i++) {
			infile >> index;
			infile >> x;
			infile >> y;
			cities2[i].setX(x);
			cities2[i].setY(y);
			cities2[i].setCityName(index);
			cities2[i].setIndex(index);
			
	   }
	}
	~Greedy() {
		delete[] cities2;
	}
	
	void swap(int i, int j, City *cities2) {
		City temp;
	   temp = cities2[i];
	   cities2[i]=cities2[j];
	   cities2[j]=temp;
	
	}
	
	
	void solve() {
	   int distanceOriginal=0;
	   int distanceChange;
	   int smallestIndex=1;

	   for (int i=0;i<num-1;i++){
   
         distanceOriginal = distance(cities2[i],cities2[i+1]);
         
         for(int j=i+2;j<num;j++){
            
            distanceChange=distance(cities2[i],cities2[j]);
            
               if(distanceChange<distanceOriginal) {
                  
                  distanceOriginal = distanceChange;
                  swap(smallestIndex,j,cities2);                         
               }                             
	      }
	   smallestIndex ++;
	   }
	
	}
	
		void print() {
		ofstream outfile2("Lab5_partI_task2_output.txt");
	   outfile2 << "Final Distance of Greedy Method: " <<(int)cost(num, cities2)<<endl;
	   
		for (int i = 0; i < num; i++) {
			int indexCity =cities2[i].getIndex();
			
         outfile2 << indexCity << endl;
       
		} outfile2 <<cities2[0].getIndex();
		outfile2.close();
	}
	
};

int main() {
	ifstream inFile("Lab5_partI_input.txt");
	if (!inFile) {
		cerr << "Error opening file.." << endl;
		return(1);
	}
	
	SimulatedAnnealing s = SimulatedAnnealing(100, 1e-6, inFile);
	s.solve();
	s.print();
	
	ifstream inFile2("Lab5_partI_input.txt");

   Greedy g = Greedy(inFile2);
   g.solve();
   g.print();

   inFile.close();
   inFile2.close();
	return 0;
}
