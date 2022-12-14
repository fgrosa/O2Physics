// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.
///
/// \brief task that checks the reconstructed and generated collisions in the MC
/// \author
/// \since

#include "Framework/runDataProcessing.h"
#include "Framework/AnalysisTask.h"

using namespace o2;
using namespace o2::framework;
using namespace o2::framework::expressions;

struct CheckCollisionsMc {

  HistogramRegistry registry{"registry", 
  {{"hRecoCollsOverGenColls", "Ratio between reconstructed and generated collisions", {HistType::kTH1F, {{200, 0., 2.}}}}}};

  void process(aod::Collisions const& recoCollisions,
               aod::McCollisions const& mcCollisions)
  {
    float effRecoColls = float(recoCollisions.size()) / mcCollisions.size();
    registry.fill(HIST("hRecoCollsOverGenColls"), effRecoColls);
  }
};

WorkflowSpec defineDataProcessing(ConfigContext const& cfgc)
{
  return WorkflowSpec{adaptAnalysisTask<CheckCollisionsMc>(cfgc)};
}
