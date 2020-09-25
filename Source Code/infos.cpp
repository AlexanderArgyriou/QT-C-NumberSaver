#include "infos.h"

//------------------------------------//
//------Infos Class Implementation-----//
//------------------------------------//

inline Infos::Infos( QString info1,
                     QString info2,
                     QString info3,
                     QString info4,
                     QString info5 ) noexcept
    : Feature1(info1), Feature2(info2), Feature3(info3),
    Feature4(info4), Feature5(info5)
{}  // Constructor

inline Infos::~Infos() noexcept
{
    Feature1 = Feature2 = Feature3 = Feature4 = Feature5 = "";
}   // Destructor

inline const QString &Infos::GetFeature1() const noexcept { return Feature1; }  // GeatFeature1
inline const QString &Infos::GetFeature2() const noexcept { return Feature2; }  // GeatFeature2
inline const QString &Infos::GetFeature3() const noexcept { return Feature3; }  // GeatFeature3
inline const QString &Infos::GetFeature4() const noexcept { return Feature4; }  // GeatFeature3
inline const QString &Infos::GetFeature5() const noexcept { return Feature5; }  // GeatFeature3
inline void Infos::SetFeature1(const QString &newFeature1) noexcept { Feature1 = newFeature1; } // SetFeature1
inline void Infos::SetFeature2(const QString &newFeature2) noexcept { Feature2 = newFeature2; } // SetFeature2
inline void Infos::SetFeature3(const QString &newFeature3) noexcept { Feature3 = newFeature3; } // SetFeature3
inline void Infos::SetFeature4(const QString &newFeature4) noexcept { Feature4 = newFeature4; } // SetFeature3
inline void Infos::SetFeature5(const QString &newFeature5) noexcept { Feature5 = newFeature5; } // SetFeature3

inline Infos::Infos(const Infos &other) noexcept
{
    if ( this != &other )
    {
        Feature1 = other.Feature1;
        Feature2 = other.Feature2;
        Feature3 = other.Feature3;
        Feature4 = other.Feature4;
        Feature5 = other.Feature5;
    }   // if
}   // Copy Constructor

inline const Infos &Infos::operator=(const Infos &op2) noexcept
{
    if ( this != &op2 )
    {
        Feature1 = op2.Feature1;
        Feature2 = op2.Feature2;
        Feature3 = op2.Feature3;
        Feature4 = op2.Feature4;
        Feature5 = op2.Feature5;
    }   // if

    return *this;
}   // operator =
