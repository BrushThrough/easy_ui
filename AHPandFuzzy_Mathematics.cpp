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

struct Judeg_mat{ //�жϾ��� 
    string name;
	double  a[N][N];
	double m[N];
	double w[N];
	int size;
	vector<int >son; 
}U[20];

struct Fuzzy_mat{ //ģ������ 
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


void init(){ //��ʼ��ģ��������жϾ������ز��� 
	rep(i,1,12)
	 if(i==1||i==3||i==4||i==6) U[i].size=3;
	 else U[i].size=2;
	U[1].name="��������ͨϵͳ�����ۺ�����U";
	U[2].name="�����ν�Эͬ��U1"; 
    U[3].name="������ӪЭͬ��U2";
    U[4].name="����ϵͳЭͬ��U3";
    U[5].name="��Ӫ��֯U11";
    U[6].name="��Ӫ����U12";
    U[7].name="������ϵЭͬ��U21";
    U[8].name="������֯Эͬ��U22";
    U[9].name="��Ӫ����Эͬ��U23";
    U[10].name="����ʽ����Эͬ��U31";
    U[11].name="����ʽ�滮Эͬ��U32";
    U[12].name="����ʽ����Эͬ��U33";

	U[1].son.pb(2),U[1].son.pb(3),U[1].son.pb(4);
	U[2].son.pb(5),U[2].son.pb(6);
	U[3].son.pb(7),U[3].son.pb(8),U[3].son.pb(9);
	U[4].son.pb(10),U[4].son.pb(11),U[4].son.pb(12);
		
	rep(i,1,12) F[i].son=U[i].son,F[i].r=U[i].size,F[i].c=5,F[i].name=U[i].name;  
}

double cal(double x,int n){
	//����res���е����� ������Binary search
	double l=0,r=1e6;
	while(fabs(r-l)>=eps){
		double mid=(l+r)/2;
		double t=1; rep(i,1,n) t*=mid;
		if(t<=x) l=mid;
		else r=mid;
	}
	return l;
}

vector<double> mul(Fuzzy_mat a,Fuzzy_mat b){ //����˷� 
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
	if(abs(x-1)<=0.5) return "��";
	if(abs(x-2)<=0.5) return "����";
	if(abs(x-3)<=0.5) return "һ��";
	if(abs(x-4)<=0.5) return "�Ϻ�";
	if(abs(x-5)<=0.5) return "��";			
}

void dfs(int u){
	//�ݹ鵽Ҷ�ӽڵ㣬ֱ�Ӵ��������Ȳ�retuen 
	if(u>=5){
		Fuzzy_mat temp; temp.clear();temp.r=1,temp.c=U[u].size; //�õ�Ȩֵ���� 
        rep(i,1,temp.c) temp.a[1][i]=U[u].w[i];	
        
		vector<double >g=mul(temp,F[u]); //Ȩֵ�����ģ������õ��������
		double sum=0; 
		rep(i,1,5) F[u].membership[i]=g[i-1],sum+=i*F[u].membership[i];
		F[u].score=sum; F[u].degree=solve(F[u].score);
		return ;
	}
	
	//�����ʹ�����ӽڵ� 
	for(auto v:F[u].son) dfs(v);
	
    //���ݴ���ǰ�ڵ�������� 
    Fuzzy_mat temp; temp.clear();temp.r=1,temp.c=U[u].size; //�õ�Ȩֵ���� 
    rep(i,1,temp.c) temp.a[1][i]=U[u].w[i];	
    
	rep(i,1,F[u].r)  //�ϲ����ж��ӽڵ�������������õ���ǰ�ڵ��ģ������ 
     rep(j,1,5)
	F[u].a[i][j]=F[F[u].son[i-1]].membership[j];  
          
	vector<double >g=mul(temp,F[u]); //Ȩֵ�����ģ������õ�������� 
	double sum=0; 
	rep(i,1,5) F[u].membership[i]=g[i-1],sum+=i*F[u].membership[i];
	F[u].score=sum; F[u].degree=solve(F[u].score);
}

void print(int u){ //��������ȼ�������� 
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
	//�����жϾ��� 
    rep(i,1,12) rep(j,1,U[i].size) rep(k,1,U[i].size) cin>>U[i].a[j][k];
	
	//����Ȩֵ 
	
	//step 1.�����жϾ���ÿһ�еĳ˻�Mi 
	rep(i,1,12) 
	for(int j=1;j<=U[i].size;j++){
	    double temp=1;
		rep(k,1,U[i].size) temp*=U[i].a[j][k];	
		U[i].m[j]=temp;
	}
	
	//step 2.�����жϾ�֤ÿһ�еĳ˻�Mi��n�η��� 	
	rep(i,1,12) rep(j,1,U[i].size) U[i].w[j]=cal(U[i].m[j],U[i].size); 
	
	//step 3.��n�η������й�һ�������õ����յ�Ȩֵ 	
    rep(i,1,12){
    	double sum=0;
    	rep(j,1,U[i].size) sum+=U[i].w[j];
		rep(j,1,U[i].size) U[i].w[j]/=sum;
	}
}

void Fuzzy_Mathematics(){
	//����Ҷ�ӽڵ��ģ������ 
	rep(i,5,12) rep(j,1,F[i].r) rep(k,1,F[i].c) cin>>F[i].a[j][k];
	
//	rep(i,5,12) rep(j,1,F[i].r) {
//		
//		cout<<"(";
//	   rep(k,1,F[i].c)  if(k!=F[i].c) cout<<F[i].a[j][k]<<",";else cout<<F[i].a[j][k]<<")\n";
//	
//}

   
	//�ݹ����ÿ���ڵ�������� 
	dfs(1); 
	//���ÿ���ڵ�������� ���ȼ�������� 
	printf("ָ��  �ϲ� һ�� �Ϻ� ��  �ܵ÷�  �ȼ�����\n"); 
	print(1);
}

int main(){
	freopen("in.txt","r",stdin); 
	freopen("out.txt","w",stdout); 
	init();
	AHP(); 
	Fuzzy_Mathematics();
} 
