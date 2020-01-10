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
	      double sum=0;
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
	

   
	double solve() {
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
						sum +=rate;
						iter ++;	
					}
				}
			
			count ++;
			
			if(count > 50000) break;
			}
			//cout << sum;
			//cout <<"\n"<<iter<<endl;
			//cout <<  double(sum/iter)<< endl;
			return double(sum/iter);
			
	
	}


	
};




int main() {
	ifstream inFile("Lab5_partI_input.txt");
	if (!inFile) {
		cerr << "Error opening file.." << endl;
		return(1);
	}
	
	SimulatedAnnealing s = SimulatedAnnealing(100, 1e-6, inFile);
	double r = s.solve();
	//cout <<r<<endl;
	double T0=-r/log(0.8);
	cout <<"T0 is: "<< T0<<endl;
	


   inFile.close();

	return 0;
}
