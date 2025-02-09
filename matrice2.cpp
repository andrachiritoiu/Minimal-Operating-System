#include<iostream>
#include<fstream>
using namespace std;

int m[1024][1024],i,nrop,op,nrfis,j,descr,dim,a,d,p=0,k,cst,cso,lp,lc,ok,pc,st,so,lk,ck,ds,dst,dlc,dso,aux,l,val,nr=0,me[1048576];

void add(ifstream& f)
{
f>>descr;
f>>dim;

ok=0;
cso=0;

a=dim/8;
d=dim%8;
if(d!=0)a++;//a=nr de blocuri ocupate

//lp=-1;
lc=0;
cst=0;cso=0;
pc=0;
while(ok==0&&pc<1048576)
{if(cso>=7){lc=lc+1;cst=0;}
    else cst=cso;
 while(m[lc][cst]!=0&&cst<1024){cst++;pc++;}
 cso=cst;
 while(m[lc][cso]==0&&cso<1024){cso++;pc++;}
 if(cso-cst>=a)ok=1;
}

if(ok==0)cout<<descr<<":"<<" "<<"("<<0<<","<<0<<")"<<endl;
    else
       {for(k=cst;k<cst+a;k++)
              m[lc][k]=descr;
         cout<<descr<<":"<<" "<<"("<<"("<<lc<<","<<cst<<")"<<","<<" "<<"("<<lc<<","<<cst+a-1<<")"<<")"<<endl;
     }
if(pc>p)p+=a;
 }


void get(ifstream& f)
{
cst=-1;cso=0;
f>>descr;
lc=0;
 for(k=0;k<1024;k++)
    for(j=0;j<1024;j++)
     {if(m[k][j]==descr&&cst==-1){cst=j;cso=j;lc=k;}
        else if(m[k][j]==descr)cso=j;
     }
if(cst==-1)cst++;
cout<<"("<<"("<<lc<<","<<cst<<")"<<","<<" "<<"("<<lc<<","<<cso<<")"<<")"<<endl;
/*if(cst==-1)cout<<descr<<":"<<" "<<"("<<"("<<lc<<","<<cst<<")"<<","<<" "<<"("<<lc<<","<<cso<<")"<<")"<<endl;
else cout<<descr<<":"<<" "<<"("<<"("<<0<<","<<0<<")"<<","<<" "<<"("<<0<<","<<0<<")"<<")"<<endl;*/
}

void deletef(ifstream& f)
{cst=-1;cso=-1;
ok=0;
 f>>descr;
 for(k=0;k<1024;k++)
    for(j=0;j<1024;j++)
     {if(m[k][j]==descr && cst==-1){cst=j;lc=k;cso=j;
                                     //ok=1;
                                    }
        else if(m[k][j]==descr)cso=j;
     }


//if(ok==1)
{for(j=cst;j<=cso;j++)
    m[lc][j]=0;
}

for(k=0;k<1024;k++)//l = k in assembley
   {j=0;
    while(j<1024)
       {descr=m[k][j];
        cst=j;
        while(descr==m[k][j]&&j<1024)j++;
        cso=j-1;
        if(descr!=0)cout<<descr<<":"<<" "<<"("<<"("<<k<<","<<cst<<")"<<","<<" "<<"("<<k<<","<<cso<<")"<<")"<<endl;
       }
   }
}

void defragmentation(ifstream& f)
{
k=0;
for(l=0;l<1024;l++)
   {j=0;
    while(j<1024)
       {descr=m[l][j];
        cst=j;
        while(descr==m[l][j]&&j<1024)j++;
        cso=j;
        if(descr!=0)
        {me[k]=descr;me[k+1]=cso-cst;k+=2;}
        }
   }

nr=k;
for(l=0;l<1024;l++)
   for(j=0;j<1024;j++)
    m[l][j]=0;
    
lc=0;pc=0;
for(k=0;k<nr;k+=2)
   {a=me[k+1];
   if(a>1024-pc)
      {/*for(j=pc;j<pc+a;j++)
            m[lc][j]=0;*/
         lc+=1; pc=0; 
      }
   for(j=pc;j<pc+a;j++)
      m[lc][j]=me[k];
   pc=pc+a;
   if(pc==1024){pc=0;lc+=1;}
   }

for(k=0;k<1024;k++)//l = k in assembley
   {j=0;
    while(j<1024)
       {descr=m[k][j];
        cst=j;
        while(descr==m[k][j]&&j<1024)j++;
        cso=j-1;
        if(descr!=0)cout<<descr<<":"<<" "<<"("<<"("<<k<<","<<cst<<")"<<","<<" "<<"("<<k<<","<<cso<<")"<<")"<<endl;
       }
   }
   
}



int main()
{
p=0;
for (i=0; i<1024; i++)
    for (j=0; j<1024; j++)
        m[i][j]=0;
ifstream f("inputm2.txt");
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
cout<<endl;
for(i=0;i<1024;i++)
  {for(j=0;j<6;j++)
        cout<<m[i][j]<<" ";
   cout<<endl;
  }
f.close();
return 0;
}


