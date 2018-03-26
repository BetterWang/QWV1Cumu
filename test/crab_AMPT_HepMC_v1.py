from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

config = config()

config.General.requestName = 'AMPT1_HepMC_v1'
config.General.workArea = 'CrabArea'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'qwcumu_ampt_hepmc.py'
#config.JobType.inputFiles = ['Hydjet_PbPb_eff_v1.root', 'PbPb15_ppReco_normAcc.root']
#config.JobType.maxJobRuntimeMin = 2500
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch1-ceca3f60d503999c0ee34e74626e4441/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 20
config.Data.outLFNDirBase = '/store/group/phys_heavyions/qwang/AMPT/'
#config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions15/HI/Cert_262548-263757_PromptReco_HICollisions15_JSON_v2.txt'
config.Data.publication = False
#config.Data.useParent = True
#config.Data.ignoreLocality = True
#config.Site.whitelist = ['T2_US_Vanderbilt', 'T2_US_MIT']
config.Site.storageSite = 'T2_CH_CERN'
#config.Data.allowNonValidInputDataset = True
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)


