
{
        vector<TString> files;
        files.push_back("ZZZ-1TeV-llvl");
        files.push_back("back1-llll");
        files.push_back("back2-wwz");
        files.push_back("back3-mumuww");
        files.push_back("back4-mumuzz");
        files.push_back("back5-mumuwwz");

        const int nfiles = files.size();
        cout<<"file size "<<nfiles<<endl;
  for(int i=0;i<nfiles;i++){
  TString IFile =  "ntuple_" + files.at(i)+".root";
  TFile *ifile = new TFile(IFile);
  TTree *tree = (TTree*)ifile->Get("tree");

 //       int nentries1 = (int)tree1->GetEntries();
        int nentries1 = tree->GetEntries();
        double SF,Mll1,Mll2,Ptll1,Ptll2,Pt4l,M4l,met,Mrecoil;
        cout<<"Sample = "<<files.at(i)<<" "<<"nentries1 = "<<nentries1<<endl;
         tree->SetBranchAddress("Mll1",&Mll1);
 	 tree->SetBranchAddress("Mll2", &Mll2);
	 tree->SetBranchAddress("Ptll1", &Ptll1);
 	 tree->SetBranchAddress("Ptll2", &Ptll2);
	 tree->SetBranchAddress("Pt4l", &Pt4l);
	 tree->SetBranchAddress("M4l", &M4l);
	 tree->SetBranchAddress("SF",&SF);
	 tree->SetBranchAddress("met",&met);
	 tree->SetBranchAddress("Mrecoil",&Mrecoil);
        double invmll, weight;
       
	TString OFile =  "cut2"+files.at(i)+".root";
	TFile  *ofile=new TFile(OFile, "recreate");
  	TTree *otree = new TTree(files.at(i),"keep events after cut1");        
	otree->Branch("Mll1",&Mll1,"Mll1/D");
        otree->Branch("Mll2",&Mll2,"Mll2/D");
	otree->Branch("Ptll1",&Ptll1,"Ptll1/D");
	otree->Branch("Ptll2",&Ptll2,"Ptll2/D");
        otree->Branch("Pt4l",&Pt4l,"Pt4l/D");
	otree->Branch("M4l",&M4l,"M4l/D");
      	otree->Branch("met",&met,"met/D");
	otree->Branch("SF",&SF,"SF/D");

         for(int j=0; j<nentries1; j++)
        {
         tree->GetEntry(j);
       if(met<30.||met>500.)continue;
       if(Mrecoil<40.||Mrecoil>250.)continue;
       if(Mll1<60.||Mll1>120.)continue;
      // if(Ptll1>450.)continue;
     //  if(Pt4l<30.||Pt4l>500.)continue;
       if(M4l<200.||M4l>900.)continue;
       if(Mll2<25.||Mll2>110.)continue;
      // if(Ptll2>470.)continue;
      
      // sum = SF*lumi;

       otree->Fill();
	}
       ofile->Write();
  }

  }
  
// TString  OFile = "j1.root";

 


