#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>


enum class CameraProjectionMode
{
	Perspective,
	Orthogonal
};

// �߽ɿ��� orientation�������� distance��ŭ ������ ��ġ����
// ���� ������ �׻� ���� z���� ������ ä ������ �ٶ󺸴� ī�޶�.
class Camera
{
public:
	Camera();
	~Camera();

public:
	void Zoom(float diff) { distance_ += diff; }
	void Rotate(float angle, const glm::vec3& v) { orientation_ = glm::rotate(orientation_, angle, v); }

	glm::mat4 GetViewMatrix() const;

public:
	CameraProjectionMode GetProjectionMode() { return projectionMode_; }
	void SetProjectionMode(const CameraProjectionMode& projection_mode) { projectionMode_ = projection_mode; }
	void SetFrustum(const glm::vec2& size, float near, float far);

	glm::mat4 GetProjectionMatrix() const;

private:
	// camera pos
	float distance_;
	glm::vec4 orientation_;

	// frustum
	glm::vec2 halfSize_;
	float near_, far_;
	CameraProjectionMode projectionMode_;
};