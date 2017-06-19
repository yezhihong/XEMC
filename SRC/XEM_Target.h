#ifndef ROOT_XEM_TGT
#define ROOT_XEM_TGT
#define U2GeV  0.931494028       //Convert from atomic mass unit to GeV unit   
////////////////////////////////////////
//IMPORTANT: Define Target info
//const TString TARGET_TABLE = "/Users/yez/work/github/XEMC/SRC/target.table";
//Target Table: include two types of tables: Radiative Corrected and Non-Radiative Corrected  
////////////////////////////////////////

class XEM_TGT
{
 public:
   //Very Dangerous but I have no choice unless I change the entire code, too late so far
   TString Name;  // Target Name
   Double_t Mass; // Target Mass
   Int_t A;       // Target Nuclear Number
   Int_t Z;       // Target Proton Number
 
  /* Double_t epsn; */
  /* Double_t fermi; //Fermi Momentum */
  /* Double_t aa,bb,cc,dd,ee,ff; //Target fitting paramaters */

   Double_t RL; //Radiation Length
   Double_t Resol; //Parameter for DEEPSIG smearing
   Double_t ESep;  //Separation Energy
   Double_t f0,B,a,b,alpha; //parameters to calculate F(y)
  
  public:
  XEM_TGT() {
 //   GetValue();
 //   GetValueAZ();
  };
		
  /*~XEM_TGT{{{*/
  virtual ~XEM_TGT(){

  }
  /*}}}*/

 /* XEM_TGT(XEM_TGT const&){};*/
  //XEM_TGT& operator=(XEM_TGT const&){return *this;};
  //XEM_TGT& operator*=(const Double_t& aNum){
    ////     this->Name *= aNum;
    //this->Mass *= aNum;
    //this->A *= (int) aNum;
    //this->Z *= (int) aNum;
      
    //[> this->epsn *= aNum; <]
    //[> this->fermi *=aNum; <]
    //[> this->aa *=aNum; <]
    //[> this->bb *=aNum; <]
    //[> this->cc *=aNum; <]
    //[> this->dd *=aNum; <]
    //[> this->ee *=aNum; <]
    //[> this->ff *=aNum; <]
      
    //this->RL *=aNum;
    //this->Resol *=aNum;
    //this->ESep *=aNum;
    //this->f0 *=aNum;
    //this->B *=aNum;
    //this->a *=aNum;
    //this->b *=aNum;
    //this->alpha *=aNum;
      
    //return *this;
  /*};*/
 
  void LoadTargetTable(const TString& kTarget_Table ){
      //fTARGET_TABLE=kTarget_Table;
      cout<<"&&&& XEM_TGT: Loading Table from "<<kTarget_Table.Data()<<endl;
      ifstream table; table.open(kTarget_Table.Data());
      //FIX_HERE: temperate method to read target info. will improve it later.
      TString content; Int_t CommentLine=0;
      while( content.ReadLine(table)){
          cout<<content.Data()<<endl;
          if ( content.BeginsWith("#") )
              CommentLine++;
          else
              break;
      }
      table.close();

      Int_t aLine=0;
      table.open(kTarget_Table.Data());
      int i=0;
      while(!(table.eof())){
          aLine++;
          if(aLine<=CommentLine)
              content.ReadLine(table);
          else{
              table >> fName[i] >> fA[i] >> fZ[i] >> fMass[i] >> fRL[i] >> fResol[i] >> fESep[i] 
                  >> fF0[i] >> fBigB[i] >> fSmallA[i] >> fSmallB[i] >> fAlpha[i];
              cout<<Form("-- Target: Name= %s, A=%d, Z=%d", fName[i].Data(), fA[i], fZ[i])<<endl;
              i++;
          }
      }
      N_Target = i-1;
      table.close();
  };

  void GetValue( const TString& kName ){
      fExist = kFALSE;
      for (int i=0;i<N_Target;i++){
          if(kName==fName[i]){

              A = fA[i];
              Z = fZ[i];
              Mass = fMass[i];
              RL = fRL[i];
              Resol = fResol[i];
              ESep = fESep[i];
              f0 = fF0[i];
              B = fBigB[i];
              a = fSmallA[i];
              b = fSmallB[i];
              alpha = fAlpha[i];

              fExist = kTRUE;
              break;
          }
      }

      if(fExist)
          cerr <<endl<< "@@@@@@ I have found your target from the table!" <<endl;
      else{
          cerr << "****** ERROR, your target is not in the table! Check the following table:" <<endl;
          List();
      }
      //Be careful -- the following variables needed to be converted:
      Mass *= U2GeV ; //From u to GeV;
      ESep/=1000.0; 
      f0  /=1000.0;
      B/=1000.0;
      a /=1000.0;
      b /=1000.0;
  }; 

  void GetValueAZ( const int kA, const int kZ ){
      fExist = kFALSE;
      for (int i=0;i<N_Target;i++){
          if((fA[i]==kA)&&(fZ[i]==kZ)){

              A = fA[i];
              Z = fZ[i];
              Mass = fMass[i];
              RL = fRL[i];
              Resol = fResol[i];
              ESep = fESep[i];
              f0 = fF0[i];
              B = fBigB[i];
              a = fSmallA[i];
              b = fSmallB[i];
              alpha = fAlpha[i];

              fExist = kTRUE;
              break;
          }
      }


      if(!(fExist)){
          //     cerr <<endl<< "@@@@@@ I have found your target from the table!" <<endl;
          //  else{
          cerr << "****** ERROR, your target is not in the table! Check the following table:" <<endl;
          List();
      }
      //Be careful -- the following variables needed to be converted:
      Mass *= U2GeV ; //From u to GeV;
      ESep/=1000.0; 
      f0  /=1000.0;
      B/=1000.0;
      a /=1000.0;
      b /=1000.0;
    }; 
    
  void SetValue(
                const TString& kName=" ",
                const Double_t& kMass=0,
                const Int_t& kA=0,
                const Int_t& kZ=0,
                const Double_t& kRL=0,
                const Double_t& kResol=0,
                const Double_t& kESep=0,
                const Double_t& kf0=0,
                const Double_t& kB=0,
                const Double_t& ka=0,
                const Double_t& kb=0,
                const Double_t& kalpha=0
                ){
    Name = kName;
    Mass = kMass;
    A=kA;
    Z=kZ;
    RL=kRL;
    Resol=kResol;
    ESep=kESep;
    f0=kf0;
    B=kB;
    a=ka;
    b=kb;
    alpha=kalpha;
  }; 
  
  void List(){
    ifstream table(fTARGET_TABLE.Data());
    TString content; 
    cerr <<endl<< "~~~~~~~~~~~~~~~~~ Target Table ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cerr <<"Name     A     Z      Mass       R.L.     RESOL     ESEP       f0         B           a          b        alpha"<<endl;
    cerr <<"-----------------------------------------------------------------------------------------------------------------"<<endl;
    while( content.ReadLine(table)){
      if ( !content.BeginsWith("#") )
        cerr << content <<endl;
    }
    cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl<<endl;
    table.close();
  }
  
  void Print()
  {
    cerr <<endl<< "--------------------------------------"<<endl;
    Printf("%-*s%s",20,"|   Target Name:  ",Name.Data());
    Printf("%-*s%f",20,"|   Mass(GeV):  ",Mass);
    Printf("%-*s%d",20,"|   A:  ",A);
    Printf("%-*s%d",20,"|   Z:  ",Z);
    Printf("%-*s%f",20,"|   Rad. Length:  ",RL);
    Printf("%-*s%f",20,"|   Resol:  ",Resol);
    Printf("%-*s%f",20,"|   Sep. Energy:  ",ESep);
    Printf("%-*s%f",20,"|   f0:  ",f0);
    Printf("%-*s%f",20,"|   B:  ",B);
    Printf("%-*s%f",20,"|   a:  ",a);
    Printf("%-*s%f",20,"|   b:  ",b);
    Printf("%-*s%f",20,"|   alpha:  ",alpha);
    cerr << "--------------------------------------"<<endl<<endl;

  };
     
 private:
   Bool_t fExist;

   TString fName[20];
   Int_t fA[20];
   Int_t fZ[20];
   Double_t fMass[20];
   Double_t fRL[20];
   Double_t fResol[20];
   Double_t fESep[20];
   Double_t fF0[20];
   Double_t fBigB[20];
   Double_t fSmallA[20];
   Double_t fSmallB[20];
   Double_t fAlpha[20];

   Int_t N_Target;

   TString fTARGET_TABLE;

 };



//   //Define in DBisNew4He3.f, but I don't know why the epsn values are different with the target table
//   Double_t fermip[200]={200*0.};
//   Double_t epsn[200]={200*0.};
//   
//   fermip[197]=.264;
//   fermip[64]=.260;
//   fermip[27]=.240;
//   fermip[12]=.221;
//   fermip[4]=.160;
//   fermip[3]=.160;
//   fermip[2]=.160;
// 
//   epsn[197]=.006;
//   epsn[64]=0.01;
//   epsn[27]=.0083;
//   epsn[12]=.016;
//   epsn[4]=.02;
//   epsn[3]=.0055;
//   epsn[2]=.0022;

#endif
