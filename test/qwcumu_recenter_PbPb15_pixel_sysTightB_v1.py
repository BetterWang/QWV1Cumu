import FWCore.ParameterSet.Config as cms

process = cms.Process("CumuV3")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = 100

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_v13', '')

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

process.source = cms.Source("PoolSource",
        fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/q/qwang/work/cleanroomRun2/Ana/data/pixeltracking_1.root")
)

import HLTrigger.HLTfilters.hltHighLevel_cfi

process.hltMB = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.hltMB.HLTPaths = [
	"HLT_HIL1MinimumBiasHF2AND*",
	"HLT_HIL1MinimumBiasHF1AND*",
]
process.hltMB.andOr = cms.bool(True)
process.hltMB.throw = cms.bool(False)

process.FakeRP = cms.EDProducer('QWDoubleProducer',
	src = cms.untracked.double(0.0)
)

process.CaloQ = cms.EDProducer('QWCaloQProducer',
		caloSrc = cms.untracked.InputTag('towerMaker'),
		etaMin = cms.untracked.double(4.),
		etaMax = cms.untracked.double(5.),
		N = cms.untracked.int32(1),
		)

process.V1Cumu = cms.EDAnalyzer('QWV1Cumu'
	, trackEta = cms.untracked.InputTag('QWEvent', "eta")
	, trackPhi = cms.untracked.InputTag('QWEvent', "phi")
	, trackPt = cms.untracked.InputTag('QWEvent', "pt")
	, trackWeight = cms.untracked.InputTag('QWEvent', "weight")
	, trackCharge = cms.untracked.InputTag('QWEvent', "charge")
	, vertexZ = cms.untracked.InputTag('QWEvent', "vz")
	, RP = cms.untracked.InputTag('FakeRP')
	, psiHFp = cms.untracked.InputTag('CaloQ', 'argp')
	, psiHFm = cms.untracked.InputTag('CaloQ', 'argm')
	, centrality = cms.untracked.InputTag('centralityBin', "HFtowers")
	, minvz = cms.untracked.double(-15.0)
	, maxvz = cms.untracked.double(15.0)
	, rfpmineta = cms.untracked.double(-2.4)
	, rfpmaxeta = cms.untracked.double(2.4)
	, rfpminpt = cms.untracked.double(0.3)
	, rfpmaxpt = cms.untracked.double(3.0)
	, poimineta = cms.untracked.double(-2.4)
	, poimaxeta = cms.untracked.double(2.4)
	, poiminpt = cms.untracked.double(0.3)
	, poimaxpt = cms.untracked.double(20.0)
	, dEtaGap = cms.untracked.double(2.0)
	, cmode = cms.untracked.int32(1)
	, nvtx = cms.untracked.int32(100)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('cumu.root')
)

# tightB
process.load('PbPb_HIMB2_pixel_eff')
process.QWEvent.ptMax = cms.untracked.double(15.0)
process.QWEvent.fweight = cms.untracked.InputTag('EffCorrectionsPixelPbPb_TightB.root')
process.QWEvent.chi2 = cms.untracked.double(9.0)
process.QWEvent.dzdzerror_pix = cms.untracked.double(6.0)
process.QWEvent.pterrorpt = cms.untracked.double(0.05)
process.QWEvent.dzdzerror = cms.untracked.double(2.)
process.QWEvent.d0d0error = cms.untracked.double(2.)

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)

process.eventSelection = cms.Sequence(
        process.hfCoincFilter3
        + process.primaryVertexFilter
#        + process.clusterCompatibilityFilter
)

process.QWRecenter = cms.EDAnalyzer('QWRecenter'
	, trackEta = cms.untracked.InputTag('QWEvent', "eta")
	, trackPhi = cms.untracked.InputTag('QWEvent', "phi")
	, trackPt = cms.untracked.InputTag('QWEvent', "pt")
	, trackWeight = cms.untracked.InputTag('QWEvent', "weight")
	, vertexZ = cms.untracked.InputTag('QWEvent', "vz")
	, centrality = cms.untracked.InputTag('centralityBin', "HFtowers")
	)

process.ana = cms.Path(process.hltMB
		* process.eventSelection
#		* process.FakeRP
#		* process.CaloQ
		* process.makeEvent
#		* process.V1Cumu
		* process.QWRecenter
		* process.vectMonW
)

process.schedule = cms.Schedule(
	process.ana,
)
