#ifndef INFOS_H
#define INFOS_H

#include <QString>
//------------------------------------//
//-------Infos Class Declaration-------//
//------------------------------------//

class Infos
{
    private:
        QString Feature1, Feature2, Feature3, Feature4, Feature5;

    public:
        inline explicit Infos( QString info1 = "",
                               QString info2 = "",
                               QString info3 = "",
                               QString info4 = "",
                               QString info5 = "" ) noexcept;   // Constructor
        inline Infos(const Infos &other) noexcept;   // Copy Constructor
        inline ~Infos() noexcept;   // Destructor
        inline const QString &GetFeature1() const noexcept; // GeatFeature1
        inline const QString &GetFeature2() const noexcept; // GeatFeature2
        inline const QString &GetFeature3() const noexcept; // GeatFeature3
        inline const QString &GetFeature4() const noexcept; // GeatFeature4
        inline const QString &GetFeature5() const noexcept; // GeatFeature5
        inline void SetFeature1(const QString &newFeature1) noexcept; // SetFeature1
        inline void SetFeature2(const QString &newFeature2) noexcept; // SetFeature2
        inline void SetFeature3(const QString &newFeature3) noexcept; // SetFeature3
        inline void SetFeature4(const QString &newFeature4) noexcept; // SetFeature3
        inline void SetFeature5(const QString &newFeature5) noexcept; // SetFeature3
        inline const Infos &operator=(const Infos &op2) noexcept;   // operator =
};  // Infos Interface

#endif // INFOS_H
