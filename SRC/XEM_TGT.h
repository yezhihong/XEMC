#define U2GeV 0.931494028

class XEM_TGT{

    private:
        static const int CHAR_LEN=1024;

        string fName;  // Target Name
        double fMass; // Target Mass
        Int_t fA;       // Target Nuclear Number
        Int_t fZ;       // Target Proton Number

        double fRL; //Radiation Length
        double fResol; //Parameter for DEEPSIG smearing
        double fESep;  //Separation Energy
        double ff0;
        double fB;
        double fa;
        double fb;
        double falpha; //parameters to calculate F(y)

    public:
        void GetTargetPar(const TString& kTarget_Table, const int kA, const int kZ);
        TString GetName();
        Int_t GetA();
        Int_t GetZ();
        Double_t GetFyPar(const TString& kFyName);


        inline void Print(){
            cerr <<endl<< "--------------------------------------"<<endl;
            Printf("%-*s%s",20,"|   Target Name:  ",fName.c_str());
            Printf("%-*s%f",20,"|   Mass(GeV):  ",fMass);
            Printf("%-*s%d",20,"|   A:  ",fA);
            Printf("%-*s%d",20,"|   Z:  ",fZ);
            Printf("%-*s%f",20,"|   Rad. Length:  ",fRL);
            Printf("%-*s%f",20,"|   Resol:  ",fResol);
            Printf("%-*s%f",20,"|   Sep. Energy:  ",fESep);
            Printf("%-*s%f",20,"|   f0:  ",ff0);
            Printf("%-*s%f",20,"|   B:  ",fB);
            Printf("%-*s%f",20,"|   a:  ",fa);
            Printf("%-*s%f",20,"|   b:  ",fb);
            Printf("%-*s%f",20,"|   alpha:  ",falpha);
            cerr << "--------------------------------------"<<endl<<endl;

        };
};
