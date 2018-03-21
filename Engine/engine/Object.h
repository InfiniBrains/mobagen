//
// Created by Alexandre Tolstenko Nogueira on 3/20/18.
//

#include <string>
#include "HideFlags.h"
#include <vector>

class Object {
public:
  /// Should the object be hidden, saved with the scene or modifiable by the user?
  HideFlags hideFlags;

  /// The name of the object.
  std::string name;

  /// Returns the instance id of the object.
  int GetInstanceID();

  /// Removes a gameobject, component or asset.
  static void Destroy(std::shared_ptr<Object>);

  /// Destroys the object obj immediately. You are strongly recommended to use Destroy instead.
  static void DestroyImmediate(std::shared_ptr<Object>);

  /// Makes the object target not be destroyed automatically when loading a new scene.
  static void DontDestroyOnLoad(std::shared_ptr<Object>);

  /// Returns the first active loaded object of Type type.
  template <class T>
  static std::shared_ptr<T> FindObjectOfType(void);

  /// Returns a list of all active loaded objects of Type type.
  template <class T>
  static std::vector<std::shared_ptr<T>> FindObjectsOfType();

  /// Clones the object original and returns the clone.
  template <class T, class... _Types>
  static std::shared_ptr<T> Instantiate(_Types&&... _Args);

  /// Compares two object references to see if they refer to the same object.
  inline bool operator == (const Object & other);

  /// Compares if two objects refer to a different object.
  inline bool operator != (const Object & other);

private:
  int m_InstanceID;
};
