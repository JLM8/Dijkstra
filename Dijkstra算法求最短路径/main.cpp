#include<iostream>
#include<stack>
#include"_Matrix.h"
using namespace std;

int main(){
	//输入顶点和边的个数
	int num_vertexs,  num_sides;
	cout<<"Please input the number of vertexs..."<<endl;
	cin>>num_vertexs;
	cout<<"Please input the number of sides..."<<endl;
	cin>>num_sides;
	//创建相应的邻接矩阵 并将其值都初始化为-1 代表两点之间距离无限远
	_Matrix A(num_vertexs,num_vertexs);
	//用户输入此图为有向图还是无向图
	int type;
	cout<<"Please input the type of this map...Inputing '1' represents DIRECTED GRAPH. Inputing '0' represents UNDIRECTED GRAPH..."<<endl;
	do{
		cin>>type;
		if(type!=0 && type!=1)
			cout<<"Your input is wrong!!!\nPlease re-input!\nInputing '1' represents DIRECTED GRAPH. Inputing '0' represents UNDIRECTED GRAPH..."<<endl;
	}while(type!=0 && type!=1);
	//对邻接矩阵的各个位置进行相应权的赋值
	cout<<"Please input the distance of each side as 'vertex 1' 'vertex 2' 'distance'..."<<endl;
	cout<<"And if your graph is DIRECTED GRAPH, vertex 1 is start and vertex 2 is end !!!"<<endl;
	cout<<"NOTICE!!! 0<VERTEX<=NUMBER OF VERTEXS!!! DISTANCE > 0 !!!"<<endl;
	for(int i=0; i<num_sides; i++){
		cout<<"Please input the SIDE "<<i+1<<" ..."<<endl;
		int vertex1, vertex2, distance;
		do{
			cin>>vertex1>>vertex2>>distance;
			vertex1-=1;
			vertex2-=1;
			//区别不同类型图进行赋值
			if(type == 0){
				A.write(vertex1,vertex2,distance);
				A.write(vertex2,vertex1,distance);
			}else
				A.write(vertex1,vertex2,distance);

			if(vertex1<0 || vertex2<0 || vertex1>num_vertexs-1 || vertex2>num_vertexs-1 || distance<=0){
				cout<<"Your input is wrong!!!\nNOTICE!!! 0<VERTEX<=NUMBER OF VERTEXS!!! DISTANCE > 0 !!!"<<endl;
				cout<<"Please re-input the SIDE "<<num_sides<<" ..."<<endl;
			}
		}while(vertex1<0 || vertex2<0 || vertex1>num_vertexs-1 || vertex2>num_vertexs-1 || distance<=0);
	}
	//赋权矩阵展示
	cout<<"Your Matrix is..."<<endl;
	A.display();
	//Dijkstra算法
	//<1
	int u,t;
	cout<<"Please input which Two Vertexs's distance you want to know..."<<endl;
	cin>>u>>t;
	/*
	int * S = new int [num_vertexs+1];
	S[num_vertexs] = 1;
	S[0] = u;*/
	_Matrix S(2,num_vertexs+1);
	S.write(0,num_vertexs,1);
	S.write(0,0,u);
	S.write(1,0,0);

	_Matrix T(2,num_vertexs-1);
	for(int i=0; i<num_vertexs-1; i++){
		if(i == u-1)
			break;
		else
			T.write(0,i,i+1);
	}
	for(int i=u-1; i<num_vertexs-1; i++){
		T.write(0,i,i+2);
	}
	//显示T
	/*
	cout<<"T is ..."<<endl;
	T.display();
	*/
	//创建Dijkstra算法的矩阵
	_Matrix B(num_vertexs-1,num_vertexs+1);

    //<2 处理Dijkstra算法矩阵中第一行的数据
	//cout<<"<2"<<endl;
	bool u_withside = false;
	for(int i=0; i<num_vertexs-1; i++){
		if(A.read(u-1,T.read(0,i)-1) != -1){
			B.write(0,i,A.read(u-1,T.read(0,i)-1));
			u_withside = true;
		}
	}
     if(u_withside){
		 int row = 0;
		 int result = 0;
		 while(row != num_vertexs-1){
			 //<3
			 //该行 t l(t) 的赋值
			// cout<<"<3"<<endl;
			 int min=0;
			 int num=0;
			 for(int i=0; i<num_vertexs-1; i++){
				 if(B.read(row,i) > min){
					 min = B.read(row,i);
					 num = T.read(0,i);
					 for(int j=i+1; j<num_vertexs-1; j++){
						 if(B.read(row,j) < min && B.read(row,j) != -1){
							 min = B.read(row,j);
							 num = T.read(0,j);
						 }
					 }
					 break;
				 }
			 }
			 B.write(row,num_vertexs-1,num);
			 B.write(row,num_vertexs,min);

			 //打印B的该行值
			 /*
			 cout<<"B->No."<<row<<endl;
			 for(int i=0; i<num_vertexs+1; i++){
				 cout<<B.read(row,i)<<"\t";
			 }
			 cout<<endl;*/

			 //判断该点是否为t
			 if(num == t){
				 result = min;
				 break;
			 }

			 //<4 
			 //S = SU{t} 
			// cout<<"<4"<<endl;

			 S.write(0,S.read(0,num_vertexs),num);
			 S.write(1,S.read(0,num_vertexs),min);
			 S.write(0,num_vertexs,S.read(0,num_vertexs)+1);
			//打印S
			 /*
			 cout<<"S ..."<<endl;
			 for(int i=0; i<S.read(0,num_vertexs); i++)
				 cout<<S.read(0,i)<<"\t";
			 cout<<endl;
			 */
			 //T =T - {t};
			 for(int i= 0; i<num_vertexs-1; i++){
				 if(T.read(0,i) == num)
					 T.write(1,i,0);
			 }
			 //打印T
			 /*
			 cout<<"T ..."<<endl;
			 for(int i=0; i<num_vertexs-1; i++){
				 if(T.read(1,i) != 0)
					 cout<<T.read(0,i)<<"\t";
			 }*/
 
			 //<5
			// cout<<"<5"<<endl;

			 bool end = true;
			 for(int i=0; i<num_vertexs-1; i++){
				 if(T.read(1,i) != 0){
					 end = false;
				 }
			 }
			 if(end == true)
				 break;
			 
			 //对于T集合的x, ls(x) = min{ ls(x) , ls(t) + W(t,x)};
			 row+=1;
			 for(int i=0; i<num_vertexs-1; i++){
				 if(A.read(num-1,T.read(0,i)-1) != -1 && T.read(1,i) != 0){
					 int min1=B.read(row-1,i);
					 int min2 = A.read(num-1,T.read(0,i)-1) + min;
					 /*
					 bool withmin2 = false;
					 for(int j=1; j<S.read(0,num_vertexs); j++){
						 if(A.read(S.read(0,j),T[i]) != -1){
							 min2 = S.read(1,j) + A.read(S.read(0,j),T[i]);
							 withmin2 = true; 
						 }
					 }*/
					 if(min1 != -1){
						 if(min1<min2)
							 B.write(row,i,min1);
						 else
							 B.write(row,i,min2);
					 }else
						 B.write(row,i,min2);
				 }
			 }
		 }
		 cout<<"The distance between vertex "<<u<<" and vertex "<<t<<" is "<<result<<" ."<<endl;
		 cout<<"The route is ";
		 row+=1;
		 int list = 0;
		 int p = t;
		 stack<int> num;
		 num.push(t);
		 while(row--){
			 for(int i=0; i<num_vertexs-1; i++){
				 if(T.read(0,i)==p)
					 list = i;
			 }

			 for(int i = row; i>=0; i--){

				 if(B.read(i-1,list) != B.read(i,list)){
					 row = i -1;
					 break;
				 }
				
			 }
			 if(row == -1)
				 break;

			 num.push(B.read(row,num_vertexs-1));
			 p = B.read(row,num_vertexs-1);
			 row+=1;
	
		 }
		 num.push(u);
		 while(!num.empty()){
			 int i = num.top();
			 num.pop();
			 cout<<i<<" ";
		 }
		 cout<<endl;
	 }else
		 cout<<"The vertex u have not side. The distance between u and t is infinite!"<<endl;





	B.free_matrix();
	T.free_matrix();
	S.free_matrix();
	A.free_matrix();
	system("pause");
	return 0;
}