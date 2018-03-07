////////////////////////////////////////////////
// Generate Cross Section Look-up Table
//  --Zhihong Ye, 07/03/2012
////////////////////////////////////////////////
/*Include{{{*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <errno.h>
#include <sstream>
//#include <iterator>
//from root
#include <TMath.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TLorentzVector.h>
#include <TMatrix.h>
#include <TFile.h>
#include <TTree.h>
#include <TStopwatch.h>
/*}}}*/
using namespace::std;
using namespace::TMath;
#include "XEMC.h"
//#include "/work/halla/e08014/disk1/yez/XEMC/SRC/XEMC.h"
char* gTarget;
Double_t E0=-1.0;   //GeV
Double_t Ep=-1.0;   //GeV
Double_t Theta=-1.0; //Degree
Bool_t bAsk=kFALSE;
int getargs(int argc, char**argv);

int main(int argc,char** argv){

	Double_t xbj=0.0, cs_qe=0.0, cs_dis=0.0, cs_rad=0.0,cs_born=0.0;
    Double_t cs_dis_f2allm=0.0, cs_dis_f1f209=0.0;
	TString Target;
	int gerr = getargs(argc,argv);

	if(gerr<0)
		bAsk=kTRUE;
    else{
	    bAsk=kFALSE;
		Target = gTarget;
	}
	if(bAsk){
		cerr<<" Target (H2,H3, He3,He4,C12,Al,Ca40,Ca48) = "; cin >> Target;
		cerr<<" E0 (GeV/c) = "; cin >> E0;
		cerr<<" Ep (GeV/c) = "; cin >> Ep;
		cerr<<" Theta (Degree) = "; cin >> Theta;	
	}

	Double_t Q2 = 4.0 * E0 * Ep * pow(sin(Theta*3.1415926/180./2.0),2);
	xbj = Q2/2.0/0.938272/(E0-Ep);

    //Basic input file, mostly important for radiated cross sections
	TString Target_Input = Form("./input/%s_Input.dat",Target.Data());	

	//Define a event to calculate radiated cross section
	XEMC* Event = new XEMC(); 
	Event->Init(Target_Input.Data());
    Event->SetTargetTable("/work/halla/e08014/disk1/yez/XEMC/target.table");
	Int_t err = -1;
     Event->DebugPrint();

	err = Event->Process(E0,Ep,Theta);	
	if(err>=0){
		cs_qe = Event->XS_QE();
		cs_dis = Event->XS_DIS();//default
		cs_dis_f2allm = Event->XS_DIS(4);//4->F2ALLM
		cs_dis_f1f209 = Event->XS_DIS(5);//5->F1F209;
		cs_born = Event->XS_Born();
		cs_rad = Event->XS_Rad();
	}else{
         cerr<<"*** ERROR, Something wrong with the XS calculation!!!"<<endl;
        
        }
	delete Event;
	cerr <<"------------------------------------------------------------------------"<<endl;
	cerr <<"------------------------------------------------------------------------"<<endl;
	cerr << Form("For Ep=%f, Theta=%f, xbj=%f, Q2=%f", Ep, Theta, xbj, Q2)<<endl;
	cerr <<"------------------------------------------------------------------------"<<endl;
	cerr << Form("@@@ XS_QE = %e, XS_DIS = %e(%e), XS_Born = %e, XS_Rad = %e", cs_qe, cs_dis_f2allm,cs_dis_f1f209, cs_born,cs_rad)<<endl;
	cerr <<"------------------------------------------------------------------------"<<endl;
	cerr <<"------------------------------------------------------------------------"<<endl;
	return 0;
}


/*int getargs(int argc,char** argv){{{*/
int getargs(int argc,char** argv){
	char* argptr;
	bool noStop;  
	int err=-1;

	for(int i=0;i<argc;i++){
		argptr = argv[i];
		if(*argptr=='-'){
			argptr++;
			switch (*argptr){
				case 'E':
					if(*(++argptr))
						E0 = atof(argptr);
					err=0;
					break;
				case 'P':
					if(*(++argptr))
						Ep = atof(argptr);
					err=0;
					break;
				case 'A':
					if(*(++argptr))
						Theta = atof(argptr);
					err=0;
					break;
				case 'T':
					if(*(++argptr))
						gTarget = argptr;
					err=0;
					break;
				case 'h':
					cerr <<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-E[GeV]  Beam Energy" <<endl;
					cerr <<"-P[GeV]  Scattering Momentum" <<endl;
					cerr <<"-A[Deg]  Scattering Angle"<<endl;
					cerr <<"-T[H2,H3, He3,He4,C12,Ca40,Ca48,...]  Target Name" <<endl;
					cerr <<endl<<"================================================"<<endl;
					noStop=false;
					err=-1;
					goto OUT;
					break;
				default:
					cerr <<"Unrecognized argument: " << argptr << endl;
					cerr <<endl<<"================================================"<<endl;
					cerr <<"Option: " <<endl;
					cerr <<"-E[GeV]  Beam Energy" <<endl;
					cerr <<"-P[GeV]  Scattering Momentum" <<endl;
					cerr <<"-A[Deg]  Scattering Angle"<<endl;
					cerr <<"-T[H2,He3,He4,C12,Ca40,Ca48,...]  Target Name" <<endl;
					cerr <<"             Zhihong Ye 10/04/2009" <<endl;
					cerr <<"================================================"<<endl;
					err=-1;
					break;
			}

		}
		noStop=true;
OUT:if(!noStop){break;}
	continue;
	}
	return err; 
}
/**/
