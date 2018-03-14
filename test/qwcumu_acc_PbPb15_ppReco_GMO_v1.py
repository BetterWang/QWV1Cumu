import FWCore.ParameterSet.Config as cms

process = cms.Process("CumuGap1")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')


process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = 100
process.MessageLogger.suppressWarning = cms.untracked.vstring('GMOVertex')

from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, '75X_dataRun2_PromptHI_v3', '')

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring("file:/afs/cern.ch/user/q/qwang/work/cleanroomRun2/Ana/data/ppReco_GMOV0.root"),
        secondaryFileNames = cms.untracked.vstring("file:/afs/cern.ch/user/q/qwang/work/cleanroomRun2/Ana/data/ppReco.root")
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

#process.primaryVertexFilter.src = cms.InputTag("offlinePrimaryVertices")
process.primaryVertexFilter.src = cms.InputTag("GMOVertex")

process.load('RecoHI.HiCentralityAlgos.CentralityFilter_cfi')
process.ppRecoCentFilter = process.centralityFilter.clone(
	selectedBins = cms.vint32(
		*range(60, 180)
		),
	BinLabel = cms.InputTag("centralityBins")
	)

process.eventSelection = cms.Sequence(
        process.hfCoincFilter3
        + process.primaryVertexFilter
#        + process.clusterCompatibilityFilter
)

process.load('PbPb_HIMB5_ppReco_eff')
process.QWEvent.fweight = cms.untracked.InputTag('NA')


process.QWOfflineVtx = cms.EDProducer('QWVertexProducer',
		vertexSrc = cms.untracked.InputTag("offlinePrimaryVertices")
		)

process.QWGMOVtx = cms.EDProducer('QWVertexProducer',
		vertexSrc = cms.untracked.InputTag("GMOVertex")
		)

process.histVtxSize = cms.EDAnalyzer('QWHistAnalyzer',
		src = cms.untracked.InputTag("QWOfflineVtx", "size"),
		Nbins = cms.untracked.int32(50),
		start = cms.untracked.double(0),
		end = cms.untracked.double(50),
		)

process.GMONoff = cms.EDProducer("QWNtrkOfflineProducer",
                vertexSrc = cms.untracked.InputTag("GMOVertex"),
                trackSrc  = cms.untracked.InputTag("generalTracks")
                )

process.centralityBins = cms.EDProducer("QWPPRecoCentBinProducer")


process.QWGMOEvent = process.QWEvent.clone(
		vertexSrc = cms.untracked.InputTag('GMOVertex'),
                centralitySrc = cms.untracked.InputTag("GMONoff")
		)


process.dbGMONoff = cms.EDProducer('QWInt2Double',
		src = cms.untracked.InputTag('GMONoff'),
		)


process.makeGMOEvent = cms.Sequence( process.GMONoff * process.QWGMOEvent )

process.histGMONoff = process.histNoff.clone(
		src = cms.untracked.InputTag("GMONoff"),
		)

process.histCentrality = process.histNoff.clone(
		src = cms.untracked.InputTag("centralityBins"),
		)

process.vectGMOPhi = process.vectPhi.clone(
		src = cms.untracked.InputTag("QWGMOEvent", "phi"),
		)

process.vectGMOEta = process.vectEta.clone(
		src = cms.untracked.InputTag("QWGMOEvent", "eta"),
		)

process.vectGMOPt = process.vectPt.clone(
		src = cms.untracked.InputTag("QWGMOEvent", "pt"),
		)

process.vectGMOPhiW = process.vectGMOPhi.clone(
		srcW = cms.untracked.InputTag("QWGMOEvent", "weight")
		)

process.vectGMOEtaW = process.vectGMOEta.clone(
		srcW = cms.untracked.InputTag("QWGMOEvent", "weight")
		)

process.vectGMOPtW = process.vectGMOPt.clone(
		srcW = cms.untracked.InputTag("QWGMOEvent", "weight")
		)

process.vectGMOMonW = cms.Sequence( process.histGMONoff *
		process.histCentrality *
		process.vectGMOPhi *
		process.vectGMOEta *
		process.vectGMOPt *
		process.vectGMOPhiW *
		process.vectGMOEtaW *
		process.vectGMOPtW )

process.QWAcc60 = cms.EDAnalyzer('QW2DAccAnalyzer',
		srcPhi = cms.untracked.InputTag("QWGMOEvent", "phi"),
		srcEta = cms.untracked.InputTag("QWGMOEvent", "eta"),
		srcPt = cms.untracked.InputTag("QWGMOEvent", "pt"),
		)

process.QWAcc70 = process.QWAcc60.clone()
process.QWAcc80 = process.QWAcc60.clone()
process.QWAcc100 = process.QWAcc60.clone()
process.QWAcc120 = process.QWAcc60.clone()

process.load('RecoHI.HiCentralityAlgos.CentralityFilter_cfi')
process.cent60= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(60, 70)
			),
		BinLabel = cms.InputTag("centralityBins")
		)

process.cent70= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(70, 80)
			),
		BinLabel = cms.InputTag("centralityBins")
		)

process.cent80= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(80, 100)
			),
		BinLabel = cms.InputTag("centralityBins")
		)

process.cent100= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(100, 120)
			),
		BinLabel = cms.InputTag("centralityBins")
		)

process.cent120= process.centralityFilter.clone(
		selectedBins = cms.vint32(
			*range(120, 140)
			),
		BinLabel = cms.InputTag("centralityBins")
		)

process.acc60 = cms.Sequence( process.cent60 * process.QWAcc60 )
#process.acc60 = cms.Sequence( process.cent60 * process.QWAcc60 )
process.acc70 = cms.Sequence( process.cent70 * process.QWAcc70 )
process.acc80 = cms.Sequence( process.cent80 * process.QWAcc80 )
process.acc100 = cms.Sequence( process.cent100 * process.QWAcc100 )
process.acc120 = cms.Sequence( process.cent120 * process.QWAcc120 )


#process.ana = cms.Path(process.eventSelection*process.makeEvent*process.ppRecoCentFilter*process.cumugap * process.vectMonW )
process.ana60 = cms.Path(
		process.hfCoincFilter3 *
		process.centralityBins*
		process.makeGMOEvent *
		process.acc60
		)

process.ana70 = cms.Path(
		process.hfCoincFilter3 *
		process.centralityBins*
		process.makeGMOEvent *
		process.acc70
		)

process.ana80 = cms.Path(
		process.hfCoincFilter3 *
		process.centralityBins*
		process.makeGMOEvent *
		process.acc80
		)

process.ana100 = cms.Path(
		process.hfCoincFilter3 *
		process.centralityBins*
		process.makeGMOEvent *
		process.acc100
		)

process.ana120 = cms.Path(
		process.hfCoincFilter3 *
		process.centralityBins*
		process.makeGMOEvent *
		process.acc120
		)

process.schedule = cms.Schedule(
	process.ana60,
	process.ana70,
	process.ana80,
	process.ana100,
	process.ana120,
)
