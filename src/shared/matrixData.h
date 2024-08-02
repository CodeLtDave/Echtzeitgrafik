#pragma once
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

static glm::vec3 viewPosVec = glm::vec3(0.0f, 10.0f, 10.0f);
static glm::mat4 viewMatrix = glm::lookAt(viewPosVec, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));
static glm::mat4 modelMatrix = glm::mat4(1.0f);
static glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), windowWidth / windowHeight, 0.1f, 100.0f);

static glm::vec3 emissionSunVec = glm::vec3(1.0f, 1.0f, 1.0f);
static glm::vec3 emissionPlanetVec = glm::vec3(0.0f, 0.0f, 0.0f);