from CRABAPI.RawCommand import crabCommand
from CRABClient.UserUtilities import config, getUsernameFromSiteDB
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

config = config()

config.General.requestName = 'AMPT1_V1_v1'
config.General.workArea = 'CrabArea'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'qwcumu_V1_ampt_v1.py'
#config.JobType.inputFiles = ['Hydjet_PbPb_eff_v1.root', 'PbPb15_ppReco_normAcc.root']
#config.JobType.maxJobRuntimeMin = 2500
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch1-ceca3f60d503999c0ee34e74626e4441/USER'
config.Data.inputDBS = 'phys03'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 200
config.Data.outLFNDirBase = '/store/group/phys_heavyions/qwang/PbPb2015_cumu/'
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


config.General.requestName = 'AMPT2_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch2-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)




config.General.requestName = 'AMPT3_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch3-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)



config.General.requestName = 'AMPT4_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch4-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)



config.General.requestName = 'AMPT5_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch5-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)


config.General.requestName = 'AMPT6_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch6-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)


config.General.requestName = 'AMPT7_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch7-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)



config.General.requestName = 'AMPT8_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch8-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)



config.General.requestName = 'AMPT9_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch9-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)



config.General.requestName = 'AMPT10_V1_v1'
config.Data.inputDataset = '/AMPT_PbPb5TeV_Gen/davidlw-mb_string_batch10-ceca3f60d503999c0ee34e74626e4441/USER'
try:
        crabCommand('submit', config = config)
except HTTPException as hte:
        print "Failed submitting task: %s" % (hte.headers)
except ClientException as cle:
        print "Failed submitting task: %s" % (cle)

