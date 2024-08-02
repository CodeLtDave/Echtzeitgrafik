#include "data.h"

static const std::filesystem::path SPHERE_PATH = root / "res" / "sphere.obj";

static struct PlanetData {
    std::string name;
    float rotationSpeed; // in Minuten
    float orbitSpeed; // in km/s
    float distanceToSun; // in Millionen Kilometern
    float size; // Skalierungsfaktor für die Größe
};

static const std::vector<PlanetData> planetData = {
    {"sun", 36000.0f, 0.0f, 0.0f, 3.0f},
    {"mercury", 1000.0f, 47.87f, 2.0f, 0.8f},
    {"venus", -349947.0f, 35.02f, 2.5, 1.2f},
    {"earth", 1436.0f, 29.78f, 3.5f, 1.2f},
    {"Mars", 1477.0f, 24.08f, 5.0f, 0.8f},
    {"jupiter", 595.0f, 13.07f, 6.5f, 2.0f},
    {"saturn", 647.0f, 9.69f, 8.f, 1.5f},
    {"uranus", -1034.0f, 6.81f, 10.f, 1.6f},
    {"neptune", 966.0f, 5.43f, 12.f, 0.58f}
};