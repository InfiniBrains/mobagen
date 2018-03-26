//
//  Author: Shervin Aflatooni
//

#pragma once

#define GLM_SWIZZLE
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
  Transform(const glm::vec3& position = glm::vec3(), const glm::quat& rotation = glm::quat(), const glm::vec3& scale = glm::vec3(1.0f));
  ~Transform(void);

  void rotate(const glm::vec3& axis, float angle);
  void scale(float scale);
  void scale(const glm::vec3& scale);
  void translate(const glm::vec3& position);

  void setPosition(const glm::vec3& position);

  void setScale(const glm::vec3& scale);

  void setRotation(const glm::quat& rotation);
  void setRotation(const glm::vec3& axis, float w);

  glm::vec4 getPosition(void) const;
  glm::vec3 getScale(void) const;
  glm::quat getRotation(void) const;

  glm::mat4 getTransformMatrix(void) const;

  glm::vec4 getDirection(void) const;

  /// @brief The number of children the Transform has.
  int childCount();

//  eulerAngles	The rotation as Euler angles in degrees.
//  forward	The blue axis of the transform in world space.
//  hasChanged	Has the transform changed since the last time the flag was set to 'false'?
//  hierarchyCapacity	The transform capacity of the transform's hierarchy data structure.
//  hierarchyCount	The number of transforms in the transform's hierarchy data structure.
//  localEulerAngles	The rotation as Euler angles in degrees relative to the parent transform's rotation.
//  localPosition	Position of the transform relative to the parent transform.
//  localRotation	The rotation of the transform relative to the parent transform's rotation.
//  localScale	The scale of the transform relative to the parent.
//  localToWorldMatrix	Matrix that transforms a point from local space into world space (Read Only).
//  lossyScale	The global scale of the object (Read Only).
//  parent	The parent of the transform.
//  position	The position of the transform in world space.
//  right	The red axis of the transform in world space.
//  root	Returns the topmost transform in the hierarchy.
//  rotation	The rotation of the transform in world space stored as a Quaternion.
//  up	The green axis of the transform in world space.
//  worldToLocalMatrix	Matrix that transforms a point from world space into local space (Read Only).



//  DetachChildren	Unparents all children.
//  Find	Finds a child by n and returns it.
//  GetChild	Returns a transform child by index.
//  GetSiblingIndex	Gets the sibling index.
//  InverseTransformDirection	Transforms a direction from world space to local space. The opposite of Transform.TransformDirection.
//  InverseTransformPoint	Transforms position from world space to local space.
//  InverseTransformVector	Transforms a vector from world space to local space. The opposite of Transform.TransformVector.
//  IsChildOf	Is this transform a child of parent?
//  LookAt	Rotates the transform so the forward vector points at /target/'s current position.
//  Rotate	Applies a rotation of eulerAngles.z degrees around the z axis, eulerAngles.x degrees around the x axis, and eulerAngles.y degrees around the y axis (in that order).
//  RotateAround	Rotates the transform about axis passing through point in world coordinates by angle degrees.
//  SetAsFirstSibling	Move the transform to the start of the local transform list.
//  SetAsLastSibling	Move the transform to the end of the local transform list.
//  SetParent	Set the parent of the transform.
//  SetPositionAndRotation	Sets the world space position and rotation of the Transform component.
//  SetSiblingIndex	Sets the sibling index.
//  TransformDirection	Transforms direction from local space to world space.
//  TransformPoint	Transforms position from local space to world space.
//  TransformVector	Transforms vector from local space to world space.
//  Translate	Moves the transform in the direction and distance of translation.


  // private:
  glm::vec4 m_position;
  glm::quat m_rotation;
  glm::vec3 m_scale;
};
