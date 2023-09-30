#include <iostream>
#include <stdio.h>
using namespace std;
class CTnode
{
public:
	char letter[5000];
	int ct;
	CTnode*Pleft;
	CTnode*Pright;
};
class Cnode
{
public:
	char info[5000];
	int ct;
	Cnode*Pnext;
	CTnode*PRoot;

};
class CSlist
{
public:
	Cnode*Phead;
	Cnode*Ptail;
	
	CSlist ()
	{
		Phead=NULL;
		Ptail=NULL;
	}
	~CSlist()
	{
		Cnode * Ptrav;
		Ptrav=Phead;
		while(Ptrav!=NULL)
		{
			Phead=Phead->Pnext;
			delete Ptrav;
			Ptrav=Phead;
		}
	}
	void insert (Cnode*Pnn)
	{
		Cnode*Ptrav=NULL;
		Cnode*Pb=NULL;
		if (Phead==NULL)
		{
			Phead=Pnn;
		}
		else
		{
			Pb=NULL;
			Ptrav=Phead;
		}
		while (Ptrav!=NULL)
		{
			if(Ptrav->ct>Pnn->ct)
			{
				break;
			}
			Pb=Ptrav;
			Ptrav=Ptrav->Pnext;
		}
		if(Pb!=NULL)
		{
			Pb->Pnext=Pnn;
		}
		else
		{
			Phead=Pnn;
		}
		Pnn->Pnext=Ptrav;
	}
	void DispAll()
	{
		Cnode * Ptrav=NULL;
		Ptrav=Phead;
		while (Ptrav!=NULL)
		{
				cout<<"Letter= "<<Ptrav->info<<" ";
				cout<<"Count = "<<Ptrav->ct<<endl;
				Ptrav=Ptrav->Pnext;
		}
	}
};
class CGnode
{
public:
	char code;
	char generate[5000];
	int ctg;
	CGnode*Pnext;
};
class CGlist
{
public:
	CGnode*Phead;
	CGnode*Ptail;

	CGlist()
	{
		Phead = NULL;
		Ptail = NULL;

	}

	~CGlist()
	{
		CGnode* Ptrav = Phead;
		while (Ptrav != NULL)
		{
			Phead = Phead->Pnext;
			delete Ptrav;
			Ptrav = Phead;
		}
	}
	void Attach(CGnode* pnn)
	{
		if (Phead == NULL)
		{
			Phead = pnn;
			Ptail = pnn;
		}
		else
		{
			Ptail->Pnext = pnn;
			Ptail = pnn;
		}
	}
	void DispAll()
	{
		CGnode* Ptrav = Phead;
		while (Ptrav != NULL)
		{
			cout << Ptrav->code << "=" << Ptrav->generate<< endl;
			Ptrav = Ptrav->Pnext;
		}
		cout << endl;
	}



};
void Generate(CTnode*Ptrav,
	int d,
	char generate[],
	CGlist & L)
{
	if(Ptrav==NULL)
	{
		return;
	}
	if (Ptrav->Pleft==NULL && Ptrav->Pright==NULL)
	{
		CGnode*pnn;
		int y;
		pnn= new CGnode;

		pnn->code=Ptrav->letter[0];
		pnn->ctg=Ptrav->ct;
		for (y= 0; y<d; y++)
		{
			pnn->generate[y] = generate[y];
		}
		pnn->generate[y]=NULL;
		L.Attach(pnn);
		pnn->Pnext=NULL;
		//generate[y-1]='\0';
		return;
	}
	generate[d]='0';
	Generate(Ptrav->Pleft, d+1, generate, L);
	generate[d]='1';
	Generate(Ptrav->Pright,d+1, generate, L);
}

void main()
{
	char Name[5000];
	
	char X;
	char XP;
	int pos;
	CSlist Sorted;
	Cnode*Pnn=NULL; 
	int Flag;
	int s=1;
	char generate[5000];
	CTnode*Pget=NULL;
	CGlist L;
	
	cout<<"insert word"<<endl;
	gets_s (Name);

	for(int i=0; Name[i]!='\0'; i++)
	{
		Cnode *Ptemp =Sorted.Phead;
		Flag = 0;
		X=Name[i];
		pos=i;

		while(Ptemp!=NULL)
		{
			if(Name[i]==Ptemp->info[0])
			{
				Flag=1;
			}
			Ptemp=Ptemp->Pnext;
		}

		if(Flag==0)
		{
			Pnn=new Cnode;
			Pnn->Pnext=NULL;
			Pnn->PRoot=NULL;

			for(int m=0; Name[m]!='\0'; m++)
			{
				if(Name[m]==X && m!=pos)
				{
					s++;
				}
			}
			Pnn->info[0]=X;
			Pnn->info[1]=NULL;
			Pnn->ct=s;
			Sorted.insert(Pnn);
			s=1;
			
		}
	}
	Sorted.DispAll();
	//system("pause");

	Cnode*Pnew=NULL;
	int i=0;
	while(Sorted.Phead->Pnext!=NULL)
	{
		i=0;
		Cnode*Ptrav1=Sorted.Phead->Pnext;
		Cnode*Pb1=Sorted.Phead;
		
		Pnew=new Cnode;
		
		Pnew->Pnext=NULL;
		Pnew->PRoot=NULL;

		
		Pnew->ct=(Pb1->ct)+(Ptrav1->ct);


		for(int o=0; Pb1->info[o]!='\0'; o++)
		{
			Pnew->info[i]=Pb1->info[o];
			i++;
		}


		for(int m=0; Ptrav1->info[m]!='\0'; m++)
		{
			Pnew->info[i]=Ptrav1->info[m];
			i++;
		}

		Pnew->info[i]=NULL;

		CTnode*Ptree;
		Pnew->PRoot=new CTnode;
		CTnode*Ptree1;
		Ptree1=Pnew->PRoot;
		//Pnew->PRoot->Pleft=Ptree1;
		Ptree1->ct=Pnew->ct;
		int h;
		for(h=0; Pnew->info[h]!='\0'; h++)
		{
			Ptree1->letter[h]=Pnew->info[h];
		}
		Ptree1->letter[h]=NULL;

		if(Pb1->PRoot==NULL && Ptrav1->PRoot==NULL)
		{
			Ptree1->Pleft=new CTnode;
			Ptree1->Pleft->ct=Pb1->ct;
			int x;
			for (x=0; Pb1->info[x]!='\0'; x++)
			{
				Ptree1->Pleft->letter[x]=Pb1->info[x];
			}
			Ptree1->Pleft->letter[x]=NULL;
			
			Ptree1->Pright=new CTnode;
			Ptree1->Pright->ct=Ptrav1->ct;
			int y;
			for( y=0; Ptrav1->info[y]!='\0'; y++)
			{
				Ptree1->Pright->letter[y]=Ptrav1->info[y];
			}
			
			Ptree1->Pright->letter[y]=NULL;
			
			Ptree1->Pright->Pright=NULL;
			Ptree1->Pright->Pleft=NULL;
			Ptree1->Pleft->Pleft=NULL;
			Ptree1->Pleft->Pright=NULL;
		}

		if(Pb1->PRoot!=NULL && Ptrav1->PRoot==NULL)
		{
			Ptree1->Pright=new CTnode;
			Ptree1->Pright->ct=Ptrav1->ct;
			int y;
			for( y=0; Ptrav1->info[y]!='\0'; y++)
			{
				Ptree1->Pright->letter[y]=Ptrav1->info[y];
			}
			Ptree1->Pright->letter[y]=NULL;
			
			Ptree1->Pright->Pright=NULL;
			Ptree1->Pright->Pleft=NULL;
			Ptree1->Pleft=Pb1->PRoot;
		}

		if(Pb1->PRoot==NULL && Ptrav1->PRoot!=NULL)
		{
			Ptree1->Pleft=new CTnode;
			Ptree1->Pleft->ct=Pb1->ct;
			int x;
			for (x=0; Pb1->info[x]!='\0'; x++)
			{
				Ptree1->Pleft->letter[x]=Pb1->info[x];
			}
			Ptree1->Pleft->letter[x]=NULL;
			Ptree1->Pleft->Pleft=NULL;
			Ptree1->Pleft->Pright=NULL;
			Ptree1->Pright=Ptrav1->PRoot;
		}

		if(Pb1->PRoot!=NULL && Ptrav1->PRoot!=NULL)
		{
			Ptree1->Pleft=Pb1->PRoot;
			Ptree1->Pright=Ptrav1->PRoot;
		}

		Sorted.Phead=Ptrav1->Pnext;
		Ptrav1->Pnext=NULL;
		Sorted.insert(Pnew);
	}
	Sorted.DispAll();
	cout<<endl;

	for(int b=0; b<5000; b++)
	{
		generate[b]='\0';
	}
	Pget=Sorted.Phead->PRoot;
	Generate(Pget, 0, generate, L);
	cout<<endl;
	L.DispAll();

	//Phase 2
	char m = 1;
	CGnode* Pt1;
	char z[2000];
	int ibit = 7;
	int w = 0;
	int ce = 0;

	for (int l = 0; l < 2000; l++)
	{
		z[l] = '\0';
	}
	
	for (int i = 0; Name[i] != '\0'; i++)
	{
		Pt1 = L.Phead;

		while (Pt1 != NULL)
		{
			if (Pt1->code == Name[i])
			{
				for (int k = 0; Pt1->generate[k] != '\0'; k++)
				{
					if (Pt1->generate[k] == '1')
					{
					
						z[w] = z[w] | (m << ibit);
					}
					ibit--;
					if (ibit < 0)
					{
						ibit = 7;
						w++;
					}
				}
				
			}
			Pt1 = Pt1->Pnext;
		}
	}

	cout << "Compressed Text="<<" ";
	int jj;
	for (jj = 0; z[jj] != '\0'; jj++)
	{
		cout <<z[jj];
	}
	cout << "compressed char=" << jj << endl;

	char D[5000];
	char check[5000];
	char zch;
	int  c = 0;
	int countl = 0;
	ibit = 7;

	for (int v = 0; z[v] != '\0'; v++)
	{
		for (int b = 0; b < 8; b++)
		{
			zch = z[v] & (m << ibit);

			if (zch == 0)
			{
				check[c] = '0';
				c++;
				cout << "0";
			}
			else
			{
				check[c] = '1';
				c++;
				cout << "1";
			}
			countl++;
			ibit--;
			if (ibit < 0)
			{
				ibit = 7;
			}
		}
		cout << endl;
	}

	for (int tempo = 0; tempo <c ; tempo++)
	{
		if (check[tempo] == '0')
		{
			cout << "0";
		}
		else
		{
			cout << "1";
		}
	}

	CGnode* Pcheck;
	Pcheck = L.Phead;
	int ii = 0;
	int j = 0;
	char testing[20];
	int bor3y = 0;
	int counter = 0;
	int counter2 = 0;
	int de = 0;

	char chgen;
	Pcheck = L.Phead;

		for (j = 0; j < countl; j++)
		{
			while (Pcheck != NULL)
			{
				counter = j;
				counter2 = ii;
				for (ii = 0; Pcheck->generate[ii] != '\0'; ii++)
				{		

					if (Pcheck->generate[ii] == check[j])
					{
						bor3y++;
						j++;
					}
					else
					{
						bor3y = 0;
						j = counter;
						break;
					}
				}

				if (bor3y > 0)
				{
					D[de] = Pcheck->code;
					de++;
					bor3y = 0;	
					j--;
					Pcheck = L.Phead;
					break;
					
				}
				else
				Pcheck = Pcheck->Pnext;
				
			}
		}

	cout << endl;
	int qq = 0;
	for (int q = 0; q< de; q++)
	{
		qq++;
		cout << D[qq];
	}
	cout << "Decompressed = " << qq << endl;









	system("pause");
}