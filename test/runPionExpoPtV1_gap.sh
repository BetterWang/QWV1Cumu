#/bin/bash

echo $PWD
WORKDIR=$PWD
ls -l
cd /afs/cern.ch/user/q/qwang/work/cleanroomRun2/Ana/CMSSW_7_5_8_patch3/src/QWAna/QWV1Cumu/test
eval `scramv1 runtime -sh`
cp qwcumu_toyMC_V1_test.py $WORKDIR/cfg.py
cd $WORKDIR
cmsRun cfg.py
ls -l
NEW_UUID=$(openssl rand -base64 32 | tr -dc 'a-zA-Z0-9' | head -c 8)
cp ampt_gen.root /eos/cms/store/group/phys_heavyions/qwang/PbPb2015_cumu/MC/PionExpoPtV1V2_gap/ampt_gen_$NEW_UUID.root
echo done transfter
