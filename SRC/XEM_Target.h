/*#ifndef ROOT_XEM_TGT*/
/*#define ROOT_XEM_TGT*/
#define U2GeV  0.931494028       //Convert from atomic mass unit to GeV unit   
////////////////////////////////////////
//IMPORTANT: Define Target info
//const TString TARGET_TABLE = "/Users/yez/work/github/XEMC/SRC/target.table";
//Target Table: include two types of tables: Radiative Corrected and Non-Radiative Corrected  
////////////////////////////////////////

class XEM_TGT
{
    public:
        XEM_TGT() {
        }
        virtual ~XEM_TGT(){

        }

        void GetTargetPar(const TString& kTarget_Table,  const int kA, const int kZ ){
            //fTarget_Table=kTarget_Table;
            cout<<"&&&& XEM_TGT: Loading Table from "<<kTarget_Table.Data()<<endl;
            ifstream table; 
            table.open(kTarget_Table.Data());
            //FIX_HERE: temperate method to read target info. will improve it later.
            TString content; Int_t CommentLine=0;
            while( content.ReadLine(table)){
                if ( content.BeginsWith("#") )
                    CommentLine++;
                else
                    break;
            }
            table.close();

            Int_t aLine=0;
            table.open(kTarget_Table.Data());
            TString name1;
            Int_t A1, Z1;
            Double_t mass1, RL1, Resol1, ESep1, f01, B1, a1, b1, alpha1;
            while(!(table.eof())){
                aLine++;
                if(aLine<=CommentLine)
                    content.ReadLine(table);
                else{
                    table >> name1 >> A1 >> Z1 >> mass1 >> RL1 >> Resol1 >>ESep1 >> f01>> B1>>a1>>b1>>alpha1;

                    if((A1==kA)&&(Z1==kZ)){
                        cout<<Form("--- Name = %s, A = %d, Z = %d", name1.Data(), A1, Z1)<<endl;
                        //Name = name1;
                        A = A1;
                        Z = Z1;
                        Mass = mass1;
                        RL = RL1;
                        Resol = Resol1;
                        ESep = ESep1;
                        f0 = f01;
                        B = B1;
                        a = a1;
                        b = b1;
                        alpha = alpha1;

                        fExist = kTRUE;
                        break;
                    }
                }
            }
            table.close();

            //Be careful -- the following variables needed to be converted:
            Mass *= U2GeV ; //From u to GeV;
            ESep/=1000.0; 
            f0  /=1000.0;
            B/=1000.0;
            a /=1000.0;
            b /=1000.0;

            if(!(fExist)){
                //     cerr <<endl<< "@@@@@@ I have found your target from the table!" <<endl;
                //  else{
                cerr << "****** ERROR, your target is not in the table! Check the following table:" <<endl;
                List();
            }
            }

            void SetValue(
                    const TString kName=" ",
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
            }

            void List(){
                ifstream table(fTarget_Table.Data());
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

            void Print(){
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

            }

            private:
            //Very Dangerous but I have no choice unless I change the entire code, too late so far
            TString Name;  // Target Name
            Double_t Mass; // Target Mass
            Int_t A;       // Target Nuclear Number
            Int_t Z;       // Target Proton Number

            Double_t RL; //Radiation Length
            Double_t Resol; //Parameter for DEEPSIG smearing
            Double_t ESep;  //Separation Energy
            Double_t f0;
            Double_t B;
            Double_t a;
            Double_t b;
            Double_t alpha; //parameters to calculate F(y)

            Bool_t fExist;
            TString fTarget_Table;
        };

        /*#endif*/
