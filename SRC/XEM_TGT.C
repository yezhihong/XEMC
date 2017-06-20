#include "XEMC_Main.h"
void XEM_TGT::GetTargetPar(const TString& kTarget_Table, const int kA, const int kZ){
    cout<<"&&& XEM_TGT: Loading Target Table from "<<kTarget_Table.Data()<<endl;

    /*Read Target Table{{{*/
    FILE* table;
    table=fopen(kTarget_Table.Data(),"r");
    char buf[CHAR_LEN];
    char data[CHAR_LEN];
    vector<string> inputdata;
    int i,j;

    while ( fgets(buf,CHAR_LEN,table) )
    {
        i=0;
        while ( buf[i]==' ' )
        {
            i++;
        }
        if ( buf[i]!='#' )
        {
            j=0;
            while ( buf[i]!='#' && buf[i]!='\0' && buf[i]!='\n' )
            {
                data[j]=buf[i];
                i++; j++;
            }
            data[j]='\0';
            while ( data[--j]==' ' || data[j]=='\t' )
            {
                //remove space or tab at the end of data
                data[j]='\0';
            }
            inputdata.push_back(data);
        }
        //else it's comment, skipped
    }
    fclose(table);
    /*}}}*/

    /*Assign Values{{{*/
    unsigned int N_Line = inputdata.size();
    bool Exist = kFALSE;
    for(unsigned int i=0;i<N_Line;i++){
        vector<TString> line = Tokens(inputdata[i].c_str());
        cout<<inputdata[i].c_str()<<endl;
        cout<<inputdata[i].c_str()<<endl;
        //fName = line[0].Data();
        fName = "TEST";
        cout<<"A"<<endl;
        fA = line[1].Atoi();
        cout<<"B"<<endl;
        fZ = line[2].Atoi();
        cout<<Form("Line#%d:  Size=%lu, Name=%s, A=%d, Z=%d", i, line.size(), fName.c_str(), fA, fZ)<<endl;
        if(fA==kA && fZ==kZ){
            fMass = line[3].Atof();
            fRL = line[4].Atof();
            fResol = line[5].Atof();
            fESep = line[6].Atof();
            ff0 = line[7].Atof();
            fB = line[8].Atof();
            fa = line[9].Atof();
            fb = line[10].Atof();
            falpha = line[11].Atof();

            Exist = kTRUE;
            //break;
        }
        //line.clear();
    }
    inputdata.clear();/*}}}*/

    //Be careful -- the following variables needed to be converted:
    fMass *= U2GeV ; //From u to GeV;
    fESep/=1000.0; 
    ff0  /=1000.0;
    fB/=1000.0;
    fa /=1000.0;
    fb /=1000.0;

    if(!(Exist)){
        cerr << "****** ERROR, your target is not in the table! Check the following table:" <<endl;
    }
}

TString XEM_TGT::GetName(){
    return fName.c_str();
}

Int_t XEM_TGT::GetA(){
    return fA;
}

Int_t XEM_TGT::GetZ(){
    return fZ;
}

Double_t XEM_TGT::GetFyPar(const TString& kFyName){
    if(kFyName=="RL") return fRL;
    if(kFyName=="Resol") return fResol;
    if(kFyName=="ESep") return fESep;
    if(kFyName=="f0") return ff0;
    if(kFyName=="B") return fB;
    if(kFyName=="a") return fa;
    if(kFyName=="b") return fb;
    if(kFyName=="alpha") return falpha;
    else{
      cerr<<"--- Couldn't fine the parameter: %s"<<kFyName.Data()<<endl;
      return 0;
    }
}

