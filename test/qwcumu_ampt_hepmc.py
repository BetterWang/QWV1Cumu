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
#process.MessageLogger.cerr.FwkReport.reportEvery = 100


l = open('ampt.flist').read().split()

flist = cms.untracked.vstring()

for item in l:
	flist.append(item)

#flist = cms.untracked.vstring("root://xrootd.unl.edu//store/user/davidlw/AMPT_PbPb5TeV_Gen/mb_string_batch1/160219_191452/0000/amptDefault_cfi_py_GEN_43.root")

process.source = cms.Source("PoolSource",
	fileNames = flist
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

process.QWGenTree = cms.EDAnalyzer('QWDTagTreeMaker',
	vTag = cms.untracked.VInputTag(
		cms.untracked.InputTag('QWHIEvent', 'Ncoll'),
		cms.untracked.InputTag('QWHIEvent', 'Npart'),
		cms.untracked.InputTag('QWHIEvent', 'b')
	)
)

process.RECO = cms.OutputModule("PoolOutputModule",
	outputCommands = cms.untracked.vstring('keep *'),
	SelectEvents = cms.untracked.PSet(
		SelectEvents = cms.vstring('ana')
		),
	fileName = cms.untracked.string('reco.root')
)

process.ana = cms.Path(
#	process.GeneInfo * 
	process.QWHIEvent * 
#	process.QWGenEvent *
	process.QWGenTree
)

#process.out = cms.EndPath(process.RECO)
