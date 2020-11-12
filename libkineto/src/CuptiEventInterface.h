/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 * All rights reserved.
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cupti.h>
#include <queue>
#include <string>

namespace KINETO_NAMESPACE {

// C++ interface to CUPTI Events C API.
// Virtual methods are here mainly to allow easier testing.
class CuptiEventInterface {
 public:
  explicit CuptiEventInterface(CUcontext context_);
  virtual ~CuptiEventInterface() {}

  CUdevice device() {
    return device_;
  }

  virtual CUpti_EventGroupSets* createGroupSets(
      std::vector<CUpti_EventID>& ids);
  virtual void destroyGroupSets(CUpti_EventGroupSets* sets);

  virtual void setContinuousMode();

  virtual void enablePerInstance(CUpti_EventGroup eventGroup);
  virtual uint32_t instanceCount(CUpti_EventGroup eventGroup);

  virtual void enableGroupSet(CUpti_EventGroupSet& set);
  virtual void disableGroupSet(CUpti_EventGroupSet& set);

  virtual void
  readEvent(CUpti_EventGroup g, CUpti_EventID id, std::vector<int64_t>& vals);
  virtual std::vector<CUpti_EventID> eventsInGroup(CUpti_EventGroup g);

  virtual CUpti_EventID eventId(const std::string& name);

 protected:
  // Unit testing
  CuptiEventInterface() : context_(nullptr), device_(0) {}

 private:
  CUcontext context_;
  CUdevice device_;
};

} // namespace KINETO_NAMESPACE