#include "WorkloadProfile.h"

#include <cassert>
#include <stdexcept>

int main() {
    using namespace cc232::week14;
    auto profile = makeDictionaryWorkload(100);
    profile.validate();
    assert(profile.totalOperationRatio() <= 1.0);

    WorkloadProfile invalid;
    invalid.dataSize = 0;
    bool failed = false;
    try {
        invalid.validate();
    } catch (const std::invalid_argument&) {
        failed = true;
    }
    assert(failed);

    invalid.dataSize = 10;
    invalid.insertRatio = 0.7;
    invalid.searchRatio = 0.7;
    failed = false;
    try {
        invalid.validate();
    } catch (const std::invalid_argument&) {
        failed = true;
    }
    assert(failed);
    return 0;
}
