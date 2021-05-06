//~ while (clock()<=69*CLOCKS_PER_SEC)
//~ #pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("O3")
//~ #pragma GCC target ("avx2")
//~ #pragma GCC optimize("Ofast")
//~ #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
//~ #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
using namespace __gnu_pbds;
using namespace std;
 
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
    *this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "
 
#define shandom_ruffle random_shuffle


#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;i++)
const int N=20;
const double eps=1e-10;

struct Judeg_mat{ //判断矩阵 
    string name;
	double  a[N][N];
	double m[N];
	double w[N];
	int size;
	vector<int >son; 
}U[20];

struct Fuzzy_mat{ //模糊矩阵 
    string name;
    double  a[N][N];
    int r,c;
    double membership[N];
    vector<int >son;
    double score;
	string degree; 
   	void clear(){
		rep(i,1,N-1) rep(j,1,N-1) a[i][j]=0;
	}
}F[20];


void init(){ //初始化模糊矩阵和判断矩阵的相关参数 
	rep(i,1,12)
	 if(i==1||i==3||i==4||i==6) U[i].size=3;
	 else U[i].size=2;
	U[1].name="区域轨道交通系统运输综合评价U";
	U[2].name="换乘衔接协同性U1"; 
    U[3].name="跨线运营协同性U2";
    U[4].name="网络系统协同性U3";
    U[5].name="运营组织U11";
    U[6].name="运营管理U12";
    U[7].name="技术体系协同性U21";
    U[8].name="运输组织协同性U22";
    U[9].name="运营管理协同性U23";
    U[10].name="多制式线网协同度U31";
    U[11].name="多制式规划协同度U32";
    U[12].name="多制式管理协同度U33";

	U[1].son.pb(2),U[1].son.pb(3),U[1].son.pb(4);
	U[2].son.pb(5),U[2].son.pb(6);
	U[3].son.pb(7),U[3].son.pb(8),U[3].son.pb(9);
	U[4].son.pb(10),U[4].son.pb(11),U[4].son.pb(12);
		
	rep(i,1,12) F[i].son=U[i].son,F[i].r=U[i].size,F[i].c=5,F[i].name=U[i].name;  
}

double cal(double x,int n){
	//明显res具有单调性 ，采用Binary search
	double l=0,r=1e6;
	while(fabs(r-l)>=eps){
		double mid=(l+r)/2;
		double t=1; rep(i,1,n) t*=mid;
		if(t<=x) l=mid;
		else r=mid;
	}
	return l;
}

vector<double> mul(Fuzzy_mat a,Fuzzy_mat b){ //矩阵乘法 
	Fuzzy_mat temp;temp.clear();
	
	rep(i,1,a.r)
	rep(j,1,b.c)
	rep(k,1,a.c)
      temp.a[i][j]+=a.a[i][k]*b.a[k][j];	

	vector<double >res;
	rep(i,1,5) res.pb(temp.a[1][i]);
	return res; 
}

string solve(double x){
	if(abs(x-1)<=0.5) return "差";
	if(abs(x-2)<=0.5) return "交差";
	if(abs(x-3)<=0.5) return "一般";
	if(abs(x-4)<=0.5) return "较好";
	if(abs(x-5)<=0.5) return "好";			
}

void dfs(int u){
	//递归到叶子节点，直接处理隶属度并retuen 
	if(u>=5){
		Fuzzy_mat temp; temp.clear();temp.r=1,temp.c=U[u].size; //得到权值矩阵 
        rep(i,1,temp.c) temp.a[1][i]=U[u].w[i];	
        
		vector<double >g=mul(temp,F[u]); //权值矩阵乘模糊矩阵得到结果向量
		double sum=0; 
		rep(i,1,5) F[u].membership[i]=g[i-1],sum+=i*F[u].membership[i];
		F[u].score=sum; F[u].degree=solve(F[u].score);
		return ;
	}
	
	//遍历和处理儿子节点 
	for(auto v:F[u].son) dfs(v);
	
    //回溯处理当前节点的隶属度 
    Fuzzy_mat temp; temp.clear();temp.r=1,temp.c=U[u].size; //得到权值矩阵 
    rep(i,1,temp.c) temp.a[1][i]=U[u].w[i];	
    
	rep(i,1,F[u].r)  //合并所有儿子节点的隶属度向量得到当前节点的模糊矩阵 
     rep(j,1,5)
	F[u].a[i][j]=F[F[u].son[i-1]].membership[j];  
          
	vector<double >g=mul(temp,F[u]); //权值矩阵乘模糊矩阵得到结果向量 
	double sum=0; 
	rep(i,1,5) F[u].membership[i]=g[i-1],sum+=i*F[u].membership[i];
	F[u].score=sum; F[u].degree=solve(F[u].score);
}

void print(int u){ //输出隶属度及结果函数 
//  double sum=0; 
	cout<<F[u].name<<":(";
//	for(int i=1;i<=5;i++) if(i!=5)cout<<F[u].membership[i]<<","; else cout<<F[u].membership[i]<<")\n";
	cout<<F[u].score<<","<<F[u].degree<<")"<<endl;
	
//    cout<<U[u].name<<":(";
//    for(int i=1;i<=U[u].size;i++) {
//	if(i!=U[u].size)cout<<U[u].w[i]<<",";

	// else cout<<U[u].w[i]<<")";}
    //cout<<endl;
	for(auto v:F[u].son) print(v);
}

void AHP(){
	//读入判断矩阵 
    rep(i,1,12) rep(j,1,U[i].size) rep(k,1,U[i].size) cin>>U[i].a[j][k];
	
	//计算权值 
	
	//step 1.计算判断矩阵每一行的乘积Mi 
	rep(i,1,12) 
	for(int j=1;j<=U[i].size;j++){
	    double temp=1;
		rep(k,1,U[i].size) temp*=U[i].a[j][k];	
		U[i].m[j]=temp;
	}
	
	//step 2.计算判断举证每一行的乘积Mi的n次方根 	
	rep(i,1,12) rep(j,1,U[i].size) U[i].w[j]=cal(U[i].m[j],U[i].size); 
	
	//step 3.对n次方根进行归一化处理，得到最终的权值 	
    rep(i,1,12){
    	double sum=0;
    	rep(j,1,U[i].size) sum+=U[i].w[j];
		rep(j,1,U[i].size) U[i].w[j]/=sum;
	}
}

void Fuzzy_Mathematics(){
	//读入叶子节点的模糊矩阵 
	rep(i,5,12) rep(j,1,F[i].r) rep(k,1,F[i].c) cin>>F[i].a[j][k];
	
//	rep(i,5,12) rep(j,1,F[i].r) {
//		
//		cout<<"(";
//	   rep(k,1,F[i].c)  if(k!=F[i].c) cout<<F[i].a[j][k]<<",";else cout<<F[i].a[j][k]<<")\n";
//	
//}

   
	//递归计算每个节点的隶属度 
	dfs(1); 
	//输出每个节点的隶属度 及等级评定结果 
	printf("指标  较差 一般 较好 好  总得分  等级评定\n"); 
	print(1);
}

int main(){
	freopen("in.txt","r",stdin); 
	freopen("out.txt","w",stdout); 
	init();
	AHP(); 
	Fuzzy_Mathematics();
} 
