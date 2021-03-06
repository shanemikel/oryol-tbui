//------------------------------------------------------------------------------
//  tbResourceContainer.cc
//------------------------------------------------------------------------------
#include "Pre.h"
#include "tbResourceContainer.h"

namespace Oryol {
namespace _priv {

//------------------------------------------------------------------------------
tbResourceContainer::tbResourceContainer() :
uniqueCounter(0) {
    // empty
}

//------------------------------------------------------------------------------
void
tbResourceContainer::setup(const TBUISetup& setup) {
    o_assert_dbg(!this->IsValid());
    this->resPool.Reserve(setup.ResourcePoolSize);
    this->resPool.SetAllocStrategy(0, 0);
    ResourceContainerBase::Setup(setup.ResourceLabelStackCapacity, setup.ResourceRegistryCapacity);
}

//------------------------------------------------------------------------------
void
tbResourceContainer::discard() {
    o_assert_dbg(this->IsValid());
    this->resPool.Clear();
    ResourceContainerBase::Discard();
}

//------------------------------------------------------------------------------
void
tbResourceContainer::add(const Locator& loc, Buffer&& data) {
    o_assert_dbg(this->IsValid());
    Id id = this->registry.Lookup(loc);
    if (id.IsValid()) {
        Log::Warn("TBUIResourceContainer::Add(): resource '%s' already exists!\n", loc.Location().AsCStr());
    }
    else {
        Id newId(this->uniqueCounter++, this->resPool.Size(), 0);
        this->registry.Add(loc, newId, this->PeekLabel());
        this->resPool.Add(std::move(data));
    }
}

//------------------------------------------------------------------------------
Buffer*
tbResourceContainer::lookupResource(const Locator& loc) {
    o_assert_dbg(this->IsValid());
    Id id = this->registry.Lookup(loc);
    if (id.IsValid()) {
        return &(resPool[id.SlotIndex]);
    }
    else {
        return nullptr;
    }
}

} // namespace _priv
} // namespace Oryol
