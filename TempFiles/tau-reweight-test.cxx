/**
 * @author T. Przedzinski
 * @date 7 Jul 2011 22:30 pm
 */

// To run with MC-TESTER, uncomment this line or at compilation step add flag:
// -D_USE_MCTESTER_
//#define _USE_MCTESTER_

// When running with MC-TESTER, to use MC-TESTER for spin validation only,
// uncomment this line or at compilation step add flag:
// -D_SPIN_VALIDATION_ONLY_
//#define _SPIN_VALIDATION_ONLY_

#ifdef _USE_MCTESTER_

// MC-TESTER headers
#include "Generate.h"
#include "HepMCEvent.H"
#include "Setup.H"

#endif


// HepMC IO_GenEvent header
#include "HepMC/IO_GenEvent.h"

// TAUOLA header
#include "Tauola/Tauola.h"

#include "TauSpinner/Particle.h"
#include "TauSpinner/SimpleParticle.h"
#include "TauSpinner/tau_reweight_lib.h"
#include "TauSpinner/nonSM.h"
#include "TauSpinner/EWtables.h"

#include "read_particles_from_TAUOLA.h"

// LHAPDF header
#include "LHAPDF/LHAPDF.h"
using namespace std;
using namespace Tauolapp;
using namespace TauSpinner;

/*
 We are using routine from 'distr.f' as an example of
 function for user-defined born calculation.
 We need to adjust conventions for signs etc.
 In our example: we  adapt convention for flavour of incoming quark
 and signs of spin states -- from helicity.
*/
double nonSM_adopt(int ID, double S, double cost, int H1, int H2, int key)
// extern "C" double distjkwk_(int*, double*, double*, int*, int*, int*);
{
  int ID2=3-ID;
  // for distjkwk_ conventions
  if(ID2<1) ID2=ID2+2;  // Since Feb 2016  we allow ID in range [1,5]
  if(ID2<1) ID2=ID2+2;
  int HH1= H1;   // to be fixed a bit later.
  int HH2=-H2;
  //  an example of use:
  //  return distjkwk_(&ID2, &S, &cost, &HH1, &HH2, &key);
  //  }
 
      cout<<"             this function is dummy\n"<<endl;
      cout<<"             user must provide his own nonSM_born"<<endl;
      cout<<"             that is nonSM_adopt()"<<endl;
      exit(-1);
      return 1.0;
}


/*
   EW born can be initialized with the options  passed  through the
   dummy call on sigbornswdelt() the function which is used here 
   as void, but its returned value is used for graphics in Dizet-example.
*/
void EWreInit(int variant){
       int mode=0;
       int FLAV=2;
       double GAM=Gamz(FLAV);
       double AMZ00=91.18870000000;//91.1876;//91.18870000; //91.1876
       AMZ00=Amz(FLAV);
       double SWeff=0.2315200;// 0.2235200000;//0.2315200; //0.2235200000;// 0.2121517; //0.22352;// 0.22351946; //0.231708; //.231; 
       double DeltSQ=0.;
       double DeltV=0.;
       double Gmu=0.00001166389;// 0.00001166378; //1.16639e-5;
       double alfinv=137.0359895;
       int keyGSW=1; //3; //4; //5;

       int ID=1;// dummy
       double s=(AMZ00)*(AMZ00);// dummy
       double si;// dummy
       double   cc=0.5;// dummy
       if(variant==2){ // modifications for nonSM Born initialization of second calculation
	 setNonSMkey(1);
	 mode=0;
	 keyGSW=2;//0;//10;
	 AMZ00=91.18870000000; GAM=2.4952; SWeff=0.2315200;
	 alfinv=128.86674175; // to reproduce t_born 
       }
       si=sigbornswdelt(mode,ID, s, cc, SWeff, DeltSQ, DeltV, Gmu, alfinv, AMZ00,GAM,keyGSW);
}

/*
   Introduce variation for effective loop corrected Born of Dizet library.
   Some formfactors may be switched off or anomalous couplings added.
*/
void EWanomInit(){

   int FLAV=2;
   double AMZ00=Amz(FLAV);

   double SWeff=0.2235200000;//0.2315200;// 0.2235200000;// 0.2121517; //0.22352;// 0.22351946; //0.231708; //.231; // dummy
   double DeltSQ=0.;
   double DeltV=0.;
   double Gmu=0.00001166389;// 0.00001166378; //1.16639e-5;
   double alfinv=137.0359895;// dummy
   int keyGSW=1;// 2;
   double AMZi=91.18870000;
   double GAM=2.49520000;


   cout <<" "<< endl;
   cout <<" Initialization for anomalus couplings of Dizet Born with electroweak loops"<< endl;
   cout <<" "<< endl;
   
   cout << "   SWeff   =  "<<SWeff;
   cout << ",  DeltSQ  =  "<<DeltSQ;
   cout << ",  DeltV   =  "<< DeltV;
   cout <<" "<< endl;
   cout << "   Gmu     =  "<<Gmu;
   cout << ",  alfinv  =  "<<alfinv;
   cout <<" "<< endl;
   cout << "   AMZi    =  "<<AMZi;
   cout << ",  GAM     =  "<<GAM;
   cout <<" "<< endl << endl;
   cout << " Level of formfactors implementation:"<< endl<< endl;
   cout << "   keyGSW  =  "<<keyGSW<< endl;
   cout <<" "<< endl;
 
   ExtraEWparamsSet(AMZi, GAM, SWeff, alfinv,DeltSQ, DeltV, Gmu,keyGSW);

}

/*
 We are using routine from 'ggHXtautau.f' as an example of
 function for user-defined Higgs born calculation.
 We need to adjust conventions for signs etc.
 In our example: we adapt convention for signs of spin states -- from helicity.
*/
// extern "C" double disthjkwk_(double*, double*, int*, int*, int*);

double nonSM_adoptH(int ID, double S, double cost, int H1, int H2, int key)
{
  int HH1= H1;
  int HH2=-H1; // appropriate for X2 of spin 2
  
  if(key==0) HH2 = H1; // appropriate for Higgs
  
  //  an example of use:
  //  return disthjkwk_(&S, &cost, &HH1, &HH2, &key);
  //  }
 
      cout<<"             this function is dummy\n"<<endl;
      cout<<"             user must provide his own nonSM_bornH"<<endl;
      cout<<"             that is nonSM_adoptH()"<<endl;
      exit(-1);
      return 1.0;
}

// This is an example of the program reweighting unpolarized tau events.
int main(int argc, char **argv) {

  char *input_filename = "events.dat";
  
  if(argc<2)
  {
    cout<<endl<<"Processing all available events from default input file: "<<input_filename<<endl;
    cout<<      "You can change this option by using:   "<<argv[0]<<" <filename> [<events_limit>]"<<endl<<endl;
  }
  else input_filename = argv[1];

  //---------------------------------------------------------------------------
  //- Initialization ----------------------------------------------------------
  //---------------------------------------------------------------------------

  // Limit number of processed events
  int events_limit = 0;
  
  if(argc>2) events_limit = atoi(argv[2]);
  


  // Initialize Tauola
  Tauola::initialize();

  string name="MSTW2008nnlo90cl.LHgrid";
  LHAPDF::initPDFSetByName(name);

  
  double CMSENE = 7000.0; // center of mass system energy.
                          // used in PDF calculation. For pp collisions only
  bool Ipp = true;  // for pp collisions
  //bool Ipp = false; // otherwise (not prepared yet)

  int Ipol = 1; // are input samples polarized?

  int nonSM2 = 1; // are we using nonSM calculations?
                  // at present we have checked only that for nonSM2 = 0
                  // all works as in the past. nonSM2 = 1 default is for 
                  // claculation with electroweak corrections from KKMC library. 
                  // More tests are needed  for this option.
  int nonSMN = 0; // If we are using nonSM calculations we may want corrections 
                  // to shapes only: y/n  (1/0)
  int IFset=0;    // status variable whether user provided nonSM Born was set  
  int IFsetH=0;   // status variable whether user provided nonSM Born was set for Higgs channel

 //#############
  // optional initialization for Dizet electroweak tables
  char* mumu="Dizet-example/table.mu";
  char* downdown= "Dizet-example/table.down";
  char* upup= "Dizet-example/table.up";
  int initResult=initTables(mumu,downdown,upup);
  EWanomInit();
  //#############
 
  
  // Initialize TauSpinner
  initialize_spinner(Ipp, Ipol, nonSM2, nonSMN,  CMSENE);
  
  /*
     Set function for user-defined  born, including new physics
     This function must be of format:

     double fun(int ID, double S, double cost, int H1, int H2, int key)

     Where: ID    -- 1 for down-type qqbar, 2 for up-type qqbar
            S     -- cm qqbar energy^2
            cost  -- cosTheta (scattering angle of tau- with respect to quark)
            H1,H2 -- spin state of first, second tau 
            key   -- 1 when new effect is added, 0  Standard Model

     If set to NULL, default function will be used.

     Here, as an example, we are using FUNCTION DISTR from file 'distr.f'
     file. Wrapper/adopter nonSM_adopt (adjustments for conventions of some input variables)  
     is defined earlier in our example.
  */

  //  set nonSM borns to user provided function, leave a track if it was done
  // IFset=set_nonSM_born( nonSM_adopt );
  // IFsetH=set_nonSM_bornH( nonSM_adoptH );
  
  // next line is needed for CP-test  CP-bench-pi
  // FOR SCALAR H USE:
  //setHiggsParametersTR(-1.0, 1.0, 0.0, 0.0);
  // FOR PSEUDOSCALAR A USE:
  //  setHiggsParametersTR( 1.0,-1.0, 0.0, 0.0);
  // for mixed parity case
  // double theta=0.2;
  // setHiggsParametersTR(-cos(2*theta),cos(2*theta) ,-sin(2*theta),-sin(2*theta));

  // Next line is needed for CP-test-Z-pi, CP-test-Z-rho
  // Switch components of transverse density matrix for DY
  //                  (Rxx,Ryy,Rxy,Ryx)
  //setZgamMultipliersTR(1., 1., 1., 1. );

  // For use of electroweak corrections KKMC style
  // default_nonSM_bornZ  must be  used for
  // default_nonSM_bornH this is of no concern. IN any case
  // user nonSM_born has a priority
   IFset=set_nonSM_born( NULL );
   IFsetH=set_nonSM_bornH( NULL );

  // Initialize EW tables and electroweak effective Born if it is requested
  if (nonSM2 ==1&& IFset==0){
   if (initResult == 1)cout << "EW tables initialized from: " << mumu << " " << downdown << " " << upup << endl;
   if (initResult != 1){
      cout << "Error initializing tables from files " << mumu << " " << downdown << " " << upup << endl;
      return -1;
   }
  }
  
  // Open I/O files  (in our example events are taken from "events.dat")
  HepMC::IO_GenEvent input_file(input_filename,std::ios::in);

#ifdef _USE_MCTESTER_
  // Initialize MC-Tester
  MC_Initialize();
#endif

  int    events_count = 0;
  double wt_average   = 0.0;
  double wt_average_nonSM   = 0.0;
  double wtnonSM =1.0;
  
  //---------------------------------------------------------------------------
  //- Event loop --------------------------------------------------------------
  //---------------------------------------------------------------------------
  while(true) {
    double WT1    = 1.0, WT2    = 1.0;  // we assume that there may be be at most two bosons decaying into
    int    pdgid1 = 0,   pdgid2 = 0;    // taus (tau neutrinos) and requiring reweight

    SimpleParticle X, tau, tau2;      // SimpleParticle consist of 4 momentum and PDGid.
    vector<SimpleParticle> tau_daughters, tau_daughters2;

    // Here, we read another event from input_file.
    
    // In this example, we use event generated by Pythia8 with tau decays from
    // Pythia8 or Tauola++.

    // NOTE: for W+/- or H+/- tau2 contain neutrino and tau_daughters2 is empty
    // User may introduce his own method of initializing X, tau, tau2, tau_daughters, tau_daughters2.
    // Then it may be convenient to follow format of the
    // 'readParticlesFromTAUOLA_HepMC' example line below
    int status = readParticlesFromTAUOLA_HepMC(input_file, X, tau, tau2, tau_daughters, tau_daughters2);

    // Go to next one if there is nothing more to do with this event
    if( status==1 ) continue;
    
    // Finish if there is nothing more to read from the file
    if( status==0 ) break;
    
    pdgid1 = X.pdgid();

    // Sets polarization state of the input sample
    //setSpinOfSample(0);
        
    // Calculate weight for first boson
    if( abs(X.pdgid())==24 ||  abs(X.pdgid())==37 )
    {
      WT1 = calculateWeightFromParticlesWorHpn(X, tau, tau2, tau_daughters); // note that tau2 is tau neutrino
    }
    else if(  nonSM2 && (X.pdgid()==25 || X.pdgid()==36 || X.pdgid()==22 || X.pdgid()==23 ))
    { 
      // nonSM2=1 !!  Special case for reweighting with user defined contribution to Born: can be Z', spin 2 state etc.
      //              WT1 is calculate   for gamma/Z sample with spin effects  included.

      // basic initialization of nonSM Born
       setNonSMkey(0);
       //       EWreInit(1);

      WT1 = calculateWeightFromParticlesH(X, tau, tau2, tau_daughters,tau_daughters2);  // SM spin weight
      // Returns spin of the taus attributed stochastically by calculateWeightFromParticlesH() -- SM case
      //double polSM = getTauSpin();
      wtnonSM = getWtNonSM();
       setNonSMkey(1);
       EWreInit(2);
      WT1 = calculateWeightFromParticlesH(X, tau, tau2, tau_daughters,tau_daughters2)/WT1; // (SM+NP spin wt)/(SM spin wt)

      // Returns spin of the taus attributed anew  by calculateWeightFromParticlesH() -- nonSM case
      //double polnonSM = getTauSpin();

      wtnonSM = getWtNonSM()/wtnonSM;
      double eni=sqrt((tau.e()+tau2.e())*(tau.e()+tau2.e())
		     -(tau.px()+tau2.px())*(tau.px()+tau2.px())
		     -(tau.py()+tau2.py())*(tau.py()+tau2.py())
		     -(tau.pz()+tau2.pz())*(tau.pz()+tau2.pz()) );
      printf(" Event No:%5i Inv mass=%13.6f ",events_count+1,eni);
      // alfinv=137.0359895;
      // wtnonSM*alfinv*alfinv; //  needed for normalization matching of Tauola born and nonSM born 
      printf("  WT(nonSM/SM):%13.10f  spinWT1 = %13.10f\n",wtnonSM,WT1);
      WT1 = WT1*wtnonSM; // normalization weight taken in.
      // 
    }
    else if( X.pdgid()==25 || X.pdgid()==36 || X.pdgid()==22 || X.pdgid()==23 )
    {
      // NOTE: if any component of transverse density matrix for DY has been turned on
      //       using setZgamMultipliersTR, weight WT will contain transverse part
      //       of the spin amplitude (calculated from tables table1-1.txt table2-2.txt
      //       which must be stored in the same directory as the program)

      WT1 = calculateWeightFromParticlesH(X, tau, tau2, tau_daughters,tau_daughters2);
    }
    else
    {
      cout<<"WARNING: Unexpected PDG for tau mother: "<<X.pdgid()<<endl;
    }
    
    // Returns spin of the taus attributed during reweighting
    //double pol = getTauSpin();
    
    //--------------------------------------------------------------------------
    // If event was not finished processing, then status = 2.
    // In this case, check if there is a second boson
    // decaying into tau in the event
    //--------------------------------------------------------------------------
    if( status==2 )
    {
      int status2 = readParticlesFromTAUOLA_HepMC(input_file, X, tau, tau2, tau_daughters, tau_daughters2);

      if( status2==2 )
      {
        pdgid2 = X.pdgid();

        // Calculate second weight
        if( abs(X.pdgid())==24 ||  abs(X.pdgid())==37 )
        {
          WT2 = calculateWeightFromParticlesWorHpn(X, tau, tau2, tau_daughters); // note that tau2 is tau neutrino
        }
        else if( X.pdgid()==25 || X.pdgid()==36 || X.pdgid()==22 || X.pdgid()==23 )
        {
          WT2 = calculateWeightFromParticlesH(X, tau, tau2, tau_daughters,tau_daughters2);
        }
        else
        {
          cout<<"WARNING: Unexpected PDG for tau mother: "<<X.pdgid()<<endl;
        }
        
      } // if( status2==2 )
    } // if( status==2 )
    
    // At this step we have two weights: WT1 and WT2.
    // If there was no 2nd boson decaying to taus, WT2 = 1.0
    
    // Options:
    // WT=1.0/WT      // to unspin sample having spin
    // WT=(2-WT)/(WT) // to flip spin correlations between (H+- <-->  W+-)
    // WT=(2-WT)/(WT) // to flip spin correlations between (H <-->  Z/gamma)
    //                   (this simple trick is valid with no Z couplings taken)
    //                   for Z calculation of weight for Higgs has to be done
    //                   directly
    // WARNING: these new WT will not be limited from above!

    wt_average += WT1;
    wt_average_nonSM +=wtnonSM;
    events_count++;
    // Run MC-TESTER on the event
    // Use WT to check if spin is properly installed (unweight events).
#ifdef _USE_MCTESTER_

    double WT = 1.0;
    
    // Check pdgid. If pdgid1 or pdgid2 matches particle we're studying
    // with MC-TESTER, then WT = WT1 or WT2 respectively
    if(pdgid1==Setup::decay_particle) WT = WT1;
    if(pdgid2==Setup::decay_particle) WT = WT2;

#ifdef _SPIN_VALIDATION_ONLY_
    WT=100; // ignore weight for validation of spin content of the production
#endif

    // For MC-TESTER analysis we use event defined in TauSpinner/src/readParticlesFromTAUOLA_HepMC
    HepMC::GenEvent *mc_tester_event = readParticlesFromTAUOLA_HepMC_getEvent();
    HepMCEvent *temp_event = new HepMCEvent(*mc_tester_event,false);

    // next two lines are needed for CP-test  CP-bench-pi
    //    Setup::UTA_nparams   = 1;
    //    Setup::UTA_params[0] = WT;

    MC_Analyze(temp_event,WT);

    // Cleanup
    delete temp_event;
#endif

    if(events_count%10000==0) cout<<"EVT: "<<events_count<<endl;
    if(events_limit && events_count>=events_limit) break;
  }

#ifdef _USE_MCTESTER_
  MC_Finalize();
#endif

  cout<<endl<<"No of events processed for spin weight: "<<events_count<<endl;
  cout<<      "WT average for these events:            "<<wt_average/events_count<<endl;
  cout<<      "WTnonSM average for these events:       "<<wt_average_nonSM/events_count<<endl;
}
