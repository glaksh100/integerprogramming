#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <vector>
const int M=100;
using namespace std;
using namespace std;
void generate_tour(int x[M][M],int n);
void swap_vertices(int i, int j, int arr[M][M], int n);
int calc_cost(int c[M][M], int x[M][M], int n);
void arrcopy(int source[M][M],int dest[M][M], int n);
void printarr(int x[M][M], int n);
void reverse_vertices(int i, int j, int arr[M][M], int n);
void printtour(int arr[M][M],int n);

// A function to generate the initial tour


int main (int argc, char* argv[])
{
	// formulate the the TSP ILP from input data
	int a=0;
    int number_of_vertices=0;
    int c[M][M];
    ifstream input_filename(argv[1]);

    if (input_filename.is_open()) {
		
		cout << "Input File Name: " << argv[1] << endl;
    	input_filename >> number_of_vertices;
		cout << "Number of Vertices = " << number_of_vertices << endl;
	
	
    for (int i=0;i<number_of_vertices;i++)
    {
        for (int j=0; j<number_of_vertices; j++)
        {
            int value_just_read;
			input_filename >> value_just_read;
            c[i][j]=value_just_read;
            
            
        }
        
      
    }
   
    
    

  
   	int n=number_of_vertices;
	int x[M][M];
    int existing_tour[M][M],best_sr_tour[M][M],original_tour[M][M],original_tour_new[M][M];
    int new_tour[M][M];
    int best_cost,new_cost,new_cost_swap,new_cost_rev,best_sr_cost;
    generate_tour(x,n);
    best_cost=calc_cost(c,x,n);
    best_sr_cost=calc_cost(c,x,n);
    //cout<<best_cost;
    arrcopy(x,existing_tour,n);
    arrcopy(x,best_sr_tour,n);


do{
	best_cost=best_sr_cost;
	arrcopy(best_sr_tour,existing_tour,n);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n && i!=j;j++){
			arrcopy(existing_tour,original_tour,n);
			reverse_vertices(i,j,existing_tour,n);
		
			new_cost_rev=calc_cost(c,existing_tour,n);
			if(new_cost_rev<best_sr_cost){
				best_sr_cost=new_cost_rev;
				arrcopy(existing_tour,best_sr_tour,n);
			}
			//generate_tour(existing_tour,n);
			arrcopy(original_tour,original_tour_new,n);
			swap_vertices(i,j,original_tour,n);
			new_cost_swap=calc_cost(c,original_tour,n);
			//cout<<new_cost_swap<<endl;
			if(new_cost_swap<best_sr_cost){
				best_sr_cost=new_cost_swap;
				arrcopy(original_tour,best_sr_tour,n);
			}
			arrcopy(original_tour_new,existing_tour,n);
			


	}

}

	
} while(best_sr_cost<best_cost);
	
	cout<<"best_cost  "<<best_cost<<endl;
	printtour(best_sr_tour,n);
}
else
 cout<<"Input File Missing"<<endl;
    return(0);
   }
void generate_tour(int x[M][M], int n)
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            x[i][j]=0;
        }
    }
        for (int i=0; i<n; i++) {
                if(i<n-1)
                    x[i][i+1]=1;
                else
                    x[i][0]=1;
            }

    
    

    
}
void swap_vertices(int i, int j, int arr[M][M], int n){
	/*for (int i=0; i <=3 ; i++)
	{
		for (int j=0; j <=3 ; j++)
		{
			arr[i][j] = 0;
		}
	}*/
	int ni1,ni2,nj1,nj2;
	if(i!=0)
		ni1=i-1;
	else
		ni1=n-1;
	if(j!=0)
		nj1=j-1;
	else
		nj1=n-1;
	if(i!=n-1)
		ni2=i+1;
	else
		ni2=0;
	if(j!=n-1 )
		nj2=j+1;
	else 
		nj2=0;

	arr[i][ni2]=0;
	arr[ni1][i]=0;
	arr[j][nj2]=0;
	arr[nj1][j]=0;
	if(j!=i+1 && !(i==0 && j==n-1)){
		arr[ni1][j]=1;
	
		arr[nj1][i]=1;
	
		arr[j][ni2]=1;
	
		arr[i][nj2]=1;
	}
	else{
		if(j==i+1){
			arr[i][nj2]=1;
			arr[ni1][j]=1;
			arr[j][i]=1;

		}
		if(i==0 && j==n-1){
			arr[i][j]=1;
			arr[nj1][i]=1;
			arr[j][ni2]=1;
		}
	}

}
void reverse_vertices(int i, int j, int arr[M][M],int n){
	/*for (int i=0; i <=3 ; i++)
	{
		for (int j=0; j <=3 ; j++)
		{
			arr[i][j] = 0;
		}
	}*/
	int ni1,ni2,nj1,nj2;
	if(i!=0)
		ni1=i-1;
	else
		ni1=n-1;
	
	if(j!=n-1 )
		nj2=j+1;
	else 
		nj2=0;

	arr[ni1][i]=0;
	arr[j][nj2]=0;
	if(i==0 && j==n-1){
		arr[i][j]=1;
	}
	else{	
		arr[i][nj2]=1;
		arr[ni1][j]=1;
	}
	
	while(j>i){
		//cout<<"yes";
		arr[j][j-1]=1;
		arr[j-1][j]=0;
		j=j-1;
	}

}
int calc_cost(int c[M][M], int x[M][M], int n){
	int pdt=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
		
			pdt+=x[i][j]*c[i][j];
			
		}
	}
	return pdt;
}
void arrcopy(int source[M][M],int dest[M][M],int n){
	for (int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dest[i][j]=source[i][j];
		}
	}
}
void printarr(int x[M][M],int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<x[i][j];
		}
		cout<<endl;
	}
}

void printtour(int arr[M][M],int n){
	int current;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(arr[i][j]==1)
				current=j+1;
		}
	}
	cout<<current<<"-->";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(arr[i][j]==1){
				if(j+1!=current)
				cout<<j+1<<"-->";
				else
				cout<<j+1;
			}
		}
	}
cout<<endl;
}
