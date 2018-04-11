#include <correlations/Types.hh>
#include <correlations/Result.hh>
#include <correlations/QVector.hh>
#include <correlations/recursive/FromQVector.hh>
#include <correlations/recurrence/FromQVector.hh>
#include <correlations/closed/FromQVector.hh>
#include <TComplex.h>
#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TNtupleD.h>
#include <TRandom3.h>
#include <TFile.h>
//
// constants, enums and typedefs
//

//#define QW_DEBUG 1
//#define QW_PEREVENT 1

#define PRD(x) cout << "!!QW!! " << __LINE__ << " DEBUG OUTPUT " << (#x) << " = " << (x) << endl;
#define PR(x) cout << "!!QW!! " << __LINE__ << " DEBUG OUTPUT " << (#x) << endl;
//
// class declaration
//

///////////////// Class ////////////////////////////

class QWV1Cumu : public edm::EDAnalyzer {
	public:
		explicit QWV1Cumu(const edm::ParameterSet&);
		~QWV1Cumu();

		static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

	private:
		virtual void beginJob() ;
		virtual void analyze(const edm::Event&, const edm::EventSetup&);
		virtual void endJob() ;

		virtual void beginRun(edm::Run const&, edm::EventSetup const&);
		virtual void endRun(edm::Run const&, edm::EventSetup const&);
		virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
		virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

	/////////////////////////////////////////////
		//TRandom3 * gRandom;
		// ----------member data ---------------------------

		edm::InputTag					trackEta_;
		edm::InputTag					trackPhi_;
		edm::InputTag					trackPt_;
		edm::InputTag					trackWeight_;
		edm::InputTag					vertexZ_;
		edm::InputTag					RP_;
		edm::InputTag					psiHFp_;
		edm::InputTag					psiHFm_;

		edm::InputTag					centralityTag_;

		double	minvz_, maxvz_;
		double	etaCmin_, etaCmax_;
		double	etaTrackerMin_, etaTrackerMax_;
	/////////////////////////////////////////////
//		double	rfpmineta_, rfpmaxeta_;
//		double	rfpminpt_, rfpmaxpt_;

		int	cmode_;

		int	nvtx_;

		bool	b3point_;
	/////////////////////////////////////////////
		TTree * trV;

		int gMult;
		int gNoff;

		double rQ1Q1_Q2[12];
		double wQ1Q1_Q2[12];

		double rV1[12];
		double rV2[12];
		double wV[12];

		double r3point[12];
		double w3point[12];

		correlations::HarmonicVector	hc;
		correlations::HarmonicVector	hc2;
		correlations::QVector		q3[12];
		correlations::QVector		qC;

		void initQ();
		void doneQ();

};



