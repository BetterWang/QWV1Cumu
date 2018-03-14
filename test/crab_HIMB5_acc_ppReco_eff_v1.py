from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

config = config()

config.General.requestName = 'HIMB5_acc_ppReco_eff_v2'
config.General.workArea = 'CrabArea'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'qwcumu_acc_PbPb15_ppReco_GMO_v1.py'
#config.JobType.inputFiles = ['Hydjet_PbPb_eff_v1.root']
config.JobType.maxJobRuntimeMin = 2500
config.Data.inputDataset = '/HIMinimumBias5/qwang-crab_HIMB5_ppReco_GMOVtxV0_Skim_v2-609c7cc39bfd4228bd9b8717a70a3c41/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/group/phys_heavyions/qwang/PbPb2015_cumu/'
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.publication = False
config.Data.useParent = True
config.Data.ignoreLocality = True
config.Site.whitelist = ['T2_US_Vanderbilt', 'T2_US_MIT']
config.Site.storageSite = 'T2_CH_CERN'
#config.Data.allowNonValidInputDataset = True
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)


## HIMB6
config.General.requestName = 'HIMB6_acc_ppReco_eff_v2'
config.Data.inputDataset = '/HIMinimumBias6/qwang-crab_HIMB6_ppReco_GMOVtxV0_Skim_v2-609c7cc39bfd4228bd9b8717a70a3c41/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)

## HIMB7
config.General.requestName = 'HIMB7_acc_ppReco_eff_v2'
config.Data.inputDataset = '/HIMinimumBias7/qwang-crab_HIMB7_ppReco_GMOVtxV0_Skim_v2-609c7cc39bfd4228bd9b8717a70a3c41/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)

