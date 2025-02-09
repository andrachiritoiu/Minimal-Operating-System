#include<iostream>
#include<fstream>
using namespace std;

int v[1024],i,nrop,op,nrfis,j,descr,dim,a,d,p=0,k,aux=0,st,so,ok,pc;

void add(ifstream& f)
{
f>>descr;
f>>dim;

ok=0;
so=0;

a=dim/8;
d=dim%8;
if(d!=0)a++;

st=0;pc=0;
while(ok==0&&pc<1023)
{st=so;pc=so;
 while(v[st]!=0&&st<1023){st++;pc++;}
 so=st;
 while(v[so]==0&&so<1023){so++;pc++;}
 if(so-st>=a)ok=1;
}

//if(so-st<=1)ok=0;
/*if(d==0)*/
if (ok==0) cout<<descr<<":"<<" "<<"("<<0<<","<<0<<")"<<endl;
    else
     {for(k=st;k<st+a;k++)
              v[k]=descr;
         cout<<descr<<":"<<" "<<"("<<st<<","<<st+a-1<<")"<<endl;
     }
if(pc>p)p+=a;
  /* else{for(k=p;k<p+a;k++)
              v[k]=descr;
        cout<<descr<<":"<<" "<<"("<<p<<","<<p+a-1<<")"<<endl;
        p+=a;
        }
  }
else{if (a+1>1024-p)cout<<descr<<":"<<" "<<"("<<0<<","<<0<<")"<<endl;
       else if(so-st>=a+1)
      {for(k=st;k<st+a;k++)
              v[k]=descr;
         cout<<descr<<":"<<" "<<"("<<st<<","<<st+a-1<<")"<<endl;
      }
    else{for(k=p;k<p+a+1;k++)
            v[k]=descr;
        cout<<descr<<":"<<" "<<"("<<p<<","<<p+a<<")"<<endl;
        p+=a+1;
        }
     }*/

 }


void get(ifstream& f)
{int start=-1,stop=0;
f>>descr;
for(j=0;j<1024;j++)
 {if(v[j]==descr && start==-1)start=j;
  else if(v[j]==descr)stop=j;
 }
 if(start==-1)start=0;
 cout<<"("<<start<<","<<stop<<")"<<endl;
}

void deletef(ifstream& f)
{int start=-1,stop=0;
ok=0;
f>>descr;
 //functia get
for(j=0;j<1024;j++)
 {if(v[j]==descr && start==-1){start=j;ok=1;}
  else if(v[j]==descr)stop=j;
 }

if(ok==1)
{for(j=start;j<=stop;j++)
    v[j]=0;
}
 p=0;
 while(p<1023)
 {descr=v[p];
  start=p;
  while(descr==v[p]&&p<1024)p++;
  stop=p-1;
  if(descr!=0)cout<<descr<<":"<<" "<<"("<<start<<","<<stop<<")"<<endl;
 }

}

void defragmentation(ifstream& f)
{int aux=0,start=0,stop=0;
 for(j=0;j<1023;j++)
    {if(v[j]==0)
      {
      k=j+1;
      while(v[k]==0&&k<1023)k++;
      aux=v[j];
      v[j]=v[k];
      v[k]=aux;
      }
    }
p=0;
descr=v[p];
while(descr!=0 &&p<1023)
 {//descr=v[p];
  start=p;
  while(p<=1023&&descr==v[p])p++;
 /*if(p==1023) stop=1023;
  else stop=p-1;*/
   if(start!=p)stop=p-1;
  cout<<descr<<":"<<" "<<"("<<start<<","<<stop<<")"<<endl;
  descr=v[p];
 }
}


int main()
{
p=0;
for (i=0; i<1024; i++)
    v[i]=0;
ifstream f("input.txt");
f>>nrop;
for(i=0;i<nrop;i++)
    {f>>op;
    if(op==1)
    {f>>nrfis;
    for(j=0;j<nrfis;j++)
      {add(f);}
    }
    else if(op==2) get(f);
    else if(op==3) deletef(f);
    else if(op==4) defragmentation(f);
    }

for(i=0;i<1024;i++)
        cout<<v[i]<<" ";
f.close();
return 0;
}


