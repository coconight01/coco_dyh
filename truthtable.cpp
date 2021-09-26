#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstring>
using namespace std;
int tp,lft[10010],bef[10010]; 
void init(){
	printf("以下是逻辑运算符号的形式与具体意义\n"); 
	printf("^:异或\n~:否定\n&:与\n|:或\n->:蕴涵\n<->:双蕴涵\n");
	printf("请输入命题公式，仅支持大写字母、逻辑运算符和小括号的输入\n"); 
	printf("输入中请不要带有空格或空括号！\n"); 
}
char a[10010];
int st[10010],work[10010],w[2][10010];
int len,lenw,lens;
int ans[10010];
int nxt[10010],h[230];
void _do(int &x,int &y,int &z){
	if(y==203){z^=1;y=-1;return;}
	if(y==204)z=x&z;
	if(y==205)z=x|z;
	if(y==206)
		z=((x&&z)||!x);
	if(y==207)
		z=((x&&z)||(!x&&!z));
	x=y=-1;
}
int solve(){
	if(!lenw)return 0;
	for(int i=201;i<=210;i++)h[i]=0; 
	for(int i=lenw;i;i--)if(work[i]>200){
		nxt[i]=h[work[i]];
		h[work[i]]=nxt[i];
	}int nw=0;
	for(int t=203;t<=207;t++,nw^=1){
		for(int i=1;i<=lenw;i++)if(w[nw][i]==t)
			_do(w[nw][i-1],w[nw][i],w[nw][i+1]);
		int llen=0;
		for(int i=1;i<=lenw;i++)if(w[nw][i]!=-1)w[nw^1][++llen]=w[nw][i];
		lenw=llen;
	}
	return w[nw][1]; 
}
int idk[10010],cntk,a1[10010];
int in[300];int cntz,cz[30];
void pre(){
	for(int i=0;i<=len;i++){
		if(a[i]=='(')a1[i]=201;else if(a[i]==')')a1[i]=202;
		else if(a[i]=='~')a1[i]=203;else if(a[i]=='&')a1[i]=204;
		else if(a[i]=='|')a1[i]=205;else if(a[i]=='-'){i++;a1[i-1]=0;a1[i]=206;continue;}
		else if(a[i]=='<'){i+=2;a1[i]=207;a1[i-1]=a1[i-2]=0;continue;}
		else {a1[i]=a[i];if(in[a[i]]==0)cz[++cntz]=a[i],in[a[i]]=cntz;}
	}int j=0; 
	for(int i=0;i<=len;j++,i++){
		while(a1[i]==0)i++;a1[j]=a1[i];
	}
	len=j-1;
	for(int i=0;i<=len;i++){
		if(a1[i]!=202)st[++tp]=i,lft[i]=-1;
		else{lenw=0;
			while(a1[st[tp]]!=201)tp--;
			lft[i]=st[tp];idk[++cntk]=i;tp--;
		}		
	}int posid=cntz*2;
	for(int i=1;i<=cntz;i++) printf("%c ",cz[i]);
	for(int ii=1,lle,i;ii<=cntk;ii++){
		i=idk[ii];
		lle=i-lft[i]+1;
		for(j=lft[i];j<=i;j++)if(a1[j]>200){
			if(a1[j]==201)printf("(");else if(a1[j]==202)printf(")");
			else if(a1[j]==203)printf("~");else if(a1[j]==204)printf("&");
			else if(a1[j]==205)printf("|");else if(a1[j]==206){lle++;printf("->");}
			else if(a1[j]==207){lle+=2;printf("<->");}
		}else printf("%c",a1[j]);
		printf(" ");
		bef[ii]=posid+lle/2;posid+=lle+1;
	}
	puts("");
}
void prt(){
	for(int i=1,Id=cntz*2;i<=lens;i++){
		while(Id<bef[i]){Id++;printf(" ");}
		printf("%d",ans[i]);
	}
	puts("");
}
int p0_1[210],aa[10010];
bool _nxt(){
	if(p0_1[cntz]==-1){
		p0_1[cntz]++;
	}else {bool ok=0;
		for(int i=cntz;i;i--)if(!p0_1[i]){p0_1[i]=1;
			for(int j=i+1;j<=cntz;j++)p0_1[j]=0;ok=1;break;
		}if(!ok)return 0;		
	}
	for(int i=0;i<=len;i++){
		if(a1[i]>200)aa[i]=a1[i];
		else aa[i]=p0_1[in[a1[i]]];
	}
	for(int i=1;i<=cntz;i++)printf("%d ",p0_1[i]);
	return 1;
}
int main(){ 
//freopen("a.in","r",stdin);
	init();
	
	scanf("%s",a+1);len=strlen(a+1);
	a[0]='(';a[len+1]=')';len++;
	pre();p0_1[cntz]=-1;
	while(1){
		lens=tp=0;
		if(!_nxt())return 0;
		
		for(int i=0;i<=len;i++){
			if(aa[i]!=202)st[++tp]=aa[i];
			else{lenw=0;
				while(st[tp]!=201)w[0][++lenw]=st[tp],tp--;
				tp--;
				reverse(w[0]+1,w[0]+lenw+1);
				ans[++lens]=solve();st[++tp]=ans[lens];
			}
		}
		prt();		
	}

}
