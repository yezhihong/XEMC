/******************************************/
/*         XEM Cross Section Model        */
/*         Zhihong Ye, 01/11/2012         */
/*   --Modified from Fortran version XEM  */
/******************************************/
#include "XEM_Fy2Sig.h"
#include "XEM_SigCal.h"
//#include "XEM_F1F2.h"
//#include "XEM_DIS.h"

bool IsGoodFlag(int kflag){
  if(kflag==1||kflag==2||kflag==3||kflag==4||kflag==5) 
    return kTRUE;
  else
    return kFALSE;  

}

//XEM_VAR3* XEMC_Born(double iE0set, double iEpset, double iTheta, XEM_TGT* iTarget)
//Change to Double_t type to be called from outside
<<<<<<< HEAD
//                         GeV             GeV           Deg
Double_t XEMC_Born(double iE0set, double iEpset, double iTheta, int iA,int iZ,int iFlag)
=======
//                         MeV             MeV           Deg
Double_t XEMC_Born(double iE0set, double iEpset, double iTheta, XEM_TGT* iTarget, int iFlag)
>>>>>>> ca00fa49466f7e3edd4c4d0aa0feaf3c00867c8c
{
  //The unit of XS is nb/(sr*GeV/c);

  //  XEM_VAR3* xs = new XEM_VAR3();
  Double_t xs_all=0.0;

  //Bool_t bCCor = kFALSE; //Give an option to calculate Coulomb Correction
  Bool_t bCCor = kTRUE; //Only turn on the CC when calculating radiated cross section
  Double_t E0 = iE0set; //GeV 
  Double_t Ep = iEpset; //GeV
  Double_t Theta = iTheta*TMath::DegToRad();
  //XEM_TGT* iTarget=new XEM_TGT();
  //iTarget->GetValueAZ(iA,iZ);

//  if(IsDebug)
//      iTarget->Print();

  //iFlag =1->QE+DIS, iFlag=2->QE Only, iFlag=3->DIS Only (F1F2IN09 or F2ALLM), iFlag==4->DIS Only (F1F2IN06) 
  XEM_XS* xs = new XEM_XS();  

  if(IsGoodFlag(iFlag)) 
     gCal_Sigma(E0,Ep,Theta,iTarget,bCCor,iFlag,xs);
  else{
     cerr<< "******* Warning, Wrong XEMC Flag!!!"<<endl;
  }
    
  xs_all = xs->All;

<<<<<<< HEAD
  delete iTarget;
  delete xs;
  return xs_all;
=======
  delete XS_Born;
  return xs;
>>>>>>> ca00fa49466f7e3edd4c4d0aa0feaf3c00867c8c
}

