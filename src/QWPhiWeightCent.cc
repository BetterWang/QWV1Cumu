#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "SimDataFormats/HiGenData/interface/GenHIEvent.h"

#include "TFile.h"
#include "TH2.h"
#include "TMath.h"
#include "TRandom.h"

namespace {
	const int Npt = 28;
	const double ptBins[] = {0.30, 0.35, 0.40, 0.45, 0.50, 0.55, 0.60, 0.65, 0.70, 0.75,
				 0.80, 0.85, 0.90, 0.95, 1.00, 1.05, 1.10, 1.15, 1.20, 1.30, 1.40, 1.50,
				 1.60, 1.70, 1.80, 1.90, 2.00, 2.50, 3.00, 100000000};
}
class QWPhiWeightCent : public edm::EDProducer {
public:
	explicit QWPhiWeightCent(const edm::ParameterSet&);
	~QWPhiWeightCent();

private:
	virtual void produce(edm::Event&, const edm::EventSetup&) override;
	///
	edm::InputTag	src_;
	edm::InputTag	srcPhi_;
	edm::InputTag	srcEta_;
	edm::InputTag	srcPt_;
	edm::InputTag	centralityTag_;
	edm::InputTag	srcWeight_;
	TH2D * 		hPhi[200][Npt];
};

QWPhiWeightCent::QWPhiWeightCent(const edm::ParameterSet& pset) :
	src_(pset.getUntrackedParameter<edm::InputTag>("src")),
	srcPhi_(pset.getUntrackedParameter<edm::InputTag>("srcPhi")),
	srcEta_(pset.getUntrackedParameter<edm::InputTag>("srcEta")),
	srcPt_(pset.getUntrackedParameter<edm::InputTag>("srcPt")),
	centralityTag_( iConfig.getUntrackedParameter<edm::InputTag>("centrality") ),
	srcWeight_(pset.getUntrackedParameter<edm::InputTag>("srcWeight"))
{
	consumes<std::vector<double> >(srcPhi_);
	consumes<std::vector<double> >(srcEta_);
	consumes<std::vector<double> >(srcPt_);
	consumes<std::vector<double> >(srcWeight_);
	consumes<int>(centralityTag_),

	TFile *f = new TFile(src_.label().c_str());
	for ( int i = 0; i < Npt; i++ ) {
		for ( int c = 0; c < 10; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc0/hc_%i", i));
		}
		for ( int c = 10; c < 20; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc10/hc_%i", i));
		}
		for ( int c = 20; c < 30; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc20/hc_%i", i));
		}
		for ( int c = 30; c < 40; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc30/hc_%i", i));
		}
		for ( int c = 40; c < 50; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc40/hc_%i", i));
		}
		for ( int c = 50; c < 60; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc50/hc_%i", i));
		}
		for ( int c = 60; c < 70; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc60/hc_%i", i));
		}
		for ( int c = 70; c < 80; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc70/hc_%i", i));
		}
		for ( int c = 80; c < 100; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc80/hc_%i", i));
		}
		for ( int c = 100; c < 120; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc100/hc_%i", i));
		}
		for ( int c = 120; c < 200; c++ ) {
			hPhi[c][i] = (TH2D*) f->Get(Form("QWAcc120/hc_%i", i));
		}
	}

	produces<std::vector<double> >("");
}

QWPhiWeightCent::~QWPhiWeightCent()
{
	return;
}

void QWPhiWeightCent::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
	using namespace edm;
	Handle< std::vector<double> > pphi;
	Handle< std::vector<double> > peta;
	Handle< std::vector<double> > ppt;
	Handle< std::vector<double> > pweight;
	iEvent.getByLabel(srcPhi_, pphi);
	iEvent.getByLabel(srcEta_, peta);
	iEvent.getByLabel(srcPt_, ppt);
	iEvent.getByLabel(srcWeight_, pweight);

	edm::Handle<int> ch;
	iEvent.getByLabel(centralityTag_,ch);

	int sz = pphi->size();

	std::vector<double> pw;
	pw.reserve(sz);

	for ( int i = 0; i < sz; i++ ) {
		int ipt = -1;
		while ( (*ppt)[i] > ptBins[ipt+1] ) ipt++;

		double weight = hPhi[*ch][ipt]->GetBinContent( hPhi[*ch][ipt]->FindBin((*pphi)[i], (*peta)[i]) );

		weight = (*pweight)[i] / weight;
		pw.push_back(weight);
	}

	iEvent.put(std::make_unique<std::vector<double> >(pw), string(""));
}


DEFINE_FWK_MODULE(QWPhiWeightCent);
