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
	, trackEta = cms.untracked.InputTag('QWGMOEvent', "eta")
	, trackPhi = cms.untracked.InputTag('QWGMOEvent', "phi")
	, trackPt = cms.untracked.InputTag('QWGMOEvent', "pt")
	, trackWeight = cms.untracked.InputTag('QWGMOEvent', "weight")
	, trackCharge = cms.untracked.InputTag('QWGMOEvent', "charge")
	, vertexZ = cms.untracked.InputTag('QWGMOEvent', "vz")
	, RP = cms.untracked.InputTag('FakeRP')
	, psiHFp = cms.untracked.InputTag('CaloQ', 'argp')
	, psiHFm = cms.untracked.InputTag('CaloQ', 'argm')
	, centrality = cms.untracked.InputTag('centralityBins')
	, minvz = cms.untracked.double(-15.0)
	, maxvz = cms.untracked.double(15.0)
	, rfpmineta = cms.untracked.double(-2.4)
	, rfpmaxeta = cms.untracked.double(2.4)
	, rfpminpt = cms.untracked.double(0.3)
	, rfpmaxpt = cms.untracked.double(3.0)
	, cmode = cms.untracked.int32(1)
	, nvtx = cms.untracked.int32(100)
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('cumu.root')
)


process.load('HeavyIonsAnalysis.Configuration.collisionEventSelection_cff')

#process.primaryVertexFilter.src = cms.InputTag("offlinePrimaryVertices")
process.primaryVertexFilter.src = cms.InputTag("GMOVertex")

process.load('RecoHI.HiCentralityAlgos.CentralityFilter_cfi')
process.ppRecoCentFilter = process.centralityFilter.clone(
	selectedBins = cms.vint32(
		*range(60, 140)
		),
	BinLabel = cms.InputTag("centralityBins")
	)

process.eventSelection = cms.Sequence(
        process.hfCoincFilter3
        + process.primaryVertexFilter
#        + process.clusterCompatibilityFilter
)

process.load('PbPb_HIMB5_ppReco_eff')
process.QWEvent.fweight = cms.untracked.InputTag('Hydjet_PbPb_eff_v1.root')


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
		srcW = cms.untracked.InputTag('QWPhiAcc')
		)

process.vectGMOEtaW = process.vectGMOEta.clone(
		srcW = cms.untracked.InputTag('QWPhiAcc')
		)

process.vectGMOPtW = process.vectGMOPt.clone(
		srcW = cms.untracked.InputTag('QWPhiAcc')
		)

process.vectGMOMonW = cms.Sequence( process.histGMONoff *
		process.histCentrality *
		process.vectGMOPhi *
		process.vectGMOEta *
		process.vectGMOPt *
		process.vectGMOPhiW *
		process.vectGMOEtaW *
		process.vectGMOPtW )

process.QWPhiAcc = cms.EDProducer('QWPhiWeightCent',
		src = cms.untracked.InputTag('PbPb15_ppReco_normAcc.root'),
		srcEta = cms.untracked.InputTag('QWGMOEvent', "eta"),
		srcPhi = cms.untracked.InputTag('QWGMOEvent', "phi"),
		srcPt = cms.untracked.InputTag('QWGMOEvent', "pt"),
		srcWeight = cms.untracked.InputTag('QWGMOEvent', "weight"),
		centrality = cms.untracked.InputTag('centralityBins')
		)

process.V1Cumu.trackWeight = cms.untracked.InputTag('QWPhiAcc')

#process.ana = cms.Path(process.eventSelection*process.makeEvent*process.ppRecoCentFilter*process.cumugap * process.vectMonW )
process.ana = cms.Path(
		process.hfCoincFilter3 *
		process.centralityBins*
		process.FakeRP *
		process.CaloQ *
		process.makeGMOEvent *
		process.ppRecoCentFilter *
		process.QWPhiAcc *
#		process.QWOfflineVtx *
#		process.QWGMOVtx *
		process.V1Cumu *
#		process.histVtxSize *
#		process.histGMOVtxSize *
#		process.monHFsumEtVsNoff *
#		process.monHFsumEtVsGMONoff *
#		process.monGMONoffVsNoff *
#		process.histGMONoff *
#		process.vectMonW *
		process.vectGMOMonW
		)

process.schedule = cms.Schedule(
	process.ana,
)
