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
	RP_( iConfig.getUntrackedParameter<edm::InputTag>("RP") ),
	psiHFp_( iConfig.getUntrackedParameter<edm::InputTag>("psiHFp") ),
	psiHFm_( iConfig.getUntrackedParameter<edm::InputTag>("psiHFm") ),
	centralityTag_( iConfig.getUntrackedParameter<edm::InputTag>("centrality") )
{
	//now do what ever initialization is needed
	minvz_ = iConfig.getUntrackedParameter<double>("minvz", -15.);
	maxvz_ = iConfig.getUntrackedParameter<double>("maxvz", 15.);

	etaCmin_ = iConfig.getUntrackedParameter<double>("etaCmin", -2.4);
	etaCmax_ = iConfig.getUntrackedParameter<double>("etaCmax", 2.4);

	etaTrackerMin_ = iConfig.getUntrackedParameter<double>("etaTrackerMin", 2.0);
	etaTrackerMax_ = iConfig.getUntrackedParameter<double>("etaTrackerMax", 2.4);

	cmode_ = iConfig.getUntrackedParameter<int>("cmode", 1);
	nvtx_ = iConfig.getUntrackedParameter<int>("nvtx", 100);

	if ( psiHFp_.label() == "NA" ) b3point_ = false;
	else b3point_ = true;

        consumes<int>(centralityTag_);
        consumes<std::vector<double> >(trackEta_);
        consumes<std::vector<double> >(trackPhi_);
        consumes<std::vector<double> >(trackPt_);
        consumes<std::vector<double> >(trackWeight_);
        consumes<std::vector<double> >(vertexZ_);
        consumes<double>(RP_);
	if ( b3point_ ) {
        	consumes<double>(psiHFp_);
        	consumes<double>(psiHFm_);
	}

	for ( int i = 0; i < 12; i++ ) {
		q3[i] = correlations::QVector(0, 0, true);
	}
	qC = correlations::QVector(0, 0, true);

	//
	//cout << __LINE__ << "\t" << tracks_.label().c_str() << "\t|" << tracks_.instance() << "\t|" << tracks_.process() << endl;
	//
	edm::Service<TFileService> fs;

	trV = fs->make<TTree>("trV", "trV");
	trV->Branch("Noff", &gNoff, "Noff/I");
	trV->Branch("Mult", &gMult, "Mult/I");

	trV->Branch("rQ1Q1_Q2", &rQ1Q1_Q2, "rQ1Q1_Q2[12]/D");
	trV->Branch("wQ1Q1_Q2", &wQ1Q1_Q2, "wQ1Q1_Q2[12]/D");

	trV->Branch("rV1", &rV1, "rV1[12]/D");
	trV->Branch("rV2", &rV2, "rV2[12]/D");
	trV->Branch("wV",  &wV,  "wV[12]/D");

	trV->Branch("r3point", &r3point, "r3point[12]/D");
	trV->Branch("w3point", &w3point, "w3point[12]/D");

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
	Handle<double>			hRP;
	Handle<double>			hpsiHFp;
	Handle<double>			hpsiHFm;

	iEvent.getByLabel(trackEta_,	hEta);
	iEvent.getByLabel(trackPhi_,	hPhi);
	iEvent.getByLabel(trackPt_,	hPt);
	iEvent.getByLabel(trackWeight_, hWeight);
	iEvent.getByLabel(vertexZ_, 	hVz);
	iEvent.getByLabel(RP_,	 	hRP);

	if ( b3point_ ) {
		iEvent.getByLabel(psiHFp_,	hpsiHFp);
		iEvent.getByLabel(psiHFm_,	hpsiHFm);
	}

	if ( hVz->size() < 1 ) return;
	if ( fabs((*hVz)[0]) > maxvz_ or fabs((*hVz)[0]) < minvz_ ) return;
	int sz = int(hEta->size());
	if ( sz == 0 ) return;

	std::vector<int>	vEtaBin(sz);

//	PRD(sz);
	for ( int i = 0; i < sz; i++ ) {
		if ( ((*hEta)[i]) > etaCmin_ and ((*hEta)[i]) < etaCmax_ ) qC.fill( (*hPhi)[i], (*hWeight)[i] );
		int ieta = (((*hEta)[i] + 2.4) * 10)/4;
		vEtaBin[i] = ieta;
		if ( ieta < 0 or ieta >= 12 ) {
			continue;
		};
		q3[ieta].fill( (*hPhi)[i], (*hWeight)[i] );

	}

	for ( int i = 0; i < 12; i++ ) {
		rQ1Q1_Q2[i] = 0;
		wQ1Q1_Q2[i] = 0;
		rV1[i] = 0;
		rV2[i] = 0;
		wV[i] = 0;
		r3point[i] = 0;
		w3point[i] = 0;
	}

	for ( int ieta = 0; ieta < 6; ieta++ ) {
		correlations::QVector tq = qC;
		for ( int i = 0; i < sz; i++ ) {
			if ( vEtaBin[i] == ieta or vEtaBin[i] == 11 - ieta ) {
				tq.unfill( (*hPhi)[i], (*hWeight)[i] );
			}
		}
		std::unique_ptr<correlations::FromQVector> cqA;
		std::unique_ptr<correlations::FromQVector> cqB;
		std::unique_ptr<correlations::FromQVector> cqC;
		switch ( cmode_ ) {
			case 1:
				cqA = std::make_unique< correlations::closed::FromQVector >(q3[ieta]);
				cqB = std::make_unique< correlations::closed::FromQVector >(q3[11-ieta]);
				cqC = std::make_unique< correlations::closed::FromQVector >(tq);
				break;
			case 2:
				cqA = std::make_unique< correlations::recurrence::FromQVector >(q3[ieta]);
				cqB = std::make_unique< correlations::recurrence::FromQVector >(q3[11-ieta]);
				cqC = std::make_unique< correlations::recurrence::FromQVector >(tq);
				break;
			case 3:
				cqA = std::make_unique< correlations::recursive::FromQVector >(q3[ieta]);
				cqB = std::make_unique< correlations::recursive::FromQVector >(q3[11-ieta]);
				cqC = std::make_unique< correlations::recursive::FromQVector >(tq);
				break;
		}
		correlations::Result A = cqA->calculate(1, hc);
		correlations::Result B = cqB->calculate(1, hc);
		correlations::Result C = cqC->calculate(1, hc2);

		auto qp = A.sum() * B.sum() * C.sum();
		auto wt = A.weight() * B.weight() * C.weight();

		rQ1Q1_Q2[ieta] = qp.real();
		wQ1Q1_Q2[ieta] = wt;
//		PRD(ieta);
//		PRD(rQ1Q1_Q2[ieta]);
	}

//	for ( int ieta = 0; ieta < 12; ieta++ ) {
//		correlations::Complex qp = 0;
//		double wt = 0;
//		for ( int i = 0; i < sz; i++ ) {
//			correlations::QVector tq = q3[ieta];
//			if ( ieta == int(((*hEta)[i] + 2.4) * 10/4) ) {
//				tq.unfill((*hPhi)[i], (*hWeight)[i]);
//			}
//			correlations::FromQVector *cq = 0;
//			switch ( cmode_ ) {
//				case 1:
//					cq = new correlations::closed::FromQVector(tq);
//					break;
//				case 2:
//					cq = new correlations::recurrence::FromQVector(tq);
//					break;
//				case 3:
//					cq = new correlations::recursive::FromQVector(tq);
//					break;
//			}
//			correlations::Result r = cq->calculate(2, hc);
//			qp += (*hWeight)[i] * correlations::Complex( TMath::Cos( -2. * (*hPhi)[i] ) , TMath::Sin( -2. * (*hPhi)[i] ) ) * r.sum();
//			wt += (*hWeight)[i] * r.weight();
//			delete cq;
//		}
//		rQ1Q1_Q2[ieta] = qp.real();
//		wQ1Q1_Q2[ieta] = wt;
//	}

	for ( int i = 0; i < sz; i++ ) {
		int ieta = int(((*hEta)[i] + 2.4) * 10/4);
		if ( ieta < 0 or ieta >= 12 ) continue;

		rV1[ieta] += (*hWeight)[i] * TMath::Cos( (*hPhi)[i] - (*hRP) );
		rV2[ieta] += (*hWeight)[i] * TMath::Cos( 2.*((*hPhi)[i] - (*hRP)) );

		wV[ieta] += (*hWeight)[i];
	}

	TComplex trkQp(0., 0.);
	TComplex trkQm(0., 0.);
	for ( int i = 0; i < sz; i++ ) {
		if ( (*hEta)[i] > etaTrackerMin_ and (*hEta)[i] < etaTrackerMax_ ) {
			trkQp += TComplex((*hWeight)[i], (*hPhi)[i] );
		} else
		if ( (*hEta)[i] > -etaTrackerMax_ and (*hEta)[i] < -etaTrackerMin_ ) {
			trkQm += TComplex((*hWeight)[i], (*hPhi)[i] );
		}
	}

	TComplex q3point[12];
	for ( int i = 0; i < sz; i++ ) {
		if ( vEtaBin[i] < 0 or vEtaBin[i] >= 12 ) continue;

		TComplex q3p;
		if ( (*hEta)[i] > 0 ) {
			q3p = TComplex( (*hWeight)[i], (*hPhi)[i] + trkQm.Theta() - (*hpsiHFm), true);
		} else {
			q3p = TComplex( (*hWeight)[i], (*hPhi)[i] + trkQp.Theta() - (*hpsiHFp), true);
		}

		q3point[ vEtaBin[i] ] += q3p;
	}

	for ( int i = 0; i < 12; i++ ) {
		r3point[i] = q3point[i].Re();
		w3point[i] = q3point[i].Rho();
	}

	edm::Handle<int> ch;
	iEvent.getByLabel(centralityTag_,ch);
	gNoff = *ch;
	gMult = sz;

	trV->Fill();
	doneQ();
//	PRD(*ch);
}


void
QWV1Cumu::initQ()
{
	hc = correlations::HarmonicVector(2);
	hc[0] = 1;
	hc[1] = 1;
//	hc[2] = -2;
	hc2 = correlations::HarmonicVector(1);
	hc2[0] = -2;
	for ( int i = 0; i < 12; i++ ) {
		q3[i].resize(hc);
	}
	qC.resize(hc2);
}

void
QWV1Cumu::doneQ()
{
	for ( int i = 0; i < 12; i++ ) {
		q3[i].reset();
	}
	qC.reset();
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
