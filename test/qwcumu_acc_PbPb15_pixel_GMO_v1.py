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


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('cumu.root')
)

process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')
process.clusterCompatibilityFilter.clusterPars = cms.vdouble(0.0,0.006)


process.eventSelection = cms.Sequence(
        process.hfCoincFilter3
        + process.primaryVertexFilter
        + process.clusterCompatibilityFilter
)


process.load('RecoHI.HiCentralityAlgos.CentralityFilter_cfi')
process.cent0= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(0, 10)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)
process.cent10= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(10, 20)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)
process.cent20= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(20, 30)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)
process.cent30= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(30, 40)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)
process.cent40= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(40, 50)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.cent50= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(50, 60)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.cent60= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(60, 70)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.cent70= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(70, 80)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.cent80= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(80, 100)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.cent100= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(100, 120)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.cent120= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(120, 140)
			),
		BinLabel = cms.InputTag("centralityBin", "HFtowers")
		)

process.QWAcc0 = cms.EDAnalyzer('QW2DAccAnalyzer',
		srcPhi = cms.untracked.InputTag("QWEvent", "phi"),
		srcEta = cms.untracked.InputTag("QWEvent", "eta"),
		srcPt = cms.untracked.InputTag("QWEvent", "pt"),
		)

process.QWAcc10 = process.QWAcc0.clone()
process.QWAcc20 = process.QWAcc0.clone()
process.QWAcc30 = process.QWAcc0.clone()
process.QWAcc40 = process.QWAcc0.clone()
process.QWAcc50 = process.QWAcc0.clone()
process.QWAcc60 = process.QWAcc0.clone()
process.QWAcc70 = process.QWAcc0.clone()
process.QWAcc80 = process.QWAcc0.clone()
process.QWAcc100 = process.QWAcc0.clone()
process.QWAcc120 = process.QWAcc0.clone()

process.load('PbPb_HIMB2_pixel_eff')
process.QWEvent.ptMax = cms.untracked.double(3.0)
process.QWEvent.fweight = cms.untracked.InputTag('NA')


process.acc0 = cms.Sequence( process.cent0 * process.QWAcc0 )
process.acc10 = cms.Sequence( process.cent10 * process.QWAcc10 )
process.acc20 = cms.Sequence( process.cent20 * process.QWAcc20 )
process.acc30 = cms.Sequence( process.cent30 * process.QWAcc30 )
process.acc40 = cms.Sequence( process.cent40 * process.QWAcc40 )
process.acc50 = cms.Sequence( process.cent50 * process.QWAcc50 )
process.acc60 = cms.Sequence( process.cent60 * process.QWAcc60 )
process.acc70 = cms.Sequence( process.cent70 * process.QWAcc70 )
process.acc80 = cms.Sequence( process.cent80 * process.QWAcc80 )
process.acc100 = cms.Sequence( process.cent100 * process.QWAcc100 )
process.acc120 = cms.Sequence( process.cent120 * process.QWAcc120 )

process.ana0 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc0
		)

process.ana10 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc10
		)

process.ana20 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc20
		)

process.ana30 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc30
		)

process.ana40 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc40
		)

process.ana50 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc50
		)

process.ana60 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc60
		)

process.ana70 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc70
		)

process.ana80 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc80
		)

process.ana100 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc100
		)

process.ana120 = cms.Path(process.hltMB
		* process.eventSelection
		* process.makeEvent
		* process.acc120
		)





process.schedule = cms.Schedule(
	process.ana0,
	process.ana10,
	process.ana20,
	process.ana30,
	process.ana40,
	process.ana50,
	process.ana60,
	process.ana70,
	process.ana80,
	process.ana100,
	process.ana120,
)
