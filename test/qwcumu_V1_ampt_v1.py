import FWCore.ParameterSet.Config as cms

process = cms.Process("CumuV1")

process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
#process.load('Configuration.StandardSequences.GeometryDB_cff')
#process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
process.load('Configuration.StandardSequences.Generator_cff')

process.maxEvents = cms.untracked.PSet(input = cms.untracked.int32(-1))
process.MessageLogger.cerr.FwkReport.reportEvery = 100



process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring("file:/afs/cern.ch/work/q/qwang/public/amptDefault_cfi_py_GEN_1.root")
)

process.TFileService = cms.Service("TFileService",
	fileName = cms.string('ampt_gen.root')
)

process.QWHIEvent = cms.EDProducer("QWHepMCProducer",
	src = cms.untracked.InputTag("generator")
)

process.QWGenEvent = cms.EDProducer("QWGenEventProducer",
	trackSrc  = cms.untracked.InputTag("genParticles"),
	ptMin = cms.untracked.double(0.3),
	ptMax = cms.untracked.double(3.),
	isPrompt  = cms.untracked.bool(True)
)

process.AMPTCentrality = cms.EDProducer("QWPbPbAMPTB2CentProducer",
	src = cms.untracked.InputTag('QWHIEvent', 'b')
)

process.V1Cumu = cms.EDAnalyzer('QWV1Cumu'
	, trackEta = cms.untracked.InputTag('QWGenEvent', "eta")
	, trackPhi = cms.untracked.InputTag('QWGenEvent', "phi")
	, trackPt = cms.untracked.InputTag('QWGenEvent', "pt")
	, trackWeight = cms.untracked.InputTag('QWGenEvent', "weight")
	, trackCharge = cms.untracked.InputTag('QWGenEvent', "charge")
	, RP = cms.untracked.InputTag('QWHIEvent', "EP")
	, vertexZ = cms.untracked.InputTag('QWGenEvent', "vz")
	, centrality = cms.untracked.InputTag('AMPTCentrality', 'AMPT')
	, minvz = cms.untracked.double(-15.0)
	, maxvz = cms.untracked.double(15.0)
	, rfpmineta = cms.untracked.double(-2.4)
	, rfpmaxeta = cms.untracked.double(2.4)
	, rfpminpt = cms.untracked.double(0.3)
	, rfpmaxpt = cms.untracked.double(3.0)
	, cmode = cms.untracked.int32(1)
	, nvtx = cms.untracked.int32(100)
)

process.histNoff = cms.EDAnalyzer('QWHistAnalyzer',
		src = cms.untracked.InputTag("AMPTCentrality", "AMPT"),
		Nbins = cms.untracked.int32(200),
		start = cms.untracked.double(0),
		end = cms.untracked.double(200),
		)

process.histRP = cms.EDAnalyzer('QWHistDAnalyzer',
		src = cms.untracked.InputTag("QWHIEvent", "EP"),
		Nbins = cms.untracked.int32(1000),
		start = cms.untracked.double(0),
		end = cms.untracked.double(2*3.14159265358979323846),
		)

process.vectPhi = cms.EDAnalyzer('QWVectorAnalyzer',
		src = cms.untracked.InputTag("QWGenEvent", "phi"),
		hNbins = cms.untracked.int32(5000),
		hstart = cms.untracked.double(0),
		hend = cms.untracked.double(5000),
		cNbins = cms.untracked.int32(1000),
		cstart = cms.untracked.double(-3.14159265358979323846),
		cend = cms.untracked.double(3.14159265358979323846),
		)

process.vectPt = cms.EDAnalyzer('QWVectorAnalyzer',
		src = cms.untracked.InputTag("QWGenEvent", "pt"),
		hNbins = cms.untracked.int32(5000),
		hstart = cms.untracked.double(0),
		hend = cms.untracked.double(5000),
		cNbins = cms.untracked.int32(1000),
		cstart = cms.untracked.double(0),
		cend = cms.untracked.double(5),
		)

process.vectEta = cms.EDAnalyzer('QWVectorAnalyzer',
		src = cms.untracked.InputTag("QWGenEvent", "eta"),
		hNbins = cms.untracked.int32(5000),
		hstart = cms.untracked.double(0),
		hend = cms.untracked.double(5000),
		cNbins = cms.untracked.int32(48),
		cstart = cms.untracked.double(-2.4),
		cend = cms.untracked.double(2.4),
		)

process.RECO = cms.OutputModule("PoolOutputModule",
	outputCommands = cms.untracked.vstring('keep *'),
	SelectEvents = cms.untracked.PSet(
		SelectEvents = cms.vstring('ana')
		),
	fileName = cms.untracked.string('reco.root')
)

process.vectMon = cms.Sequence(process.histNoff*process.histRP*process.vectPhi*process.vectPt*process.vectEta)

process.ana = cms.Path(
		process.GeneInfo *
		process.QWHIEvent *
		process.AMPTCentrality *
		process.QWGenEvent *
		process.V1Cumu *
		process.vectMon
		)

#process.out = cms.EndPath(process.RECO)
