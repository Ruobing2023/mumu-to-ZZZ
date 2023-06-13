/*
This macro is used to produce the ntuple.root,
storing useful informations we need
//root -b -q ntuple_chain.C\(\"WW\"\)  
*/

//------------------------------------------------------------------------------

double deltaPhi(const double& phi1, const double& phi2)
{
        double deltaphi = fabs(phi1 - phi2);
        if (deltaphi > 3.141592654) deltaphi = 6.283185308 - deltaphi;
        return deltaphi;
}

double deltaEta(const double& eta1, const double& eta2)
{
        double deltaeta = fabs(eta1 - eta2);
        return deltaeta;
}

double deltaR(const double& eta1, const double& phi1,
                const double& eta2, const double& phi2)
{
        double deltaphi = deltaPhi(phi1, phi2);
        double deltaeta = deltaEta(eta1, eta2);
        double deltar = sqrt(deltaphi*deltaphi + deltaeta*deltaeta);
        return deltar;
}

//------------------------------------------------------------------------------

class ExRootResult;
class ExRootTreeReader;

//------------------------------------------------------------------------------

void AnalyseEvents(ExRootTreeReader *treeReader, TString filename)
{
  // create a root file to store the variables
  TFile file(filename, "recreate");
  TTree *tree = new TTree("tree", "keep events after cuts");
  double SF=1.0;
  if(filename.Contains("ZZZ-1TeV-llvl")==1) {SF= 1.026e-3/10000.;}
  if(filename.Contains("back1-llll")==1) {SF= 5.093/10000.;}
  if(filename.Contains("back2-wwz")==1) {SF= 7.067e-2/10000.;}
  if(filename.Contains("back3-mumuww")==1) {SF= 0.4023/10000.;}
  if(filename.Contains("back4-mumuzz")==1) {SF= 2.278e-3/10000.;}
  if(filename.Contains("back5-mumuwwz")==1) {SF= 7.993e-2/10000.;}
  
  
  int inputNum=0;
  int event;
  double M4l,deltaM,deltaM1234,deltaM1324,deltaM1423,Ptll1,Ptll2,Mll1,Mll2,Pt4l,E4l;
  double met,meta,mll,ptll,p1,p2,costheta,pt1,pt2,Mrecoil;//,etaMu1,etaMu2,phiMu1,phiMu2;
  int  numMu, numLep,numGen,numEl;
  double ptMu1[99],etaMu1[99],phiMu1[99],chargeMu1[99],ptMu2[99],etaMu2[99],phiMu2[99],chargeMu2[99],Emu1[99],Emu2[99],px[99],py[99],pz[99],E[99],ptEl1[99],etaEl1[99],phiEl1[99],chargeEl1[99],ptEl2[99],etaEl2[99],phiEl2[99],chargeEl2[99],Eel1[99],Eel2[99];
  double ptMu3[99],etaMu3[99],phiMu3[99],chargeMu3[99],ptMu4[99],etaMu4[99],phiMu4[99],chargeMu4[99],Emu3[99],Emu4[99],ptEl3[99],etaEl3[99],phiEl3[99],chargeEl3[99],ptEl4[99],etaEl4[99],phiEl4[99],chargeEl4[99],Eel3[99],Eel4[99];
 double Pt1,Pt2,Pt3,Pt4;
  tree->Branch("event", &event, "event/I");
  tree->Branch("SF", &SF, "SF/D");
  tree->Branch("numMu", &numMu, "numMu/I");
  tree->Branch("numEl", &numEl, "numEl/I");
  tree->Branch("numLep", &numLep, "numLep/I");
  tree->Branch("met",&met,"met/D");
  tree->Branch("meta",&meta,"meta/D");
  tree->Branch("chargeMu1",&chargeMu1,"chargeMu1/D");
  tree->Branch("chargeMu2",&chargeMu2,"chargeMu2/D");
  tree->Branch("chargeEl1",&chargeEl1,"chargeEl1/D");
  tree->Branch("chargeEl2",&chargeEl2,"chargeEl2/D");
  tree->Branch("ptMu1",&ptMu1,"ptMu1/D");
  tree->Branch("ptMu2",&ptMu2,"ptMu2/D");
  tree->Branch("ptEl1",&ptEl1,"ptEl1/D");
  tree->Branch("ptEl2",&ptEl2,"ptEl2/D");
  tree->Branch("etaMu1",&etaMu1,"etaMu1/D");
  tree->Branch("etaMu2",&etaMu2,"etaMu2/D");
  tree->Branch("etaEl1",&etaEl1,"etaEl1/D");
  tree->Branch("etaEl2",&etaEl2,"etaEl2/D");
  tree->Branch("phiMu1",&phiMu1,"phiMu1/D");
  tree->Branch("phiMu2",&phiMu2,"phiMu2/D"); 
  tree->Branch("phiEl1",&phiEl1,"phiEl1/D");
  tree->Branch("phiEl2",&phiEl2,"phiEl2/D");
  tree->Branch("Pt4l",&Pt4l,"Pt4l/D");
  tree->Branch("M4l",&M4l,"M4l/D");
  tree->Branch("Mrecoil",&Mrecoil,"Mrecoil/D");
  tree->Branch("deltaM1423",&deltaM1423,"deltaM1423/D");
  tree->Branch("deltaM1234",&deltaM1234,"deltaM1234/D");
  tree->Branch("deltaM",&deltaM,"deltaM/D");
  tree->Branch("Ptll1",&Ptll1,"Ptll1/D");
  tree->Branch("Ptll2",&Ptll2,"Ptll2/D");
  tree->Branch("Mll1",&Mll1,"Mll1/D");
  tree->Branch("Mll2",&Mll2,"Mll2/D");

  
  TClonesArray *branchEvent = treeReader->UseBranch("Event");
  TClonesArray *branchGenParticle = treeReader->UseBranch("Particle");
  TClonesArray *branchElectron = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon = treeReader->UseBranch("Muon");
  TClonesArray *branchMET = treeReader->UseBranch("MissingET");

  Long64_t numberOfEntries = treeReader->GetEntries();
  inputNum = numberOfEntries;
  cout << "** Chain contains " << numberOfEntries << " events" << endl;

  for(int count=0; count < numberOfEntries; count++) {
      //initiate branch members
 
     event=-1; met=-99.0;meta=-99.; mll=-99.0; ptll=-99.0;  numMu=-1;numEl=-1; costheta=-99;
     p1=-99;p2=-99;pt1=-99.;pt2=-99.;//etaMu1=-99.;etaMu2=-99.;phiMu1=-99.;phiMu2=-99.;//pxMu_gen=-99.0;pyMu_gen=-99.0;pzMu_gen=-99.0;
     numGen=-1;numLep=-1;M4l=-99.;deltaM=-99.;deltaM1234=-99.;deltaM1324=-99.;deltaM1423=-99.;Pt4l=-99.;Ptll1=-99.;Ptll2=-99.;Mll1=-99.;Mll2=-99.;
    Mrecoil=-99.;Pt1=-99.;Pt2=-99.;Pt3=-99.;Pt4=-99.;E4l=-99.;
     //********************************************************************
   for(int i=0; i<99; i++)
      {
       
                ptMu1[i]=-99;etaMu1[i]=-99;phiMu1[i]=-99;chargeMu1[i]=-99;Emu1[i]=-99;Eel1[i]=-99;
	        ptMu2[i]=-99;etaMu2[i]=-99;phiMu2[i]=-99;chargeMu2[i]=-99;Emu2[i]=-99;Eel2[i]=-99;
	       	ptEl1[i]=-99;etaEl1[i]=-99;phiEl1[i]=-99;chargeEl1[i]=-99;
                ptEl2[i]=-99;etaEl2[i]=-99;phiEl2[i]=-99;chargeEl2[i]=-99;
	        px[i]=-99;py[i]=-99;pz[i]=-99;E[i]=-99;
	        ptMu3[i]=-99;etaMu3[i]=-99;phiMu3[i]=-99;chargeMu3[i]=-99;Emu3[i]=-99;Eel3[i]=-99;
                ptMu4[i]=-99;etaMu4[i]=-99;phiMu4[i]=-99;chargeMu4[i]=-99;Emu4[i]=-99;Eel4[i]=-99;
                ptEl3[i]=-99;etaEl3[i]=-99;phiEl3[i]=-99;chargeEl3[i]=-99;
                ptEl4[i]=-99;etaEl4[i]=-99;phiEl4[i]=-99;chargeEl4[i]=-99;
      }

      treeReader->ReadEntry(count) ;
      //********************************************************************


      Event* ev = (Event*)branchEvent->At(0);
      event=ev->Number;
    
      MissingET* Met = (MissingET *) branchMET->At(0);
      met=Met->MET;
      meta=Met->Eta;
      numMu=branchMuon->GetEntries();
      numGen=branchGenParticle->GetEntries();
      numEl=branchElectron->GetEntries();
      numLep=numEl+numMu;
      if((numEl+numMu)!=4)continue;
      if(numEl==3&&numMu==1)continue;
      if(numEl==1&&numMu==3)continue;
     double Mz = 91.0 ;
        Muon* M[99];
        Electron*El[99];
     int mark2=0;
     int mark3=0;
     int mark4=0;
     double MMass=0.10500;
     double MMass2=0.10500/207;
  TLorentzVector l1,l2,l3,l4;
     if(numMu==2&&numEl==2){
   for(int j=0; j<2; j++){
  M[j]=(Muon*)branchMuon->At(j);
  El[j]=(Electron*)branchElectron->At(j);
   chargeMu1[mark2]=M[j]->Charge;      
   ptMu1[mark2]=M[j]->PT;
   etaMu1[mark2]=M[j]->Eta;
   phiMu1[mark2]=M[j]->Phi;
   chargeEl1[mark2]=El[j]->Charge;
   ptEl1[mark2]=El[j]->PT;
   etaEl1[mark2]=El[j]->Eta;
   phiEl1[mark2]=El[j]->Phi;
  mark2++;
   }

if(((chargeMu1[0]+chargeMu1[1])!=0) || ((chargeEl1[0]+chargeEl1[1])!=0)) continue;
if(chargeMu1[0]==1 && chargeMu1[1]==-1){
	if(chargeEl1[0]==1 && chargeEl1[1]==-1){
		l1.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);
		l2.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);   
		l3.SetPtEtaPhiM(ptEl1[0],etaEl1[0],phiEl1[0],MMass2);  
		l4.SetPtEtaPhiM(ptEl1[1],etaEl1[1],phiEl1[1],MMass2);
	}
	if(chargeEl1[0]==-1 && chargeEl1[1]==1){
		l1.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);
		l2.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);   
		l3.SetPtEtaPhiM(ptEl1[1],etaEl1[1],phiEl1[1],MMass2);  
		l4.SetPtEtaPhiM(ptEl1[0],etaEl1[0],phiEl1[0],MMass2);
	}
}
       if(chargeMu1[0]==-1 && chargeMu1[1]==1){
	if(chargeEl1[0]==1 && chargeEl1[1]==-1){
		l1.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);
		l2.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);   
		l3.SetPtEtaPhiM(ptEl1[0],etaEl1[0],phiEl1[0],MMass2);  
		l4.SetPtEtaPhiM(ptEl1[1],etaEl1[1],phiEl1[1],MMass2);
	}
	if(chargeEl1[0]==-1 && chargeEl1[1]==1){
		l1.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);
		l2.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);   
		l3.SetPtEtaPhiM(ptEl1[1],etaEl1[1],phiEl1[1],MMass2);  
		l4.SetPtEtaPhiM(ptEl1[0],etaEl1[0],phiEl1[0],MMass2);
	}
}
//-------------------------
   Pt4l=(l1+l2+l3+l4).Pt();
   M4l=(l1+l2+l3+l4).M();
   Mrecoil=sqrt(pow(1000.-(l1+l2+l3+l4).E(),2)-pow((l1+l2+l3+l4).Pt(),2)-pow((l1+l2+l3+l4).Pz(),2));
   deltaM1234=pow(((l1+l2).M()-Mz),2)+pow(((l3+l4).M()-Mz),2); //注释：z只能衰变到同种味道的正负轻子对，对于numMu==2&&numEl==2的情况只有一种组合。
   deltaM=deltaM1234;
   Mll1=(l1+l2).M();
   Ptll1=(l1+l2).Pt();
   Mll2=(l3+l4).M();
   Ptll2=(l3+l4).Pt();
   }
  if(numMu==4&&numEl==0){
   for(int j1=0; j1<numLep; j1++){
  M[j1]=(Muon*)branchMuon->At(j1);
  El[j1]=(Electron*)branchElectron->At(j1);
   chargeMu2[mark2]=M[j1]->Charge;      
   ptMu2[mark2]=M[j1]->PT;
   etaMu2[mark2]=M[j1]->Eta;
   phiMu2[mark2]=M[j1]->Phi;   
   mark2++;
   }
 
if((chargeMu1[0]+chargeMu1[1]+chargeMu1[2]+chargeMu1[3])!=0) continue;
if(chargeMu1[0]==1 && chargeMu1[1]==-1){
	if(chargeMu1[2]==1 && chargeMu1[3]==-1){
		l1.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);
		l2.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);   
		l3.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
		l4.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
	}
	if(chargeEl1[2]==-1 && chargeEl1[3]==1){
		l1.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);
		l2.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);   
		l3.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
		l4.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
	}
}
        if(chargeMu1[0]==-1 && chargeMu1[1]==1){
	if(chargeMu1[2]==1 && chargeMu1[3]==-1){
		l1.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);
		l2.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);   
		l3.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
		l4.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
	}
	if(chargeEl1[2]==-1 && chargeEl1[3]==1){
		l1.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);
		l2.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);   
		l3.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
		l4.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
	}
}
//-------------------------
   Pt4l=(l1+l2+l3+l4).Pt();
   M4l=(l1+l2+l3+l4).M();
   Mrecoil=sqrt(pow(1000.-(l1+l2+l3+l4).E(),2)-pow((l1+l2+l3+l4).Pt(),2)-pow((l1+l2+l3+l4).Pz(),2));
   
    deltaM1234=pow(((l1+l2).M()-Mz),2)+pow(((l3+l4).M()-Mz),2);
   deltaM1423=pow(((l1+l4).M()-Mz),2)+pow(((l2+l3).M()-Mz),2);
   if(deltaM1234>deltaM1423){
   deltaM=deltaM1423;
   Mll1=(l1+l4).M();
   Ptll1=(l1+l4).Pt();
   Mll2=(l2+l3).M();
   Ptll2=(l2+l3).Pt();
   }
   else{
    deltaM=deltaM1234;
   Mll1=(l1+l2).M();
   Ptll1=(l1+l2).Pt();
   Mll2=(l3+l4).M();
   Ptll2=(l3+l4).Pt();
   }
  }
   if(numEl==4&&numMu==0){
  for(int j2=0; j2<numLep; j2++){
  M[j2]=(Muon*)branchMuon->At(j2);
  El[j2]=(Electron*)branchElectron->At(j2); 
  chargeEl2[mark2]=El[j2]->Charge;      
   ptEl2[mark2]=El[j2]->PT;
   etaEl2[mark2]=El[j2]->Eta;
   phiEl2[mark2]=El[j2]->Phi;
   mark2++;
  }
if((chargeEl1[0]+chargeEl1[1]+chargeEl1[2]+chargeEl1[3])!=0) continue;
if(chargeEl1[0]==1 && chargeEl1[1]==-1){
	if(chargeEl1[2]==1 && chargeEl1[3]==-1){
		l1.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);
		l2.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);   
		l3.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
		l4.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
	}
	if(chargeEl1[2]==-1 && chargeEl1[3]==1){
		l1.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);
		l2.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);   
		l3.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
		l4.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
	}
}
if(chargeEl1[0]==-1 && chargeEl1[1]==1){
	if(chargeEl1[2]==1 && chargeEl1[3]==-1){
		l1.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);
		l2.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);   
		l3.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
		l4.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
	}
	if(chargeEl1[2]==-1 && chargeEl1[3]==1){
		l1.SetPtEtaPhiM(ptMu1[1],etaMu1[1],phiMu1[1],MMass);
		l2.SetPtEtaPhiM(ptMu1[0],etaMu1[0],phiMu1[0],MMass);   
		l3.SetPtEtaPhiM(ptMu2[3],etaMu2[3],phiMu2[3],MMass);
		l4.SetPtEtaPhiM(ptMu2[2],etaMu2[2],phiMu2[2],MMass);
	}
}
//-------------------------
   Pt4l=(l1+l2+l3+l4).Pt();
   M4l=(l1+l2+l3+l4).M();
   Mrecoil=sqrt(pow(1000.-(l1+l2+l3+l4).E(),2)-pow((l1+l2+l3+l4).Pt(),2)-pow((l1+l2+l3+l4).Pz(),2));

    deltaM1234=pow(((l1+l2).M()-Mz),2)+pow(((l3+l4).M()-Mz),2);
   deltaM1423=pow(((l1+l4).M()-Mz),2)+pow(((l2+l3).M()-Mz),2);
   if(deltaM1234>deltaM1423){
   deltaM=deltaM1423;
   Mll1=(l1+l4).M();
   Ptll1=(l1+l4).Pt();
   Mll2=(l2+l3).M();
   Ptll2=(l2+l3).Pt();
   }
   else{
    deltaM=deltaM1234;
   Mll1=(l1+l2).M();
   Ptll1=(l1+l2).Pt();
   Mll2=(l3+l4).M();
   Ptll2=(l3+l4).Pt();
   }
}

 //////////////////////////////////////////////////////////////////////////////
 tree->Fill();
   // end of chain loop
  //tree->Print();
}
  file.Write();
}


//------------------------------------------------------------------------------

void ntuple_chain(char* filename)
{
  gSystem->Load("/mnt/c/Users/Administrator/Desktop/MadGraph/MG5_aMC_v3_4_0/Delphes/libDelphes");
  //THStack *stack;
  TChain *chain = new TChain("Delphes");

  TString buffer = filename;
  cout<<buffer<<endl;
  TString IFile =  buffer + ".root";
  TString OFile =  "ntuple_" + buffer+".root";

  chain->Add(IFile);
  ExRootTreeReader *treeReader1 = new ExRootTreeReader(chain);
  ExRootResult *result1 = new ExRootResult();
  AnalyseEvents(treeReader1, OFile);

  cout << "** Exiting..." << endl;

  delete result1;
  delete treeReader1;
  delete chain;
}

//------------------------------------------------------------------------------
