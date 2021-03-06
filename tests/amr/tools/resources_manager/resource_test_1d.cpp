
#include "resource_test_1d.h"


using VecField1D      = VecField<NdArrayVector1D<>, HybridQuantity>;
using IonPopulation1D = IonPopulation<ParticleArray<1>, VecField1D>;




struct IonPopulation1D_P
{
    std::string name = "protons";
    double mass      = 1.;
    IonPopulation1D user{name, mass};
};


struct VecField1D_P
{
    std::string name = "B";
    HybridQuantity::Vector qty{HybridQuantity::Vector::B};
    VecField1D user{name, qty};
};



using IonPop1DOnly          = std::tuple<IonPopulation1D_P>;
using VecField1DOnly        = std::tuple<VecField1D_P>;
using VecField1DAndIonPop1D = std::tuple<VecField1D_P, IonPopulation1D_P>;


TYPED_TEST_CASE_P(aResourceUserCollection);




TYPED_TEST_P(aResourceUserCollection, hasPointersValidOnlyWithGuard)
{
    TypeParam resourceUserCollection;

    auto check = [this](auto &resourceUserPack) {
        auto &hierarchy    = this->hierarchy->hierarchy;
        auto &resourceUser = resourceUserPack.user;

        for (int iLevel = 0; iLevel < hierarchy->getNumberOfLevels(); ++iLevel)
        {
            auto patchLevel = hierarchy->getPatchLevel(iLevel);
            for (auto const &patch : *patchLevel)
            {
                auto guard = this->resourcesManager.makeResourcesGuard(*patch, resourceUser);
                EXPECT_TRUE(resourceUser.isUsable());
            }
            EXPECT_FALSE(resourceUser.isUsable());
        }
    };

    std::apply(check, resourceUserCollection);
}



REGISTER_TYPED_TEST_CASE_P(aResourceUserCollection, hasPointersValidOnlyWithGuard);


typedef ::testing::Types<IonPop1DOnly, VecField1DOnly> MyTypes;
INSTANTIATE_TYPED_TEST_CASE_P(testResourcesManager, aResourceUserCollection, MyTypes);
