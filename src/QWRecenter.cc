// -*- C++ -*-
//
// Package:    QWRecenter
// Class:      QWRecenter

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


using namespace std;

//#ifdef QW_DEBUG
//
// constructors and destructor
//
class QWRecenter : public edm::EDAnalyzer {
	public:
		explicit QWRecenter(const edm::ParameterSet&);
		~QWRecenter();

	private:
		virtual void analyze(const edm::Event&, const edm::EventSetup&) override;

	/////////////////////////////////////////////
		// ----------member data ---------------------------

		edm::InputTag					trackEta_;
		edm::InputTag					trackPhi_;
		edm::InputTag					trackPt_;
		edm::InputTag					trackWeight_;
		edm::InputTag					vertexZ_;
		edm::InputTag					centralityTag_;

		double	minvz_, maxvz_;
	/////////////////////////////////////////////
		//                          0,   1,   2,   3,    4,   5,    6,   7,    8,   9,   10,   11,   12,   13,   14,   15,  16,   17,   18,   19,   20
		double const ptBin[21] = {0.3, 0.4, 0.5, 0.6,  0.8, 1.0, 1.25, 1.50, 2.0, 2.5,  3.0,  3.5,  4.0,  5.0,  6.0,  7.0, 8.0, 10.0, 12.0, 14.0, 1000.};

		TH1D * hS1[20][12];
		TH1D * hC1[20][12];
		TH1D * hS2[20][12];
		TH1D * hC2[20][12];

		TH1D * hNS1[20][12];
		TH1D * hNC1[20][12];
		TH1D * hNS2[20][12];
		TH1D * hNC2[20][12];
};


QWRecenter::QWRecenter(const edm::ParameterSet& iConfig):
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

        consumes<int>(centralityTag_);
        consumes<std::vector<double> >(trackEta_);
        consumes<std::vector<double> >(trackPhi_);
        consumes<std::vector<double> >(trackPt_);
        consumes<std::vector<double> >(trackWeight_);
        consumes<std::vector<double> >(vertexZ_);


	edm::Service<TFileService> fs;

	for ( int ipt = 0; ipt < 20; ipt++ ) {
		for ( int ieta = 0; ieta < 12; ieta++ ) {
			hS1[ipt][ieta] = fs->make<TH1D>(Form("hS1_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
			hC1[ipt][ieta] = fs->make<TH1D>(Form("hC1_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
			hS2[ipt][ieta] = fs->make<TH1D>(Form("hS2_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
			hC2[ipt][ieta] = fs->make<TH1D>(Form("hC2_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);

			hNS1[ipt][ieta] = fs->make<TH1D>(Form("hNS1_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
			hNC1[ipt][ieta] = fs->make<TH1D>(Form("hNC1_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
			hNS2[ipt][ieta] = fs->make<TH1D>(Form("hNS2_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
			hNC2[ipt][ieta] = fs->make<TH1D>(Form("hNC2_%i_%i", ipt, ieta), Form("%0.1f<pT<%0.1f, %0.1f<eta<%0.1f", ptBin[ipt], ptBin[ipt+1], 0.4*ieta - 2.4, 0.4*ieta - 2.0), 200, 0, 200);
		}
	}
}


QWRecenter::~QWRecenter()
{

	// do anything here that needs to be done at desctruction time
	// (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

void
QWRecenter::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
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

	edm::Handle<int> ch;
	iEvent.getByLabel(centralityTag_,ch);

	if ( hVz->size() < 1 ) return;
	if ( fabs((*hVz)[0]) > maxvz_ or fabs((*hVz)[0]) < minvz_ ) return;
	int sz = int(hEta->size());
	if ( sz == 0 ) return;

	std::vector<int>	vEtaBin(sz);
	std::vector<int>	vPtBin(sz);

	for ( int i = 0; i < sz; i++ ) {
		int ieta = (((*hEta)[i] + 2.4) * 10)/4;
		vEtaBin[i] = ieta;
	}
	for ( int i = 0; i < sz; i++ ) {
		int ipt = 0;
		while ( (*hPt)[i] > ptBin[ipt+1] ) ipt++;
		vPtBin[i] = ipt;
	}

	for ( int i = 0; i < sz; i++ ) {
		int ipt = vPtBin[i];
		int ieta = vEtaBin[i];
		if ( ipt >= 20 ) continue;
		if ( ieta < 0 or ieta >=12 ) continue;

		hS1[ipt][ieta]->Fill( (*ch), (*hWeight)[i] * TMath::Sin( (*hPhi)[i] ) );
		hC1[ipt][ieta]->Fill( (*ch), (*hWeight)[i] * TMath::Cos( (*hPhi)[i] ) );
		hS2[ipt][ieta]->Fill( (*ch), (*hWeight)[i] * TMath::Sin( 2*(*hPhi)[i] ) );
		hC2[ipt][ieta]->Fill( (*ch), (*hWeight)[i] * TMath::Cos( 2*(*hPhi)[i] ) );

		hNS1[ipt][ieta]->Fill( (*ch), (*hWeight)[i] );
		hNC1[ipt][ieta]->Fill( (*ch), (*hWeight)[i] );
		hNS2[ipt][ieta]->Fill( (*ch), (*hWeight)[i] );
		hNC2[ipt][ieta]->Fill( (*ch), (*hWeight)[i] );
	}
}


//define this as a plug-in
DEFINE_FWK_MODULE(QWRecenter);
