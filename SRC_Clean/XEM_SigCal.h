//                           GeV     GeV            Rad
#include "DIS_Lite.h"
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

  Double_t Qsq=-1000.,xbj=-1000.,nu=-1000.,y=-1000.,Wsq=-1000.,Elastic_Peak=-1000.;

  /*Coulomb Correction{{{*/
  //Get DeltaE value 
  Double_t DeltaE = 0.0;
  
  if(kCCor&&kFlag==4){
// first get the vertex quantities and do a target dependent
// boost to beam energy and scattered electron energy
// and do Coulomb correction.  recipe is given in:
// Aste et al., Eur. Phys. J. A 26, 167 (2005)
// note that these deltae_cc's are calculated as follows:
// deltae_cc = (1.5)*(Z/R)*(hbar*c)*alpha*0.775
// the 0.775 comes from Aste EPJ A 26 167 (2005)
// also, all deltae_cc's are computed for Z-1, not Z!/-*    
    if(kTarget->A==1) //  !Hydrogen
		DeltaE = 0.0;
	else if(kTarget->A==2) // !Deuterium
		DeltaE = 0.0;
	else if(kTarget->A==3) // !Helium-3
		DeltaE = 0.0; //0.00085;
	else if(kTarget->A==4) // !Helium-4
		DeltaE = 0.0; //0.0010;
	else if(kTarget->A==9) // !Beryllium
		DeltaE = 0.001875;
	else if(kTarget->A==12) // !Carbon
		DeltaE = 0.00292;
	else if(kTarget->A==27) // !Aluminum
		DeltaE = 0.0061;
	else if(kTarget->A==40) // !Cacium-40
		DeltaE = 0.00743;
	else if(kTarget->A==48) // !Cacium-48
		DeltaE = 0.00699;
	else if(kTarget->A==64) // !Copper
		DeltaE = 0.0102;
	else if(kTarget->A==197) // !Gold
		DeltaE = 0.0199;
	else{
		cerr<<"**** Target not in the list! Coulumb Correction give up~ "<<endl;
		DeltaE = 0.0;
	}     
  }
  /*}}}*/

  Double_t FF1 = (kE0 + DeltaE)/kE0; //Fix the bug here, shoudl be kE0+... - ZYe 05/12/2014
  Double_t E0_cc = kE0 + DeltaE;
  Double_t Ep_cc = kEp + DeltaE;

  //Define a Structure class to keep additional target info, such as Fermi Motion and Seperation Energy
  Double_t SN_Theta = sin(kTheta/2.0);
  Double_t SN_SQ = SN_Theta*SN_Theta;
  
  Double_t aTarget_Mass = kTarget->Mass;
  Qsq = 4.0*E0_cc*Ep_cc*SN_SQ;
  nu = E0_cc - Ep_cc;
  xbj = Qsq/2.0/P_MASS/nu;
  y = nu/Ep_cc;
  Wsq = -Qsq + P_MASS*P_MASS + 2.0*P_MASS*nu;
  Elastic_Peak = E0_cc/(1.0+2.0*E0_cc*SN_SQ/aTarget_Mass);
    
  if(kFlag==1 || kFlag ==2 || kFlag ==4){
    if(kTarget->A > 1.5)
      gCal_Fy2Sig(E0_cc,Ep_cc,kTheta,kTarget,Sig_QE);
    else
      Sig_QE->Value = 0.0;
    Sig_QE->Value *= FF1*FF1; 
  }//if(kFlag==1  || kFlag ==2|| kFlag ==4)
     
  sig_dis =0.0;

  if(kFlag==1 || kFlag==3|| kFlag ==4){
      //Using F2ALLM97 model:--Z. Ye 05/30/2017
      DIS *dis = new DIS();
      dis->SetKin(kE0, kEp, kTheta);//GeV,GeV/c, Radius
      Double_t Sigma_DIS = dis->Sigma(kTarget->A, kTarget->Z);//nbarn/sr/GeV
      sig_dis = Sigma_DIS/1000.0; //nb/sr/MeV

      /*Christy&Bosted's DIS model, Need christy_bosted_inelastic.h{{{*/ //--Z. Ye 05/30/2017
      //double xs_p = sigma_p(kE0, kTheta, kEp);//Peter Bosted's DIS model
      //double xs_n = sigma_n(kE0, kTheta, kEp);//Peter Bosted's DIS model
      //double xs_d = sigma_d(kE0, kTheta, kEp);//Peter Bosted's DIS model
      //if(kTarget->A==3&&kTarget->Z==1) sig_dis = xs_n + xs_d;
      //else if(kTarget->A==3&&kTarget->Z==2) sig_dis = xs_p + xs_d;
      //else sig_dis = kTarget->Z * xs_p + (kTarget->A-kTarget->Z)*xs_n;
      //sig_dis /= 1000.0; //nb/sr/MeV
      /*}}}*/

      if(sig_dis<0.0||isnan(sig_dis)||isinf(sig_dis))
          sig_dis = 0.0;

      delete dis;
  }

  sig_dis *= FF1*FF1;

  delete F; delete W;
    
  sig->Factor = Sig_QE->Factor;
  sig->QE = Sig_QE->Value;
  sig->DIS = sig_dis;
  sig->All = Sig_QE->Value + sig_dis;

  delete Sig_Donal; delete Sig_QE;
  return;
} 
