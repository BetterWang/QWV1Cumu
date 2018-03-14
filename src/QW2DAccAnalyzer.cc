#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include <iostream>


namespace {
	const int Npt = 31;
	const double ptBins[] = {0.30, 0.35, 0.40, 0.45, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75,
				 0.80, 0.85, 0.90, 0.95, 1.00, 1.05, 1.10, 1.15, 1.20, 1.30, 1.40, 1.50,
				 1.60, 1.70, 1.80, 1.90, 2.00, 2.50, 3.00, 100000000};
}



class QW2DAccAnalyzer : public edm::EDAnalyzer {
public:
	explicit QW2DAccAnalyzer(const edm::ParameterSet&);
	~QW2DAccAnalyzer() {};
private:
	virtual void beginJob() {};
	virtual void analyze(const edm::Event&, const edm::EventSetup&);
	virtual void endJob() {};

	edm::InputTag   srcPhi_;
	edm::InputTag   srcEta_;
	edm::InputTag   srcPt_;

	TH2D * hc[Npt];
};



QW2DAccAnalyzer::QW2DAccAnalyzer(const edm::ParameterSet& pset) :
	srcPhi_(pset.getUntrackedParameter<edm::InputTag>("srcPhi")),
	srcEta_(pset.getUntrackedParameter<edm::InputTag>("srcEta")),
	srcPt_(pset.getUntrackedParameter<edm::InputTag>("srcPt")),
	srcWeight_(pset.getUntrackedParameter<edm::InputTag>("srcWeight"))
{
	consumes<std::vector<double> >(srcPhi_);
	consumes<std::vector<double> >(srcEta_);
	consumes<std::vector<double> >(srcPt_);
	consumes<std::vector<double> >(srcWeight_);

	int NbinsPhi = pset.getUntrackedParameter<int>("NbinsPhi", 48);
	int NbinsEta = pset.getUntrackedParameter<int>("NbinsEta", 48);
	double hstartPhi = pset.getUntrackedParameter<double>("hstartPhi", -3.14159265358979323846);
	double hendPhi = pset.getUntrackedParameter<double>("hendPhi", 3.14159265358979323846);
	double hstartEta = pset.getUntrackedParameter<double>("hstartEta", -2.4);
	double hendEta = pset.getUntrackedParameter<double>("hendEta", 2.4);

	minPt_ = pset.getUntrackedParameter<double>("minPt", std::numeric_limits<double>::min());
	maxPt_ = pset.getUntrackedParameter<double>("maxPt", std::numeric_limits<double>::max());

	edm::Service<TFileService> fs;
	for ( int i = 0; i < Npt; i++ ) {
		hc[i] = fs->make<TH2D>(Form("hc_%i", i), "", NbinsPhi, hstartPhi, hendPhi, NbinsEta, hstartEta, hendEta);
		hc[i]->Sumw2();
	}
}

void
QW2DAccAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	Handle<std::vector<double> > pPhi;
	Handle<std::vector<double> > pEta;
	Handle<std::vector<double> > pPt;
	Handle<std::vector<double> > pWeight;

	iEvent.getByLabel(srcPhi_, pPhi);
	iEvent.getByLabel(srcEta_, pEta);
	iEvent.getByLabel(srcPt_, pPt);
	iEvent.getByLabel(srcWeight_, pWeight);

	int szPt = pPt->size();
	int szPhi = pPhi->size();
	int szEta = pEta->size();
	int szWeight = pWeight->size();
	if ( szPt != szPhi or szPt != szEta or szPt != szWeight ) return;

	for ( int i = 0; i < szPt; i++ ) {
		int ipt = -1;
		while ( (*pPt)[i] > ptBins[ipt+1] ) ipt++;
		if ( ipt < 0 or ipt > Npt ) continue;

		hc->Fill( (*pPhi)[i], (*pEta)[i] );
	}
	return;
}

DEFINE_FWK_MODULE(QW2DAccAnalyzer);
