#include "camera.h"


Camera::Camera() :
	distance_(5.f),
	orientation_(0.f, -1.f, 0.f, 1.f)
{

}

Camera::~Camera()
{

}

glm::mat4 Camera::GetViewMatrix() const
{
	glm::vec3 eye(distance_ * orientation_);
	glm::vec3 center(0.f, 0.f, 0.f);
	glm::vec3 up(0.f, 0.f, 1.f);
	return glm::lookAt(eye, center, up);
}

void Camera::SetFrustum(const glm::vec2& size, float near, float far)
{
	halfSize_.x = size.x / 2.f;
	halfSize_.y = size.y / 2.f;

	near_ = near;
	far_ = far;
}

glm::mat4 Camera::GetProjectionMatrix() const
{
	if (projectionMode_ == CameraProjectionMode::Perspective)
	{
		return glm::frustum(
			-halfSize_.x, halfSize_.x,
			-halfSize_.y, halfSize_.y,
			near_, far_
		);
	}
	else if (projectionMode_ == CameraProjectionMode::Orthogonal)
	{
		return glm::ortho(
			-halfSize_.x, halfSize_.x,
			-halfSize_.y, halfSize_.y,
			near_, far_
		);
	}
}