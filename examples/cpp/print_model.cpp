#include <xbot2_interface/xbotinterface2.h>
#include <fmt/format.h>
#include <cmrc/cmrc.hpp>

CMRC_DECLARE(example_resources);

int main(int argc, char **argv)
{
    auto urdf_file = cmrc::example_resources::get_filesystem().open("resources/mobile_manipulator_3dof.urdf");
    std::string urdf(urdf_file.begin(), urdf_file.end());

    auto model = XBot::ModelInterface::getModel(urdf, "pin");

    std::cout << "model name: " << model->getName() << "\n";
    std::cout << "model type: " << model->getType() << "\n";
    std::cout << "n_joints:   " << model->getJointNum() << "\n";
    std::cout << "n_q:        " << model->getNq() << "\n";
    std::cout << "n_v:        " << model->getNv() << "\n";

    std::cout << "\n";

    std::cout << "joints: \n";

    for(auto j : model->getJoints())
    {
        auto jinfo = j->getJointInfo();

        std::cout << " - "
                  << j->getName() << " iq = " << jinfo.iq << " iv = " << jinfo.iv
                  << " nq = " << jinfo.nq << " nv = " << jinfo.nv << "\n";
    }

    std::cout << "\n";

    std::cout << "model mass: " << model->getMass() << " kg\n\n";

    std::cout << "q_neutral: " << model->getNeutralQ().transpose().format(2) << "\n\n";

    std::cout << "q names: " << fmt::format("{} \n\n", fmt::join(model->getQNames(), ", "));

    std::cout << "v names: " << fmt::format("{} \n\n", fmt::join(model->getVNames(), ", "));

    auto qrand = model->generateRandomQ();
    std::cout << "q_random          : " << qrand.transpose().format(2) << "\n\n";

    std::cout << "q_random (minimal): " << model->positionToMinimal(qrand).transpose().format(2) << "\n\n";

}
