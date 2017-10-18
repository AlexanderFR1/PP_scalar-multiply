#define VECSIZE 3
#include <mpi.h> 
#include <iostream> 
#include <vector> 
using namespace std; 

int main(int argc, char **argv) 
{ 
	double sumA, sumB,tempA=0,tempB=0,res,wew;
	int ProcRank, coutOfProcs,i; 
	int n=VECSIZE;
	vector<int> a(VECSIZE),b(VECSIZE); 
	double cos; 
	cout<<"vector a:\n"; 
	for (int j=0;j<VECSIZE;j++)
		cin>>a[j];
	cout<<"vector b:\n"; 
	for (int j=0;j<VECSIZE;j++)
		cin>>b[j];
	cout<<"cosinus:\n"; 
	cin>>cos; 
	if((cos>1)||(cos<-1))
	{
		cout<<"Wrong cosinus\n";
		return 0;
	}
	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD,&coutOfProcs); 
	MPI_Comm_rank(MPI_COMM_WORLD,&ProcRank); 
	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	sumA=0.0;
	sumB=0.0;
	for (i = ProcRank + 1; i <= n; i += coutOfProcs) 
	{
		tempA+=a[ProcRank]*a[ProcRank];
		tempB+=b[ProcRank]*b[ProcRank];
	}
	MPI_Reduce(&tempA,&sumA,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	MPI_Reduce(&tempB,&sumB,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
	if(ProcRank==0)
	{
		res=sqrt(sumA)*sqrt(sumB)*cos;
		cout<<"a*b = "<<res<<"\n";		
	}
	MPI_Finalize();
	cin>>wew;
	return 0;
}
