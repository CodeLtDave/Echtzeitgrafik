#include "data.h"

static const std::filesystem::path SPHERE_PATH = root / "res" / "sphere.obj";

struct PlanetData {
    std::string name;
    float rotationSpeed; // in Minuten
    float orbitSpeed; // in km/s
    float distanceToSun; // in Millionen Kilometern
    float size; // Skalierungsfaktor für die Größe
};

const std::vector<PlanetData> planetData = {
    {"Sonne", 36000.0f, 0.0f, 0.0f, 1.0f},
    {"Merkur", 84456.0f, 47.87f, 2.9f, 2.383f},
    {"Venus", 349947.0f, 35.02f, 4.2f, 0.949f},
    {"Erde", 1436.0f, 29.78f, 6.6f, 1.0f},
    {"Mars", 1477.0f, 24.08f, 8.9f, 0.532f},
    {"Jupiter", 595.0f, 13.07f, 778.6f, 1.21f},
    {"Saturn", 647.0f, 9.69f, 1433.5f, 1.45f},
    {"Uranus", 1034.0f, 6.81f, 2872.5f, 1.01f},
    {"Neptun", 966.0f, 5.43f, 4495.1f, 1.88f}
};