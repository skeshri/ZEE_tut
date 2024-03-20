// -*- C++ -*-
//
// Package:    ZEE/ZEEAnlysis
// Class:      ZEEAnlysis
//
/**\class ZEEAnlysis ZEEAnlysis.cc ZEE/ZEEAnlysis/plugins/ZEEAnlysis.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sumit Keshri
//         Created:  Fri, 15 Mar 2024 07:41:56 GMT
//
//

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<>
// This will improve performance in multithreaded jobs.

using reco::TrackCollection;
using namespace std;
class ZEEAnlysis : public edm::one::EDAnalyzer<edm::one::SharedResources> {
public:
  explicit ZEEAnlysis(const edm::ParameterSet&);
  ~ZEEAnlysis() override;

  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void beginJob() override;
  void analyze(const edm::Event&, const edm::EventSetup&) override;
  void endJob() override;

  // ----------member data ---------------------------
  //const edm::EDGetTokenT<"c++ class DataType"> "variable name that you can choose";
  
  //typedef std::vector<pat::Electron> pat::ElectronCollection;

  //const edm::EDGetTokenT<vector<pat::Electron>> electronToken_;
  const edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  edm::ESGetToken<SetupData, SetupRecord> setupToken_;
#endif
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ZEEAnlysis::ZEEAnlysis(const edm::ParameterSet& iConfig)
        : electronToken_(consumes<pat::ElectronCollection >(iConfig.getParameter<edm::InputTag>("electron")))
        {
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  setupDataToken_ = esConsumes<SetupData, SetupRecord>();
#endif
  //now do what ever initialization is needed
}

ZEEAnlysis::~ZEEAnlysis() {
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  //
  // please remove this method altogether if it would be left empty
}

//
// member functions
//

// ------------ method called for each event  ------------
void ZEEAnlysis::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;

  //Handle<reco::MuonCollection> muons;
  //iEvent.getByToken(theMuonToken, muons);

  Handle<pat::ElectronCollection> electron;
  iEvent.getByToken(electronToken_,electron);


  cout<<"number of Electrons: "<<electron->size()<<endl;
  int count=0;
  for(auto const &iele: *electron)
  {
      count++;

      cout<<count<<" ,Energy:"<<iele.energy()<<" ,px:"<<iele.px()<<", py:"<<iele.py()<<" ,pz:"<<iele.pz()<<endl;
  }

  //for (const auto& track : iEvent.get(tracksToken_)) {
    // do something with track parameters, e.g, plot the charge.
    // int charge = track.charge();
  //}

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
  // if the SetupData is always needed
  auto setup = iSetup.getData(setupToken_);
  // if need the ESHandle to check if the SetupData was there or not
  auto pSetup = iSetup.getHandle(setupToken_);
#endif
}

// ------------ method called once each job just before starting event loop  ------------
void ZEEAnlysis::beginJob() {
  // please remove this method if not needed
}

// ------------ method called once each job just after ending the event loop  ------------
void ZEEAnlysis::endJob() {
  // please remove this method if not needed
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void ZEEAnlysis::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

  //Specify that only 'tracks' is allowed
  //To use, remove the default given above and uncomment below
  //ParameterSetDescription desc;
  //desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
  //descriptions.addWithDefaultLabel(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ZEEAnlysis);
