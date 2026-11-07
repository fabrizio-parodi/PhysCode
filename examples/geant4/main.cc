#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4VUserActionInitialization.hh"
#include "FTFP_BERT.hh"
#include "G4UImanager.hh"
#include <stdexcept>
#include <string>
#ifdef LAB_GUI
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#endif

class Detector final : public G4VUserDetectorConstruction {
 public:
  G4VPhysicalVolume* Construct() override {
    auto* nist = G4NistManager::Instance();
    auto* world = new G4LogicalVolume(new G4Box("World", 50*cm, 50*cm, 50*cm),
                                      nist->FindOrBuildMaterial("G4_AIR"), "World");
    auto* physical = new G4PVPlacement(nullptr, {}, world, "World", nullptr, false, 0);
    auto* block = new G4LogicalVolume(new G4Box("Block", 5*cm, 5*cm, 1*cm),
                                      nist->FindOrBuildMaterial("G4_W"), "Block");
    new G4PVPlacement(nullptr, {}, block, "Block", world, false, 0);
    return physical;
  }
};

class Generator final : public G4VUserPrimaryGeneratorAction {
  G4ParticleGun gun{1};
 public:
  Generator() {
    gun.SetParticleDefinition(G4ParticleTable::GetParticleTable()->FindParticle("e-"));
    gun.SetParticleEnergy(10*MeV);
    gun.SetParticlePosition({0, 0, -20*cm});
    gun.SetParticleMomentumDirection({0, 0, 1});
  }
  void GeneratePrimaries(G4Event* event) override { gun.GeneratePrimaryVertex(event); }
};

class Actions final : public G4VUserActionInitialization {
 public:
  void Build() const override { SetUserAction(new Generator); }
};

int main(int argc, char** argv) {
  auto* run = new G4RunManager;
  run->SetUserInitialization(new Detector);
  run->SetUserInitialization(new FTFP_BERT);
  run->SetUserInitialization(new Actions);
  run->Initialize();
  auto* ui = G4UImanager::GetUIpointer();
  const auto command = [ui](const char* text) {
    if (ui->ApplyCommand(text) != 0) throw std::runtime_error(text);
  };
#ifdef LAB_GUI
  if (argc > 1 && std::string(argv[1]) == "--gui") {
    // Explicitly request Qt, so macOS does not need XQuartz for this example.
    G4UIExecutive session(argc, argv, "Qt");
    auto* vis = new G4VisExecutive;
    vis->Initialize();
    command("/vis/open OGL");
    command("/vis/drawVolume");
    command("/vis/scene/add/trajectories smooth");
    command("/vis/scene/endOfEventAction accumulate");
    command("/run/beamOn 3");
    session.SessionStart();
    delete vis;
    delete run;
    return 0;
  }
#endif
  command("/run/verbose 1");
  command("/run/beamOn 3");
  delete run;
  return 0;
}
