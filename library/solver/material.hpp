// Nuclear Data
class Material{
public:
  double sigT;
  std::vector<double> sigS;
  double sigA;
  double nuSigF;

  Material(double sigT, std::vector<double> sigS, double nuSigF)
    : sigT(sigT), sigS(sigS), nuSigF(nuSigF)
  {
    sigA = sigT - sigS[0];
  }
};

