// -*- C++ -*-
//
// Package:    QWV1Cumu
// Class:      QWV1Cumu
// 
/**\class QWV1Cumu QWV1Cumu.cc QWAna/QWV1Cumu/src/QWV1Cumu.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
*/
//
// Original Author:  Quan Wang
//         Created:  03/09/2018
//


// system include files
#include <memory>
#include <algorithm>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include "TComplex.h"
#include <complex>


#include "QWAna/QWV1Cumu/interface/QWV1Cumu.h"


using namespace std;

//#ifdef QW_DEBUG
//
// constructors and destructor
//
QWV1Cumu::QWV1Cumu(const edm::ParameterSet& iConfig):
	trackEta_( iConfig.getUntrackedParameter<edm::InputTag>("trackEta") ),
	trackPhi_( iConfig.getUntrackedParameter<edm::InputTag>("trackPhi") ),
	trackPt_( iConfig.getUntrackedParameter<edm::InputTag>("trackPt") ),
	trackWeight_( iConfig.getUntrackedParameter<edm::InputTag>("trackWeight") ),
	vertexZ_( iConfig.getUntrackedParameter<edm::InputTag>("vertexZ") ),
	centralityTag_( iConfig.getUntrackedParameter<edm::InputTag>("centrality") )
{
	//now do what ever initialization is needed
	minvz_ = iConfig.getUntrackedParameter<double>("minvz", -15.);
	maxvz_ = iConfig.getUntrackedParameter<double>("maxvz", 15.);

//	rfpmineta_ = iConfig.getUntrackedParameter<double>("rfpmineta", -2.4);
//	rfpmaxeta_ = iConfig.getUntrackedParameter<double>("rfpmaxeta", 2.4);
//	rfpminpt_ = iConfig.getUntrackedParameter<double>("rfpminpt", 0.3);
//	rfpmaxpt_ = iConfig.getUntrackedParameter<double>("rfpmaxpt", 3.0);

	cmode_ = iConfig.getUntrackedParameter<int>("cmode", 1);
	nvtx_ = iConfig.getUntrackedParameter<int>("nvtx", 100);

        consumes<int>(centralityTag_);
        consumes<std::vector<double> >(trackEta_);
        consumes<std::vector<double> >(trackPhi_);
        consumes<std::vector<double> >(trackPt_);
        consumes<std::vector<double> >(trackWeight_);
        consumes<std::vector<double> >(vertexZ_);

	for ( int i = 0; i < 48; i++ ) {
		q3[i] = correlations::QVector(0, 0, true);
	}

	//
	//cout << __LINE__ << "\t" << tracks_.label().c_str() << "\t|" << tracks_.instance() << "\t|" << tracks_.process() << endl;
	//
	edm::Service<TFileService> fs;

	trV = fs->make<TTree>("trV", "trV");
	trV->Branch("Noff", &gNoff, "Noff/I");
	trV->Branch("Mult", &gMult, "Mult/I");

	trV->Branch("rQ1Q1_Q2", &rQ1Q1_Q2, "rQ1Q1_Q2[48]/D");
	trV->Branch("wQ1Q1_Q2", &wQ1Q1_Q2, "wQ1Q1_Q2[48]/D");

	cout << " cmode_ = " << cmode_ << endl;

	initQ();
}


QWV1Cumu::~QWV1Cumu()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

void
QWV1Cumu::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;

	Handle<std::vector<double> >	hEta;
	Handle<std::vector<double> >	hPhi;
	Handle<std::vector<double> >	hPt;
	Handle<std::vector<double> >	hWeight;
	Handle<std::vector<double> >	hVz;

	iEvent.getByLabel(trackEta_,	hEta);
	iEvent.getByLabel(trackPhi_,	hPhi);
	iEvent.getByLabel(trackPt_,	hPt);
	iEvent.getByLabel(trackWeight_, hWeight);
	iEvent.getByLabel(vertexZ_, 	hVz);

	if ( hVz->size() < 1 ) return;
	if ( fabs((*hVz)[0]) > maxvz_ or fabs((*hVz)[0]) < minvz_ ) return;
	int sz = int(hEta->size());
	if ( sz == 0 ) return;

	for ( int i = 0; i < sz; i++ ) {
		int ieta = ((*hEta)[i] + 2.4) * 10;
		if ( ieta < 0 or ieta >= 24 ) continue;
		q3[ieta].fill( (*hPhi)[i], (*hWeight)[i] );
	}
	for ( int i = 0; i < 48; i++ ) {
		rQ1Q1_Q2[i] = 0;
		wQ1Q1_Q2[i] = 0;
	}
	for ( int ieta = 0; ieta < 48; ieta++ ) {
		correlations::Complex qp = 0;
		double wt = 0;
		correlations::QVector tq = q3[ieta];
		for ( int i = 0; i < sz; i++ ) {
			if ( ieta == int(((*hEta)[i] + 2.4) * 10) ) {
				tq.unfill((*hPhi)[i], (*hWeight)[i]);
			}
			correlations::FromQVector *cq = 0;
			switch ( cmode_ ) {
				case 1:
					cq = new correlations::closed::FromQVector(tq);
					break;
				case 2:
					cq = new correlations::recurrence::FromQVector(tq);
					break;
				case 3:
					cq = new correlations::recursive::FromQVector(tq);
					break;
			}
			correlations::Result r = cq->calculate(2, hc);
			qp += (*hWeight)[i] * correlations::Complex( TMath::Cos( -2. * (*hPhi)[i] ) , TMath::Sin( -2. * (*hPhi)[i] ) ) * r.sum();
			wt += (*hWeight)[i] * r.weight();
			delete cq;
		}
		rQ1Q1_Q2[ieta] = qp.real();
		wQ1Q1_Q2[ieta] = wt;
	}

	edm::Handle<int> ch;
	iEvent.getByLabel(centralityTag_,ch);
	gNoff = *ch;
	gMult = sz;

	trV->Fill();
	doneQ();
}


void
QWV1Cumu::initQ()
{
	hc = correlations::HarmonicVector(2);
	hc[0] = 1;
	hc[1] = 1;
//	hc[2] = -2;
	for ( int i = 0; i < 48; i++ ) {
		q3[i].resize(hc);
	}
}

void
QWV1Cumu::doneQ()
{
	for ( int i = 0; i < 48; i++ ) {
		q3[i].reset();
	}
}

// ------------ method called once each job just before starting event loop  ------------
	void 
QWV1Cumu::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
	void 
QWV1Cumu::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
	void 
QWV1Cumu::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
	void 
QWV1Cumu::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
	void 
QWV1Cumu::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
	void 
QWV1Cumu::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
QWV1Cumu::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);

	//Specify that only 'tracks' is allowed
	//To use, remove the default given above and uncomment below
	//ParameterSetDescription desc;
	//desc.addUntracked<edm::InputTag>("tracks","ctfWithMaterialTracks");
	//descriptions.addDefault(desc);
}

//////////////////////////////////////////


//define this as a plug-in
DEFINE_FWK_MODULE(QWV1Cumu);
