/******************************************/
/*         XEM Cross Section Model        */
/*         Zhihong Ye, 01/11/2012         */
/*   --Modified from Fortran version XEM  */
/******************************************/
#include "XEM_Fy2Sig.h"
#include "XEM_SigCal.h"

bool IsGoodFlag(int kflag){
  if(kflag==1||kflag==2||kflag==3||kflag==4||kflag==5) 
    return kTRUE;
  else
    return kFALSE;  

}

//XEM_VAR3* XEMC_Born(double iE0set, double iEpset, double iTheta, XEM_TGT* iTarget)
//Change to Double_t type to be called from outside
//                         GeV             GeV           Deg
Double_t XEMC_Born(double iE0set, double iEpset, double iTheta, XEM_TGT* iTarget, int iFlag)
{
  //The unit of XS is nb/(sr*GeV/c);

  //  XEM_VAR3* xs = new XEM_VAR3();
  Double_t xs=0.0;

  Bool_t bCCor = kFALSE; //Give an option to calculate Coulomb Correction
  //Bool_t bCCor = kTRUE; //Only turn on the CC when calculating radiated cross section
  Double_t E0 = iE0set; //GeV 
  Double_t Ep = iEpset; //GeV
  Double_t Theta = iTheta*TMath::DegToRad();

//  if(IsDebug)
//      iTarget->Print();

  //iFlag =1->QE+DIS_F2ALLM, 2->QE+F1F2IN09+Coulomb Correction, 
  //iFlag =3->QE Only, iFlag=4->DIS Only (F2ALLM), iFlag==5->DIS Only (F1F2IN09) 
  XEM_XS* XS_Born = new XEM_XS();  

  if(IsGoodFlag(iFlag)) 
     gCal_Sigma(E0,Ep,Theta,iTarget,bCCor,iFlag,XS_Born);
  else{
     cerr<< "******* Warning, Wrong XEMC Flag!!!"<<endl;
  }
    
  xs = XS_Born->All;

  delete XS_Born;
  return xs;
}

