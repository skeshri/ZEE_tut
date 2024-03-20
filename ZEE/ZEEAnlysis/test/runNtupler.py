import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("ZEEAnlysis")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.MessageLogger.cerr.FwkReport.reportEvery = 1

#
# Define input data to read
#
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )


process.source = cms.Source("PoolSource",
			    fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/mc/Run3Summer22MiniAODv3/DYJetsToLL_M-50_TuneCP5_13p6TeV-madgraphMLM-pythia8/MINIAODSIM/forPOG_124X_mcRun3_2022_realistic_v12-v4/70000/00162fe8-5a19-4c83-ac2a-a6d037507ecc.root',)
			   )

outputFile = "electron_ntuple.root"
#
# Configure the ntupler module
#
process.ZEEAnlysis = cms.EDAnalyzer('ZEEAnlysis',
                                 electron    = cms.InputTag("slimmedElectrons"),
                                 )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( outputFile )
                                   )

process.p = cms.Path(process.ZEEAnlysis)
