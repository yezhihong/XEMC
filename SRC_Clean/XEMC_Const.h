//Define some constants, maybe redefine in other subroutine, so please double check the units
// and comment out some reduplicated values.

//const Double_t Na=TMath::Na();           //Avogadro's Number
//const Double_t Qe=TMath::Qe();
const Double_t GeVToMeV = 1000.0; 
const Double_t MeVToGeV = 0.001;
const Double_t PION_MASS = 0.135;          //GeV Mass of Pion
const Double_t E_MASS = 0.510999*MeVToGeV; //Electron Mass
const Double_t P_MASS = 0.938272;          //Proton Mass
const Double_t N_MASS = 0.939565;          //Neutron Mass
const Double_t D_MASS = 1.8756;            //Deutrilium mass
const Double_t PM_SQ = P_MASS*P_MASS;      //:->
const Double_t NM_SQ = N_MASS*N_MASS;      //:->
const Double_t PI_SQ = PION_MASS*PION_MASS;//:->
const Double_t UToGeV = 0.931494028;       //Convert from atomic mass unit to GeV unit
const Double_t META = 0.547;
const Double_t HC_SQ = 0.3893857;          //mB/sR, Look like is different with MEV2SR_TO_NBARNSR, FIX_HERE
//const Double_t FM2TONBARN=1e-7;          //1 fm^2=1e7 nbarn
//const Double_t MEV2SR_TO_NBARNSR=HBARC*HBARC*FM2TONBARN; //default cross section 1/(MeV^2*sr) to nbarn/sr


static const double ALPHA=1/137.036; //fine-structure constant
static const double PI=3.14159265358979323846;
static const double AP=ALPHA/PI;
static const double ELECTRON_MASS=0.510998918; //MeV
static const double M2=ELECTRON_MASS*ELECTRON_MASS; //MeV
static const double AMU=931.494043; //MeV
static const double PROTON_MASS=938.272029; //MeV
static const double DELTA_MASS=1232.; //MeV
static const double PI_MASS=139.57; //MeV
static const double MU_P=2.7928456; //MeV/T proton magnetic momentum
static const double MU_N=-1.91304184; //MeV/T neutron magnetic momentum
static const double HBARC=197.326968; //hbar*c MeV fm
static const double MEV2SR_TO_NBARNSR=3.89379*1e11; //1/(MeV^2 sr)--->nbarn/sr
static const double K_P=1.7927; //anomalous magnetic moment of Proton, used for Proton MeV fm
static const double K_N=-1.91348; //anomalous magnetic moment of Netutron, used for Neutron MeV fm
static const double K_HE=-4.2; //anomalous magnetic moment of He3, used for He3 and He4 MeV fm


