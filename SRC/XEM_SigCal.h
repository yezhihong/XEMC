//                           GeV     GeV            Rad
#include "DIS_Lite.h"
<<<<<<< HEAD
//#include "XEM_F1F2.h"
=======
#include "XEM_F1F2.h"
>>>>>>> ca00fa49466f7e3edd4c4d0aa0feaf3c00867c8c
//#include "christy_bosted_inelastic.h"
inline void gCal_Sigma(double kE0,double kEp,double kTheta,XEM_TGT *kTarget,bool kCCor, int kFlag, XEM_XS* sig)
{
  /*____________________________________________________________________________________
  //      Subroutine to compute model unradiated cross section from a combination
  //      of Y-scaling and deep inelastic models. The DEEPSIG model can be smeared
  //      with a gaussian in missing mass squared of width RESOL$ (one sigma).
  //      If SMEAR$ is .TRUE., such smearing will occur. If SMEAR$ is .FALSE.,
  //      smearing is suppresed. It should be noted that the smearing involves
  //      computing a convolution integral, which significantly slows down
  //      this subroutine!
  //      
  //      ARGUMENTS:
  //      
  //      E1:             -       Incident energy in GeV.
  //      E2:             - Scattered energy in GeV.
  //      TH:             - Scattering angle in rad     
  //      A:              - 'A' of nucleus.
  //      Z:              - Number of protons in nucleus.
  //      M_TGT:  - Mass of target nucleus in GeV/c2.
  //      M_REC:  - Mass of recoiling nucleon in GeV/c2.
  //      E_SEP:  - Separation energy for target nucleus in GeV/c2.
  //      SIG  :  - Calculated cross section in nb/(MeV-ster).

  //
  // OUTPUT ARGUMENTS:
  //
  //   SIG:        (R*8) - Calculated cross section
  //   Y:          (R*8) - Scaling variable Y in 1/GeV.

  //   AUX(1) = RESOL parameter for DEEPSIG smearing (not used).
  //   AUX(2) = ES    Separation energy
  //   AUX(3) = F(0)  parameter for F(y) function
  //   AUX(4) = BigB  parameter for F(y)
  //   AUX(5) = a     parameter for F(y)
  //   AUX(6) = b     parameter for F(y)
  //   AUX(7) = alpha parameter for F(y)
  //       ______________________________________________________________________________*/
    
  //Define Cross Section
  XEM_SIG* Sig_QE = new XEM_SIG();
  XEM_SIG* Sig_Donal = new XEM_SIG();
  Double_t sig_dis=0.0;
 
  //Define quantities for CS calculation
  XEM_VAR3 *F = new XEM_VAR3(); //store F1,F2,RC values
  XEM_VAR2 *W = new XEM_VAR2(); //store W1,W2 values

  /*Coulomb Correction{{{*/
  //Get kDeltaE value 
  Double_t kDeltaE = 0.0;
  
  if(kCCor&&kFlag==5){
// first get the vertex quantities and do a target dependent
// boost to beam energy and scattered electron energy
// and do Coulomb correction.  recipe is given in:
// Aste et al., Eur. Phys. J. A 26, 167 (2005)
// note that these deltae_cc's are calculated as follows:
// deltae_cc = (1.5)*(Z/R)*(hbar*c)*alpha*0.775
// the 0.775 comes from Aste EPJ A 26 167 (2005)
// also, all deltae_cc's are computed for Z-1, not Z!/-*    
    if(kTarget->A==1) //  !Hydrogen
		kDeltaE = 0.0;
	else if(kTarget->A==2) // !Deuterium
		kDeltaE = 0.0;
	else if(kTarget->A==3) // !Helium-3
		kDeltaE = 0.0; //0.00085;
	else if(kTarget->A==4) // !Helium-4
		kDeltaE = 0.0; //0.0010;
	else if(kTarget->A==9) // !Beryllium
		kDeltaE = 0.001875;
	else if(kTarget->A==12) // !Carbon
		kDeltaE = 0.00292;
	else if(kTarget->A==27) // !Aluminum
		kDeltaE = 0.0061;
	else if(kTarget->A==40) // !Cacium-40
		kDeltaE = 0.00743;
	else if(kTarget->A==48) // !Cacium-48
		kDeltaE = 0.00699;
	else if(kTarget->A==64) // !Copper
		kDeltaE = 0.0102;
	else if(kTarget->A==197) // !Gold
		kDeltaE = 0.0199;
	else{
		cerr<<"**** Target not in the list! Coulumb Correction give up~ "<<endl;
		kDeltaE = 0.0;
	}     
  }
  /*}}}*/

  Double_t FF1 = (kE0 + kDeltaE)/kE0; //Fix the bug here, shoudl be kE0+... - ZYe 05/12/2014
  Double_t E0_cc = kE0 + kDeltaE;
  Double_t Ep_cc = kEp + kDeltaE;

  if(kFlag==1 || kFlag ==2 || kFlag ==5){
    if(kTarget->A > 1.5)
      gCal_Fy2Sig(E0_cc,Ep_cc,kTheta,kTarget,Sig_QE);
    else
      Sig_QE->Value = 0.0;
    Sig_QE->Value *= FF1*FF1; 
  }//if(kFlag==1 || kFlag ==2)
     
  sig_dis =0.0;
  if(kFlag==1 || kFlag ==3 || kFlag==4|| kFlag ==5){

          if(kFlag==1 || kFlag==3|| kFlag ==5){
              //F1F2 Fitting from P.Bosted,2009, a fortran code
              //--Zhihong Ye, 12/05/2012
              //-- replaced with "DIS.h" which includes three DIS models, including PB,
              //and remove compiling the fortran code -- Zhihoong Ye, 05/30/2017
              /*Note: this needs the fortran PB code, not in used anymore{{{*/
<<<<<<< HEAD
              /*
=======
>>>>>>> ca00fa49466f7e3edd4c4d0aa0feaf3c00867c8c
              Double_t CS_Theta = cos(kTheta/2.0);
              Double_t SN_Theta = sin(kTheta/2.0);
              Double_t TN_Theta = tan(kTheta/2.0);
              Double_t SN_SQ = SN_Theta*SN_Theta;
              Double_t CS_SQ = CS_Theta*CS_Theta;

              Double_t  Qsq = 4.0*E0_cc*Ep_cc*SN_SQ;
              Double_t nu = E0_cc - Ep_cc;
<<<<<<< HEAD
              Double_t Wsq = -Qsq + PROTON_MASS*PROTON_MASS + 2.0*PROTON_MASS*nu;

              gCal_F1F2(kTarget->A,kTarget->Z,Qsq,Wsq,F); 
              W->First = F->First/PROTON_MASS;
              W->Second = F->Second/nu;
              Double_t sig_mott = pow((19732.0/(2.0*137.0388*E0_cc*SN_SQ)),2)*pow(CS_SQ,1)/1e3;
              sig_dis = sig_mott*(W->Second+2.0*W->First*pow(TN_Theta,2));
              */
=======
              Double_t Wsq = -Qsq + P_MASS*P_MASS + 2.0*P_MASS*nu;
              Double_t xbj = Qsq/2.0/P_MASS/nu;

              gCal_F1F2(kTarget->A,kTarget->Z,Qsq,Wsq,F); 
              W->First = F->First/P_MASS;
              W->Second = F->Second/nu;
              Double_t sig_mott = pow((19732.0/(2.0*137.0388*E0_cc*SN_SQ)),2)*pow(CS_SQ,1)/1e6;
              sig_dis = sig_mott*(W->Second+2.0*W->First*pow(TN_Theta,2));
              //double sig_dis_temp= sig_dis;
>>>>>>> ca00fa49466f7e3edd4c4d0aa0feaf3c00867c8c
              /*}}}*/

              //Using F2ALLM97 model:--Z. Ye 05/30/2017
<<<<<<< HEAD
              DIS_Lite *dis = new DIS_Lite();
              dis->SetKin(kE0, kEp, kTheta);//GeV,GeV/c, Radius
              sig_dis = dis->Sigma(kTarget->A, kTarget->Z);//nbarn/sr/GeV
              delete dis;
=======
              /* DIS *dis = new DIS();*/
              //dis->SetKin(E0_cc, Ep_cc, kTheta);//GeV,GeV/c, Radius
              //Double_t Sigma_DIS = dis->Sigma(kTarget->A, kTarget->Z);//nbarn/sr/GeV
              //sig_dis = Sigma_DIS/1000.0; //nb/sr/MeV
              /*delete dis;*/

              //cout<<"x = "<<xbj<<" DIS_AM / DIS_PB = "<<sig_dis/sig_dis_temp<<endl;
>>>>>>> ca00fa49466f7e3edd4c4d0aa0feaf3c00867c8c

              /*Christy&Bosted's DIS model, Need christy_bosted_inelastic.h{{{*/ //--Z. Ye 05/30/2017
              //double xs_p = sigma_p(kE0, kTheta, kEp);//Peter Bosted's DIS model
              //double xs_n = sigma_n(kE0, kTheta, kEp);//Peter Bosted's DIS model
              //double xs_d = sigma_d(kE0, kTheta, kEp);//Peter Bosted's DIS model
              //if(kTarget->A==3&&kTarget->Z==1) sig_dis = xs_n + xs_d;
              //else if(kTarget->A==3&&kTarget->Z==2) sig_dis = xs_p + xs_d;
              //else sig_dis = kTarget->Z * xs_p + (kTarget->A-kTarget->Z)*xs_n;
              /*}}}*/

              if(sig_dis<0.0||isnan(sig_dis)||isinf(sig_dis))
                  sig_dis = 0.0;

          }

	  sig_dis *= FF1*FF1;
  }// if(kFlag==1 || kFlag ==3 || kFlag==4 || kFlag==5){

  delete F; delete W;

  sig->Factor = Sig_QE->Factor;
  sig->QE = Sig_QE->Value;
  sig->DIS = sig_dis;
  sig->All = Sig_QE->Value + sig_dis;

  delete Sig_Donal; delete Sig_QE;
  return;
} //Double_t gCal_Sigma(double kE0,double kEp,double kTheta,double kZ,double kA,TString& kTarget, int kFlag)

  //==========================
  // What we have next:
  //  Double_t gGet_EMC_Func(A,xbj)
  //  Double_t gGet_EMC_Func_Slac(A,xbj)
  //  Double_t gGet_Dis_HighX_Cor(A,xbj);
  //==========================
    

inline Double_t gGet_EMC_Func(Int_t aA, Double_t aXbj)/*{{{*/
{
  /*
    aji note:
    polynomial fit made to inelastic emc ratios from xem data
    at low x (x<0.3) the fit is constrained with world data (to get some sort of shadowing behaviour).

    DJG NOTE 7/11/2007
    Note that although this is called "emc_func", it is really a fit to the ratio of the emc effect to 
    a pure smearing claculation. So - this function is applied to the smeared n+p cross section
    to reproduce the correct emc effect. If you plot these functions, it will not look like
    the emc effect, so don't panic.
  */
  Double_t xtmp,emc;
 
  if(aXbj<=0.9) 
    xtmp = aXbj;
  else
    xtmp = 0.9;
  emc =1.0;

    if(aA==2) 
      emc = 0.70443 +2.3742*xtmp - 4.6566*pow(xtmp,2) -0.78540*pow(xtmp,3)
        +9.3838*pow(xtmp,4) - 6.1256*pow(xtmp,5);
    else if(aA==3)
      emc = 0.92170 +1.7544*xtmp -3.7324*pow(xtmp,2) - 0.24293*pow(xtmp,3)
        + 6.7613*pow(xtmp,4) - 4.6089*pow(xtmp,5);
    else if(aA==4)
      emc = 0.70050 + 3.1241*xtmp - 6.1738*pow(xtmp,2)
        - 0.049988*pow(xtmp,3) + 9.3053*pow(xtmp,4) - 6.1348*pow(xtmp,5);
    else if(aA==9)
      emc = 0.46324 + 6.1220*xtmp - 12.184*pow(xtmp,2) -1.0956*pow(xtmp,3)
        + 20.316*pow(xtmp,4) -12.899*pow(xtmp,5);
    else if(aA==12)
      emc = 0.63653 + 4.6458*xtmp -9.2994*pow(xtmp,2) 
        -1.2226*pow(xtmp,3) +16.157*pow(xtmp,4) -10.236*pow(xtmp,5);
    else if(aA==27)
      emc = 0.98645 + 3.0385*xtmp - 22.072*pow(xtmp,2) + 74.981*pow(xtmp,3)
        - 132.97*pow(xtmp,4) + 113.06*pow(xtmp,5) -35.612*pow(xtmp,6);
     else if(aA==40 || aA==48)  //FIX_HERE
      emc = 0.58372 + 6.0358*xtmp - 11.988*pow(xtmp,2) -1.0211*pow(xtmp,3)
        +18.567*pow(xtmp,4) - 11.482*pow(xtmp,5);
    else if(aA==64) 
      emc = 0.58372 + 6.0358*xtmp - 11.988*pow(xtmp,2) -1.0211*pow(xtmp,3)
        +18.567*pow(xtmp,4) - 11.482*pow(xtmp,5);
    else if(aA==197)
      emc = 0.44132 + 8.1232*xtmp -16.141*pow(xtmp,2) -5.6562*pow(xtmp,3)
        + 35.606*pow(xtmp,4) - 22.008*pow(xtmp,5);
    else{
      cerr << "********* ERROR, Unknown Target!!!"<<endl;
      emc = 0.0;
    }
 
  return emc;
}//Double_t gGet_EMC_Func(...)/*}}}*/
   
inline Double_t gGet_EMC_Func_Slac(Int_t aA, Double_t aXbj)/*{{{*/
{
  Double_t aAlpha, aC, aTemp;
  
  aTemp = aA;
  //if(aA==4||aA==3)  // emc effect is more like C for these 2...
  //   aTemp = 12;
  
  aAlpha = -0.070+2.189*pow(aXbj,1) - 24.667*pow(aXbj,2) + 145.291*pow(aXbj,3)
    -497.237*pow(aXbj,4) + 1013.129*pow(aXbj,5) - 1208.393*pow(aXbj,6)
    +775.767*pow(aXbj,7) - 205.8720*pow(aXbj,8);

  aC = exp(0.017 + 0.018*log(aXbj) + 0.005*pow(log(aXbj),2));
 
  return aC*pow(aTemp,aAlpha);
}//Double_t gGet_EMC_Func_Slac(...)/*}}}*/

//For DIS cross section, make a correction at x->1 region
inline Double_t gGet_Dis_HighX_Cor(Int_t aA, Double_t aXbj)/*{{{*/
{
  Double_t x1_low = 0.9, x1_high = 0.95;
 // Double_t x2_low = 1.9, x2_high = 2.00;
  Double_t frac=1.0, cor=1.0;
  Bool_t bA = kTRUE;
  
  if(aA == 2)
    cor = -3.30482*aXbj + 4.10442;
  else if(aA ==3){
    x1_low = 1.0; x1_high = 1.15;
    if(aXbj>x1_low){
      if(aXbj<x1_high)
        cor = -4.80303*aXbj + 5.74758;
      else
        cor = 0.5;
    }
  }
  else if(aA == 4)
    cor=-1.78944*aXbj+ 2.63272; 
  else if(aA == 9)
    cor=-1.7549631060248*aXbj+ 2.6646629067298; 
  else if(aA == 12)
    cor=-1.29213*aXbj+ 2.2087; 
  else if(aA == 64)
    cor=-1.65829142599487*aXbj+ 2.48174872208596;
  else if(aA == 197)
    cor=-1.42430013496752*aXbj+ 2.25789690593227;
  else{
    bA = kFALSE; cor = 1.0;
  }
   
  if(bA){
    if((aXbj>=x1_low)&&(aXbj<=x1_high))
      frac = (aXbj-x1_low)/(x1_high-x1_low);
    cor = 1.0+frac*cor-frac;  
  }
  if(cor<0.4)
    cor=0.4;
  
  return cor; 
}//Double gGet_Dis_HighX_Cor(...)
    /*}}}*/
    
