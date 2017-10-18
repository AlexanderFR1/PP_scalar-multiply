#define VECSIZE 3
#include <mpi.h> 
#include <iostream> 
#include <vector> 
using namespace std; 

int main(int argc, char **argv) 
{ 
	double sumA, sumB,tempA=0.0,tempB=0.0,res,wew;
	int ProcRank, coutOfProcs,i; 
	int n=VECSIZE;
	int done=0;
	sumA=0.0;
	sumB=0.0;
	vector<int> a(VECSIZE),b(VECSIZE); 
	double cos; 
	
	MPI_Init(&argc, &argv); 
	MPI_Comm_size(MPI_COMM_WORLD,&coutOfProcs); 
	MPI_Comm_rank(MPI_COMM_WORLD,&ProcRank); 

		if(ProcRank==0)
		{
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
				MPI_Finalize();
				return 0;
			}
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	
		for (i = ProcRank + 1; i <= n; i += coutOfProcs) //почему-то всё выполняется на одном процессоре
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

