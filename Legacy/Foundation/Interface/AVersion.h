#pragma once

#include "AGreekAlphabet.h"

#include <algorithm>

constexpr static size_t DevelopmentPhaseValue = 0;
constexpr static size_t MinTestingPhaseValue = DevelopmentPhaseValue + 1;
constexpr static size_t MaxTestingPhaseValue = DevelopmentPhaseValue + size_t(GreekAlphabet::Omega) + 2;
constexpr static size_t MinReleaseCondidatePhaseValue = MaxTestingPhaseValue + 1;
constexpr static size_t MaxReleaseCondidatePhaseValue = -2;
constexpr static size_t ReleasePhaseValue = -1;

class AVersion
{

public:

    enum PhaseType
    {
        Development,
        Testing,
        ReleaseCandidate,
        Release
    };

    size_t majorValue = 0;
    size_t minorValue = 0;
    size_t patchValue = 0;
    size_t phaseValue = 0;

    size_t buildNumber = 0;

    void upMajorValue()
    {
        ++buildNumber;
        ++majorValue;
        minorValue = 0;
        patchValue = 0;
        phaseValue = DevelopmentPhaseValue;
    }

    void upMinorValue()
    {
        ++buildNumber;
        ++minorValue;
        patchValue = 0;
        phaseValue = DevelopmentPhaseValue;
    }

    void upPatchValue()
    {
        ++buildNumber;
        ++patchValue;
        phaseValue = DevelopmentPhaseValue;
    }

    void upPhaseValue()
    {
        ++buildNumber;
        ++phaseValue;
    }

    void upBuildNumber()
    {
        ++buildNumber;
    }

    void upToNextPhase()
    {
        switch (phaseType()) {
        case Development:
            setTestingVersion();
            upBuildNumber();
            break;
        case Testing:
            setReleaseCandidateVersion();
            upBuildNumber();
            break;
        case ReleaseCandidate:
            setReleaseVersion();
            upBuildNumber();
            break;
        case Release:
            upPatchValue();
            break;
        default:
            setDevelopmentVersion();
            upBuildNumber();
            break;
        }
    }

    PhaseType phaseType() const
    {
        if(phaseValue == DevelopmentPhaseValue)
        {
            return Development;
        }
        else if(phaseValue == ReleasePhaseValue)
        {
            return Release;
        }
        else if(phaseValue < MinReleaseCondidatePhaseValue)
        {
            return Testing;
        }
        else
        {
            return ReleaseCandidate;
        }
    }

    bool isDevelopmentVersion() const
    {
        return phaseValue == DevelopmentPhaseValue;
    }

    void setDevelopmentVersion()
    {
        phaseValue = DevelopmentPhaseValue;
    }

    bool isTestingVersion() const
    {
        return DevelopmentPhaseValue < phaseValue && phaseValue < MinReleaseCondidatePhaseValue;
    }

    void setTestingVersion(size_t value = 0)
    {
        phaseValue = std::min<std::size_t>(std::max<std::size_t>(MinTestingPhaseValue + value, MinTestingPhaseValue), MaxTestingPhaseValue);
    }

    size_t getTestingNumber() const
    {
        return phaseValue - MinTestingPhaseValue;
    }

    bool isReleaseCandidateVersion() const
    {
        return MaxTestingPhaseValue < phaseValue && phaseValue < ReleasePhaseValue;
    }

    size_t getReleaseCanditateNumber() const
    {
        return phaseValue - MaxTestingPhaseValue;
    }

    void setReleaseCandidateVersion(size_t value = 0)
    {
        phaseValue = std::min<std::size_t>(std::max<std::size_t>(MinReleaseCondidatePhaseValue + value, MinReleaseCondidatePhaseValue), MaxReleaseCondidatePhaseValue);
    }

    bool isReleaseVersion() const
    {
        return phaseValue == ReleasePhaseValue;
    }

    void setReleaseVersion()
    {
        phaseValue = ReleasePhaseValue;
    }

    AVersion &operator ++()
    {
        ++buildNumber;
        return *this;
    }

    AVersion &operator --()
    {
        --buildNumber;
        return *this;
    }

    AVersion operator --(int)
    {
        AVersion version(*this);
        --buildNumber;
        return version;
    }

    AVersion operator ++(int)
    {
        AVersion version(*this);
        ++buildNumber;
        return version;
    }

    AVersion &operator -=(size_t value)
    {
        buildNumber -= value;
        return *this;
    }

    AVersion operator +=(size_t value)
    {
        buildNumber += value;
        return *this;
    }

    explicit operator String() const
    {
        return toString();
    }

    String toString() const
    {
        switch(phaseType())
        {
        case Development:
            return fmt::format("{}.{}.{}-Dev ({})", majorValue, minorValue, patchValue, buildNumber);
        case Testing:
            return fmt::format("{}.{}.{}-{} ({})", majorValue, minorValue, patchValue, GreekAlphabet::GreekLaterString[getTestingNumber()], buildNumber);
        case ReleaseCandidate:
            return fmt::format("{}.{}.{}-RC-{} ({})", majorValue, minorValue, patchValue, getReleaseCanditateNumber(), buildNumber);
        default:
            break;
        }
        return fmt::format("{}.{}.{} ({})", majorValue, minorValue, patchValue, buildNumber);
    }

};

inline bool operator >(const AVersion &lversion, const AVersion &rversion)
{
    return lversion.majorValue > rversion.majorValue ||
           (lversion.majorValue == rversion.majorValue && (lversion.minorValue > rversion.minorValue ||
           (lversion.minorValue == rversion.minorValue && (lversion.phaseValue > rversion.phaseValue ||
           (lversion.phaseValue == rversion.phaseValue && lversion.buildNumber > rversion.buildNumber)))));
}

inline bool operator <(const AVersion &lversion, const AVersion &rversion)
{
    return lversion.majorValue < rversion.majorValue ||
           (lversion.majorValue == rversion.majorValue && (lversion.minorValue < rversion.minorValue ||
           (lversion.minorValue == rversion.minorValue && (lversion.phaseValue < rversion.phaseValue ||
           (lversion.phaseValue == rversion.phaseValue && lversion.buildNumber < rversion.buildNumber)))));
}

inline bool operator <=(const AVersion &lversion, const AVersion &rversion)
{
    return rversion.majorValue > lversion.majorValue ||
           (rversion.majorValue == lversion.majorValue && (rversion.minorValue > lversion.minorValue ||
           (rversion.minorValue == lversion.minorValue && (rversion.phaseValue > lversion.phaseValue ||
           (rversion.phaseValue == lversion.phaseValue && rversion.buildNumber > lversion.buildNumber)))));
}

inline bool operator >=(const AVersion &lversion, const AVersion &rversion)
{
    return rversion.majorValue < lversion.majorValue ||
           (rversion.majorValue == lversion.majorValue && (rversion.minorValue < lversion.minorValue ||
           (rversion.minorValue == lversion.minorValue && (rversion.phaseValue < lversion.phaseValue ||
           (rversion.phaseValue == lversion.phaseValue && rversion.buildNumber < lversion.buildNumber)))));
}

inline bool operator ==(const AVersion &lversion, const AVersion &rversion)
{
    return lversion.majorValue == rversion.majorValue &&
           lversion.minorValue == rversion.minorValue &&
           lversion.phaseValue == rversion.phaseValue &&
           lversion.buildNumber == rversion.buildNumber;
}

inline bool operator !=(const AVersion &lversion, const AVersion &rversion)
{
    return lversion.majorValue != rversion.majorValue ||
           lversion.minorValue != rversion.minorValue ||
           lversion.phaseValue != rversion.phaseValue ||
           lversion.buildNumber != rversion.buildNumber;
}
