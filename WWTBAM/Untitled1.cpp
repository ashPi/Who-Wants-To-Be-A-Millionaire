#include<iostream>
#include<fstream>
#include<cstring>
#include<iomanip>
#include<cstdlib>
using namespace std;

struct Question {
       char text[115],A[40],B[40],C[40],D[40];
       int sum;
       char ra[2];
};
struct Player {
       Question q;
       char name[30], O[15], pa[2];
       int ps;
};
void Questions_dat() {
     ifstream inf;
     ofstream outf;
     inf.open("Questions.txt",ios::in);
     outf.open("Questions.dat",ios::out|ios::binary);
     Question q;
     char sum[15];
     while(!inf.eof()) {
                        inf.getline(q.text,115);
                        inf.getline(q.A,40);
                        inf.getline(q.B,40);
                        inf.getline(q.C,40);
                        inf.getline(q.D,40);
                        inf.getline(sum,15);
                        q.sum=atoi(sum);
                        inf.getline(q.ra,2);
                        outf.write((char*)&q,sizeof(Question));
     }
     outf.close();
     inf.close();
     cout<<"Complete"<<endl;
}
void Game() {
     ifstream inf;
     ofstream outf;
     inf.open("Questions.dat", ios::in|ios::binary);
     outf.open("History.txt", ios::app);
     Question q;
     Player p;
     char pa[2], name[30];
     int gus=0,ts=0,i=1,pj,ps;
     bool jh,j1=true,j2=true,j3=true;
     cout<<"Vavedete imeto si:";cin.ignore();cin.getline(name,30);
     inf.seekg(sizeof(Question)*((i-1)*10+(1+rand()%10)));
     inf.read((char*)&q,sizeof(Question));
     while(!inf.eof()) {
                        if(i==5)ts=250;
                        if(i==10) ts=2500;
                        cout<<"Igraete za "<<q.sum<<" leva"<<endl;
                        cout<<i<<" "<<q.text<<endl;
                        cout<<q.A<<endl;
                        cout<<q.B<<endl;
                        cout<<q.C<<endl;
                        cout<<q.D<<endl;
                        cout<<"O:Otkazvam se"<<endl;
                        cout<<"Jelaete li joker?(1/0) ";
                        cin>>jh;
                        if(jh) {
                                if(j1==false&&j2==false&&j3==false) cout<<"Veche ste izpolzvali vsichkite si jokeri"<<endl;
                                else {
                                      if(j1) cout<<"1: 50:50"<<endl;
                                      if(j2) cout<<"2: Obadi se na priqtel"<<endl;
                                      if(j3) cout<<"3: Pomosht ot publikata"<<endl;
                                      cout<<"Izberete joker:";
                                      cin>>pj;
                                      if(pj==1) {
                                                 int h;
                                                 char h1;
                                                 do {
                                                     h=65+rand()%3;
                                                     h1=(char)h;
                                                 }
                                                 while(strstr(q.ra,&h1));
                                                 cout<<q.ra<<":"<<h1<<endl;
                                                 j1=false;
                                      }
                                      if(pj==2) {
                                                 cout<<"Priqtelqt vi smqta, che pravilniqt otgovor e "<<q.ra<<endl;
                                                 j2=false;
                                      }
                                      if(pj==3) {
                                                 cout<<"Nai-mnogo hora ot publikata izbirat otgovor "<<q.ra<<endl;
                                                 j3=false;
                                      }
                                }
                        }
                        cout<<"Izberete svoq otgovor:";
                        cin.ignore();cin.getline(pa,2);
                        outf<<name<<endl;
                        outf<<q.text<<endl;
                        outf<<q.A<<endl;
                        outf<<q.B<<endl;
                        outf<<q.C<<endl;
                        outf<<q.D<<endl;
                        outf<<"O:Otkazvam se"<<endl;
                        outf<<q.sum<<endl;
                        outf<<q.ra<<endl;
                        outf<<pa<<endl;
                        if(strstr(pa,"O")) {
                                            cout<<"Vie pechelite "<<gus<<" leva"<<endl;
                                            ps=gus;
                                            outf<<ps<<endl;
                                            break;
                        }
                        else if(strstr(q.ra,pa)) {
                                                  cout<<"Pravilen otgovor"<<endl;
                                                  ps=q.sum;
                                                  outf<<ps<<endl;
                                                  gus=q.sum;
                                                  if(i==15) {
                                                             cout<<"Chestito, vie pobedihte!"<<endl;
                                                             break;
                                                  }
                                                                            
                        }
                        else {
                              cout<<"Greshen otgovor. Pravilniyat e "<<q.ra<<endl;
                              cout<<"Vie pechelite "<<ts<<" leva"<<endl;
                              ps=ts;
                              outf<<ps<<endl;
                              break;
                        }
                        i++;
                        inf.seekg(sizeof(Question)*((i-1)*10+(1+rand()%10)));
                        inf.read((char*)&q,sizeof(Question)); 
     }
     outf.close();
     inf.close();
}
void Count(int &n) {
     ifstream inf;
     Player p;
     char sum[15];
     inf.open("History.txt",ios::in);
     int br=0;
     while(!inf.eof()) {
                        inf.getline(p.name,30); 
                        inf.getline(p.q.text,115);
                        inf.getline(p.q.A,40);
                        inf.getline(p.q.B,40);
                        inf.getline(p.q.C,40);
                        inf.getline(p.q.D,40);
                        inf.getline(p.O,15);
                        inf.getline(sum,15);
                        p.q.sum=atoi(sum);
                        inf.getline(p.q.ra,2);
                        inf.getline(p.pa,2);
                        inf.getline(sum,15);
                        p.ps=atoi(sum);
                        br++;
     }
     inf.close();
     n=br;
}
void Sort(){
     ifstream inf;
     int n;
     Count(n);
     n-=1;
     Player arr[n];
     inf.open("History.txt",ios::in);
     int i=0;
     char sum[15];
     for(int i=0;i<n;i++) {
                           inf.getline(arr[i].name,30);
                           inf.getline(arr[i].q.text,115);
                           inf.getline(arr[i].q.A,40);
                           inf.getline(arr[i].q.B,40);
                           inf.getline(arr[i].q.C,40);
                           inf.getline(arr[i].q.D,40);
                           inf.getline(arr[i].O,15);
                           inf.getline(sum,15);
                           arr[i].q.sum=atoi(sum);
                           inf.getline(arr[i].q.ra,2);
                           inf.getline(arr[i].pa,2);
                           inf.getline(sum,15);
                           arr[i].ps=atoi(sum);
     }
     inf.close();
     int k;
     Player max;
     for(int i=0;i<n-1;i++) {
                             max=arr[0];
                             k=i;
                             for(int j=i+1;j<n;j++) {
                                                     if(max.q.sum<arr[j].q.sum) {
                                                                                 max=arr[j];
                                                                                 k=j;
                                                     }
                                                     if(max.q.sum==arr[j].q.sum) {
                                                                                  if(strcmp(max.name,arr[j].name)>0) {
                                                                                                                      max=arr[j];
                                                                                                                      k=j;
                                                                                  }
                                                     }
                             }
                                                     Player swap=arr[i];
                                                     arr[i]=arr[k];
                                                     arr[k]=swap;
     }
     for(int i=0;i<n;i++) {
                           cout<<"Suma za vaprosa:"<<arr[i].q.sum<<endl;
                           cout<<"Ime na igracha:"<<arr[i].name<<endl;
                           cout<<arr[i].q.text<<endl;;
                           cout<<arr[i].q.A<<endl;
                           cout<<arr[i].q.B<<endl;
                           cout<<arr[i].q.C<<endl;
                           cout<<arr[i].q.D<<endl;
                           cout<<arr[i].O<<endl;
                           cout<<"Pravilen otgovor:"<<arr[i].q.ra<<endl;
                           cout<<"Otgovor na igraca:"<<arr[i].pa<<endl;
                           cout<<"Suma, koqto igracha pecheli:"<<arr[i].ps<<endl;
     }
}
void Winner() {
     ifstream inf;
     Player p;
     bool flag=false;
     char sum[15];
     inf.open("History.txt",ios::in);
     while(!inf.eof()) {
                        inf.getline(p.name,30); 
                        inf.getline(p.q.text,115);
                        inf.getline(p.q.A,40);
                        inf.getline(p.q.B,40);
                        inf.getline(p.q.C,40);
                        inf.getline(p.q.D,40);
                        inf.getline(p.O,15);
                        inf.getline(sum,15);
                        p.q.sum=atoi(sum);
                        inf.getline(p.q.ra,2);
                        inf.getline(p.pa,2);
                        inf.getline(sum,15);
                        p.ps=atoi(sum);
                        if(p.ps==100000) {
                                          cout<<p.name<<endl;
                                          flag=true;
                        }
     }
     inf.close();
     if(flag==false) cout<<"Nqma takiva"<<endl;
}
void Questions(){
     ifstream inf;
     Question q;
     char sum[15];
     inf.open("Questions.txt",ios::in);
     while(!inf.eof()) {
                        inf.getline(q.text,115);
                        inf.getline(q.A,40);
                        inf.getline(q.B,40);
                        inf.getline(q.C,40);
                        inf.getline(q.D,40);
                        inf.getline(sum,15);
                        q.sum=atoi(sum);
                        inf.getline(q.ra,2);
                        int br=0;
                        for(int i=0;i<strlen(q.text);i++)
                        if(isspace(q.text[i])) br++;
                        cout<<q.text<<endl;
                        cout<<"Veren otgovor:"<<q.ra<<endl;
                        cout<<"Broi na dumite v teksta na vaprosa:"<<br+1<<endl;
     }
     inf.close();
}
int main() {
    //Questions_dat();
    int n;
    do {
        cout<<"Menu:"<<endl;
        cout<<"1:Nova igra"<<endl;
        cout<<"2:Informaciya za vaprosite, podredeni po suma i ime"<<endl;
        cout<<"3:Imena na uchastnicite, spechelili maksimalna suma"<<endl;
        cout<<"4:Spisak s vaprosite, verniq otgovor i broq na dumite v teksta na vaprosa"<<endl;
        cout<<"5:Izhod"<<endl;
        do {
            cout<<"n=";cin>>n;
        }
        while(n<1||n>5);
        switch(n) {
                   case 1: Game();break;
                   case 2: Sort();break;
                   case 3: Winner();break;
                   case 4: Questions();break;
        }
    }
    while(n!=5);
    system("pause");
    return 0;
}
